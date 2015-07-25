#include <stdio.h>
#include <string.h>

char tracks[][80]={
"I left my heart in Harvard Med school",
"NewYack, NewWark - a wonderful town",
"Dancing with a Dock",
"From here to Maternity",
"The girl from Iwo Jima"};

void find_track(char search_for[])
{
int i;
for (i = 0; i<5; i++)
	{
		if (strstr(tracks[i], search_for))
		{
			printf("Track %i: '%s'\n", i+1, tracks[i]);
			break;
		}
		/*else
		{
			printf("'%s' was not found in any of the song list\n", search_for);
		}*/
	}
}

int main()
{
char search_for[80];
char temp[80];
printf("search_for: ");
fgets(temp, 80, stdin);
strtok(temp,"\n");
strcpy(search_for, temp);

find_track(search_for);


return 0;
}