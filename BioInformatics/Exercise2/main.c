#include <stdio.h>
#include <stdlib.h>



double trans[3][3];
double pos[2][3];
double viterbi[2][6];
int pathVal[6];

void init(){
	int i,j;
	for (i=0;i<3;i++){
		for (j=0;j<3;j++){
			if (i==j){
				trans[i][j]=-1;
			}
			else {
				trans[i][j]=-2;
			}
		}
	}
	
	for (i=0;i<2;i++){
		for (j=0;j<3;j++){
			if (i==j){
				pos[i][j]=-1;
			}
			else {
				pos[i][j]=-2;
			}
		}
	}
	pathVal[0] = 0;
	pathVal[1] = 0;
	pathVal[2] = 1;
	pathVal[3] = 0;
	pathVal[4] = 1;
	pathVal[5] = 1;
}

double max(int i,int j){
	double value1;
	double value2;
	value1 = viterbi[i][j-1]+trans[i][i];
	value2 = viterbi[(i+1)%2][j-1]+trans[(i+1)%2][i];
	return ((value1>value2)?value1:value2);
}

void step(int i){
	
	if (i==0){
		viterbi[0][0] = pos[0][pathVal[0]];
		viterbi[1][0] = pos[1][pathVal[0]];
		
	}
	else{
		viterbi[0][i] = pos[0][pathVal[i]]+max(0,i);
		viterbi[1][i] = pos[1][pathVal[i]]+max(1,i);
		
	}
	
}

void printPath(){
	int i;
	for (i=0;i<6;i++){
		if (viterbi[0][i]>viterbi[1][i]){
			printf(" A ");
		}
		else {
			printf(" B ");
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	int i,j;
	init();
	for (i=0;i<6;i++){
		step(i);
	}
	for (i=0;i<2;i++){
		for (j=0;j<6;j++){
			printf("%f ",viterbi[i][j]);
		}
		printf("\n");
	}
	printPath();
	return 0;
}
