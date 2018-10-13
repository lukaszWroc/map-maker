#ifndef DISPLAY_WINDOWS_H

#define DISPLAY_WINDOWS_H
#include <string.h>
#include <gtk/gtk.h>

#include<stdio.h>
#include"image.h"
#include"colors.h"
#define ROWS 256
#define COLUMNS 2
GtkWidget *mainWindow;
GtkWidget *mainContainer;
GtkWidget *showResultButton;
GtkWidget *colorButtons[3];
GtkWidget *rgbEntry[3];
GtkWidget *colorMenuWindow;
GtkWidget *colorMenuButtons[250];
GtkWidget *colorMenuTable;
GtkWidget *entryNameFile;
GtkEntry *mainEntry[4];
GtkEntry *entry[250];
void setColors();
void addNewColor(int R,int G,int B);
void displayWindows(int argc,char *argv[]);
void displayColorMenu();
void startDrawing();
void newColor();
void setValue();
void add(int x,int r ,int g,int b);
void showImage();
bool validateInput();
#endif // DISPLAY_WINDOWS_H
