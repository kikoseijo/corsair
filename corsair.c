/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:54:21 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/14 19:02:33 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

char *read_key(char *path)
{
	char *res;
	char *line;
	int fd;

	fd = open(path, 'r');
	line = get_next_line(fd);
	while(line)
	{
		if(strcmp(line, "-----BEGIN PUBLIC KEY-----") != 0
			&& strcmp(line, "-----END PUBLIC KEY-----") != 0 )
				res = ft_strjoin(res, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (res);
}

void print_modulus(char *key_path, char* pre_cmd) {
	char *cmd;

	printf("%s\n", key_path);
	cmd = ft_strjoin(pre_cmd, key_path);
	// cmd = ft_strjoin(cmd, " -modulus -exponent");
	printf("%s\n", cmd);
	system(cmd);
}

void openssl_modulus(char *pub_key)
{
	int res;
	unsigned char *hex;
	int len;
	long long decimal = 0, base = 1;
	int i = 0;

	len = ft_strlen(pub_key);
	hex = (unsigned char*)malloc(2048 * sizeof(unsigned char));
	res = b64_decode(pub_key, hex, len);


	for(i = 0; i < 163 - 1; i++)
	{
		printf("%d - %X\n", i, hex[i]);
	}

	for(i = 162; i >= 28; i--)
	{
		if(hex[i] >= '0' && hex[i] <= '9')
		{
			decimal += (hex[i] - '0') * base;
			base *= 16;
		}
		else if(hex[i] >= 'A' && hex[i] <= 'F')
		{
			decimal += (hex[i] - 'A' + 10) * base;
			base *= 16;
		}
		else if(hex[i] >= 'a' && hex[i] <= 'f')
		{
			decimal += (hex[i] - 'a' + 10) * base;
			base *= 16;
		}
	}

	printf("\nHexadecimal number = %s", hex);
	printf("Decimal number = %lld\n", decimal);
	// printf("key:%s\nres:%s\nd:%d\n", pub_key, res_out, res);
}

int main(int argc, char **argv) {
	// rsa_from_prime();
	if(argc == 2)
		print_modulus(argv[1], "openssl rsa -pubin -inform PEM -text -noout < ");
	else
		openssl_modulus(read_key("key.pub"));
		// print_modulus("key.pub", "openssl rsa -pubin -inform PEM -text -noout < ");
	return (0);
}
