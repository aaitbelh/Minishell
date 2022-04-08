#include <unistd.h>
int main(int ac , char **av, char **env)
{
	char *str[2] = {"/Users/aaitbelh/Desktop/minishelaal", NULL};
	if(execve(str[0], str, NULL) == -1)
	{
		perror(NULL);
	}
}