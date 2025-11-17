#include <stdio.h>

// Function prototypes
void inputMatrix(int r, int c, int A[r][c]);
void displayMatrix(int r, int c, int A[r][c]);
void addMatrix(int r, int c, int A[r][c], int B[r][c], int R[r][c]);
void multiplyMatrix(int r1, int c1, int A[r1][c1],
                    int r2, int c2, int B[r2][c2],
                    int R[r1][c2]);
void transposeMatrix(int r, int c, int A[r][c], int T[c][r]);

int main() {
    int r1, c1, r2, c2, choice;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    int A[r1][c1];
    inputMatrix(r1, c1, A);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    int B[r2][c2];
    inputMatrix(r2, c2, B);

    printf("\nMatrix A:\n");
    displayMatrix(r1, c1, A);

    printf("\nMatrix B:\n");
    displayMatrix(r2, c2, B);

    printf("\nSelect Operation:\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Transpose of Matrix A\n");
    printf("4. Transpose of Matrix B\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            if(r1 == r2 && c1 == c2) {
                int R[r1][c1];
                addMatrix(r1, c1, A, B, R);
                printf("\nResult of Addition:\n");
                displayMatrix(r1, c1, R);
            } else {
                printf("\nAddition Not Possible! Dimensions Must Match.\n");
            }
            break;

        case 2:
            if(c1 == r2) {
                int R[r1][c2];
                multiplyMatrix(r1, c1, A, r2, c2, B, R);
                printf("\nResult of Multiplication:\n");
                displayMatrix(r1, c2, R);
            } else {
                printf("\nMultiplication Not Possible! (Columns of A != Rows of B)\n");
            }
            break;

        case 3: {
            int T[c1][r1];
            transposeMatrix(r1, c1, A, T);
            printf("\nTranspose of Matrix A:\n");
            displayMatrix(c1, r1, T);
            break;
        }

        case 4: {
            int T[c2][r2];
            transposeMatrix(r2, c2, B, T);
            printf("\nTranspose of Matrix B:\n");
            displayMatrix(c2, r2, T);
            break;
        }

        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}

// Input matrix
void inputMatrix(int r, int c, int A[r][c]) {
    printf("Enter elements (%d x %d):\n", r, c);
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            scanf("%d", &A[i][j]);
}

// Display matrix
void displayMatrix(int r, int c, int A[r][c]) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

// Matrix Addition
void addMatrix(int r, int c, int A[r][c], int B[r][c], int R[r][c]) {
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            R[i][j] = A[i][j] + B[i][j];
}

// Matrix Multiplication
void multiplyMatrix(int r1, int c1, int A[r1][c1],
                    int r2, int c2, int B[r2][c2],
                    int R[r1][c2]) 
{
    for(int i = 0; i < r1; i++)
        for(int j = 0; j < c2; j++) {
            R[i][j] = 0;
            for(int k = 0; k < c1; k++)
                R[i][j] += A[i][k] * B[k][j];
        }
}

// Matrix Transpose
void transposeMatrix(int r, int c, int A[r][c], int T[c][r]) {
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            T[j][i] = A[i][j];
}
