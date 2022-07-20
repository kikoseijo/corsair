/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:44:08 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/20 12:07:21 by jseijo-p         ###   ########.fr       */
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
	char *prime_e;
	char *prime_d;

} t_model;

#endif
