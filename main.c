#include <SFML/Graphics.h>
#include "entity.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

// Function to draw the player entity
void drawPlayer(struct entity* ent, sfRenderWindow* window, sfRectangleShape* rect){
    // Just very simple for now
    sfRectangleShape_setPosition(rect, ent->pos);
    sfRectangleShape_setSize(rect, ent->size);
    sfRectangleShape_setFillColor(rect, ent->color);
    
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
}

// Function to update the player
void updatePlayer(struct entity* ent){
    ent->pos.x += ent->vel.x;
    ent->pos.y += ent->vel.y;
    
    // Boundary check
    if(ent->pos.x < 0){
        ent->pos.x = 0;
    }
    if(ent->pos.x > WINDOWWIDTH){
        ent->pos.x = WINDOWWIDTH;
    }
    if(ent->pos.y < 0){
        ent->pos.y = 0;
    }
    if(ent->pos.y > WINDOWHEIGHT){
        ent->pos.y = WINDOWHEIGHT;
    }
}
 
int main() {
    sfVideoMode mode = {WINDOWWIDTH, WINDOWHEIGHT, 32};
    sfRenderWindow* window;
    sfRectangleShape* rect;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    
    rect = sfRectangleShape_create();
    struct entity* player = createEntity(/*Size*/ 50, 50, /*Pos*/ WINDOWWIDTH/2, WINDOWHEIGHT/2, /*Vel*/ 0, 0, /*Color*/ sfWhite, drawPlayer, updatePlayer);
    
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event)) {
            switch(event.type){
                case sfEvtClosed:
                    sfRenderWindow_close(window);
                    break;
                case sfEvtKeyPressed:
                    switch(event.key.code){
                        case sfKeyEscape:
                            sfRenderWindow_close(window);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        
        // Check for keys that are held
        // I should probably eventually make something that handles all input or something because having input split across this and the events system just feels like I'm doing something wrong
        // Also having each key hard coded also feels wrong, could probably at least make something like a #define that just makes INPUT_LEFT be sfKeyA or something
        if(sfRenderWindow_hasFocus(window)){
            // Input stuff goes here (I honestly don't care enough to put some default stuff here right now)
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);
 
        //sfRenderWindow_drawRectangleShape(window, rect, NULL);
        //drawEntity(window, rect, player);
        //(*player->draw)(player, window, rect);
        for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
            (*entListCurrent->ent->draw)(entListCurrent->ent, window, rect);
            (*entListCurrent->ent->update)(entListCurrent->ent);
        }
 
        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfRectangleShape_destroy(rect);
    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}
