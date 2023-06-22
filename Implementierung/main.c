#include <stdio.h>
#include <stdbool.h>

#include "conversion.h"

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
    print_uint128_binary(to_bm1pi(3, 2), false);

    return 0;
}
