#include <stdio.h>
#include <immintrin.h>

#define ROW1 2
#define COL1 8
#define COL2 8

void multiplyMatrices(int16_t matrix1[ROW1][COL1], int16_t matrix2[COL1][COL2], int32_t result[ROW1][COL2]) {
    int i, j;
    __m128i row1, row2, temp;

    for (i = 0; i < ROW1; i++) {
        for (j = 0; j < COL2; j++) {
            row1 = _mm_loadu_si128((__m128i *) &matrix1[i]);
            row2 = _mm_loadu_si128((__m128i *) &matrix2[j]);
            temp = _mm_madd_epi16(row1, row2);
            temp = _mm_hadd_epi32(temp, temp);
            temp = _mm_hadd_epi32(temp, temp);

            // Extract the result from the sum vector
            result[i][j] = _mm_cvtsi128_si32(temp);
        }
    }
}

void displayMatrix(int32_t matrix[ROW1][COL2]) {
    int i, j;
    for (i = 0; i < ROW1; i++) {
        for (j = 0; j < COL2; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int16_t matrix1[ROW1][COL1] = {
            {1, -1, 0,  2, -4, 4,  0, -8},
            {0, 1,  -2, 2, 0,  -4, 8, -8}
    };

    int16_t matrix2[COL1][COL2] = {
            {1, 0, 1, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int32_t resultMatrix[ROW1][COL2];

    multiplyMatrices(matrix1, matrix2, resultMatrix);

    printf("Resultant matrix:\n");
    displayMatrix(resultMatrix);

    return 0;
}
