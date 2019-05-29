#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM 4

typedef struct{
    double **data;
    int row;
    int col;
} Matrix;

Matrix get_dct_matrix(int N);
Matrix get_idct_matrix(int N);
Matrix multi_matrix(Matrix m1, Matrix m2);
void malloc_matrix(Matrix *mat, int row, int col);
void print_matrix(Matrix mat);

int main(){
    int i, j;

    Matrix c; //DCT行列
    Matrix ic; //IDCT行列
    Matrix xn;　//元のデータ
    Matrix Xk; //xnにDCT行列をかけた結果用
    Matrix cache; //XkからIDCT行列をかけて元のデータに戻ったか確認する用
    malloc_matrix(&xn, NUM, 1);
    xn.data[0][0] = 1;
    xn.data[1][0] = 2;
    xn.data[2][0] = 3;
    xn.data[3][0] = 4;

    c = get_dct_matrix(NUM);
    ic = get_idct_matrix(NUM);
    Xk = multi_matrix(c, xn);
    cache = multi_matrix(ic, Xk);

    printf("C = \n");
    print_matrix(c);
    printf("---------------------------------------------\n");
    printf("iC = \n");
    print_matrix(ic);
    printf("---------------------------------------------\n");
    printf("Xk = \n");
    print_matrix(Xk);
    printf("---------------------------------------------\n");
    printf("xn = \n");
    print_matrix(cache);
    printf("---------------------------------------------\n");


    return 0;
}

/**
 * @brief DCTの行列を求める関数。
 * @param N DCT行列の要素数。
 * @return (N, N)のDCT行列のMatrix。
 */
Matrix get_dct_matrix(int N){
    int n, k;
    Matrix ans;
    malloc_matrix(&ans, N, N);

    for(k=0; k<N; k++){
        for(n=0; n<N; n++){
            if(k == 0){
                ans.data[k][n] = 1.0/sqrt(N);
            }else{
                ans.data[k][n] = (sqrt(2.0/(double)N))*cos((((2.0*(double)n+1.0)*(double)k*M_PI)/(2.0*(double)N)));
            }
        }
    }

    return ans;
}

/**
 * @brief IDCTの行列を求める関数。
 * @param N IDCT行列の要素数。
 * @return (N, N)のIDCT行列のMatrix。
 */
Matrix get_idct_matrix(int N){
    int n, k;
    Matrix ans;
    malloc_matrix(&ans, N, N);

    for(k=0; k<N; k++){
        for(n=0; n<N; n++){
            if(k == 0){
                ans.data[n][k] = 1.0/sqrt(N);
            }else{
                ans.data[n][k] = (sqrt(2.0/(double)N))*cos((((2.0*(double)n+1.0)*(double)k*M_PI)/(2.0*(double)N)));
            }
        }
    }

    return ans;
}

/**
 * @brief 与えられた二つのMatrixをかけ算し，その結果のMatrixを返す関数。
 * @param m1 対象のMatrix。
 * @param m2 対象のMatrix。
 * @return m1とm2の乗算の演算結果。
 */
Matrix multi_matrix(Matrix m1, Matrix m2){
    int i, j, n;
    Matrix ans;
    malloc_matrix(&ans, m1.row, m2.col);

    for(i=0; i<m1.row; i++){
        for(j=0; j<m2.col; j++){
            ans.data[i][j] = 0.0;
            for(n=0; n<m1.col; n++){
                ans.data[i][j] += m1.data[i][n]*m2.data[n][j];
            }
        }
    }

    return ans;
}

/**
 * @brief Matrix型の変数を指定された形でメモリ確保する関数。
 * @param mat 対象のMatrix型データ。
 * @param row 対象のMatrixの行数。
 * @param col 対象のMatrixの列数。
 */
void malloc_matrix(Matrix *mat, int row, int col){
    mat->row = row;
    mat->col = col;
    mat->data = (double **)malloc(sizeof(double *)*row);
    for(int i=0; i<mat->row; i++){
        mat->data[i] = (double *)malloc(sizeof(double)*col);
    }
}

/**
 * @brief Matrix型の引数matのdataをを行列として表示する関数。
 * @param mat 表示するMatrix型のデータ。
 */
void print_matrix(Matrix mat){
    int i, j;
    for(i=0; i<mat.row; i++){
        for(j=0; j<mat.col; j++){
            printf("%6lf\t", mat.data[i][j]);
        }
        printf("\n");
    }
}