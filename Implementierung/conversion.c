#include "conversion.h"

void to_carthesian(unsigned __int128 bm1pi, __int128 *real, __int128 *imag) {
    //TODO: implement to_carthesian

    return;
}

unsigned __int128 to_bm1pi(__int128 real, __int128 imag) {
    //DONE: implement to_bm1pi
    unsigned __int128 result = 0;
    unsigned __int128 mask = (unsigned __int128) 1;

    for (int i = 0; i < 128 && (real || imag); ++i, mask <<= 1) {
        __int128 temp = real; //secure the current value of real
        if ((real % 2 && imag % 2) || (!(real % 2) && !(imag % 2))) {
            // (imag - real) and (-temp - imag) are both even -> no remainder -> don't change result
            real = (imag - real) / 2;
            imag = (-temp - imag) / 2;
        } else {
            // (imag - real) and (-temp - imag) are both odd ->add one to them because of remainder -> change results current bit to 1
            real = (imag - real + 1) / 2;
            imag = (-temp - imag + 1) / 2;
            result |= mask;
        }
    }

    return result;
}

// TODO: alternative implementations of to_carthesian and to_bm1pi for performance comparison
