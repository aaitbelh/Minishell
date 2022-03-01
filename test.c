#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

int main()
{
	int i;
	char *str;
	while(1)
	{
		str = readline("test$: ");
		printf("%s\n", str);
		rl_redisplay();
		if(!str)
			break ;
	}
}