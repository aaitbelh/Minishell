#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>


void rl_replace_line(char *str, int i);

void handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


int main()
{
	int i;
	char *str;
	struct sigaction sa;

	sa.sa_handler = &handler;

	sigaction(SIGINT, &sa, NULL);
	while(1)
	{
		str = readline("test$: ");
		if(!str)
			break;	
	}
}