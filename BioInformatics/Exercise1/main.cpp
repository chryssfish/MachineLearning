#include <stdio.h>
#include <stdlib.h>


//пимайас летабасг йатастасеым
double trans[2][2];
//пихамотгта паяатгягсгс се й╒хе йатастасг
double pos[2][4];
//о пимайас VITERBI
double viterbi[2][6];
//г енетафолемг аккгкоувиа йатастасеым
int pathVal[4];

//аявийопоигсг тым дедолемым
void init(){
	int i,j;
	for (i=0;i<2;i++){
		for (j=0;j<2;j++){
			if (i==j){
				trans[i][j]=-0.045;
			}
			else {
				trans[i][j]=-1;
			}
		}
	}
	pos[0][0] = -0.4;
	pos[0][1] = -0.4;
	pos[0][2] = -1;
	pos[0][3] = -1;
	pos[1][0] = -0.53;
	pos[1][1] = -0.53;
	pos[1][2] = -0.7;
	pos[1][3] = -0.7;
}
//еуяесг тгс пихамотеягс летабасгс стг йатастасг I сто бгла J
double max(int i,int j){
	double value1;
	double value2;
	value1 = viterbi[i][j-1]+trans[i][i];
	value2 = viterbi[(i+1)%2][j-1]+trans[(i+1)%2][i];
	return ((value1>value2)?value1:value2);
}
//упкоцислос тым тилым тоу пимайа VITERBI сто бгла и
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
//ейтупысг тгс пихамотеягс аккгкоувиас йатастасеым
void printPath(){
	int i;
	for (i=0;i<4;i++){
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
	for (i=0;i<4;i++){
		step(i);
	}
	for (i=0;i<2;i++){
		for (j=0;j<4;j++){
			printf("%f ",viterbi[i][j]);
		}
		printf("\n");
	}
	printPath();
	return 0;
}
