#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int geo2json(void)
{
	float latitude;
float longitude;
char info[80];
int started = 0;

puts("data=[");
while (scanf("%f, %f, %79[^\n]", &latitude, &longitude, info)==3)
{
	if(started)
		printf(",\n");
	else
		started = 1;
		
	if(latitude<-90 || latitude >90)
		{
		fprintf(stderr,"Invalid latitude: %f\n", latitude);
		return 2;
		}
	if(longitude<-180||longitude >180)
		{
		fprintf(stderr,"Invalid longitude: %f\n", longitude);
		return 2;
		}
		
	printf("{latitude: %f, longitude: %f, info: '%s'}",latitude, longitude, info);
	}
	puts("\n]");
	return 0;
}

int topSecret()
{
	char word[10];
	int i =0;
	while (scanf("%9s", word) ==1)
	{
		i++;
		if(i%2)
			fprintf(stdout,"%s\n", word);
		else
			fprintf(stderr, "%s\n", word);
			
	}
	
	return 0;
}

int multifile(void)
{
	char line [80];
	FILE *in  = fopen("spooky.csv", "r");
	FILE *file1 = fopen("ufos.csv", "w");
	FILE *file2 = fopen("disapperances.csv", "w");
	FILE *file3 = fopen("others.csv", "w");
	
	while(fscanf(in, "%79[^\n]\n", line) ==1)
	{
		if(strstr(line, "UFO"))
			fprintf(file1, "%s\n", line);
		else if (strstr(line, "Disappearance"))
			fprintf(file2, "%s\n", line);
		else
			fprintf(file3, "%s\n", line);
	}
	fclose(file1);
	fclose(file2);
	fclose(file3);
	
	return 0;
}


int main(int argc, char *argv[])
{
	//geo2json();
	//topSecret();
	//multifile();
	char line[80];
	if(argc!= 6)
	{
		fprintf(stderr,"You need to provide 5 arguements!\n");
		return 1;
	}
	
	FILE *in  = fopen("spooky.csv", "r");
	FILE *file1 = fopen(argv[2], "w");
	FILE *file2 = fopen(argv[4], "w");
	FILE *file3 = fopen(argv[5], "w");
	
	while(fscanf(in, "%79[^\n]\n", line)==1)
	{
	if(strstr(line, argv[1]))
			fprintf(file1, "%s\n", line);
		else if (strstr(line, argv[3]))
			fprintf(file2, "%s\n", line);
		else
			fprintf(file3, "%s\n", line);
	}
	fclose(file1);
	fclose(file2);
	fclose(file3);
	
	return 0;
}
