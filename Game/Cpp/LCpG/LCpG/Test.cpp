#include <allegro5/allegro.h>
int x = 10;
int y = 10;

int main(){
 
 	ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *membitmap, *bitmap;
    ALLEGRO_TIMER *timer;

    if (!al_init()) {
       abort_example("Could not init Allegro.\n");
    }
    
    al_install_keyboard();
    display = al_create_display(640, 480);
    if (!display) {
       abort_example("Error creating display\n");
    }
    
    while ( !key[KEY_ESC] ){
    
        clear_keybuf();
        
        acquire_screen();
        
        textout_ex( screen, font, " ", x, y, makecol( 0, 0, 0), makecol( 0, 0, 0) );
        
        if (key[KEY_UP]) --y;        
        else if (key[KEY_DOWN]) ++y;    
        else if (key[KEY_RIGHT]) ++x;
        else if (key[KEY_LEFT]) --x;

        textout_ex( screen, font, "@", x, y, makecol( 255, 0, 0), makecol( 0, 0, 0) );
        
        release_screen();
        
        rest(50);

    }    
    
    return 0;
    
}   
END_OF_MAIN(); 
