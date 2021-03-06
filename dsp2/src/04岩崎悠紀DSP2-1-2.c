//2019年度・課題2-1-2・出席番号４番

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM 1024
#define EPSILON 1e-4

typedef struct{
	double re;
	double im;
}comp;

void inputData(comp *data, char *filename, int N);
void outputData(comp *data, char *filename, int N);
void outputAsAmp(comp *data, char *filename, int N);
void outputAsPow(comp *data, char *filename, int N);
void outputDouble(double *data, char *filename, int N);
comp comp_add(comp a, comp b);
comp comp_sub(comp a, comp b);
comp comp_mul(comp a, comp b);
comp comp_div(comp a, comp b);
comp con_reverse(comp a);
void twid(comp *wnkm, int N);
unsigned int bit_reverse(unsigned int a, int n);
void butterflyOpe(comp *x1, comp *x2, comp w);
void fft(comp *in, comp *wnk, int N, int r);
void ifft(comp *in, comp *wnk, int N, int r);
void dft(comp *xn, int N, comp *Xk, int a, int b);
void ampSpectrum(comp *Xk, int N, double *spec);
void powerSpectrum(comp *Xk, int N, double *spec);
void phaSpectrum(comp *Xk, int N, double *spec);
void hamming(comp *x1, comp *x2, int N);
double *self_correlation(double *data, int n);



comp xn[NUM];
comp Xk[NUM];
char *filename = "./data/wdata1.txt";

int main(){
	int i = 0;
	int N = NUM;
	double buf[NUM]={0}, pha_buf[NUM]={0};
	double self_cor_data[NUM/2] = {0.0};
	comp wnk[NUM], cache[NUM];
	FILE *fp;
    clock_t start, end;

	for(i=0;i<N;i++){
		Xk[i].re = 0;
		Xk[i].im = 0;
		xn[i].re = 0;
		xn[i].im = 0;
	}

	inputData(xn, filename, N);
    start = clock();
//	dft(xn, N, Xk, 1, 1);
    end = clock();
//	printf("dft time = %lf[s]\n", (double)(end - start)/CLOCKS_PER_SEC);
//	outputAsAmp(Xk, "Xk.txt", N);
    for(i=0; i<N; i++){
        self_cor_data[i] = xn[i].re;
    }
    start = clock();
	twid(wnk, N);
	fft(xn, wnk, N, 10);
    end = clock();
	printf("fft time = %lf[s]\n", (double)(end - start)/CLOCKS_PER_SEC);
	outputAsPow(xn, "xn.txt", N);
	for(i=0; i<N; i++){
	    xn[i].re=xn[i].re*xn[i].re + xn[i].im*xn[i].im;
	    xn[i].im = 0;
	    printf("%f\n", xn[i].re);
	}
	ifft(xn, wnk, N, 10);
	outputAsAmp(xn, "ixn.txt", N);
	outputDouble(self_correlation(self_cor_data, NUM/2), "self-correlation.txt", NUM/2);

	printf("2019年度・課題2-1-2・出席番号４番\n");
	printf("usage:内部の定数を変化させ実行するとDFTとFFTをします。\n");
	printf("ファイルに結果を出力しました\n");


	return 0;
}

void inputData(comp *data, char *filename, int N){
	FILE *fp;
	int i=0;

	fp = fopen(filename, "r");
	if(fp == NULL)printf("aaa\n");
	for(i=0;i<N;i++){
		if(fscanf(fp, "%lf\n", &data[i].re)==EOF){
			printf("[ERROR] cant read file to the end.");
			return;
		}
	}
}

