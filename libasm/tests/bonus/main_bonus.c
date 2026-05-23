#include <stdio.h>
#include <stdlib.h>
#include "tests_bonus.h"

void clear_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* Leer opción de menú, borrando buffer si hay más de un carácter*/
static int read_option(void)
{
    int opt;

    if (scanf("%d", &opt) != 1)
    {
        clear_stdin();
        return -1;  // entrada inválida
    }
    return opt;
}

/* ===========================
           MENÚ BONUS
   =========================== */
int main(void)
{
    int opt;

    while (1)
    {
        clear_screen();
        printf(BLUE "=====================================\n" RESET);
        printf(BLUE "              BONUS TESTS            \n" RESET);
        printf(BLUE "=====================================\n\n" RESET);

        printf("  1. ft_atoi_base\n");
        printf("  2. ft_list_push_front\n");
        printf("  3. ft_list_size\n");
        printf("  4. ft_list_sort\n");
        printf("  5. ft_list_remove_if\n\n");
        printf("  0. Exit\n\n");

        printf(GREEN "Select an option: " RESET);
        opt = read_option();

        clear_stdin();
        switch (opt)
        {
            case 1: test_atoi_base(); break;
            case 2: test_list_push_front(); break;
            case 3: test_list_size(); break;
            case 4: test_list_sort(); break;
            case 5: test_list_remove_if(); break;
            case 0: return 0;
            default: continue;
        }
    }
}
