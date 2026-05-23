#include "tests_bonus.h"

void test_list_push_front(void)
{
    t_list *lst = NULL;
    char buf[256];

    clear_screen();
    printf("***************************************\n");
    printf("* TEST INTERACTIVO ft_list_push_front *\n");
    printf("***************************************\n\n");
    printf("Introduce valores para añadir a la lista.\n");
    printf("Escribe \"exit\" para salir.\n");

    while (1)
    { 
        printf("\n  Valor: ");
        fflush(stdout);

        if (!fgets(buf, sizeof(buf), stdin))
            break;

        if (clean_buf(buf, strlen(buf)) == 1)
            break;

        ft_list_push_front(&lst, strdup(buf));
        
        printf("  Lista actual: ");
        list_print(lst);
    }

    clear_lst(&lst);
}
