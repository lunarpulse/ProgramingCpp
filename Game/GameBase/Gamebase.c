#include <allegro5/allegro.h>
#include "game.h"

int end_game;

int main(void)
{
	allegro_init();
	init();
	
	end_game =0;
	do{
		input();
		process();
		output();
		
	}while(end_game ==0);

	shutdown();
	allegro_exit();
	
	return 0;

}
