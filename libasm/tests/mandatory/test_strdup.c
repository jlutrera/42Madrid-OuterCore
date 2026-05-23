#include "tests.h"

volatile char *sink_strdup;   // evita optimización del compilador

static long benchmark(char *(*fn)(const char *), const char *s)
{
    struct timespec t1, t2;
    const int iterations = 300000;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < iterations; i++)
    {
        sink_strdup = fn(s);
        free((void *)sink_strdup);
    }
    clock_gettime(CLOCK_MONOTONIC, &t2);

    return ns_diff(t1, t2);
}

void test_strdup(void)
{
    char buffer[2048];

    while (1)
    {
        printf("******************************************\n");
        printf("* TEST INTERACTIVO ft_strdup + BENCHMARK *\n");
        printf("******************************************\n");
        printf("Introduce cadenas para duplicar con strdup() y ft_strdup().\n");
        printf("Escribe \"exit\" para salir.\n\n");

        printf("--- Entrada ---\n");
        printf("  Input: ");
        fflush(stdout);

        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        if (clean_buf(buffer, strlen(buffer)))
            break;

        /* --- Comparación funcional --- */
        char *a = strdup(buffer);
        char *b = ft_strdup(buffer);

        printf("\n--- Resultados ---\n");
        printf("  strdup:    \"%s\"\n", a);
        printf("  ft_strdup: \"%s\"\n", b);

        /* --- Benchmark --- */
        long time_std = benchmark(strdup, buffer);
        long time_ft = benchmark(ft_strdup, buffer);

        printf("\n--- Benchmark ---\n");
        printf("  strdup:    %ld ns\n", time_std);
        printf("  ft_strdup: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_std;
        printf("  Relación:  ft_strdup es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");

        free(a);
        free(b);
    }
}
