#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_interrupt(int sig)
{
	puts("\n\tfarewell the cruel world");
	exit(1);
}
void terminal_size(int sig)
{
	puts("\n\tTerminal size changed");
	return;
}

int catch_signal(int sig, void (*handler)(int))
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction(sig, &action, NULL);
}

int main()
{
	if(catch_signal(SIGINT, handle_interrupt) == -1)
	{
		fprintf(stderr, "Can't map the handler1");
		exit(2);
	}
	
	if(catch_signal(SIGWINCH, terminal_size) == -1)
	{
		fprintf(stderr, "Can't map the handler2");
		exit(2);
	}
	
	char name[30];
	printf("What is your name?");
	fgets(name,30, stdin);
	printf("Hello %s\n", name);
	return 0;
	
}