#include <stdio.h>
#include <allegro5/allegro.h>
#include <errno.h>
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

typedef struct{
	ALLEGRO_BITMAP *body;
	int bouncerSize;
   float bouncer_x;
   float bouncer_y;
   float bouncer_dx;
   float bouncer_dy;
} Bouncer;

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n",msg, strerror(errno));
	exit(1);
}

void initBouncer(Bouncer* b, int bouncerSize,float sizeW, float sizeH)
{	
	/*b->body = al_create_bitmap(sizeW*sizeW, sizeH*sizeH);
	if(!(b->body))
	{
		error("no bitmap");		
	}
	 */
	b->bouncerSize = bouncerSize;
	  
	b->bouncer_x = SCREEN_W / sizeW - b->bouncerSize / sizeW;
	b->bouncer_y = SCREEN_H / sizeH - b->bouncerSize / sizeH;
	if(!b->bouncer_x||!b->bouncer_y)
	error("no coords");
	
	b->bouncer_dx = rand()%(int)(sizeW*10);
	b->bouncer_dy = rand()%(int)(sizeH*10);
	if(!b->bouncer_dx||!b->bouncer_dy)
	error("no coords");
	
	return;
}

void moveBouncer(Bouncer* b)
{
	if(b->bouncer_x < 0 || b->bouncer_x > SCREEN_W - b->bouncerSize) {
            b->bouncer_dx = -b->bouncer_dx;
         }
 
	if(b->bouncer_y < 0 || b->bouncer_y > SCREEN_H - b->bouncerSize) {
			b->bouncer_dy = -b->bouncer_dy;
		}

	b->bouncer_x += b->bouncer_dx;
	b->bouncer_y += b->bouncer_dy;
	
	return;
}

void moveMain(Bouncer* b, bool* key)
{
		if(key[KEY_UP] && b->bouncer_y >= 4.0) {
            b->bouncer_y -= 4.0;
         }
 
         if(key[KEY_DOWN] && b->bouncer_y <= SCREEN_H - b->bouncerSize - 4.0) {
            b->bouncer_y += 4.0;
         }
 
         if(key[KEY_LEFT] && b->bouncer_x >= 4.0) {
            b->bouncer_x -= 4.0;
         }
 
         if(key[KEY_RIGHT] && b->bouncer_x <= SCREEN_W - b->bouncerSize - 4.0) {
            b->bouncer_x += 4.0;
         }
         
         return;
 }
/*


typedef struct {
float sx;//The direction it's pointing
float sy;//Where it is on the screen
float heading;
float speed;
int gone;//Is it dead?
ALLEGRO_COLOR color;
} Spaceship;

void initSpaceship()
{
	Spaceship* s;
	s->sx=1;
	s->sy=1;
	s->heading = 1;
	s->speed = 1;
	s->gone =0;
	return;
}

void drawSpaceship(Spaceship* s)
{	
	al_draw_line(-8, 9, 0, -11, s->color, 3.0f);
	al_draw_line(0, -11, 8, 9, s->color, 3.0f);
	al_draw_line(-6, 4, -1, 4, s->color, 3.0f);
	al_draw_line(6, 4, 1, 4, s->color, 3.0f);

	return;
}
*/

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   //ALLEGRO_BITMAP *bouncer = NULL;
   
   Bouncer bouncer={NULL,0,0,0,0,0};
   
   Bouncer bouncer1={NULL,0,0,0,0,0};
   Bouncer bouncer2={NULL,0,0,0,0,0};
   //
   
   //float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   //float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   
   initBouncer(&bouncer,32,2.0,2.0);
   initBouncer(&bouncer1,16,3.0,1.0);
   initBouncer(&bouncer2,8, 5.0,3.0);
   
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
 	
 	if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
   
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
   bouncer.body = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer.body) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
    bouncer1.body = al_create_bitmap(BOUNCER_SIZE/3.0, BOUNCER_SIZE/3.0);
   if(!bouncer1.body) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
      bouncer2.body = al_create_bitmap(BOUNCER_SIZE/5.0, BOUNCER_SIZE/5.0);
   if(!bouncer2.body) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   al_set_target_bitmap(bouncer.body);
 
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
 
   al_set_target_bitmap(bouncer1.body);
 
   al_clear_to_color(al_map_rgb(0, 0, 255));
   
   
   al_set_target_bitmap(bouncer2.body);
 
   al_clear_to_color(al_map_rgb(255, 0, 0));
   
   
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer.body);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 	al_register_event_source(event_queue, al_get_mouse_event_source());
 	
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
 
   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
        moveMain(&bouncer, key);
 		moveBouncer(&bouncer1);
 		moveBouncer(&bouncer2);
 		
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;
 
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
 
         bouncer.bouncer_x = ev.mouse.x;
         bouncer.bouncer_y = ev.mouse.y;
      }
 	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
          break;
      }
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));
 
        al_draw_bitmap(bouncer.body, bouncer.bouncer_x, bouncer.bouncer_y, 0);
 		al_draw_bitmap(bouncer1.body, bouncer1.bouncer_x, bouncer1.bouncer_y, 1);
 		al_draw_bitmap(bouncer2.body, bouncer2.bouncer_x, bouncer2.bouncer_y, 0);
 
         al_flip_display();
      }
   }
 
   al_destroy_bitmap(bouncer.body);
   al_destroy_bitmap(bouncer1.body);
   al_destroy_bitmap(bouncer2.body);
   
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

