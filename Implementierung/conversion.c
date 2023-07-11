#include "conversion.h"

void to_carthesian(unsigned __int128 bm1pi, __int128 *real, __int128 *imag) {
    //DONE: implement to_carthesian
    *real = 0;
    *imag = 0;

    if (bm1pi == 0) return;

    unsigned __int128 mask = (unsigned __int128) 1 << 127;
    int bm1pi_length = 0;
    for (int i = 0; i < 128; ++i, mask >>= 1) {
        if (bm1pi & mask) {
            bm1pi_length = 128 - i;
            break;
        }
    }

    mask = 1;
    __int128 power = 1;
    for (int i = 0; i < bm1pi_length; i += 8) {

        //i=0,8,16,...
        if (bm1pi & mask) {
            *real += power;
        }
        mask <<= 1;

        //i=1,9,17,...
        if (bm1pi & mask) {
            *real -= power;
            *imag += power;
        }
        mask <<= 1;
        power <<= 1;

        //i=2,10,18,...
        if (bm1pi & mask) {
            *imag -= power;
        }
        mask <<= 1;

        //i=3,11,19,..
        if (bm1pi & mask) {
            *real += power;
            *imag += power;
        }
        mask <<= 1;
        power <<= 1;

        //i=4,12,20,...
        if (bm1pi & mask) {
            *real -= power;
        }
        mask <<= 1;

        //i=5,13,21,...
        if (bm1pi & mask) {
            *real += power;
            *imag -= power;
        }
        mask <<= 1;
        power <<= 1;

        //i=6,14,22,...
        if (bm1pi & mask) {
            *imag += power;
        }
        mask <<= 1;

        //i=7,15,23,...
        if (bm1pi & mask) {
            *real -= power;
            *imag -= power;
        }
        mask <<= 1;
        power <<= 1;
    }
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

void to_carthesian_V1(unsigned __int128 bm1pi, __int128 *real, __int128 *imag) {
    //DONE: implement to_carthesian

    __int128 baseReal = -1;
    __int128 baseImag = 1;

    __int128 powZero = (bm1pi & (0b1));
    powZero -= (bm1pi & 0b10) >> 1;
    __int128 powOne = (bm1pi & 0b10) >> 1;

    __int128 sumReal = 0;
    __int128 sumImag = 0;

    unsigned __int128 mask = 1;

    __int128 temp; //Secure the current value of real

    bm1pi >>= 2;
    while (bm1pi > 0) {

        temp = baseReal;
        baseReal = (-baseReal) - baseImag;
        baseImag = temp - baseImag;

        if (bm1pi & mask) {
            sumReal += baseReal; //Sum of real part
            sumImag += baseImag; //Sum of imaginary part
        }
        bm1pi >>= 1;
    }

    *real = sumReal + powZero;
    *imag = sumImag + powOne;
}
