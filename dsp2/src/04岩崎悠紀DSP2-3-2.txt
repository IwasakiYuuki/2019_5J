/**
 * @file 04岩崎悠紀DSP2-3-2.c
 * @brief DSP2-3-2・固有値と固有ベクトルをべき乗法により算出する
 * @authur 岩崎悠紀
 * @date 2019/07/03
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM 3
#define EPSILON 0.0001

typedef struct{
    double **data;
    int row;
    int col;
} Matrix;

void multi_matrix(Matrix m1, Matrix m2, Matrix *ans);
void sub_matrix(Matrix m1, Matrix m2, Matrix *ans);
void copy_matrix(Matrix origin, Matrix *target);
double get_norm(Matrix mat);
void norm_matrix(Matrix *mat);
void transpose_matrix(Matrix mat, Matrix *mat_t);
void malloc_matrix(Matrix *mat, int row, int col);
void print_matrix(Matrix mat);

int main(){
    int i, j;

    Matrix Ann;
    Matrix v;
    Matrix v_buf;
    Matrix v_buf_t;
    Matrix v_next;
    Matrix lambda;
    Matrix sub;
    double err;

    malloc_matrix(&Ann, NUM, NUM);
    Ann.data[0][0] = 2; Ann.data[0][1] = 1; Ann.data[0][2] = 3;
    Ann.data[1][0] = 1; Ann.data[1][1] = 2; Ann.data[1][2] = 3;
    Ann.data[2][0] = 3; Ann.data[2][1] = 3; Ann.data[2][2] = 20;

    malloc_matrix(&v, NUM, 1);
    v.data[0][0] = 0;
    v.data[1][0] = 1;
    v.data[2][0] = 0;

    malloc_matrix(&v_buf, NUM, 1);
    malloc_matrix(&v_next, NUM, 1);
    malloc_matrix(&lambda, 1, 1);
    malloc_matrix(&sub, NUM, 1);

    do {
        multi_matrix(Ann, v, &v_buf);
        transpose_matrix(v_buf, &v_buf_t);
        multi_matrix(v_buf_t, v, &lambda);
        copy_matrix(v_buf, &v_next);
        norm_matrix(&v_next);
        sub_matrix(v_next, v, &sub);
        err = get_norm(sub);
        if (err < 0){
            err = -err;
        }
        copy_matrix(v_next, &v);
    } while(err > EPSILON);
    printf("固有ベクトル\n");
    print_matrix(v_next);
    printf("固有値\n");
    print_matrix(lambda);

    return 0;
}

/**
 * @brief 与えられた二つのMatrixをかけ算し，その結果のMatrixを返す関数。
 * @param m1 対象のMatrix。
 * @param m2 対象のMatrix。
 * @return m1とm2の乗算の演算結果。
 */
void multi_matrix(Matrix m1, Matrix m2, Matrix *ans){
    int i, j, n;
    malloc_matrix(ans, m1.row, m2.col);

    for(i=0; i<m1.row; i++){
        for(j=0; j<m2.col; j++){
            ans->data[i][j] = 0.0;
            for(n=0; n<m1.col; n++){
                ans->data[i][j] += m1.data[i][n]*m2.data[n][j];
            }
        }
    }
}

/**
 * @brief 引数の行列のノルムを返す関数。
 * @param mat 対象のMatrix型のデータ。
 * @return norm matの行列のノルム。
 */
void sub_matrix(Matrix m1, Matrix m2, Matrix *ans){
    if((m1.row != m2.row) || (m1.col != m2.col)){
        fprintf(stderr, "[ERR] Matrices of different shape can not sub. In func [%s]\n", __func__);
        exit(-1);
    }

    int i, j;
    int row = m1.row;
    int col = m1.col;

    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            ans->data[i][j] = m1.data[i][j] - m2.data[i][j];
        }
    }
}

/**
 * @brief 行列をコピーする関数。
 * @param origin 元のMatrix型データ。
 * @return target 対象のMatrix型のデータ。
 */
void copy_matrix(Matrix origin, Matrix *target){
    int i, j;
    int row = origin.row;
    int col = origin.col;

    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            target->data[i][j] = origin.data[i][j];
        }
    }
}

/**
 * @brief 引数の行列のノルムを返す関数。
 * @param mat 対象のMatrix型のデータ。
 * @return norm matの行列のノルム。
 */
double get_norm(Matrix mat){
    int i, j;
    int row = mat.row;
    int col = mat.col;
    double norm = 0;

    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
//            if (mat.data[i][j] < 0) {
//                norm += -mat.data[i][j];
//            } else {
//                norm += mat.data[i][j];
//            }
            norm += mat.data[i][j] * mat.data[i][j];
        }
    }

    return sqrt(norm);
}

/**
 * @brief 引数の行列を正規化する関数。
 * @param mat 対象のMatrix型のデータ。
 */
void norm_matrix(Matrix *mat){
    int i, j;
    int row = mat->row;
    int col = mat->col;
    int norm = get_norm(*mat);

    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            mat->data[i][j] /= norm;
        }
    }
}

/**
 * @brief 対象の行列の転置行列を求める関数。
 * @param mat 対象のMatrix型のデータ。
 * @param t_mat matの転置行列のデータを入れるMatrix。
 */
void transpose_matrix(Matrix mat, Matrix *mat_t){
    int i, j;
    int row = mat.row;
    int col = mat.col;

    malloc_matrix(mat_t, col, row);
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            mat_t->data[j][i] = mat.data[i][j];
        }
    }
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