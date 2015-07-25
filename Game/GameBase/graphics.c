#include <allegro5/allegro.h>

int main()

{
	int x;
	install_timer();                           /* required for `rest' */
	circlefill (screen, 0, 100, 5, 15);        /* draw first time */
	for (x = 1; x < 320; x++) {               /* loop across the screen */
    rest (10);                             /* slow it down */
    circlefill (screen, x - 1, 100, 5, 0); /* erase from last place */
    circlefill (screen, x, 100, 5, 15);    /* redraw at new place */
}

}
