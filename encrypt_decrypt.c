

/*
** https://shanetully.com/2012/04/simple-public-key-encryption-with-rsa-and-openssl/
*/

#include "corsair.h"

RSA *keypair = RSA_generate_key(2048, 3, NULL, NULL);

void encrypt(void)
{


	char *msg[2048/8]
	printf("Message to encrypt: ");
	fgets(msg, 2048/8, stdin);
	msg[strlen(msg)-1] = '\0';    // Get rid of the newline

	// Encrypt the message
	char *encrypt = malloc(RSA_size(keypair));
	int encrypt_len;
	err = malloc(130);
	if((encrypt_len = RSA_public_encrypt(strlen(msg)+1, (unsigned char*)msg,
	(unsigned char*)encrypt, keypair, RSA_PKCS1_OAEP_PADDING)) == -1) {
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), err);
		fprintf(stderr, "Error encrypting message: %s\n", err);
	}

}

void decrypt(void)
{
	char *decrypt = malloc(RSA_size(keypair));
	if(RSA_private_decrypt(encrypt_len, (unsigned char*)encrypt, (unsigned char*)decrypt,
	                       keypair, RSA_PKCS1_OAEP_PADDING) == -1) {
	   ERR_load_crypto_strings();
	   ERR_error_string(ERR_get_error(), err);
	   fprintf(stderr, "Error decrypting message: %s\n", err);
	} else {
	   printf("Decrypted message: %s\n", decrypt);
	}
}

void read_the_message(void)
{
	FILE *out = fopen("out.bin", "w");
	fwrite(encrypt, sizeof(*encrypt),  RSA_size(keypair), out);
	fclose(out);
	printf("Encrypted message written to file.\n");
	free(encrypt);
	encrypt = NULL;
}

void read_back(void)
{
	printf("Reading back encrypted message and attempting decryption...\n");
	encrypt = malloc(RSA_size(keypair));
	out = fopen("out.bin", "r");
	fread(encrypt, sizeof(*encrypt), RSA_size(keypair), out);
	fclose(out);
}

void private_pub_keys(void)
{
	RSA *keypair = RSA_generate_key(KEY_LENGTH, PUB_EXP, NULL, NULL);

	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSAPublicKey(pub, keypair);

	size_t pri_len = BIO_pending(pri);
	size_t pub_len = BIO_pending(pub);

	char *pri_key = malloc(pri_len + 1);
	char *pub_key = malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	printf("\n%s\n%s\n", pri_key, pub_key);
}
