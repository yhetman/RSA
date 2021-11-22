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

/*

	unsigned long int 	random_seed;
	mpz_t				p;
	mpz_t				q;
	mpz_t				n; // p * q
	mpz_t				phi_n;	// (p - 1) * (q - 1)
	mpz_t				e; // public key
	mpz_t				d; // private key
	mpz_t				one;
	mpz_t				message;
	mpz_t				plaintext;
	mpz_t				ciphertext;
	gmp_randstate_t		random;

*/

static inline void
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


void
generate_primes(t_rsa *rsa)
{
	bool	is_prime;

	is_prime = false;
	mpz_urandomb(rsa->p, rsa->randoms.random, PRIMELEN);
	is_prime = miller_rabin_test(rsa->p, rsa->randoms);
	if (is_prime)
		return;
}

int
main() //int argc, char const *argv[])
{
	t_rsa	rsa;

	init_rsa_struct(&rsa);
	generate_primes(&rsa);
	return 0;
}