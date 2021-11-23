/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   oaep.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/22 23:18:49 by yhetman                                  */
/*   Updated: 2021/11/22 23:18:51 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"



unsigned char *
padding(unsigned char *frame, int messagelen, uint8_t *hash, unsigned char *message)
{
	int 			len,
					i,
					padding_length;



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
	return frame;
}



unsigned char *
mask_generation(int ceilv, int length, unsigned char *in, unsigned char *out)
{
	int 			i,
					j;
	unsigned char	*buff,
					temp[length + 5];

	for (i = 0; i <= ceilv; i++)
	{
		buff = (unsigned char *)malloc(20 + 1);
		
		
		for (j = 0; j < length; j++)
			temp[j] = in[j];


		ADD_MOVE(temp, length, i);

		temp[length + 4] = '\0';

		SHA1((unsigned char *)temp,strlen((char*)temp),(unsigned char *)buff);
		
		for (j = 0; j < 20; j++)
			out[i * 20 + j] = buff[j];

		free (buff);
	}
	return (out);
}





void
rsa_oaep(t_rsa *rsa)
{

	char	message[PRIMELEN],
			mlabel[PRIMELEN];
	
	printf("Enter message to encrypt: ");
	scanf("%1023s", message);

	printf("Enter message's label to encrypt: ");
	scanf("%1023s", mlabel);

	encode_oaep(message, mlabel, rsa);

	encrypting_rsa(rsa);

	decrypting_rsa(rsa);

	decode_oaep(rsa);
}