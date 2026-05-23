#include "tests_bonus.h"

void test_list_size(void)
{
    t_list *lst = NULL;
    char buf[256];
    int size;

    do
    {
        clear_screen();
        printf("*********************************\n");
        printf("* TEST INTERACTIVO ft_list_size *\n");
        printf("*********************************\n\n");
        printf("--- Creación de la lista ---\n");
        printf("Crea una lista introduciendo valores.\n");
        printf("Para finalizar la lista, introduce \"exit\".\n");
        while (1)
        {
            
            printf("  Valor: ");
            fflush(stdout);
            if (!fgets(buf, sizeof(buf), stdin))
                break;

            if (clean_buf(buf, strlen(buf)) == 1)
                break;

            ft_list_push_front(&lst, strdup(buf));
        }

        printf("  Lista : ");
        list_print(lst);

        printf("\n--- Respuesta ---\n");
        size = ft_list_size(lst);
        printf("  Tamaño de la lista: %d\n\n", size);
        clear_lst(&lst);
    } while (not_exit());
}
