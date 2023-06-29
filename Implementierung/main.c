#include <stdio.h>
#include <stdbool.h>

#include "conversion.h"

const char *usage_msg =
        "Usage: %s [options] fn   Approximate fn's zero in a given interval\n"
        "   or: %s -t             Run tests and exit\n"
        "   or: %s -h             Show help message and exit\n";

const char *help_msg =
        "Positional arguments:\n"
        "  fn   The function to approxiate zero of. One of {fn_1,fn_x,fn_x2}.\n"
        "\n"
        "Optional arguments:\n"
        "  -a X   The start of the interval (default: X = 0.0)\n"
        "  -b X   The end of the interval (default: X = 1.0)\n"
        "  -n N   The number of maximum steps (default: N = 2)\n"
        "  -t     Run tests and exit\n"
        "  -h     Show help message (this text) and exit\n";

void print_usage(const char *progname) {
    fprintf(stderr, usage_msg, progname, progname, progname);
}

void print_help(const char *progname) {
    print_usage(progname);
    fprintf(stderr, "\n%s", help_msg);
}

void print_uint128_binary(unsigned __int128 num, bool leading_zeros) {
    if (num == 0) {
        printf("0\n");
        return;
    }

    unsigned __int128 mask = (unsigned __int128) 1 << 127;

    for (int i = 0; i < 128; ++i, mask >>= 1) {
        if (num & mask) {
            leading_zeros = 1;
            printf("1");
        } else if (leading_zeros) {
            printf("0");
        }
    }
    printf("\n");
}

// TODO: implementation of different modes and according parameters, and also help
int main() {



//    print_uint128_binary(to_bm1pi(24, -11), false);
    __int128 imag = 0;
    __int128 real = 0;
    unsigned __int128 bm1pi = 0b1001;
    print_uint128_binary(bm1pi, false);
//    print_uint128_binary(real, false);
//    print_uint128_binary(imag, false);
    to_carthesian(bm1pi, &real, &imag);
    print_uint128_binary( real, false);
    print_uint128_binary(imag, false);


    return 0;
}
