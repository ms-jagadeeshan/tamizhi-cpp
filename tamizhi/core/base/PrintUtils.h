#pragma once

#define tmzPrint(...) fprintf(stdout, ##__VA_ARGS__)
#define tmzDev(...)            \
    fprintf(stdout, "[Dev] "); \
    fprintf(stdout, ##__VA_ARGS__)
#define tmzError(...) fprintf(stderr, ##__VA_ARGS__)
