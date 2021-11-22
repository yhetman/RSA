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


// void
// encode_oaep(t_rsa *rsa, char *message, char *mlabel)
// {
// 	return;
// }


int
main() //int argc, char const *argv[])
{
	t_rsa	rsa;
	char	message[PRIMELEN], 
			mlabel[PRIMELEN];

	init_rsa_struct(&rsa);
	generate_all_primes(&rsa);
	calculate_keys(&rsa);

	printf("Enter message to encrypt: ");
	scanf("%1023s", message);

	printf("Enter message's label to encrypt: ");
	scanf("%1023s", mlabel);

	// encode_oaep(&rsa, message, mlabel);


	return 0;
}