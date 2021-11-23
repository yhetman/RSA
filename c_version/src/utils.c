/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   utils.c                                                                  */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/22 23:26:03 by yhetman                                  */
/*   Updated: 2021/11/22 23:26:04 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void
ft_otoi(unsigned char *enc_message, mpz_t encoded)
{
	int 	length,
			i;

	mpz_t 	base,
			val,
			mulval;


	length = strlen((char*)enc_message);
	mpz_init(base);
	mpz_set_ui(base, (unsigned int)256);


	for (i = 0; i < length; i++)
	{
		mpz_init(mulval);
		mpz_init(val);

		mpz_pow_ui(val, base, (unsigned long int)i);
		mpz_mul_ui(mulval, val, (unsigned long int)enc_message[i]);
		mpz_add(encoded, encoded, mulval);
	}

}


unsigned char *
ft_itooct(mpz_t 	decoded, int length)
{
	unsigned char	*out;
	mpz_t 			modval,
					remainder;
	int 			i;
	char			*block;


	printf("[LOG] ft_itooct : itooct sucks\n");

	mpz_init(modval);
	mpz_set_ui(modval, 256);

	out = (unsigned char *)malloc(sizeof(unsigned char) * 2 * length + 1);

	for (i = 0; i < 2 * length; i++)
	{
		mpz_init(remainder);

		printf("[LOG] ft_itooct : problem in mpz_powm_ui : %d\n", i);

		mpz_powm_ui(remainder, decoded, (unsigned int)1, modval);
		printf("[LOG] ft_itooct : remainder : %d\n", i);
		gmp_printf("Remainder : %Zd\n", remainder);

		block = mpz_get_str(NULL, 10, remainder);
		out[i] = atoi((char *)block);
		mpz_div_ui(decoded, decoded, (unsigned int)256);		
	}
	printf("[LOG] ft_itooct : not sucks\n");

	out[2 * length] = '\0';
	return out;
}