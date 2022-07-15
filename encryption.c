/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:24:43 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/14 18:27:00 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

void log_ssl_err(const char *mes)
{
    unsigned long err, found;
    char errstr[1000];

    found = 0;
    while ((err = ERR_get_error())) {
        ERR_error_string(err, errstr);
        printf("%s: %s", mes, errstr);
        found = 1;
    }
    if (!found) {
        printf("%s", mes);
    }
}

void generate_key(void)
{
	// Generating a key with a given exponent:

	RSA *rsa;
	BIGNUM *e;
	uint32_t exponent_bin, exponent_num;

	exponent_num = 65537;
	exponent_bin = htonl(exponent);
	e = BN_bin2bn((const unsigned char *)&exponent_bin, 4, NULL);
	if (e == NULL) {
	    log_ssl_err("BN_bin2bn failed for e");
	    exit(1);
	}

	if ((rsa = RSA_new()) == NULL) {
	    log_ssl_err("RSA_new failed");
	    BN_free(e);
	    exit(1);
	}
	if (!RSA_generate_key_ex(rsa, 2048, e, NULL)) {
	    log_ssl_err("couldn't generate rsa key");
	    BN_free(e);
	    exit(1);
	}

	// Encrypting and decrypting:

	unsigned char plaintext[] = "this is the plaintext";
	unsigned char *ciphertext, *decrypted;
	int cipher_len, decrypted_len;

	ciphertext = malloc(RSA_size(rsa));
	if ((cipher_len = RSA_public_encrypt(strlen(plaintext), plaintext, ciphertext,
	                                    rsa, RSA_PKCS1_OAEP_PADDING)) == -1) {
	    log_ssl_err("RSA_public_encrypt failed");
	    exit(1);
	}

	decrypted = malloc(RSA_size(rsa));
	if ((decrypted_len = RSA_private_decrypt(cipher_len, ciphertext, decrypted,
	                                         rsa, RSA_PKCS1_OAEP_PADDING)) == -1) {
	    log_ssl_err("RSA_private_decrypt failed");
	    return 0;
	}
}
