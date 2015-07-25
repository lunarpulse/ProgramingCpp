//A file containing all of the source code to roid and display the latest position of an aste .
#include <allegro5/allegro.h>
typedef struct {
	float sx;
	float sy;
	float heading;
	float speed;
	int gone;
	ALLEGRO_COLOR color;
} Spaceship;