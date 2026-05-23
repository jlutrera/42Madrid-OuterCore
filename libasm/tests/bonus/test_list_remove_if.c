#include "tests_bonus.h"

void test_list_remove_if(void)
{
    t_list *lst = NULL;
    char buf[256];

    do
    {
        clear_screen();
        printf("**************************************\n");
        printf("* TEST INTERACTIVO ft_list_remove_if *\n");
        printf("**************************************\n\n"); 
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

        printf("  Lista inicial: ");
        list_print(lst);

        printf("\n--- Eliminación de elementos ---\n");
        printf("Introduce valores a eliminar de la lista.\n");
        printf("Escribe \"exit\" para terminar de eliminar.\n");
        while (1)
        {
            printf("\n  Valor a eliminar: ");
            fflush(stdout);

            if (!fgets(buf, sizeof(buf), stdin))
                break;
            
            if (clean_buf(buf, strlen(buf)) == 1)
                break;

            ft_list_remove_if(&lst, buf, strcmp, free);

            printf("  Lista actual: ");
            list_print(lst);
        }
        clear_lst(&lst);
    } while (not_exit());
}
