/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   oaep_decr.c                                                              */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/23 00:46:55 by yhetman                                  */
/*   Updated: 2021/11/23 00:46:57 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */



#include "rsa.h"


void decrypting_rsa(t_rsa *rsa)
{
	mpz_powm(rsa->plaintext, rsa->ciphertext, rsa->d, rsa->n);
	gmp_printf("Decrypted text : %Zd\n", rsa->plaintext);
}



unsigned char	*
decode_message(unsigned char *msg)
{
	unsigned char	seed[SHA256_HASH_SIZE],
					frame[OAEPLEN],
					masked_seed[SHA256_HASH_SIZE],
					masked_frame[OAEPLEN],
					*extended,
					*out;
	int 			i,
					ceilv;


	for (i = 0; i < SHA256_HASH_SIZE; i++)
		masked_seed[i] = msg[i + 1];
	
	for (i = 0; i < OAEPLEN; i++)
		masked_frame[i] = msg[i + SHA256_HASH_SIZE + 1];


	printf("[LOG] decode_message : two loops after\n");

	ceilv = (int)ceil((double)SHA256_HASH_SIZE / 20) - 1;
	out = (unsigned char*)malloc(sizeof(unsigned char) * 20 *(ceilv + 1));
	extended =	mask_generation(ceilv, OAEPLEN, masked_frame, out);
	
	printf("[LOG] decode_message : first mask generated\n");
	for (i = 0; i < SHA256_HASH_SIZE; i++)
		seed[i] = XOR(extended[i], masked_seed[i]);
	
	free(extended);

	ceilv = ceil((double)OAEPLEN / 20) - 1;
	out = (unsigned char*)malloc(sizeof(unsigned char) * 20 *(ceilv + 1));
	extended =	mask_generation(ceilv, SHA256_HASH_SIZE, seed, out);
	printf("[LOG] decode_message : second mask generated\n");

	for (i = 0; i < OAEPLEN; i++)
		frame[i] = XOR(extended[i], masked_frame[i]);

	free(extended);

	extended = frame;

	printf("[LOG] decode_message : redirecting pointer\n");
	return extended;
}



void
decode_oaep(t_rsa *rsa)
{
	unsigned char	*decoded,
					*decoded_msg;
	FILE 			*defile;
	int 			ind,
					i;

	decoded = decode_message(ft_itooct(rsa->plaintext, MOD));


	for (i = SHA256_HASH_SIZE; i < OAEPLEN; i++)
	{
		if (decoded[i] == '0' || decoded[i] == '1')
			continue;
		ind = i;
		break;
		printf("[LOG] decode_oaep : loop :%d\n", i);
	}

	decoded_msg = (unsigned char *)malloc(sizeof(unsigned char) * (OAEPLEN - ind));

	for (i = ind; i < OAEPLEN; i++)
		decoded_msg[ind + 1] = decoded[i];
	
	decoded_msg[OAEPLEN - ind] = '\0';
	printf("[LOG] decode_oaep : two loops passed \n");

	defile = fopen("./decoded", "w+");
	fwrite(decoded_msg, sizeof(unsigned char), strlen((char*)decoded_msg), defile);
	fclose(defile);
	printf("[LOG] decode_oaep : decoded_msg was written to file\n");
}
