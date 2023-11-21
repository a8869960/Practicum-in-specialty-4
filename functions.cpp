//
// Created by varsem on 20.11.23.
//
#include "functions.h"

void *process_main(void *arg_)
{
    ARGS *arg = (ARGS*)arg_;
    int m = arg->m, p = arg->p, n = arg->n;
    double *a = arg->a, *a_help = arg->a_help;
    double product, cpu_time = get_CPU_time(), full_time = get_full_time();

    for(int i = m; i < n; i += p)
    {
        if(i == 0 or i == n - 1)
            continue;

        product = a[i - 1] * a[i + 1];
        if(product < 0)
        {
            a_help[i] = -1;
            continue;
        }
        else
            a_help[i] = sqrt(product);
    }
    reduce_sum(p);

    for(int i = m; i < n; i += p)
    {
        if(i == 0 or i == n - 1 or abs(a_help[i] + 1) < 1e-16)
            continue;

        a[i] = a_help[i];
    }

    arg->cpu_time = get_CPU_time() - cpu_time;
    arg->full_time = get_full_time() - full_time;

    return 0;
}

void reduce_sum(int p, double* a, int n)
{
    static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
    static int t_in = 0;
    static int t_out = 0;
    static double *r = nullptr;
    int i;

    if(p <= 1)
        return;
    pthread_mutex_lock(&m);

    if(r == nullptr)
        r = a;
    else
        for(i = 0; i < n; i++) r[i] += a[i];

    t_in++;
    if(t_in >= p)
    {
        t_out = 0;
        pthread_cond_broadcast(&c_in);
    }
    else
        while(t_in < p)
            pthread_cond_wait(&c_in, &m);

    if(r != a)
        for(i = 0; i < n; i++) a[i] = r[i];

    t_out++;
    if(t_out >= p)
    {
        t_in = 0;
        r = nullptr;
        pthread_cond_broadcast(&c_out);
    }
    else
        while(t_out < p)
            pthread_cond_wait(&c_out, &m);

    pthread_mutex_unlock(&m);
}