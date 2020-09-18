#include <stdio.h>
#include <stdlib.h>


//������� �������� �����������
double trans[2][2];
//���������� ����������� �� ʢ�� ���������
double pos[2][4];
//� ������� VITERBI
double viterbi[2][6];
//� ����������� ���������� �����������
int pathVal[4];

//������������ ��� ���������
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
//������ ��� ����������� ��������� ��� ��������� I ��� ���� J
double max(int i,int j){
	double value1;
	double value2;
	value1 = viterbi[i][j-1]+trans[i][i];
	value2 = viterbi[(i+1)%2][j-1]+trans[(i+1)%2][i];
	return ((value1>value2)?value1:value2);
}
//���������� ��� ����� ��� ������ VITERBI ��� ���� �
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
//�������� ��� ����������� ����������� �����������
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
