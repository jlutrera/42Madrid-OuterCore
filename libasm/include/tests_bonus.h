#ifndef TESTS_BONUS_H
# define TESTS_BONUS_H

/* Colores ANSI */
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

/* Libraries */
#include <stdio.h>
#include <string.h>
#include "libasm_bonus.h"
#include <stdlib.h>

/* Bonus tests */
void    test_atoi_base(void);
void    test_list_push_front(void);
void    test_list_size(void);
void    test_list_sort(void);
void    test_list_remove_if(void);

int     clean_buf(char *buf, ssize_t ret);
void    clear_lst(t_list **lst);
void    list_print(t_list *lst);
int     not_exit(void);
void    clear_screen(void);
#endif