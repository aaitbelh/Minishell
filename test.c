#include <unistd.h>
#include <stdio.h>
#include <errno.h>
int main()
{
	char path[256];
	int ch = chdir("..");
	if(ch < 0)
		printf("unseccess work\n");
	else
		printf("succsecc work\n");
	if(getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd() error");
		return 10;
	}
	printf("%s", path);
}