#include <unistd.h>
#include <stdio.h>
#include <errno.h>
int main(int ac , char **av, char **env)
{
	char *path;
	int ch = chdir(NULL);
	if(ch < 0)
		printf("unseccess work\n");
	else
		printf("succsecc work\n");
	path = getcwd(NULL, 0);
	printf("%s", path);

}