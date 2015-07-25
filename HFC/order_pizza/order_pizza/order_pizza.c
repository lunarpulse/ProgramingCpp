#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,  char *argv[])
{
	char *delivery = "";
	int thick =0;
	int count =0;
	char ch;
	FILE *file1 = fopen("PizzaOrder.csv", "w");
	
	while((ch = getopt(argc, argv, "d:t")) !=EOF)
		switch(ch){
		case 'd':
		delivery =optarg;
		break;
		
		case 't':
		thick =1;
		break;
		
	default:
		fprintf(stderr, "unknown option: '%s'\n", optarg);
		
		return 1;
		}
		
		argc-=optind;
		argv+= optind;
		
		if(thick)
		{
			puts("Thick crust.");
			fprintf(file1, "%s\n", "Thick crust.");
		}	
		if(delivery[0])
		{
			printf("To be delivered %s. \n", delivery);
			fprintf(file1, "%s\n", "To be delivered %s. \n",);
		}
			
		puts("Ingredients:");
		fprintf(file1, "%s\n", "Ingredients:");
		
		for(count =0; count < argc; count ++)
		{
			puts (argv[count]);
			fprintf(file1, "%s\n", argv[count]);
		}
			
		fclose(file1);
		return 0;
		
	}
	

