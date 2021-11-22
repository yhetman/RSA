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


#include "rsa.h"


static bool
miller_check(mpz_t temp, mpz_t store, mpz_t prime, unsigned int num, gmp_randstate_t random)
{
	mpz_t 	a,
			x;
	size_t 	j;


	mpz_init(a);
	mpz_init(x);

	mpz_urandomm(a, random, store);
	mpz_powm(x, a, temp, prime);

	if (mpz_cmp_ui(prime, (unsigned int )1) == 0 ||
		 mpz_cmp(prime, store) == 0)
		return true;
	
	for (j = 0; j < num - 1; j++)
	{
		mpz_powm_ui(x, x, (unsigned long int)2, prime);
		if (mpz_cmp_ui(x, (unsigned int)1) == 0)
			return false;
		if (mpz_cmp(x, store) == 0)
			return true;
	}
	return false;
}

bool
miller_rabin_test(mpz_t prime, gmp_randstate_t randoms)
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
	mpz_set(store, temp);

	while (true)
	{
		if (mpz_even_p(temp) == 0)
			break;
		a++;
		mpz_cdiv_q_ui(temp, temp, (unsigned int)2);
	}

	for (i = 0; i < CYCLES; i++)
		if (miller_check(temp, store, prime, a, randoms) == false)
			return false;
	return true;

}