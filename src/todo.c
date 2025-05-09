#include "../include/todo.h"

FILE *gp_file;
char *g_fileName = "ToDoList.txt";

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

int editMode()
{

    size_t i = 0;

    gp_file = fopen(g_fileName, "r");
    if (gp_file == NULL)
    {
        perror("Failed to open the file for reading");
        return 1;
    }

    // Count the existing lines
    char ch;
    while ((ch = fgetc(gp_file)) != EOF)
    {
        if (ch == '\n')
        {
            i++;
        }
    }
    fclose(gp_file);

    terminalRedraw();

    int keyPressed;

    char *userInput = malloc(150 * sizeof(char));
    if (userInput == NULL)
    {
        perror("Memory allocation failed.\n");
        return 1;
    }

    userInput[0] = '\0'; // Initialize userInput buffer

    while (true)
    {
        keyPressed = _getch();

        // If ESC is pressed, exit the loop
        if (keyPressed == KEY_ESC)
        {
            break;
        }
        // If Backspace is pressed
        else if (keyPressed == KEY_BACKSPACE)
        {
            size_t len = strlen(userInput);
            if (len > 0)
            {
                // Remove the last character from userInput
                userInput[len - 1] = '\0';

                // Move the cursor back and overwrite the character with a space
                printf("\b \b");
            }
        }
        else if (keyPressed == '\r') // Handle Enter key
        {
            // Process the input when Enter is pressed
            i++;

            char *numberedInput = malloc(150 * sizeof(char));
            if (numberedInput == NULL)
            {
                perror("Memory allocation failed.\n");
                return 1;
            }

            // Format the input with a line number
            snprintf(numberedInput, 149, "%zu. %s\n", i, userInput);

            // Write the input to the file
            gp_file = fopen(g_fileName, "a");
            if (gp_file == NULL)
            {
                perror("Failed to open the file for appending");
                return 1;
            }

            fprintf(gp_file, "%s", numberedInput);
            fclose(gp_file);

            terminalRedraw();

            free(numberedInput);

            // Clear the userInput buffer for the next input
            userInput[0] = '\0';
        }
        else
        {
            // Append the character to userInput
            size_t len = strlen(userInput);
            if (len < 149) // Ensure we don't exceed the buffer size
            {
                userInput[len] = keyPressed;
                userInput[len + 1] = '\0';

                // Print the character to the screen
                printf("%c", keyPressed);
            }
        }
    }

    free(userInput);

    viewMode();

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
