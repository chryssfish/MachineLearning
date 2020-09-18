#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 20

int random(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}



typedef struct NukleoLine{
	//�� ���������� ��������� ��� �������������
	int _A; 
	int _T;
	int _C;
	int _G;
} NukleoLine;

//������� �� � ��������� ����� �����������������
int isMono(NukleoLine X){
	//���� �
	if ((X._A > 0) && (X._T == 0) && (X._C == 0) &&(X._G == 0)){
		
		return 1;
	}
	//���� �
	else if ((X._T > 0) && (X._A == 0) && (X._C == 0) &&(X._G == 0)){
		
		return 1;
	}
	//���� C
	else if ((X._C > 0) && (X._A == 0) && (X._T == 0) &&(X._G == 0)){
		
		return 1;
	}
	//MONO G
	else if ((X._G > 0) && (X._A == 0) && (X._T == 0) &&(X._C == 0)){
		
		return 1;
	}
	//������ (������� �������� ���������
	else if ((X._G < 0) || (X._A < 0) || (X._T < 0) || (X._C < 0)){
		printf("%d-%d-%d-%d\n",X._G,X._A,X._T,X._C,0);
		return -1;
	}
	return 0;
}
//������� � ������������ ��� ����� � �м �� ��������� �
//���������� 1 �� � ������� ��� ��������� ���� ��� �������� ����� ����������������, 0 �� ��� ����� ��� -1 �� �������� ������ ������
int abstruct(NukleoLine *X, int n, char k){
	switch (k){
		case 'A':{
			if (X->_A>=n){
				X->_A-=n;
				return isMono(*X);
			}
			else if (X->_A==0){
				return -1;
			}
			else {
				X->_A = 0;
				return isMono(*X);
			}
			break;
		}
		case 'T':{
			if (X->_T>=n){
				X->_T-=n;
				return isMono(*X);
			}
			else if (X->_T==0){
				return -1;
				
			}
			else {
				X->_T = 0;
				return isMono(*X);
			}
			break;
		}
		case 'C':{
			if (X->_C>=n){
				X->_C-=n;
				return isMono(*X);
			}
			else if (X->_C==0){
				return -1;
			}
			else {
				X->_C = 0;
				return isMono(*X);
			}
			break;
		}
		case 'G':{
			if (X->_G>=n){
				X->_G-=n;
				return isMono(*X);
			}
			else if (X->_G==0){
				return -1;
			}
			else {
				X->_G = 0;
				return isMono(*X);
			}
			break;
		}
	}
	return -1;
}
//������������ ��� ��������� ��� ���������� �м ������ ��������
void init(NukleoLine *X, char *filename){
	FILE *fp = fopen(filename,"r");
	int c;
	char k;
	
	X->_A = 0;
	X->_T = 0;
	X->_C = 0;
	X->_G = 0;

	int i = 0;
	while (!feof(fp)){
		k = fgetc(fp);
		switch(k){
			case 'A' :{
				
				(X->_A)++;
				
				
				break;
			}
			case 'T' :{
				
				(X->_T)++;
				break;
			}
			case 'C' :{
				
				(X->_C)++;
				break;
			}
			case 'G' :{
				
				(X->_G)++;
				break;
			}
		}
	}
	fclose(fp);
}

