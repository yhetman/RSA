#* ************************************************************************** *#
#*                                                                            *#
#*                                                                            *#
#*   Makefile                                                                 *#
#*                                                                            *#
#*   By: yhetman <yhetman@student.unit.ua>                                    *#
#*                                                                            *#
#*   Created: 2021/11/22 17:02:24 by yhetman                                  *#
#*   Updated: 2021/11/22 17:02:25 by yhetman                                  *#
#*                                                                            *#
#* ************************************************************************** *#


SRCS =  miller_rabin_test.c rsa.c oaep.c utils.c oaep_decr.c oaep_encr.c

SRCS_DIR = src/

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIB_NAME = libRSA.a

RSA = rsa

FLAGS = -I includes -I ../../SHA256/includes/  -I /usr/include/openssl/ -Wall -Wextra -Werror

DEBUG_FLAGS = -g3 -fsanitize=address

RSA_MAIN = src/main.c 

all: make_obj_dir $(RSA)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c 
	gcc $(FLAGS) -c $< -o $@

$(LIB_NAME): $(OBJ)
	ar -rv $(LIB_NAME) $^
	ranlib $(LIB_NAME)

$(RSA): $(LIB_NAME) $(RSA_MAIN)
	gcc $(FLAGS) $(RSA_MAIN) $(LIB_NAME) libSHA256.a -o $(RSA) -lgmp -lssl -lcrypto

make_obj_dir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(RSA)
	rm -f $(LIB_NAME)

re: fclean all

.PHONY: all clean flcean re debug