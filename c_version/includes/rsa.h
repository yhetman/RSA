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
# include "openssl/sha.h"
# include <time.h>
# include "sha256.h"

# define PRIMELEN		1024
# define MOD 			256

# define CYCLES			64
# define SHA256_HASH_SIZE 32

# define OAEPLEN 		MOD - SHA256_HASH_SIZE - 1

# define XOR(a, b)		(a^b)


# define ADD_MOVE(x, length, i){			\
		(x[length + 0] = (i >> 24) & 0xFF);	\
		(x[length + 1] = (i >> 16) & 0xFF);	\
		(x[length + 2] = (i >> 8) & 0xFF);	\
		(x[length + 3] =  i | 0x00);}


typedef struct 				s_random_assets 
{
	unsigned long int 		random_seed;
	gmp_randstate_t			random;

}							t_random_assets;



typedef struct 				s_rsa
{
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
}							t_rsa;


typedef struct 				s_oaep
{
	int 					mlength;
	int 					llength;
	t_bytes					hash;
	int 					counter;
}							t_oaep;




void						ft_otoi(unsigned char *enc_message, mpz_t encoded);

unsigned char * 			ft_itooct(mpz_t 	decoded, int length);

bool 						miller_rabin_test(mpz_t prime, gmp_randstate_t randoms);

void 						init_rsa_struct(t_rsa *rsa);

void 						generate_all_primes(t_rsa *rsa);

void						calculate_keys(t_rsa *rsa);



void						rsa_oaep();

unsigned char *				padding(unsigned char *frame, int messagelen, \
							uint8_t *hash, unsigned char *message);

unsigned char * 			mask_generation(int ceilv, int length, \
							unsigned char *in, unsigned char *out);

unsigned char *				forming_random_seed(unsigned char 	*seed);

void						mask_frame(unsigned char *masked_frame, \
							unsigned char *masked_seed, unsigned char *padded);


void						masking_oaep_scheme(unsigned char *enc_message, \
							char *message, char *mlabel, t_oaep *oaep);

void						encode_oaep(char *message, char *mlabel, t_rsa *rsa);


void						encrypting_rsa(t_rsa *rsa);


void						decrypting_rsa(t_rsa *rsa);

unsigned char *				decode_message(unsigned char *msg);

void						decode_oaep(t_rsa *rsa);

#endif