void outputData(comp *data, char *filename, int N){
	FILE *fp_re, *fp_im;
	int i = 0;
	char filename_re[256];
	char filename_im[256];

	strcpy(filename_re, filename);
	strcpy(filename_im, filename);
	strcat(filename_re, "_re.txt");
	strcat(filename_im, "_im.txt");

	fp_re = fopen(filename_re, "w");
	fp_im = fopen(filename_im, "w");
	if(fp_re == NULL){
		printf("cant open file.\n");
	}
	if(fp_im == NULL){
		printf("cant open file.\n");
	}

	for(i = 0; i < N; i++){
		if(fprintf(fp_re, "%lf\n", data[i].re) < 0 ){
			printf("ERROR\n");
			return;
		}
		if(fprintf(fp_im, "%lf\n", data[i].im) < 0){
			printf("[ERROR] cant write file to the end.");
			return;
		}
	}

	fclose(fp_re);
	fclose(fp_im);
}

void outputAsAmp(comp *data, char *filename, int N){
    double amp[N];
    int i;
    FILE *out;
    out = fopen(filename, "w");
    if(out == NULL){
        fprintf(stderr, "[ERROR]: cannot open file named [%s].\n", filename);
        exit(1);
    }
    ampSpectrum(data, N, amp);
    for(i=0; i<N; i++){
        if(fprintf(out, "%lf\n", amp[i]) < 0 ){
			fprintf(stderr, "[ERROR]: cannot write file named [%s].\n", filename);
			exit(1);
		}
    }
    fclose(out);
}

void outputAsPow(comp *data, char *filename, int N){
    double amp[N];
    int i;
    FILE *out;
    out = fopen(filename, "w");
    if(out == NULL){
        fprintf(stderr, "[ERROR]: cannot open file named [%s].\n", filename);
        exit(1);
    }
    powerSpectrum(data, N, amp);
    for(i=0; i<N; i++){
        if(fprintf(out, "%lf\n", amp[i]) < 0 ){
			fprintf(stderr, "[ERROR]: cannot write file named [%s].\n", filename);
			exit(1);
		}
    }
    fclose(out);
}

void outputDouble(double *data, char *filename, int N){
    int i;
    FILE *out;
    out = fopen(filename, "w");
    if(out == NULL){
        fprintf(stderr, "[ERROR]: cannot open file named [%s].\n", filename);
        exit(1);
    }
    for(i=0; i<N; i++){
        if(fprintf(out, "%lf\n", data[i]) < 0 ){
			fprintf(stderr, "[ERROR]: cannot write file named [%s].\n", filename);
			exit(1);
		}
    }
    fclose(out);
}

comp comp_add(comp a, comp b){
	comp ans;
	ans.re = a.re + b.re;
	ans.im = a.im + b.im;
	return ans;
}

comp comp_sub(comp a, comp b){
	comp ans;
	ans.re = a.re - b.re;
	ans.im = a.im - b.im;
	return ans;
}

comp comp_mul(comp a, comp b){
	comp ans;
	ans.re = a.re*b.re - a.im*b.im;
	ans.im = a.re*b.im + a.im*b.re;
	return ans;
}

comp comp_div(comp a, comp b){
	comp b_inv = con_reverse(b);
	comp buf = comp_mul(a, b_inv);
	comp ans;
	ans.re = buf.re / (b.re*b.re + b.im*b.im);
	ans.im = buf.im / (b.re*b.re + b.im*b.im);
	return ans;
}

comp con_reverse(comp a){
	comp ans;
	ans.re = a.re;
	ans.im = -a.im;
	return ans;
}

void twid(comp *wnkm, int N){
	for(int i=0; i<N/2; i++){
	    wnkm[i].re = cos(2*M_PI*-1.0*((double)i/(double)N));
	    wnkm[i].im = sin(2*M_PI*-1.0*((double)i/(double)N));
	    if(wnkm[i].re == 0){
	        wnkm[i].re = 0;
	    }
	    if(wnkm[i].im == 0){
	        wnkm[i].im = 0;
	    }
	}
}

void butterflyOpe(comp *x1, comp *x2, comp w){
    comp buf1, buf2;
    buf1 = comp_add(*x1, comp_mul(*x2, w));
    buf2 = comp_sub(*x1, comp_mul(*x2, w));
    *x1 = buf1;
    *x2 = buf2;
}

