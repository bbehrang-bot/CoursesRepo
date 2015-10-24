#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
void fillRand(int mat[4][4]){

int i =0;
int j=0;
srand(time(NULL));
for(i;i<=3;i++){
    for(j=0;j<=3;j++){
        mat[i][j]= (1+rand() % 1999 )-1000;
    }
}
}
void rotateCCW270(int mat[4][4]){
int i=0;
int j=0;
int temp[4][4]={0};
for(i;i<=3;i++){
    for(j=0;j<=3;j++){
        temp[i][j]=mat[3-j][i];
    }
}
i=0;
j=0;
for(i;i<=3;i++){
    for(j=0;j<=3;j++){
        mat[i][j]=temp[i][j];
    }
}

}
void flipH(int mat[4][4]){
int i=0;
int j=0;
int temp[4][4]={0};
for(i;i<=3;i++){
    for(j=0;j<=3;j++){
        temp[i][j]=mat[i][3-j];
    }
}
i=0;
j=0;
for(i;i<=3;i++){
    for(j=0;j<=3;j++){
        mat[i][j]=temp[i][j];
    }
}

}
void transposSide(int mat[4][4]){
int i=0;
int j=0;
int temp[4][4]={0};
for(i;i<=3;i++){
    for(j=0;j<=3;j++){
        temp[i][j]=mat[3-j][3-i];
    }
}
i=0;
j=0;
for(i;i<=3;i++){
    for(j=0;j<=3;j++){
        mat[i][j]=temp[i][j];
    }
}

}