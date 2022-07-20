/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:54:21 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/20 12:18:27 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

static void parser(int argc, char **argv, t_model *model)
{
	int i;

	i=1;
	while(i < argc)
	{
		if (strcmp(argv[i], "-incert") == 0)
			model->in_cert_path = argv[++i];
		if (strcmp(argv[i], "-p1") == 0)
			model->prime_e = argv[++i];
		if (strcmp(argv[i], "-p2") == 0)
			model->prime_d = argv[++i];
		i++;
	}
}

static void free_rsa(BIO	*bp_public, BIO	*bp_private, RSA *rsa)
{
	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(rsa);
}

static void	ft_write_privkey_pkey(t_model *model)
{
	RSA		*rsa;
	BIO		*outbio = NULL;
	int		ret;
	BN_CTX	*ctx;
	BIGNUM	*uno = BN_new();
	BIGNUM	*e = BN_new();
	BIGNUM	*p = BN_new();
	BIGNUM	*q = BN_new();
	BIGNUM	*d;
	BIGNUM	*tmp_p;
	BIGNUM	*tmp_q;
	BIGNUM	*tmp_m1;
	BIGNUM	*tmp_m2;
	BIGNUM	*m;
	BIGNUM	*n2;
	BIGNUM	*dmp1;
	BIGNUM	*dmq1;
	BIGNUM	*iqmp;

	ctx = BN_CTX_new();
	rsa = RSA_new();
	outbio  = BIO_new_fp(stdout, BIO_NOCLOSE);

	BN_dec2bn(&uno, "1");
	BN_dec2bn(&e, "65537");
	BN_dec2bn(&p, model->prime_e);
	BN_dec2bn(&q, model->prime_d);

	BN_CTX_start(ctx);
	n2 = BN_CTX_get(ctx);
	BN_mul(n2, p, q, ctx);
	tmp_m1 = BN_CTX_get(ctx);
	BN_add(tmp_m1, p, q);
	tmp_m2 = BN_CTX_get(ctx);
	BN_sub(tmp_m2, tmp_m1, uno);
	m = BN_CTX_get(ctx);
	BN_sub(m, n2, tmp_m2);
	d = BN_CTX_get(ctx);
	BN_mod_inverse(d, e, m, ctx);
	dmp1 = BN_CTX_get(ctx);
	tmp_p = BN_CTX_get(ctx);
	BN_sub(tmp_p, p, uno);
	BN_mod(dmp1, d, tmp_p, ctx);
	dmq1 = BN_CTX_get(ctx);
	tmp_q = BN_CTX_get(ctx);
	BN_sub(tmp_q, q, uno);
	BN_mod(dmq1, d, tmp_q, ctx);
	iqmp = BN_CTX_get(ctx);
	BN_mod_inverse(iqmp, q, p, ctx);


	RSA_set0_key(rsa, n2, e, d);
	RSA_set0_factors(rsa, p, q);
	RSA_set0_crt_params(rsa, dmp1, dmq1, iqmp);

	printf("\n\n");

	RSA_print(outbio, rsa, 0);
	ret = PEM_write_bio_RSAPublicKey(outbio, rsa);
	if(ret != 1)
	{
		BIO_printf(outbio, "Error writing public key data in PEM format");
		return;
	}

	printf("\n\n");


	ret = PEM_write_bio_RSAPrivateKey(outbio, rsa, 0, 0, 0, 0, 0);
	if(ret != 1)
	{
		BIO_printf(outbio, "Error writing private key data in PEM format");
		return;
	}

	BIO_free_all(outbio);
	RSA_free(rsa);
}

static void write_rsa_keys(RSA *rsa)
{
	int				ret = 0;
	BIO				*bp_public = NULL;
	BIO				*bp_private = NULL;
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

static void test_rsa(RSA *rsa)
{
	BIGNUM *test;
	test = (BIGNUM *)RSA_get0_e(rsa);
	printf("\nEXPONENT: %s\n", BN_bn2dec(test));
	test = (BIGNUM *)RSA_get0_n(rsa);
	printf("\nMODULUS: %s\n", BN_bn2dec(test));
}

static void generate_keys(t_model *model)
{
		RSA 			*rsa = RSA_new();
    BIGNUM 		*exp = BN_new();
		BIGNUM 		*e = BN_new();
		BIGNUM 		*d = BN_new();
		BIGNUM 		*p = BN_new();
		BIGNUM 		*q = BN_new();
		BIGNUM 		*one = BN_new();
		BN_CTX		*ctx = BN_CTX_new();

    BN_dec2bn(&one, "1");
    BN_dec2bn(&exp, "65537");
    BN_dec2bn(&p, model->prime_e);
    BN_dec2bn(&q, model->prime_d);

		BN_CTX_start(ctx);
		BIGNUM *n2 = BN_CTX_get(ctx);
		d = BN_CTX_get(ctx);
		BIGNUM *m = BN_CTX_get(ctx);
		BN_mod_inverse(d, e, m, ctx);

    RSA_set0_key(rsa, n2, exp, d);

		test_rsa(rsa);
		write_rsa_keys(rsa);
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
	if(1==2)
		ft_write_privkey_pkey(model);
	if(model->prime_e && model->prime_d)
		generate_keys(model);
	if(!model->in_cert_path && (!model->prime_e || !model->prime_d))
		printf("USAGE:\n ./corsair [-incert cert_path] [-p1 prime_e -p2 prime_d]\n");
	free(model);
	return (0);
}
