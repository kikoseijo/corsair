/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:44:08 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/14 18:27:10 by jseijo-p         ###   ########.fr       */
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
#include <openssl/rsa.h>

int 	gcd(int a, int h);
int		ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);

int b64_decode(const char *in, unsigned char *out, size_t outlen);
char *b64_encode(const unsigned char *in, size_t len);

void rsa_from_prime(void);

void generate_key(void);

#endif
