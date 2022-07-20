/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:54:21 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/20 10:22:21 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

RSA* key_from_bio(BIO *key_bio, int is_private) {

  EVP_PKEY *pkey = NULL;

  if(is_private)
    pkey = PEM_read_bio_PrivateKey(key_bio, NULL,NULL, NULL);
  else
    pkey = PEM_read_bio_PUBKEY(key_bio, NULL,   NULL, NULL);
  if(!pkey) {
      fprintf(stderr, "ERROR: key read from BIO is null\n");
      exit(1);
  }
  BIO_free(key_bio);
  RSA *rsa = EVP_PKEY_get1_RSA(pkey);
  EVP_PKEY_free(pkey);
  return rsa;
}

static void parser(int argc, char **argv, t_model *model)
{
	int i;

	i=1;
	while(i < argc)
	{
		// printf("%d:%s\n", i, argv[i]);
		if (strcmp(argv[i], "-incert") == 0)
			model->in_cert_path = argv[++i];
		if (strcmp(argv[i], "-p1") == 0)
			model->prime_e = argv[++i];
		if (strcmp(argv[i], "-p2") == 0)
			model->prime_d = argv[++i];
		i++;
	}
	// printf("in_cert_path:%s\n", model->in_cert_path);
	// printf("prime_e:%s\n", model->prime_e);
	// printf("prime_d:%s\n", model->prime_d);
}

static void free_rsa(BIO	*bp_public, BIO	*bp_private, RSA *rsa)
{
	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(rsa);
}

static void generate_keys(t_model *model)
{
		BIO				*bp_public = NULL, *bp_private = NULL;
		int				ret = 0;
		RSA *rsa = RSA_new();
    BIGNUM *exp = BN_new();
    BN_dec2bn(&exp, model->exponent);
    BIGNUM *e = BN_new();
    BN_dec2bn(&e, model->prime_e);
    BIGNUM *d = BN_new();
    BN_dec2bn(&d, model->prime_d);
    RSA_set0_key(rsa, e, exp, d);
    BIGNUM *test;
    test = (BIGNUM *)RSA_get0_e(rsa);
    printf("\n\nEXPONENT:   %s\n", BN_bn2dec(test));
		bp_public = BIO_new_file("res_public.pem", "w+");
		ret = PEM_write_bio_RSAPublicKey(bp_public, rsa);
		if(ret != 1){
			free_rsa(bp_public, bp_private, rsa);
			return;
		}
		bp_private = BIO_new_file("res_private.pem", "w+");
		ret = PEM_write_bio_RSAPrivateKey(bp_private, rsa, NULL, NULL, 0, NULL, NULL);
		free_rsa(bp_public, bp_private, rsa);
}

static void openssl_modulus(t_model *model)
{
	OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();

	EVP_PKEY			*pkey = NULL;
	RSA						*rsa;
	X509		  		*cert;
	const BIGNUM	*n;
	BIO 					*i = BIO_new(BIO_s_file());
	BIO				 		*o = BIO_new_fp(stdout, BIO_NOCLOSE);
	BIO_read_filename(i, model->in_cert_path);  //read file
	if (! (cert = PEM_read_bio_X509(i, NULL, 0, NULL))) {  //load cert
		BIO_printf(o, "Error load certfile\n");
		return;
	}
	if ((pkey = X509_get_pubkey(cert)) == NULL)
		BIO_printf(o, "Error getting public key from cert.");
	BIO_printf(o, "%d bit RSA Key\n", EVP_PKEY_bits(pkey));
	if (!PEM_write_bio_PUBKEY(o, pkey))
		BIO_printf(o, "Error writing public key data in PEM format");
	rsa = EVP_PKEY_get1_RSA(pkey);
	if (!rsa)
		BIO_printf(o, "Error getting rsa key from certificate");
	n = RSA_get0_n(rsa);
	printf("\nMODULUS: %s", BN_bn2dec(n));
	n = RSA_get0_e(rsa);
	printf("\nEXPONENT: %s\n", BN_bn2dec(n));
	EVP_PKEY_free(pkey);
	RSA_free(rsa);
	X509_free(cert);
	BIO_free_all(i);
	BIO_free_all(o);
}

/*
** Suppose we pick the primes p=3457631 and q=4563413.
** (In practice we might pick integers 100 or more digits each,
** 	numbers which are strong probable primes for several bases.)
** 	Suppose we also choose the exponent e=1231239
** 	and calculate d so e d \equic 1 (mod φ(n)).
*/

int main(int argc, char **argv) {
	// rsa_from_prime();
	t_model *model;

	model = (t_model*)malloc(sizeof(t_model));
	parser(argc, argv, model);
	if(model->in_cert_path)
		openssl_modulus(model);
	if(model->prime_e && model->prime_d)
	{
		model->exponent = "65537";
		generate_keys(model);
	}
	if(!model->in_cert_path && (!model->prime_e || !model->prime_d))
		printf("USAGE:\n ./corsair [-incert cert_path] [-p1 prime_e -p2 prime_d]\n");
	free(model);
	return (0);
}