//���������� �� ������������ ��� � �� ��� ���������� ���������
char maxFrequency(NukleoLine X){
	int freq = X._A;
	char ret = 'A';
	if (freq < X._T){
		freq = X._T;
		ret = 'T';
	}
	if (freq < X._C){
		freq = X._C;
		ret = 'C';
	}
	if (freq < X._G){
		freq = X._G;
		ret = 'G';
	}	
	return ret;
}
//���������� �� ������������ ��� � �� ��� ��������� ���������
char minFrequency(NukleoLine X){
	int freq = 2000;
	char ret = '-';
	if ((X._A!=0)&&(freq > X._A)){
		freq = X._A;
		ret = 'A';
	}
	if ((X._T!=0)&&(freq > X._T)){
		freq = X._T;
		ret = 'T';
	}
	if ((X._C!=0)&&(freq > X._C)){
		freq = X._C;
		ret = 'C';
	}
	if ((X._G!=0)&&(freq > X._G)){
		freq = X._G;
		ret = 'G';
	}	
	return ret;
}
//������� ��� ������ ����������
int randomPlay(NukleoLine *X){
	char N[] = {'A','T','C','G'};
	int n = random(1,2);
	int t = random(0,3);
	return abstruct(X, n, N[t]);
}
//������� ���� ������������� �м ������ �� ��� ��������� ���������
int oneMin(NukleoLine *X){
	return abstruct(X, 1, minFrequency(*X));
}

//������� ���� ������������� �м ������ �� ��� ���������� ���������
int oneMax(NukleoLine *X){
	return abstruct(X, 1, maxFrequency(*X));
}
//������� ��� ������������� �м ������ �� ��� ���������� ����������������
int twoMin(NukleoLine *X){
	return abstruct(X, 2, minFrequency(*X));
}

//������� ��� ������������� �м ������ �� ��� ���������� ���������
int twoMax(NukleoLine *X){
	return abstruct(X, 2, maxFrequency(*X));
}


int main(int argc, char *argv[]) {
	/*
	���������� 0: ������ �������
	���������� 2: 1 ��� ��� ���������� ���������
	���������� 3: 2 ��� ��� ���������� ���������
	���������� 4: 1 ��� ��� ��������� ���������
	���������� 5: 2 ��� ��� ��������� ���������
	*/
	int Wins[25][2];
	FILE *fpr;
	int kk;
	NukleoLine MYNUKLEOLINE;
	init(&MYNUKLEOLINE, "data.txt");
	
	fpr = fopen("result.txt","w");
	int r;
	int x,y,h;
	//���� ������ ����� ���������� �� ����� ��� ������� �� ���� ����������
	for (x=0;x<25;x++){
		for (y=0;y<2;y++){
			Wins[x][y] = 0;
		}
	}
	for (x=0;x<5;x++){//��� ���� ����������� � ������
		for (y=0;y<5;y++){//��� ���� ����������� � ������
			for (h=0;h<10;h++){//���� ����������
				init(&MYNUKLEOLINE, "data.txt");
				while(1){
					//player 1
					
					switch (x) {
						
						case 0:{
							r = randomPlay(&MYNUKLEOLINE);
							break;
						}
						case 1:{
							r = oneMax(&MYNUKLEOLINE);
							break;
						}
						case 2:{
							r = twoMax(&MYNUKLEOLINE);
							break;
						}
						case 3:{
							r = oneMin(&MYNUKLEOLINE);
							break;
						}
						case 4:{
							r = twoMin(&MYNUKLEOLINE);
							break;
						}
					}
					
					if (r == 1){
						Wins[x*5+y][1]++;
						
						break;
					}
					//player 2
					
					switch (y) {
						case 0:{
							r = randomPlay(&MYNUKLEOLINE);
							break;
						}
						case 1:{
							r = oneMax(&MYNUKLEOLINE);
							break;
						}
						case 2:{
							r = twoMax(&MYNUKLEOLINE);
							break;
						}
						case 3:{
							r = oneMin(&MYNUKLEOLINE);
							break;
						}
						case 4:{
							r = twoMin(&MYNUKLEOLINE);
							break;
						}
					}
					
					if (r == 1){
						Wins[x*5+y][0]++;
						
						break;
					}
				}	
			}
		}
	}
	//�������� ������������� ��� ������ result.txt
	for (x=0;x<5;x++){
		for (y=0;y<5;y++){
			fprintf(fpr,"%d. %d-%d\n",x*5+y, Wins[x*5+y][0],  Wins[x*5+y][1]);
		}
	}
	fclose(fpr);
	return 0;
}


