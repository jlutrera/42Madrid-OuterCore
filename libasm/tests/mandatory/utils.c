#include "tests.h"

long    ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

int clean_buf(char *buf, ssize_t ret)
{
    if (ret < 0)
        buf[0] = '\0';
    else
    {
        // Eliminar salto de línea si existe
        if (ret > 0 && buf[ret - 1] == '\n')
            buf[ret - 1] = '\0';
        else
            buf[ret] = '\0';
    }
    if (strcmp(buf, "exit") == 0)
        return 1;
    return 0;
}
