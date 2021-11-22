/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/22 17:02:38 by yhetman                                  */
/*   Updated: 2021/11/22 17:02:39 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"


unsigned char *
padding(int messagelen, uint8_t hash)
{
	int 			len,
					i,
					padding_length;

	unsigned char 	frame[OAEPLEN + 1];


	len = MOD - 2 - 2 * SHA256_HASH_SIZE;

	padding_length = len - messagelen;
	
	for(i = 0; i < SHA256_HASH_SIZE; i++)
		frame[i] = (unsigned char)hash[i];

	for (i = 0; i < padding_length; i++)
		frame[i + SHA256_HASH_SIZE] = '0';

	frame[SHA256_HASH_SIZE + padding_length] = '1';

	for (i = 0; i < messagelen; i++)
		frame[SHA256_HASH_SIZE + padding_length + i] = message[i];

	frame[OAEPLEN] = '\0';

	printf("%s\n", frame);
	return (frame);
}



unsigned char *
forming_random_seed()
{
	unsigned char 	seed[SHA256_HASH_SIZE + 1],
					*extended_seed;
	int  			i,
					ceil;

	srand(time(NULL));

	for(i = 0; i < SHA256_HASH_SIZE;i++)
		seed[i] = (char) rand() % 128;

	seed[SHA256_HASH_SIZE] = '\0';

	ceil = ceil((double)OAEPLEN / 20) - 1;
	
	extendedSeed = (unsigned char*)malloc(sizeof(unsigned char) * 20 *(ceil + 1));

	// mask_generation(ceil, SHA256_HASH_SIZE, seed, extendedSeed);
	return extendedSeed;
}


void
encode_oaep(char *message, char *mlabel)
{
	// mpz_t 		encoded;
	FILE  			*hash256;
	t_oaep 			oaep;
	unsigned char 	*padded;

	// len = MOD - 2 - 2 * SHA256_HASH_SIZE;
	oaep.mlength = strlen(message);
	oaep.llength = strlen(mlabel);
	
	if (oaep.mlength > (MOD - 2 - 2 * SHA256_HASH_SIZE))
		fprintf(stderr, "%s\n", "Message is too long, sorry :( ");

	calculate_sha256(mlabel, sizeof(mlabel), &oaep.hash);
	
	hash256 = fopen("./hash256", "w+");
	
	fwrite(oaep.hash.bytes, sizeof(unsigned char), SHA256_HASH_SIZE, hash256);
	
	fclose(hash256);
	
	padded = padding(oaep.mlength, oaep.hash.bytes);

	return;
}


int
main() //int argc, char const *argv[])
{
	t_rsa	rsa;
	char	message[PRIMELEN], 
			mlabel[PRIMELEN];

	init_rsa_struct(&rsa);
	generate_all_primes(&rsa);
	calculate_keys(&rsa);

	printf("Enter message to encrypt: ");
	scanf("%1023s", message);

	printf("Enter message's label to encrypt: ");
	scanf("%1023s", mlabel);

	encode_oaep(message, mlabel);


	return 0;
}