#include"display_windows.h"

void displayColorMenu()
{
    gtk_widget_show_all(colorMenuWindow);
}

void showImage()
{
    GtkWidget *imageWindow;
    GtkWidget *image;

    imageWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(imageWindow), "Pomniejszony obraz");
    gtk_window_set_resizable(GTK_WINDOW(imageWindow), FALSE);
    char name[200];
    memset(name, 0, sizeof(name));
    strcat(name,nameOfFile);
    strcat(name,"_scaled.ppm");
    image = gtk_image_new_from_file(name);
    gtk_container_add(GTK_CONTAINER(imageWindow), image);

    g_signal_connect_swapped(G_OBJECT(imageWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_widget_show_all(imageWindow);
}
void add(int x,int r,int g,int b)
{
    if(x==2)
    {
        addColor(r,g,b);
        rgbTable[rgbTableSize][3]=colorsT-1;
        rgbTable[rgbTableSize][0]=r;
        rgbTable[rgbTableSize][1]=g;
        rgbTable[rgbTableSize][2]=b;
        return;
    }
    GtkEntry *tmp1[3];
    gchar *tmp2[3];
    for(int i=0;i<3;i++){
        tmp1[i]=GTK_ENTRY(rgbEntry[i]);
        tmp2[i]=gtk_entry_get_text(tmp1[i]);
    }
    r=atoi(tmp2[0]);
    g=atoi(tmp2[1]);
    b=atoi(tmp2[2]);
    addColor(r,g,b);
   if(x==1)
    {
        rgbTable[rgbTableSize][0]=r;
        rgbTable[rgbTableSize][1]=g;
        rgbTable[rgbTableSize][2]=b;
        rgbTable[rgbTableSize][3]=colorsT-1;
    }
}
void addNewColor(int R,int G,int B)
{
    if(R >= 0)
    {
        add(2,R,G,B);
    }
    else
    {
        add(1,0,0,0);
    }
    int i=colorsT-1;
    colorMenuButtons[rgbTableSize] = gtk_button_new();
    gtk_widget_set_size_request (colorMenuButtons[rgbTableSize],40,30);
    gtk_table_attach(GTK_TABLE(colorMenuTable),colorMenuButtons[rgbTableSize],
                     0,1,rgbTableSize,rgbTableSize+1,GTK_FILL,GTK_FILL,10,10);
    char colorName[100]="colors/color";
    char str[100];
    sprintf (str, "%d", rgbTable[rgbTableSize][3]);
    strcat(colorName, str);
    strcat(colorName, ".ppm");
    GtkWidget *image = gtk_image_new_from_file(colorName);
    gtk_button_set_image (GTK_BUTTON(colorMenuButtons[rgbTableSize]),image);
    entry[rgbTableSize]=gtk_entry_new();
    gtk_widget_set_size_request ( entry[rgbTableSize],90,30);
    gtk_table_attach(GTK_TABLE(colorMenuTable),entry[rgbTableSize],
                     1,2,rgbTableSize,rgbTableSize+1,GTK_FILL,GTK_FILL,10,10);
    rgbTableSize++;
    gtk_widget_show_all(colorMenuWindow);
}
void newColor()
{
    addNewColor(-1,-1,-1);
}
void checkColor()
{
    add(0,0,0,0);
    char colorName[100]="colors/color";
    char str[100];
    sprintf (str, "%d", colorsT-1);
    strcat(colorName, str);
    strcat(colorName, ".ppm");
    GtkWidget *image = gtk_image_new_from_file(colorName);
    gtk_button_set_image (GTK_BUTTON(colorButtons[1]),image);

}

void setValue(int idx,int *val,char *sing)
{
    GtkEntry *tmp1 = GTK_ENTRY(mainEntry[idx]);
    gchar *tmp2 = gtk_entry_get_text(tmp1);
    char tmp3[200];
    memset(tmp3, 0, sizeof(tmp3));
    strcat(tmp3,tmp2);
    int tmp3T=0;
    while(tmp3[tmp3T] !='\0')
    {
        if(tmp3[tmp3T] == 'N' || tmp3[tmp3T] == 'S' || tmp3[tmp3T] == 'W' || tmp3[tmp3T] == 'E')
        {
            *sing = tmp3[tmp3T];
            break;
        }
        tmp3T++;
    }
    int tmp4T=0;
    char tmp4[200];
    while(tmp3[tmp3T] !='\0')
    {
        if('0' <= tmp3[tmp3T] && tmp3[tmp3T] <= '9')
        {
            tmp4[tmp4T++]=tmp3[tmp3T];
        }
        tmp3T++;
    }
    *val = atoi(tmp4);
}

void setColors()
{
    for(int i=0;i<rgbTableSize;i++)
    {
        for(int j=1;j<rgbTableSize;j++)
        {
            if(colorsTable[i-1].x > colorsTable[i].x)
            {
                colorStruct tmp;
                tmp = colorsTable[i];
                colorsTable[i]=colorsTable[i-1];
                colorsTable[i-1]=tmp;
            }
        }
    }
}

bool validateInput(int _cnt)
{
    if(strcmp((char*)"", nameOfFile) == 0)
        return false;
    if(_cnt == 0)
        return false;
    if(left_lin_sing != 'E' && left_lin_sing != 'W')
        return false;
    if(right_lin_sing != 'E' && right_lin_sing != 'W')
        return false;
    if(left_lon_sing != 'N' && left_lon_sing != 'S')
        return false;
    if(right_lon_sing != 'N' && right_lon_sing != 'S')
        return false;
    return true;
}

void startDrawing()
{
    GtkEntry *tp1 = GTK_ENTRY(entryNameFile);
    gchar *tp2 = gtk_entry_get_text(tp1);
    strcat(nameOfFile, tp2);

    int cnt=0;
    for(int i=0;i<rgbTableSize;i++)
    {
        GtkEntry *tmp1 = GTK_ENTRY(entry[i]);
        gchar *tmp2 = gtk_entry_get_text(tmp1);
        int a=atoi(tmp2);
        if(a==0 && tmp2[0] != '0')
            a=-1;
        else
            cnt++;
        colorsTable[i].x=a;
        colorsTable[i].idx=i;
    }
    setColors();
    setValue(0,&left_lon,&left_lon_sing);
    setValue(1,&left_lin,&left_lin_sing);
    setValue(2,&right_lon,&right_lon_sing);
    setValue(3,&right_lin,&right_lin_sing);
    if(!validateInput(cnt))
       return;
    drawImage();
    gtk_box_pack_start(GTK_BOX(mainContainer),showResultButton,TRUE,TRUE,0);
    gtk_widget_show_all(mainWindow);
}

void displayWindows(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    mainWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect( mainWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_window_set_default_size(mainWindow,400,500);

    mainContainer = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(mainWindow),mainContainer);

    GtkWidget *mainTable;
    mainTable = gtk_table_new(4,4,FALSE);
    GtkWidget *lable[4];


    lable[1]= gtk_label_new("Podaj dlugolsc lewego dolnego rogu: ");
    lable[0]= gtk_label_new("Podaj szerokosc lewego dolnego rogu: ");
    lable[3]= gtk_label_new("Podaj dlugolsc prawego gornego rogu: ");
    lable[2]= gtk_label_new("Podaj szerokosc prawego gornego rogu: ");
    gtk_box_pack_start(GTK_BOX(mainContainer),mainTable,TRUE,TRUE,0);
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<2;j++)
        {
            mainEntry[i]= gtk_entry_new ();
            gtk_table_attach(GTK_TABLE(mainTable),lable[i],j,j+1,i,i+1,
                             GTK_EXPAND,GTK_EXPAND,10,10);
            j++;
            gtk_table_attach(GTK_TABLE(mainTable),mainEntry[i],j,j+1,i,i+1,
                             GTK_EXPAND,GTK_EXPAND,10,10);
        }
    }


    GtkWidget *colorLabel;
    colorLabel = gtk_label_new("Podaj kolor w formacie RGB (Liczby od 0 do 255)");

    GtkWidget *rgbLabel[3];
    GtkWidget *rgbTable;
    rgbTable = gtk_table_new(6,2,FALSE);
    rgbLabel[0] = gtk_label_new("R: ");
    rgbLabel[1] = gtk_label_new("G: ");
    rgbLabel[2] = gtk_label_new("B: ");

    for (int i=0;i<3;i++)
    {
        rgbEntry[i]= gtk_entry_new ();
        gtk_table_attach(GTK_TABLE(rgbTable),rgbLabel[i],0,1,i,i+1,GTK_EXPAND,GTK_EXPAND,0,7);
        gtk_table_attach(GTK_TABLE(rgbTable),rgbEntry[i],1,2,i,i+1,GTK_EXPAND,GTK_EXPAND,0,7);
    }
    GtkWidget *colorTable;
    colorTable = gtk_table_new(3,3,FALSE);
    colorButtons[0] = gtk_button_new_with_label("Sprawdz kolor");
    colorButtons[1] = gtk_button_new();
    colorButtons[2] = gtk_button_new_with_label("Dodaj kolor");

    for (int i=0;i<3;i++)
    {
        gtk_widget_set_size_request (colorButtons[i],130,30);
        gtk_table_attach(GTK_TABLE(colorTable),colorButtons[i],i,i+1,0,1,GTK_EXPAND,GTK_EXPAND,0,0);
    }

    GtkWidget *nameFile;

    nameFile = gtk_label_new("Podaj nazwe pliku do ktorego zostanie zapisany obraz: ");
    entryNameFile = gtk_entry_new();
    GtkWidget *nameTable;
    nameTable = gtk_table_new(2,1,FALSE);
    gtk_table_attach(GTK_TABLE(nameTable),nameFile,0,1,0,1,GTK_EXPAND,GTK_EXPAND,0,0);
    gtk_table_attach(GTK_TABLE(nameTable),entryNameFile,1,2,0,1,GTK_EXPAND,GTK_EXPAND,0,0);

    GtkWidget *startButton;
    startButton = gtk_button_new_with_label("Start");

    showResultButton = gtk_button_new_with_label("Pokaz pomniejszony obraz");


    gtk_box_pack_start(GTK_BOX(mainContainer),colorLabel,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(mainContainer),rgbTable,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(mainContainer),colorTable,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(mainContainer),nameTable,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(mainContainer),startButton,TRUE,TRUE,0);

    gtk_widget_show_all(mainWindow);
    g_signal_connect_after(startButton,"clicked",G_CALLBACK(startDrawing),NULL);


    g_signal_connect_after( showResultButton, "clicked", G_CALLBACK(showImage), NULL);

    colorMenuWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position (colorMenuWindow,GTK_WIN_POS_CENTER);



    g_signal_connect(colorMenuWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_default_size(colorMenuWindow,200,500);

    GtkWidget *colorMenuContainer;
    colorMenuContainer = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(colorMenuWindow),colorMenuContainer);



    GtkWidget *scrolledWindow;

    scrolledWindow = gtk_scrolled_window_new( NULL, NULL );
    gtk_box_pack_start(GTK_BOX(colorMenuContainer),scrolledWindow,TRUE,TRUE,0);
    colorMenuTable=gtk_table_new(ROWS,COLUMNS,FALSE);

    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledWindow),colorMenuTable);
    g_signal_connect_after(colorButtons[2], "clicked", G_CALLBACK(newColor),NULL);
    g_signal_connect_after(colorButtons[0], "clicked", G_CALLBACK(checkColor),NULL);
    addNewColor(0,127,255);
    addNewColor(16,112,16);
    addNewColor(19,140,19);
    addNewColor(254,254,51);
    addNewColor(255,165,0);
    addNewColor(128,0,0);
    displayColorMenu();
    gtk_widget_show_all(colorMenuWindow);
    gtk_main ();
}
