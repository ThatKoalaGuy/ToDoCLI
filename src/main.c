#include "../include/todo.h"

int main()
{
    // Check if file exist and if not create it
    if (access(g_fileName, F_OK))
    {
        gp_file = fopen(g_fileName, "w");
        fclose(gp_file);
    }

    viewMode();

    return 0;
}
