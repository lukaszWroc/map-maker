#include"colors.h"

void addColor(int r,int g,int b)
{
    create_img(r,g,b,colorsT++);
}

colorsT=0;
rgbTableSize=0;
void create_img(int r,int g,int b,int x)
{
    FILE *img;
    char colorsImgName[100]="colors/color";
    char str[100];

    sprintf (str, "%d", x);
    strcat(colorsImgName, str);
    strcat(colorsImgName, ".ppm");

    img=fopen(colorsImgName, "w");
    fprintf(img, "P3\n 30 30\n 256\n");
    for(int i=0;i<230;i++)
    {
        for(int j=0;j<30;j++)
        {
            fprintf(img, "%d %d %d\n",r,g,b);
        }
    }
    fclose(img);
}
