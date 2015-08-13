#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	char *feeds[]= {"http://www.cnn.com/rss/celebs.xml","http://www.rollingstones.com/rock.xml"
				,"http://www.eonline.com/gossip.xml"};
				
	int times =3;
	char *phrase = argv[1];
	int i;
	
	for(i=0; i<times; i++){
		char var[255];
		sprintf(var, "RSS_FEED=%s", feeds[i]);
		char *vars[] ={var, NULL};
//		if(execle("/usr/bin/python", "/usr/bin/python","./rssgossip.py", phrase, NULL, vars )==-1){
//		fprintf(stderr, "Can't run script: %s\n", strerror(errno));
//		return 1;
//		}


		pid_t pid = fork();
		if(pid ==-1)
		{
			fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
			return 1;
		}
		
		if(!pid)
		{
			if(execle("/home/lunarpulse/Documents/vsCodeRepo/HFC/RssReader", "/home/lunarpulse/Documents/vsCodeRepo/HFC/RssReader","./rssgossip.py", phrase, NULL, vars )==-1)
			{
			fprintf(stderr, "Can't run script: %s\n", strerror(errno));
			return 1;
			}
		}
	}
	return 0;
}
