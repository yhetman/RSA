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


void decrypt_ctr(t_rsa *rsa)
{
	mpz_t 	dp,
			dq,
			m1,
			m2,
			subd,
			qinv,
			h;

	mpz_init(h);
	mpz_init(m1);
	mpz_init(m2);
	mpz_init(dp);
	mpz_init(dq);
	mpz_init(subd);
	mpz_init(qinv);

	mpz_sub_ui(subd, rsa->p, 1UL);
	mpz_powm_ui(dp, rsa->d, 1UL, subd);

	mpz_sub_ui(subd, rsa->q, 1UL);
	mpz_powm_ui(dq, rsa->d, 1UL, subd);

	mpz_powm(m1, rsa->ciphertext, dp, rsa->p);
	mpz_powm(m2, rsa->ciphertext, dq, rsa->q);

	mpz_invert(qinv, rsa->q, rsa->p);

	mpz_sub(m1, m1, m2);
	mpz_mul(qinv, qinv, m1);
	mpz_powm_ui(h, qinv, 1UL, rsa->p);
	mpz_mul(h, h, rsa->q);
	mpz_add(rsa->plaintext, h, m2);

	mpz_clear(m1);
	mpz_clear(m2);
	mpz_clear(h);
	mpz_clear(qinv);
	mpz_clear(subd);
	mpz_clear(dq);
	mpz_clear(dp);
}


void decrypt(t_rsa *rsa)
{
	mpz_powm(rsa->plaintext, rsa->ciphertext, rsa->d, rsa->n); 
    return;
}


void encrypt(t_rsa *rsa)
{
	mpz_powm(rsa->ciphertext, rsa->message, rsa->e, rsa->n); 
    return;
}

int
main()
{
	t_rsa	rsa;
	// char	message[PRIMELEN];

	init_rsa_struct(&rsa);
	generate_all_primes(&rsa);
	calculate_keys(&rsa);


	// printf("Enter message to encrypt: ");
	// scanf("%1023s", message);
	
	// mpz_import(rsa.message, PRIMELEN, 1, sizeof(message[0]), 0, 0, message);
 //    encrypt(&rsa);
 //    printf("Encrypted is :\n%s\n", mpz_get_str(NULL, 16, rsa.ciphertext));
 //   	decrypt(&rsa);
 //    printf("Decrypted is :\n%s\n", mpz_get_str(NULL, 16, rsa.plaintext));

	rsa_oaep(&rsa);
	return 0;
}