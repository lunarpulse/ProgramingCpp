// The great retro GameLoop!
// 02/10/2013
 
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
 
int global_screen_w = 1366;
int global_screen_h = 768;
 
ALLEGRO_TIMER *init_timer(double fps);
void destroy_timer(ALLEGRO_TIMER *t);
ALLEGRO_DISPLAY *init_display(int rx, int ry);
void destroy_display(ALLEGRO_DISPLAY *d);
bool init_primitives();
bool init_keyboard();
ALLEGRO_EVENT_QUEUE *init_events();
void destroy_events(ALLEGRO_EVENT_QUEUE *q);
ALLEGRO_BITMAP *init_backbuffer(int x, int y);
void destroy_backbuffer(ALLEGRO_BITMAP *bb);
ALLEGRO_FONT *init_font(char *filename, int size);
 
int main(void) {
    const double FPS = 60;
    const int SCREEN_RES_WIDTH=1366;
    const int SCREEN_RES_HEIGHT=768;
    const int STARS_NUM = 200;
    bool quit = false;
    bool redraw = true;
    double old_time = 0.0;
    double new_time = 0.0;
    double fps = 0.0;
    int start_x, start_y, start_size;
 
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *gfx_buffer = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *ttf_font;
 
    int num_errors = 0;
        // Initialise all Allegro stuff we're going to use.
    if (!al_init()) {
        fprintf(stderr, "INIT: Failed to initialize game library.\n");
        num_errors++;
    } else {
        fprintf(stdout, "ACK: Game library initialised.\n");
    }
        // Create the Allegro timer for locking the FPS.
    timer = init_timer(FPS);
    if (!timer) {
        num_errors++;
    } else {
        fprintf(stdout, "ACK: Game timer created.\n");
    }
        // Create the display with the desired resolution. 
    display = init_display(SCREEN_RES_WIDTH, SCREEN_RES_HEIGHT);
    if (!display) {
        num_errors++;
    } else {
        fprintf(stdout, "ACK: Display created.\n");
    }
        // Initialise the Allegro Primitives add-on.
    if (!init_primitives()) {
        num_errors++;
    } else {
        fprintf(stdout, "ACK: Primitives initialised.\n");
    }   
        // Initialise the keyboard for input.
    if (!init_keyboard()) {
        num_errors++;
    } else {
        fprintf(stdout, "ACK: Keyboard input initialised.\n");
    }
        // Initialise the Allegro event queue. 
    event_queue = init_events();
    if (!event_queue) {
        num_errors++;
    } else {
        fprintf(stdout, "ACK: Event queue created.\n");
    }
        // Create a bitmap the same resolution as the screen to act as our
        // off screen buffer for drawing.
    gfx_buffer = init_backbuffer(global_screen_w, global_screen_h);
    if (!gfx_buffer) {
        num_errors++;
    }
        // Load our TrueType font from the current directory with size of 20.
    ttf_font = init_font("Ubuntu-C.ttf", 20);
    if (!ttf_font) {
        num_errors++;
    }
        // If there were any initialisation errors, destroy everything 
        // and quit.
    if (num_errors > 0) {
        destroy_timer(timer);
        destroy_display(display);
        destroy_events(event_queue);
        destroy_backbuffer(gfx_buffer);
        return -1;
    } else {
                // Initialisation was good. Register Allegro events.
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_set_target_bitmap(gfx_buffer);
        al_set_target_bitmap(al_get_backbuffer(display));
        al_flip_display();
        al_start_timer(timer);
    }
 
        // YOUR INTIALISATION CODE HERE.
 
    redraw = true;
    old_time = al_get_time();
    al_hide_mouse_cursor(display);
         
        // Start of game loop here.
    while (!quit) {
        new_time = al_get_time();
        fps = 1.0 / (new_time - old_time);
        old_time = new_time;
 
                // YOUR UPDATE CODE HERE.
 
        if (redraw) {
                        // Time to redraw. Draw everything to the back buffer.
            al_set_target_bitmap(gfx_buffer);
            al_clear_to_color(al_map_rgb(1,1,25));
 
		al_clear_to_color(5);
                        // YOUR RENDERING CODE HERE.                        
 
            al_draw_textf(ttf_font,al_map_rgb(255,255,0), 16, 16,0,"FPS: %.1f",fps);
            al_set_target_backbuffer(display);
            al_draw_bitmap(gfx_buffer,0,0,0);
            al_flip_display();
            redraw = false;
        }
        while (1) {
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue , &ev);
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                quit = true;
                break;
            } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
 
                                redraw = true;
                                break;
                                // YOUR INPUT CODE HERE. 
 
                if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    quit = true;
                    break;
                }
            }
            if (al_is_event_queue_empty(event_queue)) {
                redraw = false;
                break;
            }
        }
    }
 
        // DESTROY YOUR GAME RESOURCES HERE.
 
    al_show_mouse_cursor(display);  
    destroy_timer(timer);
    destroy_display(display);
    destroy_events(event_queue);
    return 0;
}
 
