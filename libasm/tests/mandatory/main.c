#include "tests.h"

/* Limpiar pantalla */
static void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

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
        MENÚ MANDATORY
   =========================== */
int main(void)
{
    int opt;

    while (1)
    {
        clear_screen();
        printf(BLUE "=====================================\n" RESET);
        printf(BLUE "           MANDATORY TESTS           \n" RESET);
        printf(BLUE "=====================================\n\n" RESET);

        printf("  1. ft_strlen\n");
        printf("  2. ft_strcpy\n");
        printf("  3. ft_strcmp\n");
        printf("  4. ft_write\n");
        printf("  5. ft_read\n");
        printf("  6. ft_strdup\n\n");
        printf("  0. Exit\n\n");

        printf(GREEN "Select an option: " RESET);
        opt = read_option();

        clear_stdin();
        switch (opt)
        {
            case 1: test_strlen(); break;
            case 2: test_strcpy(); break;
            case 3: test_strcmp(); break;
            case 4: test_write(); break;
            case 5: test_read(); break;
            case 6: test_strdup(); break;
            case 0: return 0;
            default: continue;
        }
    }
}
