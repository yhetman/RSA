/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   miller_rabin_test.c                                                      */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/22 17:20:49 by yhetman                                  */
/*   Updated: 2021/11/22 17:20:51 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


# include "rsa.h"

bool
miller_rabin_test(mpz_t prime)
{
	unsigned int 	a;
	size_t 			i;
	mpz_t 			temp,
					store;


	a = 0;
	mpz_init(temp);
	mpz_init(store);


	if (mpz_even_p(prime) == 1)
		return true;

	mpz_sub_ui(temp, prime, (unsigned int)1);
	mpz_set(store,temp);

	while (true)
	{
		if (mpz_even_p(temp) == 0)
			break;
		a++;
		mpz_cdiv_q_ui(temp, temp, (unsigned int)2);
	}

	for (i = 0; i < CYCLES; i++)
		if (miller_check(temp, store, prime, a) == false)
			return false;
	return true;

}