#include "../include/todo.h"

int deleteList()
{
    system("cls");
    printf("----------------------------------- ToDo app -----------------------------------\n");
    printf("\n");
    printf("********************************************************************************\n");
    printf("***                                                                          ***\n");
    printf("***    Do you really want to delete the list? THIS ACTION IS IRREVERSIBLE    ***\n");
    printf("***                                                                          ***\n");
    printf("********************************************************************************\n");
    printf("\n");
    printf("ESC - cancel\n");
    printf("Del - delete\n");

    int keyPressed;

    // Wait because else it triggers automaticaly because of the Del key pressed for the editMode()
    Sleep(100);
    while (true)
    {
        if (_kbhit())
        {
            keyPressed = _getch();

            // ESC pressed
            if (keyPressed == KEY_ESC)
            {
                break;
            }
            // Delete pressed
            else if (GetAsyncKeyState(KEY_DEL))
            {
                gp_file = fopen(g_fileName, "w");
                if (gp_file == NULL)
                {
                    perror("Failed to open the file for writing");
                    return 1; // Handle error
                }
                fclose(gp_file);

                system("cls");
                printf("LIST DELETED");
                Sleep(2000);
                break;
            }
        }
    }

    viewMode();

    return 0;
}
