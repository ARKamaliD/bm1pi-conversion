#include "conversion.h"
#include <stdio.h>

void to_carthesian(unsigned __int128 bm1pi, __int128 *real, __int128 *imag) {
    //DONE: implement to_carthesian

    __int128 baseReal = -1;
    __int128 baseImag = 1;

    __int128 powZero = 0;
    __int128 powOne = 0;

    __int128 sumReal = 0;
    __int128 sumImag = 0;

    unsigned __int128 mask = 1;

    size_t counter = 0;

    while (bm1pi > 0) {
        if (bm1pi & mask) {
            if (counter == 0) { //(-1 + i) ^ 0 = 1

                powZero++;

            } else if (counter == 1) { //(-1 + i) ^ 1 = -1 + i

                powZero--;
                powOne++;

            } else {

                for (size_t i = 0;
                     i < counter - 1; i++) { //(-1 + i) ^ counter, (a + ib)(c + id) = ((ac - bd) + i(ad + bc) )

                    __int128 temp = baseReal; //Secure the current value of real

                    baseReal = (-baseReal) - baseImag;
                    baseImag = temp - baseImag;

                }

                sumReal += baseReal; //Sum of real part
                sumImag += baseImag; //Sum of imaginary part

                baseReal = -1;  //Reset to default base
                baseImag = 1;   //Reset to default base

            }
        }

        counter++;
        bm1pi >>= 1;
    }

    *real = sumReal + powZero;
    *imag = sumImag + powOne;
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
