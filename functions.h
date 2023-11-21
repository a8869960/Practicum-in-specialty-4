//
// Created by varsem on 20.11.23.
//
#ifndef INC_4_FUNCTIONS_H
#define INC_4_FUNCTIONS_H

#include <iostream>
#include <cmath>

#include <cstdio>
#include <cstdlib>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

enum class io_status
{
    success,
    error_open,
    error_read,
    none
};

class ARGS
{
public:
    double *a = nullptr;
    double *a_help = nullptr;
    int n = 0;
    int m = 0;
    int p = 0;

    double cpu_time = 0;
    double full_time = 0;

    io_status status = io_status::none;

    ~ARGS()
    {
        delete[] a_help;
    }
};

//other_functions.cpp
int toInt(const char* str, int* ptr);
int read_a(char *filename, double *a, int n);

double get_full_time();
double get_CPU_time();

//functions.cpp
void *process_main(void *arg_);
void reduce_sum(int p, double* a = nullptr, int n = 0);

#endif //INC_4_FUNCTIONS_H
