#include "tests_bonus.h"

static t_list *ft_create_elem(void *data)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node)
        return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

static void ft_push_element(t_list **begin_list, void *data)
{
    t_list *node = ft_create_elem(data);
    if (!node)
        return;
    node->next = *begin_list;
    *begin_list = node;
}

void test_list_sort(void)
{
    t_list *lst = NULL;

    do
    {
        clear_screen();
        printf("*********************************\n");
        printf("* TEST INTERACTIVO ft_list_sort *\n");
        printf("*********************************\n\n");
        printf("--- Creación de la lista ---\n");
        printf("Crea una lista introduciendo valores.\n");
        printf("Para finalizar la lista, introduce \"exit\".\n");
        while (1)
        {
            char buf[256];
            printf("  Valor: ");
            fflush(stdout);
            if (!fgets(buf, sizeof(buf), stdin))
                break;

            if (clean_buf(buf, strlen(buf)) == 1)
                break;

            ft_push_element(&lst, strdup(buf));
        }

        printf("  Lista inicial: ");
        list_print(lst);

        printf("\n--- Ordenamiento de la lista ---\n");
        ft_list_sort(&lst, strcmp);
        printf("  Lista ordenada: ");
        list_print(lst);
        clear_lst(&lst);
    } while (not_exit());
}

