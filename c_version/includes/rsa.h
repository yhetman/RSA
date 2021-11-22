/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   rsa.h                                                                    */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/22 17:02:54 by yhetman                                  */
/*   Updated: 2021/11/22 17:02:55 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <gmp.h>
// # include <gmpxx.h>
# include <time.h>

# define PRIMELEN		1024
# define CYCLES			64


typedef struct 				s_random_assets 
{
	unsigned long int 		random_seed;
	gmp_randstate_t			random;

}							t_random_assets;



typedef struct 				s_rsa
{
	// unsigned long int 	random_seed;
	struct s_random_assets 	randoms;
	mpz_t					p;
	mpz_t					q;
	mpz_t					n; // p * q
	mpz_t					phi_n;	// (p - 1) * (q - 1)
	mpz_t					e; // public key
	mpz_t					d; // private key
	mpz_t					one;
	mpz_t					message;
	mpz_t					plaintext;
	mpz_t					ciphertext;
	// gmp_randstate_t		random;
}							t_rsa;


void 						init_rsa_struct(t_rsa *rsa);

void 						generate_all_primes(t_rsa *rsa);

void						calculate_keys(t_rsa *rsa);

bool 						miller_rabin_test(mpz_t prime, gmp_randstate_t randoms);

void						generate_all_primes(t_rsa *rsa);


#endif
