#include "tests.h"

static long benchmark(char *(*fn)(char *, const char *), char *dst, const char *src)
{
    struct timespec t1, t2;
    const int iterations = 300000;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < iterations; i++)
        fn(dst, src);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    return ns_diff(t1, t2);
}

void test_strcpy(void)
{
    char buffer[2048];
    char dst1[2048];
    char dst2[2048];

    while (1)
    {
        printf("******************************************\n");
        printf("* TEST INTERACTIVO ft_strcpy + BENCHMARK *\n");
        printf("******************************************\n");
        printf("Introduce cadenas para copiar con strcpy() y ft_strcpy().\n");
        printf("Escribe \"exit\" para salir.\n\n");

        printf("--- Entrada ---\n");
        printf("  Input: ");
        fflush(stdout);

        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        if (clean_buf(buffer, strlen(buffer)))
            break;

        strcpy(dst1, buffer);
        ft_strcpy(dst2, buffer);

        printf("\n--- Resultados ---\n");
        printf("  strcpy:    \"%s\"\n", dst1);
        printf("  ft_strcpy: \"%s\"\n", dst2);

        /* --- Benchmark --- */
        long time_strcpy = benchmark(strcpy, dst1, buffer);
        long time_ft = benchmark(ft_strcpy, dst2, buffer);

        printf("\n--- Benchmark ---\n");
        printf("  strcpy:    %ld ns\n", time_strcpy);
        printf("  ft_strcpy: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_strcpy;
        printf("  Relación:  ft_strcpy es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
