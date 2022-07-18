/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:54:21 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/18 17:36:35 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"


void parser(int argc, char **argv, t_model *model)
{
	int i;

	i=1;
	while(i < argc)
	{
		if (strcmp(argv[i], "-in_cert"))
			model->in_cert_path = argv[i];
	}
}

void generate_keys(t_model *model)
{
		BIO				*bp_public = NULL, *bp_private = NULL;
		int				ret = 0;
		RSA *rsa = RSA_new();
    BIGNUM *n2 = BN_new();
    BN_dec2bn(&n2, model->prime_n);
    BIGNUM *e = BN_new();
    BN_dec2bn(&e, model->prime_e);
    BIGNUM *d = BN_new();
    BN_dec2bn(&e, model->prime_d);

    RSA_set0_key(rsa, n2, e, d);

    BIGNUM *test;
    // pkey = NULL;
    test = (BIGNUM *)RSA_get0_e(rsa);
    printf("\n\nEXPONENT:   %s\n", BN_bn2dec(test));


		// 2. save public key
		bp_public = BIO_new_file("res_public.pem", "w+");
		ret = PEM_write_bio_RSAPublicKey(bp_public, rsa);
		if(ret != 1){
			goto free_all;
		}

		// 3. save private key
		bp_private = BIO_new_file("res_private.pem", "w+");
		ret = PEM_write_bio_RSAPrivateKey(bp_private, rsa, NULL, NULL, 0, NULL, NULL);

		// 4. free
		free_all:

		BIO_free_all(bp_public);
		BIO_free_all(bp_private);
		RSA_free(rsa);
}

void generate_key()
{
	int				ret = 0;
	RSA				*r = NULL;
	BIGNUM			*bne = NULL;
	BIO				*bp_public = NULL, *bp_private = NULL;

	int				bits = 2048;
	unsigned long	e = RSA_F4;

	// 1. generate rsa key
	bne = BN_new();
	ret = BN_set_word(bne,e);
	if(ret != 1){
		goto free_all;
	}

	r = RSA_new();
	ret = RSA_generate_key_ex(r, bits, bne, NULL);
	if(ret != 1){
		goto free_all;
	}

	// 2. save public key
	bp_public = BIO_new_file("res_public.pem", "w+");
	ret = PEM_write_bio_RSAPublicKey(bp_public, r);
	if(ret != 1){
		goto free_all;
	}

	// 3. save private key
	bp_private = BIO_new_file("res_private.pem", "w+");
	ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

	// 4. free
	free_all:

	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(r);
	BN_free(bne);

	// return (ret == 1);
}

/*
** char *read_key(char *path)
** {
** 	char *res;
** 	char *line;
** 	int fd;
**
** 	fd = open(path, 'r');
** 	line = get_next_line(fd);
** 	while(line)
** 	{
** 		if(strcmp(line, "-----BEGIN PUBLIC KEY-----") != 0
** 			&& strcmp(line, "-----END PUBLIC KEY-----") != 0 )
** 				res = ft_strjoin(res, line);
** 		line = get_next_line(fd);
** 	}
** 	close(fd);
** 	return (res);
** }
*/

void openssl_modulus(char *pub_key, int mode)
{
	OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
 	if (mode == 1) {
		X509		  		*cert;
		BIO 					*i = BIO_new(BIO_s_file());
		BIO				 		*o = BIO_new_fp(stdout, BIO_NOCLOSE);
		BIO_read_filename(i, pub_key);  //read file
		if (! (cert = PEM_read_bio_X509(i, NULL, 0, NULL))) {  //load cert
			BIO_printf(o, "Error load certfile\n");
			return;
		}
		X509_print_ex(o, cert, XN_FLAG_COMPAT, X509_FLAG_COMPAT);  //print detail
		X509_free(cert);
		BIO_free_all(i);
		BIO_free_all(o);
 	} else if (mode == 2) {

	}
}

int main(int argc, char **argv) {
	// rsa_from_prime();
	t_model *model;

	model = (t_model*)malloc(sizeof(t_model));
	if(argc == 2)
		openssl_modulus(argv[1], 1);
	// print_modulus(argv[1], "openssl rsa -pubin -inform PEM -text -noout < ");
	else
		openssl_modulus("example.crt", 1);
		// print_modulus("key.pub", "openssl rsa -pubin -inform PEM -text -noout < ");
	model->prime_d = "13";
	model->prime_e = "7";
	model->prime_n = "65537";
	generate_keys(model);
	return (0);
}
