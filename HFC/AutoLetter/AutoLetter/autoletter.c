#include <stdio.h>
#include <stdarg.h>

enum response_type{DUMP, SECOND_CHANCE, MARRIAGE, LAW_SUIT};
typedef struct{
	char* name;
	enum response_type type;
} response;

void dump(response r)
{
	printf("Dear %s, \n", r.name);
	puts("Unfortunately your last date contacted us to");
	puts("say that they will not be seeing you again");
	}

void second_chance(response r)
{
	printf("Dear %s, \n", r.name);
	puts("Good news: your last date has asked us to");
	puts("arrange another meeting. Please call ASAP");
	}

void marriage(response r)
{
	printf("Dear %s, \n", r.name);
	puts("Congratulations! Your last date has contacted");
	puts("us with a proposal of marriage.");
	}

void law_suit(response r)
{
	printf("Dear %s, \n", r.name);
	puts("Caution! Your last date has accused you of");
	puts("us for insult.");
}

enum drink{
	MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE
};

double price (enum drink d)
{
	switch(d){
	case MUDSLIDE:
		return 6.79;
	case FUZZY_NAVEL:
		return 5.31;
	case MONKEY_GLAND:
		return 4.82;
	case ZOMBIE:
		return 5.89;
	}
	return 0;
}
		
double total (int args, ...)
{
	double total=0.0;
	va_list ap;
	
	va_start(ap, args);
	int i;
	
	for(i=0; i<args; i++)
	{
		enum drink d = va_arg(ap, enum drink);
		
		total+= price(d);
		//printf("argument: %i\n", va_arg(ap, int));
	
	}
	
	va_end(ap);
	
	return total;
	
}

void (*replies[])(response) ={dump, second_chance, marriage,law_suit};

int main()
{
	response r[] = {{"Mike",DUMP}, {"Luis",SECOND_CHANCE},{"Will",MARRIAGE},{"Maat", SECOND_CHANCE}, {"Ian", LAW_SUIT}};
	
	int i;
	
	for(i=0; i<5; i++)
	{
//		switch(r[i].type)
//		{
//			case DUMP:
//				dump(r[i]);
//				break;
//			case SECOND_CHANCE:
//				second_chance(r[i]);
//				break;
//			default:
//				marriage(r[i]);
//				break;
//				
//			
//		}

		(*replies[r[i].type])(r[i]);
		
		
	}
	
	printf("Price is %.2f\n", total(3, MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND));
	printf("Price is %.2f\n", total(3, ZOMBIE, FUZZY_NAVEL, MONKEY_GLAND));
	printf("Price is %.2f\n", total(3, MUDSLIDE, MUDSLIDE, MONKEY_GLAND));
	printf("Price is %.2f\n", total(4, MONKEY_GLAND, MONKEY_GLAND, MONKEY_GLAND,MONKEY_GLAND));
	return 0;
}
