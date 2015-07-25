//The spaceship will be able to fire its cannon at passing asteroids, so you will need code to draw
//and move a cannon blast across the screen.

#include <allegro5/allegro.h>
typedef struct {
float sx;
float sy;
float heading;
float speed;
int gone;
ALLEGRO_COLOR color;
} Blast;