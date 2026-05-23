#include "tests.h"

volatile size_t sink_strlen;

static long benchmark(size_t (*fn)(const char *), const char *s)
{
    struct timespec t1, t2;
    const int iterations = 3000000;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < iterations; i++)
        sink_strlen = fn(s);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    return ns_diff(t1, t2);
}

void test_strlen(void)
{
    char buffer[2048];

    while (1)
    {
        printf("******************************************\n");
        printf("* TEST INTERACTIVO ft_strlen + BENCHMARK *\n");
        printf("******************************************\n");
        printf("Introduce cadenas para comparar strlen() y ft_strlen().\n");
        printf("Escribe \"exit\" para salir.\n\n");

        printf("--- Entrada ---\n");
        printf("  Input: ");
        fflush(stdout);

        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        if (clean_buf(buffer, strlen(buffer)))
            break;

        size_t a = strlen(buffer);
        size_t b = ft_strlen(buffer);
        printf("\n--- Resultados ---\n");
        printf("  strlen:    %zu\n", a);
        printf("  ft_strlen: %zu\n", b);
    
        /* --- Benchmark --- */
        long time_str = benchmark(strlen, buffer);
        long time_ft = benchmark(ft_strlen, buffer);

        printf("\n--- Benchmark ---\n");
        printf("  strlen:    %ld ns\n", time_str);
        printf("  ft_strlen: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_str;
        printf("  Relación:  ft_strlen es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
