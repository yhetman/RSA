/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   rsa.c                                                                    */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/22 17:02:44 by yhetman                                  */
/*   Updated: 2021/11/22 17:02:45 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


#include "rsa.h"


void
init_rsa_struct(t_rsa *rsa)
{
	rsa->randoms.random_seed = 1;
	gmp_randinit_default(rsa->randoms.random);
	gmp_randseed_ui(rsa->randoms.random, rsa->randoms.random_seed);
	mpz_init(rsa->p);
	mpz_init(rsa->q);
	mpz_init(rsa->n);
	mpz_init(rsa->phi_n);
	mpz_init(rsa->e);
	mpz_init(rsa->d);
	mpz_init(rsa->one);
	mpz_init(rsa->message);
	mpz_init(rsa->plaintext);
	mpz_init(rsa->ciphertext);
	mpz_set_str(rsa->one, "1", 10);
}


inline static void
generate_prime(mpz_t prime, gmp_randstate_t state)
{
	mpz_urandomb(prime, state, PRIMELEN);
	while(!(miller_rabin_test(prime, state)))
		mpz_nextprime(prime, prime);
}



void
generate_all_primes(t_rsa *rsa)
{
	mpz_t 	tp,
			tq;
	
	generate_prime(rsa->p, rsa->randoms.random);
	generate_prime(rsa->q, rsa->randoms.random);

	mpz_mul(rsa->n, rsa->p, rsa->q);
	mpz_init(tp);
	mpz_init(tq);

	mpz_sub(tp,rsa->p, rsa->one);
	mpz_sub(tq,rsa->q, rsa->one);

	mpz_mul(rsa->phi_n,tp,tq);
	gmp_printf("Generated value for p : %Zd\n", rsa->p);
	printf("\n");
	gmp_printf("Generated value for q : %Zd\n", rsa->q);
	printf("\n");
	gmp_printf("RSA modulus n value : %Zd\n", rsa->n);
	printf("\n");
	gmp_printf("RSA phi(n) value : %Zd\n", rsa->phi_n);
	printf("\n");

}



void
calculate_keys(t_rsa *rsa)
{
	mpz_t 	gcd,
		 	common_prime;

	mpz_init(gcd);
	mpz_init(common_prime);
	mpz_urandomb(common_prime, rsa->randoms.random, PRIMELEN);
	while (true)
	{
		mpz_gcd(gcd, rsa->phi_n, common_prime);
		if (mpz_cmp_ui(gcd, (unsigned long int)1) == 0)
			break;
		mpz_nextprime(common_prime, common_prime);
	}
	
	mpz_set(rsa->e, common_prime);
	mpz_invert(rsa->d, rsa->e, rsa->phi_n);

	gmp_printf("Calculated value for public key: %Zd\n", rsa->e);
	printf("\n");
	gmp_printf("Calculated value for private key: %Zd\n", rsa->d);
	printf("\n");
}

