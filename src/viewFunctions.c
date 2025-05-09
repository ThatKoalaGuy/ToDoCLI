#include "../include/todo.h"

int viewMode()
{
    int keyPressed;

    system("cls");
    printf("---------- ToDo app ----------\n");
    printList();
    printf("------------------------------\n");
    printf("Press 'E' to edit\n");
    printf("Press 'Del' to delete the whole list\n");
    printf("Press 'ESC' to exit the program\n");

    while (true)
    {
        if (_kbhit())
        {
            // Get the pressed key
            keyPressed = _getch();

            // If key is E
            if (keyPressed == KEY_E)
            {
                editMode();
                break;
            }
            // If key is delete
            else if (GetAsyncKeyState(KEY_DEL))
            {
                deleteList();
                break;
            }
            // If key is ESC
            if (keyPressed == KEY_ESC)
            {
                system("cls");
                return 0;
            }
        }
    }

    return 0;
}

void terminalRedraw()
{
    system("cls");
    printf("-------------- ToDo app ---------------\n");
    printList();
    printf("---------------------------------------\n");
    printf("ESC - save & exit\n");
}

int printList()
{
    gp_file = fopen(g_fileName, "r");
    if (gp_file == NULL)
    {
        perror("Failed to open the file for reading");
        return 1;
    }

    // Iterate over every char and output it
    char ch;
    while ((ch = fgetc(gp_file)) != EOF)
    {
        putchar(ch);
    }

    fclose(gp_file);

    return 0;
}