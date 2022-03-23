#include <stdio.h>
#include <unistd.h>
int main(int ac , char **av, char **ev)
{
    char *s[2] = {"-c 10", NULL};
    execve("/usr/bin/head",s, ev);
}