ALLEGRO_TIMER *init_timer(double fps) {
    struct ALLEGRO_TIMER *t =  malloc(sizeof(t));
    t = al_create_timer(1.0 / fps);
    if (!t) {
        fprintf(stderr, "INIT: Failed to create timer.\n");
        return NULL;
    }
    return t;
}
 
void destroy_timer(ALLEGRO_TIMER *t) {
    if (t != NULL) {
        al_destroy_timer(t);
        t = NULL;
        fprintf(stdout, "ACK: Game timer destroyed.\n");
    }
}
 
ALLEGRO_DISPLAY *init_display(int rx, int ry) {
    struct ALLEGRO_DISPLAY *d = malloc(sizeof(d));
    d = al_create_display(rx, ry);
    if (!d) {
        fprintf(stderr, "INIT: Failed to create display.\n");
        return NULL;
    } else {
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_FULLSCREEN_WINDOW);
        global_screen_w = al_get_display_width(d);
        global_screen_h = al_get_display_height(d);
        al_toggle_display_flag(d, ALLEGRO_FULLSCREEN_WINDOW, true);
    }
    return d;
}
 
void destroy_display(ALLEGRO_DISPLAY *d) {
    if (d != NULL) {
        al_destroy_display(d);
        d = NULL;
        fprintf(stdout, "ACK: Display destroyed\n");
    }
}
 
bool init_primitives() {
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "INIT: Failed to initiialise primitives addon\n");
        return false;
    } else {
        return true;
    }
}
 
bool init_keyboard() {
    if (!al_install_keyboard()) {
        fprintf(stderr, "INIT: Failed to initialise the keyboard\n");
        return false;
    } else {
        return true;
    }
}
 
ALLEGRO_EVENT_QUEUE *init_events() {
    ALLEGRO_EVENT_QUEUE *e = al_create_event_queue();
    if (!e) {
        fprintf(stderr, "INIT: Failed to create event queue.\n");
        e = NULL;
    }
    return e;
}
 
void destroy_events(ALLEGRO_EVENT_QUEUE *e) {
    if (e != NULL) {
        al_destroy_event_queue(e);
        e = NULL;
        fprintf(stdout, "ACK: Event queue destroyed.\n");
    }
}
 
ALLEGRO_BITMAP *init_backbuffer(int x, int y) {
    ALLEGRO_BITMAP *bb = al_create_bitmap(x, y);
    if (!bb) {
        fprintf(stderr, "INIT: Failed to create offscreen buffer of %ix%i\n", x, y);
    } else {
        if (!(al_get_bitmap_flags(bb) & ALLEGRO_VIDEO_BITMAP)) {
            fprintf(stderr, "INIT: Offscreen buffer is not a video bitmap!\n");
            bb = NULL;
        }
    }
    return bb;
}
 
void destroy_backbuffer(ALLEGRO_BITMAP *bb) {
    if (bb != NULL) {
        al_destroy_bitmap(bb);
        bb = NULL;
        fprintf(stdout, "ACK: Offscreen buffer destroyed.\n");
    }
}
 
ALLEGRO_FONT *init_font(char *filename, int size) {
    ALLEGRO_FONT *font;
    al_init_font_addon();
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "INIT: Failed to initialise the TTF font addon.\n");
        font = NULL;
    } else {
        font = al_load_ttf_font(filename, size, 0);
        if (!font) {
            fprintf(stderr, "INIT: Failed to load font '%s'.\n", filename);
            font = NULL;
        }
    }
    return font;
}
