#include <stdio.h>
#include <stdbool.h>

#include "conversion.h"

void print_uint128_binary(unsigned __int128 num, bool leading_zeros) {
    if (num == 0) {
        printf("0\n");
        return;
    }

    for (int i = 127; i >= 0; i--) {
        unsigned __int128 mask = ((unsigned __int128) 1) << i;
        if (num & mask) {
            leading_zeros = 1;
            printf("1");
        } else if (leading_zeros) {
            printf("0");
        }
    }
    printf("\n");
}


int main() {
    print_uint128_binary(to_bm1pi(0, 0), false);

    return 0;
}
