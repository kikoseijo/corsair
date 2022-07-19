/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:44:08 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/18 17:48:26 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORSAIR_H
#define CORSAIR_H

#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/bioerr.h>
#include <openssl/crypto.h>
#include <openssl/cryptoerr.h>
#include <openssl/pem.h>
#include <openssl/pemerr.h>
#include <openssl/x509.h>
#include <openssl/x509err.h>

typedef struct s_model
{
	char *in_cert_path;
	char *exponent;
	char *prime_e;
	char *prime_d;

} t_model;

/*
** pub key
** MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCqGKukO1De7zhZj6+H0qtjTkVxwTCpvKe4eCZ0FPqri0cb2JZfXJ/DgYSF6vUpwmJG8wVQZKjeGcjDOL5UlsuusFncCzWBQ7RKNUSesmQRMSGkVb1/3j+skZ6UtW+5u09lHNsj6tQ51s1SPrCBkedbNf0Tp0GbMJDyR4e9T04ZZwIDAQAB
*/

/*
** Hex modulus
** 00AA18ABA43B50DEEF38598FAF87D2AB634E4571C130A9BCA7B878267414FAAB8B471BD8965F5C9FC3818485EAF529C26246F3055064A8DE19C8C338BE5496CBAEB059DC0B358143B44A35449EB264113121A455BD7FDE3FAC919E94B56FB9BB4F651CDB23EAD439D6CD523EB08191E75B35FD13A7419B3090F24787BD4F4E1967
*/

/*
** Decimal modulus
** 119445732379544598056145200053932732877863846799652384989588303737527328743970559883211146487286317168142202446955508902936035124709397221178664495721428029984726868375359168203283442617134197706515425366188396513684446494070223079865755643116690165578452542158755074958452695530623055205290232290667934914919
*/

// int 	gcd(int a, int h);
// int		ft_strlen(const char *s);
// char	*get_next_line(int fd);
// char	*ft_strjoin(char const *s1, char const *s2);
// int	ft_isprime(int nb)

// int b64_decode(const char *in, unsigned char *out, size_t outlen);
// char *b64_encode(const unsigned char *in, size_t len);
//
// unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);
//
// void rsa_from_prime(void);
//
// void generate_key(void);

#endif
