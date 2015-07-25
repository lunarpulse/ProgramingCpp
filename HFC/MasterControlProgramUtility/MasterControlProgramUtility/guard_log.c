#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* now()
{
	time_t t;
	time (&t);
	return asctime(localtime (&t));
	}
	
	/* Master COntrol Program Utility.
	records guard patrol check-ins.*/
	
	int main()
	{
	char comment [80];
	char cmd[20];
	
	fgets(comment, 80, stdin);
	sprintf(cmd,"echo '%s %s' >>reports.log", comment, now());
	system(cmd);
	
	char *my_env[] = {"JUICE=peach and apple", NULL};
	
	execle("dinner_info","dinner_info", "4", NULL, my_env);
	puts("Dude - the diner_info code must be busted");
	return 0;
	}
