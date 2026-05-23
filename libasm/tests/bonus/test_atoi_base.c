#include "tests_bonus.h"

void test_atoi_base(void)
{
    char str[256];
    char base[256];

    do
    {
        clear_screen();
        printf("*********************************\n");
        printf("* TEST INTERACTIVO ft_atoi_base *\n");
        printf("*********************************\n\n");
        printf("Introduce una cadena y una base para convertir.\n");
        printf("Escribe \"exit\" en cualquiera de los campos para salir.\n\n");

        printf("  Array: ");
        fflush(stdout);

        if (!fgets(str, sizeof(str), stdin))
            break;

        if (clean_buf(str, strlen(str)) == 1)
            break;

        printf("  Base:   ");
        fflush(stdout);

        if (!fgets(base, sizeof(base), stdin))
            break;

        if (clean_buf(base, strlen(base)) == 1)
            break;

        int a = ft_atoi_base(str, base);
        printf("  Resultado:  %d\n\n", a);
	} while (not_exit());
}
