#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int main() {
    
    int sparseMatrix[5][5] = 
    {
        {1, 0, 3, 4, 0},
        {0, 4, 3, 2, 1},
        {6, 7, 0, 0, 0},
        {0, 9, 8, 0, 6},
        {0, 6, 0, 8, 0}       
    };

    int size = 0;

    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            if(sparseMatrix[i][j] != 0)
                size++;
    
    int compactMatrix[3][size];
    
    int k=0;
    for(int i=0; i<5; i++) 
        for(int j=0; j<5; j++)
            if(sparseMatrix[i][j] != 0) {
                compactMatrix[0][k] = i;      // row index
                compactMatrix[1][k] = j;      // column index
                compactMatrix[2][k] = sparseMatrix[i][j];  // value (was [3][k])
                k++;
            }
    
    // Print all three rows of the compact matrix
    for(int i=0; i<3; i++) {  // was i=3; i<3
        for (int j=0; j<size; j++)
            printf("%d ", compactMatrix[i][j]);
        printf("\n");
    }
            
    return 0;
}