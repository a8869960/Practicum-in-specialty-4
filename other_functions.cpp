//
// Created by varsem on 21.11.23.
//
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "functions.h"

int toInt(const char* str, int* ptr)
{
    long L;
    char* e;

    errno = 0;
    L = strtol(str, &e, 10);

    if (!errno && *e == '\0')
        if (INT_MIN <= L && L <= INT_MAX)
        {
            *ptr = (int)L;
            return 0;
        }
        else
            return -1;
    else
        return -1;
}

int read_a(char *filename, double *a, int n)
{
    FILE *f;

    f = fopen(filename, "r");
    if(!f)
    {
        cout << "Can't open the file " << filename << endl;
        return -1;
    }

    for(int i = 0; i < n; i++)
    {
        if(fscanf(f, "%lf", &a[i]) != 1)
        {
            cout << "Can't read element " << i << endl;
            fclose(f);
            return -1;
        }
    }

    double current;
    if(fscanf(f, "%lf", &current) != EOF)
    {
        cout << "Wrong input data in " << filename << endl;
        fclose(f);
        return -1;
    }

    fclose(f);
    return 0;
}

double get_full_time()
{
    struct timeval buf;
    gettimeofday(&buf, NULL);
    return buf.tv_sec + buf.tv_usec / 1.e6;
}

double get_CPU_time()
{
    struct rusage buf;
    getrusage(RUSAGE_THREAD, &buf);
    return buf.ru_utime.tv_sec + buf.ru_utime.tv_usec / 1.e6;
}