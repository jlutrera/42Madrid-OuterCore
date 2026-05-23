#include "tests.h"

volatile ssize_t sink_read;

static long benchmark(ssize_t (*fn)(int, void *, size_t), void *buf, size_t n)
{
    struct timespec t1, t2;
    const int iterations = 300000;
    int fd = open("/dev/zero", O_RDONLY);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < iterations; i++)
        sink_read = fn(fd, buf, n);
    clock_gettime(CLOCK_MONOTONIC, &t2);
    close(fd);

    return ns_diff(t1, t2);
}

void test_read(void)
{
    char buf1[1024];
    char buf2[1024];

    while (1)
    {
        printf("****************************************\n");
        printf("* TEST INTERACTIVO ft_read + BENCHMARK *\n");
        printf("****************************************\n");
        printf("Escribe texto para leer con ft_read() y read().\n");
        printf("Escribe \"exit\" para salir.\n\n");

        /* Input con ft_read() */
        printf("\n--- Leyendo de STDIN (fd = 0) ---\n");
        printf("  Inputs: \n");
 
        printf("    ft_read : ");
        fflush(stdout);
        errno = 0;
        ssize_t ret1 = ft_read(0, buf1, sizeof(buf1) - 1);
        int e1 = errno;

        if (clean_buf(buf1, ret1))
            break;
        
        /* Input con read() */
        printf("    read    : ");
        fflush(stdout);
        errno = 0;
        ssize_t ret2 = read(0, buf2, sizeof(buf2) - 1);
        int e2 = errno;

        if (clean_buf(buf2, ret2))
            break;
        
        printf("  Resultados:\n");
        printf("    ft_read → ret = %zd,  errno = %d (%s),  buffer = \"%s\"\n",
               ret1, e1, strerror(e1), buf1);
        printf("    read    → ret = %zd,  errno = %d (%s),  buffer = \"%s\"\n",
               ret2, e2, strerror(e2), buf2);

        /* Test de error */
        printf("\n--- Leyendo de archivo inválido (fd = -1) ---\n");

        errno = 0;
        ret1 = ft_read(-1, buf1, 10);
        e1 = errno;

        errno = 0;
        ret2 = read(-1, buf2, 10);
        e2 = errno;
        printf("  Resultados:\n");
        printf("    ft_read → ret = %zd, errno = %d (%s)\n", 
            ret1, e1, strerror(e1));
        printf("    read    → ret = %zd, errno = %d (%s)\n", 
            ret2, e2, strerror(e2));

        /* --- Benchmark --- */
        char bench_buf[1024];
        long time_read = benchmark(read, bench_buf, sizeof(bench_buf));
        long time_ft = benchmark(ft_read, bench_buf, sizeof(bench_buf));
        double ratio = (double)time_ft / (double)time_read;

        printf("\n--- Benchmark ---\n");
        printf("  read:    %ld ns\n", time_read);
        printf("  ft_read: %ld ns\n", time_ft);
        printf("  Relación: ft_read es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
