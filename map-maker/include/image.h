#ifndef IMAGE_H

#define IMAGE_H

#include<stdio.h>
#include<stdbool.h>
#include <string.h>


typedef struct
{
    int x,idx;
}colorStruct;
colorStruct colorsTable[256];
int left_lon,left_lin,right_lon,right_lin,lonG,linG;
char left_lon_sing,left_lin_sing,right_lon_sing,right_lin_sing;
FILE *img;
bool vis_lon_N[280],vis_lon_S[280],vis_lin_W[280],vis_lin_E[280];
char nameOfFile[200];

int findColor(int num);
void setLon();
void setLin();
char *setFilesNames(char lon_sing[2],char lin_sing[2],int i,int j);
void drawImage();
void saveImage(char tab[400][300],int tab_size,FILE *image);
void fillFile();
void drawS();
int  unzip(char nameS[200],char nameF[200]);

#endif // IMAGE_H

