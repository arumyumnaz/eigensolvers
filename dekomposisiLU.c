#include <stdio.h>
#include <math.h>
#define N 20

void printMat(double mat[N][N], int n){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("\t%lf", mat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int i, j, k, n;
    double A[N][N]={0}, L[N][N]={0};
    double U[N][N];
    double b[N]={0}, x[N]={0}, y[N]={0};

    printf("Input elemen matriks N (N<20) : ");
    scanf("%d", &n);

    printf("Input matriks SPL (A) : \n");
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Input nilai matriks vektor (b) : \n");
    for(i=0; i<n; i++){
        scanf("%lf", &b[i]);
    }

    //dekomposisi matriks A menjadi LU
    for(j=0; j<n; j++){
        for(i=0; i<n; i++){
            if(i<=j){
                U[i][j] = A[i][j];
                for(k=0; k<=i-1; k++){
                    U[i][j] = U[i][j] - L[i][k] * U[k][j];
                }
                if(i==j){
                    L[i][j] = 1;
                }else{
                    L[i][j] = 0;
                }
            }else{
                L[i][j] = A[i][j];
                for(k=0; k<=j-1; k++){
                    L[i][j] = L[i][j] - L[i][k] * U[k][j];
                }
                L[i][j] = L[i][j] / U[j][j];
                U[i][j] = 0;
            }
        }
    }

    //cari matriks vektor y dari Ly=b
    for(i=0; i<n; i++){
        y[i] = b[i];
        for(j=0; j<i; j++){
            y[i] = y[i] - L[i][j] * y[j];
        }
    }

    //cari nilai x dari Ux = y
    for(i=n-1; i>=0; i--){
        x[i] = y[i];
        for(j=i+1; j<n; j++){
            x[i] = x[i] - U[i][j] * x[j];
        }
        x[i] = x[i] / U[i][i];
    }

    printf("\nMatriks L : \n");
    printMat(L, n);
    printf("Matriks U : \n");
    printMat(U, n);

    printf("y : \n");
    for(i=0; i<n; i++){
        printf("y%d = %lf\n", i+1, y[i]);
    }
    printf("x : \n");
    for(i=0; i<n; i++){
        printf("x%d = %lf\n", i+1, x[i]);
    }

    return 0;
}


