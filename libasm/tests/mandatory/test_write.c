#include "tests.h"

volatile ssize_t sink_write;   // evita optimización del compilador

static long benchmark(ssize_t (*fn)(int, const void *, size_t), const void *buf, size_t n)
{
    struct timespec t1, t2;
    const int iterations = 300000;

    int fd = open("/dev/null", O_WRONLY);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < iterations; i++)
        sink_write = fn(fd, buf, n);
    clock_gettime(CLOCK_MONOTONIC, &t2);
    close(fd);

    return ns_diff(t1, t2);
}

void test_write(void)
{
    char    buffer[2048];
    int     e1, e2;

    while (1)
    {
        printf("*****************************************\n");
        printf("* TEST INTERACTIVO ft_write + BENCHMARK *\n");
        printf("*****************************************\n");
        printf("Introduce texto para escribir con write() y ft_write().\n");
        printf("Escribe \"exit\" para salir.\n\n");

        printf("--- Entrada ---\n");
        printf("  Input: ");
        fflush(stdout);

        if (!fgets(buffer, sizeof(buffer), stdin))
            break;

        size_t len = strlen(buffer);
        if (clean_buf(buffer, len))
            break;

        printf("\n--- Escribiendo en STDOUT (fd = 1) ---\n");
        printf("  Outputs:\n");
        /* ft_write normal test  */
        errno = 0;
        write(1, "    ft_write → ", 17);
        ssize_t r1 = ft_write(1, buffer, len);
        e1 = errno;
        write(1, "\n", 1);

        /* write normal test */
        errno = 0;
        write(1, "    write    → ", 17); 
        ssize_t r2 = write(1, buffer, len);
        e2 = errno;
        write(1, "\n", 1);

        printf("  Resultados:\n");
        printf("    ft_write → ret = %zd, errno = %d (%s)\n", r1, e1, strerror(e1));
        printf("    write    → ret = %zd, errno = %d (%s)\n", r2, e2, strerror(e2));

        printf("\n--- Escribiendo en archivo inválido (fd = -1) ---\n");

        errno = 0;
        r1 = ft_write(-1, buffer, len);
        e1 = errno;
        printf("  ft_write → ret = %zd, errno = %d (%s)\n", r1, e1, strerror(e1));

        errno = 0;
        r2 = write(-1, buffer, len);
        e2 = errno;        
        printf("  write    → ret = %zd, errno = %d (%s)\n", r2, e2, strerror(e2));

        /* Benchmark */
        long time_write = benchmark(write, buffer, len);
        long time_ft = benchmark(ft_write, buffer, len);
        double ratio = (double)time_ft / (double)time_write;

        printf("\n--- Benchmark ---\n");
        printf("  write:    %ld ns\n", time_write);
        printf("  ft_write: %ld ns\n", time_ft);    
        printf("  Relación: ft_write es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}

