/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:54:21 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/18 09:04:37 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

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
	if(argc == 2)
		openssl_modulus(argv[1], 1);
	// print_modulus(argv[1], "openssl rsa -pubin -inform PEM -text -noout < ");
	else
		openssl_modulus("key.pem", 1);
		// print_modulus("key.pub", "openssl rsa -pubin -inform PEM -text -noout < ");
	return (0);
}
