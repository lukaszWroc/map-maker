#include"image.h"
#include"colors.h"

void drawS()
{
    int scale,oToScale;
    if(linG>lonG)
        oToScale=linG;

    else
        oToScale=lonG;
    scale=oToScale*1201/1000+1;
    FILE *img,*imgS;
    char name[200],nameS[200];
    memset(name, 0, sizeof(name));
    memset(nameS, 0, sizeof(nameS));
    strcat(name,nameOfFile);
    strcat(nameS,nameOfFile);
    strcat(name,".ppm");
    strcat(nameS,"_scaled.ppm");
    img= fopen(name, "r");
    imgS= fopen(nameS, "w");
    int a,b,c;
    char d,e;
    fscanf(img," %c %c %d %d %d",&d, &e, &a,&b,&c);
    fprintf(imgS,"P3\n %d %d\n 255\n",(linG*1201)/scale,(lonG*1201)/scale);

    int y=0,ly=0;
    for(int i=1;i<=lonG*1201;i++)
    {
        if(i%scale==0)
            ly++;
        for(int j=1;j<=linG*1201;j++)
        {
            fscanf(img,"%d %d %d", &a,&b,&c);

            if(i%scale ==0 && j%scale == 0)
            {
                y++;

                fprintf(imgS, "%d %d %d\n",a,b,c);
            }
        }
    }
    fclose(imgS);
    fclose(img);
}

void drawImage()
{
    setLon();
    setLin();
    fillFile();
    drawS();
}

void setLon()
{
    if(left_lon_sing=='S'  && right_lon_sing=='S')
    {
        for(int i=left_lon;i>=right_lon;i--)
            vis_lon_S[i]=true;
        lonG=left_lon-right_lon + 1;
    }
    else if(left_lon_sing=='S'  && right_lon_sing=='N')
    {
        for(int i=left_lon;i>0;i--)
            vis_lon_S[i]=true;
        for(int i=0;i<=right_lon;i++)
            vis_lon_N[i]=true;

        lonG=left_lon+right_lon+1;
    }
    else
    {
        for(int i=left_lon;i<=right_lon;i++)
            vis_lon_N[i]=true;
        lonG=right_lon-left_lon+1;
    }
}

void setLin(){
    if(left_lin_sing=='W'  && right_lin_sing=='W')
    {
        for(int i=left_lin;i>=right_lin;i--)
            vis_lin_W[i]=true;
        linG=left_lin-right_lin + 1;
    }
    else if(left_lin_sing=='W'  && right_lin_sing=='E')
    {
        for(int i=left_lin;i>0;i--)
            vis_lin_W[i]=true;
        for(int i=0;i<=right_lin;i++)
            vis_lin_E[i]=true;
        linG=left_lin+right_lin+1;
    }
    else
    {
        for(int i=left_lin;i<=right_lin;i++)
            vis_lin_E[i]=true;
         linG=right_lin-left_lin+1;
    }
}


char *setFilesNames(char lon_sing[2],char lin_sing[2],int i,int j)
{
    char imgImageName[100];
    char tmp_lon[100],tmp_lin[100];

    memset(imgImageName, 0, sizeof(imgImageName));
    memset(tmp_lon, 0, sizeof(tmp_lon));
    memset(tmp_lin, 0, sizeof(tmp_lin));
    sprintf (tmp_lon, "%d", i);
    sprintf (tmp_lin, "%d", j);
    strcat(imgImageName,lon_sing);
    if(i<10)
        strcat(imgImageName,"0");
    strcat(imgImageName,tmp_lon);
    strcat(imgImageName,lin_sing);
    if(j<10)
        strcat(imgImageName,"00");
    else if(j<100)
        strcat(imgImageName,"0");
    strcat(imgImageName,tmp_lin);
    strcat(imgImageName,".hgt");
    char *c = imgImageName;
    return c;
}

int findColor(int num)
{
    int returnVal=0;
    for(int i=0;i<rgbTableSize;i++)
    {
        if(colorsTable[i].x > num)
        {
            returnVal=colorsTable[i].idx;
            break;
        }
    }
    return returnVal;
}

