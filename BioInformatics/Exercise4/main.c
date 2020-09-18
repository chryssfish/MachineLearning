#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 20

int random(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}



typedef struct NukleoLine{
	//ои сувмотгтес елжамисгс тым моуйкеотидиым
	int _A; 
	int _T;
	int _C;
	int _G;
} NukleoLine;

//екецвеи ам г айокоухиа еимаи ломомоуйкеодитийг
int isMono(NukleoLine X){
	//ломо а
	if ((X._A > 0) && (X._T == 0) && (X._C == 0) &&(X._G == 0)){
		
		return 1;
	}
	//ломо т
	else if ((X._T > 0) && (X._A == 0) && (X._C == 0) &&(X._G == 0)){
		
		return 1;
	}
	//ломо C
	else if ((X._C > 0) && (X._A == 0) && (X._T == 0) &&(X._G == 0)){
		
		return 1;
	}
	//MONO G
	else if ((X._G > 0) && (X._A == 0) && (X._T == 0) &&(X._C == 0)){
		
		return 1;
	}
	//сжакла (упаявеи аямгтийг сувмотгта
	else if ((X._G < 0) || (X._A < 0) || (X._T < 0) || (X._C < 0)){
		printf("%d-%d-%d-%d\n",X._G,X._A,X._T,X._C,0);
		return -1;
	}
	return 0;
}
//ажаияеи м моуйекотидиа тоу тупоу й ап╪ тг айокоухиа в
//епистяежеи 1 ам г айоухиа поу пяойуптеи лета тгм ажаияесг еимаи ломойкоудеотийиг, 0 ам дем еимаи йаи -1 ам пяоейуье йапоио сжакла
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
//аявийопоигсг тым стоивиеым тгс айокоухиас ап╪ аявеио йеилемоу
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

//епистяежеи то моуйкеотидио тоу в ле тгм лецакутеяг сувмотгта
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
//епистяежеи то моуйкеотидио тоу в ле тгм лийяотеяг сувмотгта
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
//ейтекеи тгм туваиа стяатгцийг
int randomPlay(NukleoLine *X){
	char N[] = {'A','T','C','G'};
	int n = random(1,2);
	int t = random(0,3);
	return abstruct(X, n, N[t]);
}
//епикоцг емос моуйкеотидиоу ап╪ ейеима ле тгм лийяотеяг сувмотгта
int oneMin(NukleoLine *X){
	return abstruct(X, 1, minFrequency(*X));
}

//епикоцг емос моуйкеотидиоу ап╪ ейеима ле тгм лецакутеяг сувмотгта
int oneMax(NukleoLine *X){
	return abstruct(X, 1, maxFrequency(*X));
}
//епикоцг дуо моуйкеотидиым ап╪ ейеима ле тгм лецакутеяг лийяотеягвмотгта
int twoMin(NukleoLine *X){
	return abstruct(X, 2, minFrequency(*X));
}

//епикоцг дуо моуйкеотидиым ап╪ ейеима ле тгм лецакутеяг сувмотгта
int twoMax(NukleoLine *X){
	return abstruct(X, 2, maxFrequency(*X));
}


int main(int argc, char *argv[]) {
	/*
	стяатгцийг 0: туваиа епикоцг
	стяатгцийг 2: 1 апо тгм лецакутеяг сувмотгта
	стяатгцийг 3: 2 апо тгм лецакутеяг сувмотгта
	стяатгцийг 4: 1 апо тгм лийяотеяг сувмотгта
	стяатгцийг 5: 2 апо тгм лийяотеяг сувмотгта
	*/
	int Wins[25][2];
	FILE *fpr;
	int kk;
	NukleoLine MYNUKLEOLINE;
	init(&MYNUKLEOLINE, "data.txt");
	
	fpr = fopen("result.txt","w");
	int r;
	int x,y,h;
	//стом пимайа аутом йяатоумтаи ои мийес тым паийтым се йахе стяатгцийг
	for (x=0;x<25;x++){
		for (y=0;y<2;y++){
			Wins[x][y] = 0;
		}
	}
	for (x=0;x<5;x++){//циа йахе стяатгцгийг а паийтг
		for (y=0;y<5;y++){//циа йахе стяатгцгийг б паийтг
			for (h=0;h<10;h++){//дейа ейтекесеис
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
	//ейтупысг апотекеслатым сто аявеио result.txt
	for (x=0;x<5;x++){
		for (y=0;y<5;y++){
			fprintf(fpr,"%d. %d-%d\n",x*5+y, Wins[x*5+y][0],  Wins[x*5+y][1]);
		}
	}
	fclose(fpr);
	return 0;
}


