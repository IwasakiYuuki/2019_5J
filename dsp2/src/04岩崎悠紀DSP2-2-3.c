/**
 * @file 04岩崎悠紀DSP2-2-3.c
 * @brief DSP2-2-3・BMPの読み込みの課題
 * @authur 岩崎悠紀
 * @date 2019/06/06
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BMP_HEADER_BEGIN 0
#define BMP_HEADER_BYTES 54
#define BMP_FILE_HEADER_BEGIN 0
#define BMP_FILE_HEADER_BYTES 14
#define BMP_INFO_HEADER_BEGIN 14
#define BMP_INFO_HEADER_BYTES 40
#define BMP_RGB_DATA_BEGIN 54

typedef struct{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offbits;
} bmp_file_header;

typedef struct{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pix_per_meter;
    int32_t y_pix_per_meter;
    uint32_t clr_used;
    uint32_t clr_important;
} bmp_info_header;

typedef struct{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
} bmp_rgb;

typedef struct{
    bmp_file_header file_header;
    bmp_info_header info_header;
    bmp_rgb **rgb_data;
} bmp;

void get_bmp_from_filename(char *filename, bmp *bmp_data);
void get_bmp_header(FILE *fp, bmp *bmp_data);
void get_bmp_file_header(FILE *fp, bmp *bmp_data);
void get_bmp_info_header(FILE *fp, bmp *bmp_data);
void get_bmp_rgb_data(FILE *fp, bmp *bmp_data, int32_t width, int32_t height);
void malloc_bmp_rgb_data(bmp *bmp_data, int32_t width, int32_t height);

int main(){
    FILE *fp;
    char *filename="data/sample.bmp";
    bmp *bmp_data;
    bmp_data = (bmp *)malloc(sizeof(bmp));
    get_bmp_from_filename(filename, bmp_data);
}

/**
 * @brief 引数で与えられたファイルからBMPデータを読み込みをする関数
 * @param filename BMPファイル名
 * @param bmp_data BMPデータを格納する変数
 */
void get_bmp_from_filename(char *filename, bmp *bmp_data){
    FILE *fp;
    //ファイル読み込み
    fp = fopen(filename, "rb");
    if(fp == NULL){
        printf("[ERROR]: Failed to read %s.\n", filename);
        exit(1);
    }
    get_bmp_header(fp, bmp_data);
    malloc_bmp_rgb_data(
        bmp_data,
        bmp_data->info_header.width,
        bmp_data->info_header.height
    );
    get_bmp_rgb_data(
        fp,
        bmp_data,
        bmp_data->info_header.width,
        bmp_data->info_header.height
    );
}

/**
 * @brief 与えられたファイルポインタからBMPファイルのヘッダーを読み込む関数
 * @param fp 対象のファイルポインタ
 * @param bmp_data BMPデータを格納する変数
 */
void get_bmp_header(FILE *fp, bmp *bmp_data){
    fseek(fp, BMP_HEADER_BEGIN, SEEK_SET);
    get_bmp_file_header(fp, bmp_data);
    get_bmp_info_header(fp, bmp_data);
}

/**
 * @brief 与えられたファイルポインタからBMPファイルのFileHeaderを読み込む関数
 * @param fp 対象のファイルポインタ
 * @param bmp_data BMPデータを格納する変数
 */
void get_bmp_file_header(FILE *fp, bmp *bmp_data){
    bmp_file_header *file_header = &(bmp_data->file_header);
    fseek(fp, BMP_FILE_HEADER_BEGIN, SEEK_SET);
    fread(&(file_header->type), 2, 1, fp);
    fread(&(file_header->size), 4, 1, fp);
    fread(&(file_header->reserved1), 2, 1, fp);
    fread(&(file_header->reserved2), 2, 1, fp);
    fread(&(file_header->offbits), 4, 1, fp);
}

/**
 * @brief 与えられたファイルポインタからBMPファイルのInfoHeaderを読み込む関数
 * @param fp 対象のファイルポインタ
 * @param bmp_data BMPデータを格納する変数
 */
void get_bmp_info_header(FILE *fp, bmp *bmp_data){
    bmp_info_header *info_header = &(bmp_data->info_header);
    fseek(fp, BMP_INFO_HEADER_BEGIN, SEEK_SET);
    fread(&(info_header->size), 4, 1, fp);
    fread(&(info_header->width), 4, 1, fp);
    fread(&(info_header->height), 4, 1, fp);
    fread(&(info_header->planes), 2, 1, fp);
    fread(&(info_header->bit_count), 2, 1, fp);
    fread(&(info_header->compression), 4, 1, fp);
    fread(&(info_header->size_image), 4, 1, fp);
    fread(&(info_header->x_pix_per_meter), 4, 1, fp);
    fread(&(info_header->y_pix_per_meter), 4, 1, fp);
    fread(&(info_header->clr_used), 4, 1, fp);
    fread(&(info_header->clr_important), 4, 1, fp);
}

/**
 * @brief 与えられたファイルポインタからBMPファイルのRGBデータを読み込む関数
 * @param fp 対象のファイルポインタ
 * @param bmp_data BMPデータを格納する変数
 * @param width RGBデータ部の幅
 * @param height RGBデータ部の高さ
 */
void get_bmp_rgb_data(FILE *fp, bmp *bmp_data, int32_t width, int32_t height){
    int w, h;
    bmp_rgb **data = bmp_data->rgb_data;
    fseek(fp, BMP_RGB_DATA_BEGIN, SEEK_SET);
    for(h=0; h<height; h++){
        for(w=0; w<width; w++){
            fread(&(data[h][w].blue), 1, 1, fp);
            fread(&(data[h][w].green), 1, 1, fp);
            fread(&(data[h][w].red), 1, 1, fp);
            fread(&(data[h][w].reserved), 1, 1, fp);
        }
    }
}

/**
 * @brief BMPデータのRGBのメモリを確保する関数
 * @param bmp_data BMPデータを格納する変数
 * @param width 確保するRGBデータの幅（ヘッダーから読み込んだ値を使う）
 * @param height 確保するRGBデータの高さ（ヘッダーから読み込んだ値を使う）
 */
void malloc_bmp_rgb_data(bmp *bmp_data, int32_t width, int32_t height){
    int i;
    bmp_data->rgb_data = (bmp_rgb **)malloc(sizeof(bmp_rgb *)*height);
    for(int i=0; i<width; i++){
        bmp_data->rgb_data[i] = (bmp_rgb *)malloc(sizeof(bmp_rgb)*width);
    }
}