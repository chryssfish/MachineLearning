#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//то лецисто епитяепто лгйос 
#define MAX_SIZE 100000

int Wins[9][2];
//ои дуо айокоухиес йаи та лгйг тоус
char *N;
int nLen;
//----
char *M;
int mLen;
//ои пихамс тилес тым хесеым тгс айокоухиас
char Noukleo[] = {'A','T','C','G'};

int random(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


int isValid(int c){
	int i = 0;
	for (i=0;i<4;i++){
		if (Noukleo[i]==c){
			return 1;
		}
	}
	return 0;
}

//аявийопоигсг апо та дуо аявеиа дедолемым
void init(char *file1, char *file2){
	int i;
	char c;
	FILE *fp1 = fopen(file1,"r");
	FILE *fp2 = fopen(file2,"r");
	
	mLen = 0;
	nLen = 0;
	while (!feof(fp1)){
		c = fgetc(fp1);
		if (isValid(c)==1){
			*(N+nLen) = c;
			nLen++;
			*(N+nLen) = '\0';
		}
	
	}
	fclose(fp1);
	while (!feof(fp2)){
		c = fgetc(fp2);
		if (isValid(c)==1){
			*(M+mLen) = c;
			mLen++;
			*(M+mLen) = '\0';
		}
		
	}
	fclose(fp2);
	
}

//йатастяожг айокоухиас йаи диаияесг тгс аккгс се й/3 йаи м-й/3
//то А деивмеи то поиа апо тис дуо йатастяежетаи
int split(int a){
	int i;
	//лиа апо тис айокоухиес еимаи лгдемийг
	if ((mLen==0)||(nLen==0)){
		return 1;
	}	
	//йатастяожг тгс епикецлемгс айокоухиас йаи диаспасг тгс аккгс
	if (a==1){
		for (i=0;i<mLen/3;i++){
			*(N+i) = *(M+i);
		}
		for (i=mLen/3;i<mLen;i++){
			*(M+(i-(mLen/3)))=*(M+i);
		}
		nLen = mLen/3;
		mLen = mLen - nLen;
	}
	else if (a==2){
		for (i=0;i<nLen/3;i++){
			*(M+i) = *(N+i);
		}
		for (i=nLen/3;i<nLen;i++){
			*(N+(i-(nLen/3)))=*(N+i);
		}
		mLen = nLen/3;
		nLen = nLen - mLen;
	}
	return 0;
}

//йатастяожг тгс лийяотеягс  айокоухиас AN а = S Kйатастяожг тгс лецакутеяHс се диажояетийг пеяиптысг
int destroy(char s){
	if (s == 'S'){
		if (mLen<nLen){
			return split(2);
		}
		else {
			return split(1);
		}
	}
	else {
		if (mLen>nLen){
			return split(2);
		}
		else {
			return split(1);
		}
	}
}

	

//ейтекесг лиас ей тым тессаяым стяатгций©м
void playType(int a,int b){
	int ran;
	while (1){
		if (a==1){
			if (destroy('L')==1){
				printf("Player 1 wins!\n");
				Wins[(a-1)*3+(b-1)][0]++;
				break;
			}
		}
		else if (a==2){
			if (destroy('S')==1){
				printf("Player 1 wins!\n");
				Wins[(a-1)*3+(b-1)][0]++;
				break;
			}
		}
		else if (a==3){
			ran = random(1,10);
			if (ran%2){
				if (destroy('L')==1){
					printf("Player 1 wins!\n");
					Wins[(a-1)*3+(b-1)][0]++;
					break;
				}
			}
			else {
				if (destroy('S')==1){
					printf("Player 1 wins!\n");
					Wins[(a-1)*3+(b-1)][0]++;
					break;
				}
			}
		}
		if (b==1){
			if (destroy('L')==1){
				printf("Player 2 wins!\n");
				Wins[(a-1)*3+(b-1)][1]++;
				break;
			}
		}
		else if (b==1){
			if (destroy('S')==1){
				printf("Player 2 wins!\n");
				Wins[(a-1)*3+(b-1)][1]++;
				break;
			}
		}
		else if (b==3){
			ran = random(1,10);
			if (ran%2){
				if (destroy('L')==1){
					printf("Player 2 wins!\n");
					Wins[(a-1)*3+(b-1)][1]++;
					break;
				}
			}
			else {
				if (destroy('S')==1){
					printf("Player 2 wins!\n");
					Wins[(a-1)*3+(b-1)][1]++;
					break;
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int r;
	int i,j;
	FILE *fpr;
	N = (char *)malloc(MAX_SIZE);
	M = (char *)malloc(MAX_SIZE); 
	for (i = 0; i<9;i++){
		Wins[i][0] = 0;
		Wins[i][1] = 0;
	}
	//ейтекесг 10 жояес циа йахе лиа апо тис стяатгцийес
	for (i=1;i<=3;i++){
		for (j=1;j<=3;j++){
			for (r = 0;r<10;r++){
				init("data1.txt","data2.txt");
				playType(i,j);
			}
		}
	}
	fpr = fopen("results.txt","w");
	for (i=0;i<3;i++){
		for (j=0;j<3;j++){
			fprintf(fpr,"%d|%d|%d|%d\n",i,j,Wins[i*3+j][0],Wins[i*3+j][1]);
		}
	}
	fclose(fpr);
	return 0;
}
