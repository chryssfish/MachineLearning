#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//аявийопоиеи том дисдиастато пимайа тоу акцояихлоу
void initTable(int *F, char *x, char *y){
	int i,j;
	for (i=0;i<strlen(x);i++){
		*(F+i*strlen(y))=0-i;
	}
	for (j=0;j<strlen(y);j++){
		*(F+j) = 0-j;
	}	
}
//упокоцифеи то йеки и,J TOY пимайа
void makeTable(int *F,int i, int j, char *x, char *y){
	int pa = 0;
	int a = 0;
	int p = 0;
	int d = 1;
	int max = -999;
	int s = 0;
	if (*(x+i)==*(y+j)){
		s = 1;
	}
	else {
		s = -1;
	}
	pa = *(F+(i-1)*strlen(y)+j-1)+s;
	a = *(F+i*strlen(y)+j-1)-d;
	p = *(F+(i-1)*strlen(y)+j)-d;
	if (pa>a){
		if (pa>p){
			max = pa;
		}
		else {
			max = p;
		}
	}
	else {
		if (a>p){
			max = a;
		}
		else {
			max = p;
		}
	}
	*(F+i*strlen(y)+j)=max;
}
//йимеитаи писы йаи екецвеи та йема поу дглиоуяцгхгйам йата то таияиасла тым айокоухиым
int goBack(int k, char *A, char *B, int *F){
	int i,j;
	int pa = 0;
	int a = 0;
	int p = 0;
	int max = 0;
	int lenA = strlen(A);
	int lenB = strlen(B);
	i=lenA;
	j=lenB;
	int counter = 0;
	while ((i>0) && (j>0)){
		pa = *(F+(i-1)*lenB+j-1);
		a = *(F+i*lenB+j-1);
		p = *(F+(i-1)*lenB+j);
		if (pa>a){
			if (pa>p){
				i--;
				j--;
				if (k==0){
					return 0;
				}
			}
			else {
				*(A+i)='-';
				i--;
				k--;
				if (k==0){
					return 0;
				}
			}
		}
		else {
			if (a>p){
				*(B+j)='-';
				j--;
				k--;
				if (k==0){
					return 0;
				}
			}
			else {
				*(A+i)='-';
				i--;
				k--;
				if (k==0){
					return 0;
				}
			}
		}
		
	}
	return 1;
}
//диабафеи тгм айокоухиа апо то аявеио FILENAME йаи тгм топохетеи сто STRING
void readFromFile(char *filename, char *string){
	FILE *fp = fopen(filename,"r");
	char c;
	int counter = 0;
	while (!feof(fp)){
		c=fgetc(fp);
		if (c!='\n'){
			*(string + counter) = c;
			counter++;
		}
	}
	*(string+counter) = '\0';
	fclose(fp);
}

int main(int argc, char *argv[]) {
	char A[5000];
	char B[5000];
	int i,j;
	int max = 0;
	//то лецисто епитяепто пкгхос йемым сто таияиасла
	int parameter = 15;
	//-----------------------------------------------
	readFromFile("data1.txt",A);
	readFromFile("data2.txt",B);

	max = strlen(A);
	if (strlen(B)>max){
		max = strlen(B);
	}
	char *result = (char *)malloc(max); 
	int *Matrix;
	Matrix = (int *)malloc((strlen(A)+1)*(strlen(B)+1)*sizeof(int));
	initTable(Matrix,A,B);
	for (i=1;i<=strlen(A);i++){
		for (j=1;j<=strlen(B);j++){
			makeTable(Matrix,i,j,A,B);
		}	
	}
	if (goBack(parameter,A,B,Matrix)==1){
		printf("It is OK!\n",A,B);
		
	}
	else {
		printf("It is not OK!");
	}
	/*
	for (i=0;i<=strlen(A);i++){
		for (j=0;j<=strlen(B);j++){
			printf("%d \t",*(Matrix+strlen(B)*i+j));
		}
		printf("\n");
	}*/
	return 0;
}
