#include "../include/todo.h"
#include <sys/stat.h> // For mkdir
#include <direct.h>   // For _mkdir on Windows

// Define the global variables
FILE *gp_file = NULL;
char *g_fileName = NULL;

int main()
{
    // Create the "todoAppData" folder if it doesn't exist
    if (_mkdir("todoAppData") == -1 && errno != EEXIST)
    {
        perror("Failed to create todoAppData folder");
        return 1;
    }

    // Update the global file name to include the folder path
    g_fileName = "todoAppData/ToDoList.txt";

    // Check if the file exists, and if not, create it
    if (access(g_fileName, F_OK))
    {
        gp_file = fopen(g_fileName, "w");
        if (gp_file == NULL)
        {
            perror("Failed to create ToDoList.txt");
            return 1;
        }
        fclose(gp_file);
    }

    viewMode();

    return 0;
}
