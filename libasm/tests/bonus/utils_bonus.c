#include "tests_bonus.h"

int clean_buf(char *buf, ssize_t ret)
{
    if (ret < 0)
        buf[0] = '\0';
    else
    {
        if (ret > 0 && buf[ret - 1] == '\n')
            buf[ret - 1] = '\0';
        else
            buf[ret] = '\0';
    }
    if (strcmp(buf, "exit") == 0)
        return 1;
    return 0;
}

void clear_lst(t_list **lst)
{
    t_list *cur = *lst;
    while (cur)
    {
        t_list *next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
    }
    *lst = NULL;
}

void list_print(t_list *lst)
{
    t_list *p = lst;
    while (p)
    {
        printf("%s", (char *)p->data);
        if(p->next)
            printf(" -> ");
        p = p->next;
    }

    printf("\n");
}

int not_exit(void)
{
    char buf[256];
    printf("¿Quieres realizar otra prueba? (Y/n): ");
    fflush(stdout);
    if (!fgets(buf, sizeof(buf), stdin))
        return 1;

    if (buf[0] == 'n' || buf[0] == 'N')
        return 0;

    return 1;
}

void clear_screen(void)
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
