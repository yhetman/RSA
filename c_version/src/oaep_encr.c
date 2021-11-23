/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   oaep_encr.c                                                              */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/23 00:47:02 by yhetman                                  */
/*   Updated: 2021/11/23 00:47:04 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


#include "rsa.h"

unsigned char *
forming_random_seed(unsigned char 	*seed)
{
	unsigned char 	*extended_seed,
					*out;
	int  			i,
					ceilv;

	srand(time(NULL));

	for(i = 0; i < SHA256_HASH_SIZE;i++)
		seed[i] = (char) rand() % 128;

	seed[SHA256_HASH_SIZE] = '\0';


	ceilv = ceil((double)OAEPLEN / 20) - 1;
	out = (unsigned char *)malloc(sizeof(unsigned char) * 20 *(ceilv + 1));
	extended_seed =	mask_generation(ceilv, SHA256_HASH_SIZE, seed, out);
	return extended_seed;
}


void
mask_frame(unsigned char *masked_frame, unsigned char *masked_seed,\
	 unsigned char *padded)
{
	int 				i,
						ceilv;
	unsigned char 		*extended_seed,
						*out,
						seed[OAEPLEN + 1];

	extended_seed = forming_random_seed(seed);

	for (i = 0; i < OAEPLEN; i++)
		masked_frame[i] = XOR(extended_seed[i], padded[i]);

	masked_frame[OAEPLEN] = '\0';
	free(extended_seed);
	
	ceilv = (int)ceil((double)SHA256_HASH_SIZE / 20) - 1;
	out = (unsigned char*)malloc(sizeof(unsigned char) * 20 *(ceilv + 1));
	
	extended_seed = mask_generation(ceilv, OAEPLEN, masked_frame, out);

	for (i = 0; i < SHA256_HASH_SIZE; i++)
		masked_seed[i] = XOR(extended_seed[i], seed[i]);

	masked_seed[i] = '\0';

	free(extended_seed);
}


void
masking_oaep_scheme(unsigned char *enc_message, char *message, \
	char *mlabel, t_oaep *oaep)
{
	FILE  			*hash256;
	unsigned char 	padded[OAEPLEN + 1],
					masked_frame[OAEPLEN + 1],
					masked_seed[SHA256_HASH_SIZE + 1];
	int  			i, 
					counter;


	oaep->mlength = strlen(message);
	oaep->llength = strlen(mlabel);
	
	if (oaep->mlength > (MOD - 2 - 2 * SHA256_HASH_SIZE))
		fprintf(stderr, "%s\n", "Message is too long, sorry :( ");

	calculate_sha256(mlabel, sizeof(mlabel), &oaep->hash);
	
	hash256 = fopen("./hash256", "w+");
	
	fwrite(oaep->hash.bytes, sizeof(unsigned char), SHA256_HASH_SIZE, hash256);
	
	fclose(hash256);
	
	padding(padded, oaep->mlength, oaep->hash.bytes, (unsigned char*)message);

	mask_frame(masked_frame, masked_seed, padded);

	enc_message[0] = '0';
	counter = 0;

	for (i = 0; i < SHA256_HASH_SIZE; i++)
		enc_message[++counter] = masked_seed[i];

	for (i = 0; i < OAEPLEN; i++)
		enc_message[++counter] = masked_frame[i];

	enc_message[MOD] = '\0';
}



void
encode_oaep(char *message, char *mlabel, t_rsa *rsa)
{
	t_oaep 			oaep;

	mpz_t 			encoded;
	unsigned char	enc_message[MOD + 1];
	FILE 			*efile;

	mpz_init(encoded);

	masking_oaep_scheme(enc_message, message, mlabel, &oaep);

	efile = fopen("./encoded", "w+");
	fwrite(enc_message, sizeof(unsigned char), strlen((char*)enc_message), efile);
	fclose(efile);
	ft_otoi(enc_message, encoded);
	mpz_set(rsa->message, encoded);
}


void
encrypting_rsa(t_rsa *rsa)
{
	mpz_powm(rsa->ciphertext, rsa->message, rsa->e, rsa->n);
	gmp_printf("Cipher text : %Zd\n", rsa->ciphertext);
}
