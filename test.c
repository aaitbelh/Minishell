#include <stdio.h>
#include <unistd.h>
int main(int ac , char **av, char **ev)
{
    char *str[5] = {"rm ", "file", "file2", "file3", NULL};
    execve("/bin/rm", str, ev);
}