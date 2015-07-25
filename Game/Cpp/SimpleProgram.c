#include <allegro5/allegro.h>
int x = 10;
int y = 10;

int main(){
 
    allegro_init();
    install_keyboard();
    set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0);
    
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