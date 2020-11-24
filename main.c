#include <SFML/Graphics.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600


// Could probably make these #defines but whatever this might be more readable
// Actually why am I not just setting each thing manually, isn't it just a struct
void setSfRectPos(float posX, float posY, sfRectangleShape* rect){
    sfVector2f pos = {posX, posY};
    sfRectangleShape_setPosition(rect, pos);
}

void setSfRectSize(float sizeX, float sizeY, sfRectangleShape* rect){
    sfVector2f size = {sizeX, sizeY};
    sfRectangleShape_setSize(rect, size);
}

void setSfRectOrigin(float originX, float originY, sfRectangleShape* rect){
    sfVector2f origin = {originX, originY};
    sfRectangleShape_setPosition(rect, origin);
}

// idk if i really even need this i just am getting tired of constantly typing out every single thing in like 5 different lines and making singular sfVector2fs just to make a single box
// Also I should probably fix the name eventually, it can be confused with sfRectangleShape_create
sfRectangleShape* createSfRect(float sizeX, float sizeY, float posX, float posY, float originX, float originY, sfColor color){
    sfRectangleShape* rect = sfRectangleShape_create();
    
    setSfRectSize(sizeX, sizeY, rect);
    setSfRectOrigin(originX, originY, rect);
    setSfRectPos(posX, posY, rect);
    sfRectangleShape_setFillColor(rect, color);
    
    return rect;
}
 
int main() {
    sfVideoMode mode = {WINDOWWIDTH, WINDOWHEIGHT, 32};
    sfRenderWindow* window;
    sfRectangleShape* rect1;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    
    rect1 = createSfRect(50, 50, WINDOWWIDTH/2, WINDOWHEIGHT/2, 25, 25, sfWhite);
 
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
 
        sfRenderWindow_drawRectangleShape(window, rect1, NULL);
 
        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfRectangleShape_destroy(rect1);
    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}
