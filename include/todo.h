#ifndef TODO_H
#define TODO_H

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

#define KEY_ESC 27
#define KEY_E 101
#define KEY_DEL VK_DELETE
#define KEY_BACKSPACE 8

// Global variables
extern FILE *gp_file;
extern char *g_fileName;

// Function declarations
int viewMode();
int editMode();
void terminalRedraw();
int printList();
int deleteList();

#endif