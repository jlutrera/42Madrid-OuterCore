#include "tests.h"

volatile int sink_strcmp;   // evita optimización del compilador

static long benchmark(int (*fn)(const char *, const char *), const char *s1, const char *s2)
{
    struct timespec t1, t2;
    const int iterations = 300000;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < iterations; i++)
        sink_strcmp = fn(s1, s2);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    return ns_diff(t1, t2);
}

void test_strcmp(void)
{
    char s1[1024];
    char s2[1024];

    while (1)
    {
        printf("******************************************\n");
        printf("* TEST INTERACTIVO ft_strcmp + BENCHMARK *\n");
        printf("******************************************\n");
        printf("Introduce dos cadenas para comparar strcmp() y ft_strcmp().\n");
        printf("Escribe \"exit\" para salir.\n\n");

        printf("--- Entrada ---\n");
        printf("  Cadena 1: ");
        fflush(stdout);
        if (!fgets(s1, sizeof(s1), stdin))
            break;        
        if (clean_buf(s1, strlen(s1)))
            break;

        printf("  Cadena 2: ");
        fflush(stdout);
        if (!fgets(s2, sizeof(s2), stdin))
            break;
        if (clean_buf(s2, strlen(s2)))
            break;

        /* --- Comparación funcional --- */
        int c1 = strcmp(s1, s2);
        int c2 = ft_strcmp(s1, s2);

        printf("\n--- Resultados ---\n");
        printf("  strcmp:    %d\n", c1);
        printf("  ft_strcmp: %d\n", c2);

        /* --- Benchmark --- */
        long time_str = benchmark(strcmp, s1, s2);
        long time_ft = benchmark(ft_strcmp, s1, s2);

        printf("\n--- Benchmark ---\n");
        printf("  strcmp:    %ld ns\n", time_str);
        printf("  ft_strcmp: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_str;
        printf("  Relación:  ft_strcmp es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