unsigned int bit_reverse(unsigned int a, int n){
    int buf[n], ans=0, i;
    for(i=0; i<n; i++){
        if(((a>>i) & 1) == 1){
            buf[i]=1;
        }else{
            buf[i]=0;
        }
    }
    for(i=0; i<n; i++){
        ans = ans << 1;
        ans += buf[i];
    }
    return ans;
}

void fft(comp *in, comp *wnk, int N, int r){
    int i, j, k, current, nk, num=1;
    comp buf1, buf2, cache[N];

    for(i=0; i<r; i++){
        current = i+1;
        for(j=0; j<N; j+=num*2){
            for(k=0; k<num; k++){
                nk = N/(num*2)*k;
                butterflyOpe(&in[bit_reverse(j+k, r)], &in[bit_reverse(j+k+num, r)], wnk[nk]);
            }
        }
        num *= 2;
    }
    for(i=0; i<N; i++){
        cache[i] = in[bit_reverse(i, r)];
    }
    for(i=0; i<N; i++){
        in[i] = cache[i];
    }
}

void ifft(comp *in, comp *wnk, int N, int r){
    int i;
    for(i=0; i<N/2; i++){
        wnk[i] = con_reverse(wnk[i]);
    }
    fft(in, wnk, N, r);
    for(i=0; i<N; i++){
        in[i].re /= N;
        in[i].im /= N;
    }
}

void dft(comp *xn, int N, comp *Xk, int a, int b){
	int i,k;

	for(k=0;k<N;k++){
		for(i=0;i<N;i++){
			Xk[k].re += (xn[i].re * cos((2*M_PI/N)*i*k) + a * (xn[i].im * sin((2*M_PI/N)*i*k))) / b;
			Xk[k].im += (xn[i].im * cos((2*M_PI/N)*i*k) - a * (xn[i].re * sin((2*M_PI/N)*i*k))) / b;
		}
	}
}

void ampSpectrum(comp *Xk, int N, double *spec){
	int k=0;

	for(k=0;k<N;k++){
		spec[k] = sqrt(Xk[k].re*Xk[k].re + Xk[k].im*Xk[k].im);
//		spec[k] = Xk[k].re*Xk[k].re + Xk[k].im*Xk[k].im;
		if(spec[k] <= EPSILON){
			spec[k] = 0;
		}else{
//			spec[k] = 20 * log10(spec[k]);
		}
	}
}

void powerSpectrum(comp *Xk, int N, double *spec){
	int k=0;

	for(k=0;k<N;k++){
//		spec[k] = sqrt(Xk[k].re*Xk[k].re + Xk[k].im*Xk[k].im);
		spec[k] = Xk[k].re*Xk[k].re + Xk[k].im*Xk[k].im;
		if(spec[k] <= EPSILON){
			spec[k] = 0;
		}else{
//			spec[k] = 20 * log10(spec[k]);
		}
	}
}

void phaSpectrum(comp *Xk, int N, double *spec){
	int k=0;
	for(k=0;k<N;k++){
		spec[k] = atan(Xk[k].im/Xk[k].re);
	}
}

void hamming(comp *x1, comp *x2, int N){
	int i=0;
	for(i=0;i<N;i++){
		x2[i].re = x1[i].re * (0.54 - 0.46*cos(2*M_PI*i/N));
		x2[i].im = x1[i].im * (0.54 - 0.46*cos(2*M_PI*i/N));
	}
}

double *self_correlation(double *data, int n){
    int i, j;
    double *result;
    result = (double *)malloc(sizeof(double)*n);
    for(i=0; i<n; i++){
        result[i] = 0;
        for(j=0; j<n; j++){
            if( (i+j) < n ){
                result[i] += ((data[j] * data[j+i])/(double)n);
            }
        }
    }
    return result;
}