int  unzip(char nameS[200],char nameF[200])
{
    char name[200];
    memset(name, 0, sizeof(name));
    strcat(name,nameS);
    strcat(name,nameF);
    strcat(name,".zip -P hgt");
    printf("%s\n",name);
    int x = system(name);
    if(x == 0)
    {
        char name2[200];
        memset(name2, 0, sizeof(name2));
        strcat(name2,"unzip hgt/");
        strcat(name2,nameF);
        strcat(name2, ".zip");
        strcat(name2," -d hgt");
        printf("%s\n",name2);
        system(name2);
    }
    return x;
}

void saveImage(char tab[400][300],int tab_size,FILE *image)
{

    FILE *fp[tab_size+10];
    for(int i=0;i<tab_size;i++)
    {
        char tabName[200];
        memset(tabName, 0, sizeof(tabName));
        strcat(tabName,"hgt/");
        strcat(tabName,tab[i]);
        fp[i]=fopen(tabName, "rb");
        if(fp[i] == NULL)
        {
            int x=-1;
            x = unzip("wget https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/Eurasia/",tab[i]);
            if(x != 0)
            {
                 x =unzip("wget https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/Australia/",tab[i]);
            }
            if(x != 0)
            {
               x =  unzip("wget https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/Africa/",tab[i]);
            }
            if(x != 0)
            {
               x =  unzip("wget https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/Islands/",tab[i]);
            }
            if(x != 0)
            {
               x =  unzip("wget  https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/North_America/",tab[i]);
            }
            if(x != 0)
            {
               x =  unzip("wget  https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/South_America/",tab[i]);
            }
            if(x != 0)
            {
                fclose(img);
                return;
            }
        }
        fp[i]=fopen(tabName, "rb");
    }
    for(int y=0;y<1201;y++)
    {
       for(int i=0;i<tab_size;i++)
       {
           for(int j=0;j<1201;j++)
           {
                unsigned char data[2];
                fread(data,sizeof(char),2,fp[i]);
                short num = data[1]|(data[0]<<8);
                if(num<0)
                    num=0;
                int idx = findColor(num);
                fprintf(image, "%d %d %d\n",rgbTable[idx][0],rgbTable[idx][1],rgbTable[idx][2]);
           }
       }

    }
    for(int i=0;i<tab_size;i++)
    {
        fclose(fp[i]);
    }
}

void fillFile()
{
    char name[200];
    memset(name, 0, sizeof(name));
    strcat(name,nameOfFile);
    strcat(name,".ppm");
    img = fopen(name, "w");
    fprintf(img, "P3\n%d %d\n 255\n", linG*1201,lonG*1201);
    for(int i=180;i>=0;i--)
    {
        int t=0;
        char imgImageName[400][300];
        for(int j=180;j>0;j--)
        {
            if(vis_lon_N[i] == true && vis_lin_W[j] == true )
            {
                memset(imgImageName[t], 0, sizeof(imgImageName[t]));
                strcat(imgImageName[t],setFilesNames("N","W",i,j));
                t++;
            }
        }
        for(int j=0;j<180;j++)
        {
            if(vis_lon_N[i] == true && vis_lin_E[j] == true ){
                memset(imgImageName[t], 0, sizeof(imgImageName[t]));
                strcat(imgImageName[t],setFilesNames("N","E",i,j));
                t++;
            }
        }
        if(vis_lon_N[i] == true)
        {
            saveImage(imgImageName,t,img);
        }
    }

    for(int i=0;i<=180;i++)
    {
        int t=0;
        char imgImageName[400][300];
        for(int j=180;j>0;j--)
        {
            if(vis_lon_S[i] == true && vis_lin_W[j] == true )
            {
                memset(imgImageName[t], 0, sizeof(imgImageName[t]));
                strcat(imgImageName[t],setFilesNames("S","W",i,j));
                t++;
            }
        }
        for(int j=0;j<180;j++)
        {
            if(vis_lon_S[i] == true && vis_lin_E[j] == true )
            {
                memset(imgImageName[t], 0, sizeof(imgImageName[t]));
                strcat(imgImageName[t],setFilesNames("S","E",i,j));
                t++;
            }
        }
        if(vis_lon_S[i] == true)
        {
            saveImage(imgImageName,t,img);
        }
    }
}
