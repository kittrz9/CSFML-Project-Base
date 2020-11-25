#include "entity.h" 
#include <stdlib.h>
#include <stdio.h>

// Sets the attributes to an entity

void entSetPos(struct entity* ent, float x, float y){
    ent->pos.x = x;
    ent->pos.y = y;
    return;
}
void entSetVel(struct entity* ent, float x, float y){
    ent->vel.x = x;
    ent->vel.y = y;
    return;
}
void entSetSize(struct entity* ent, float x, float y){
    ent->size.x = x;
    ent->size.y = y;
    return;
}

// Creates an entity
struct entity* createEntity(float sizeX, float sizeY, float posX, float posY, float velY, float velX, sfColor color){
    struct entity* ent = (struct entity*) malloc(sizeof(struct entity));
    
    entSetSize(ent, sizeX, sizeY);
    entSetPos(ent, posX, posY);
    entSetVel(ent, velX, velY);
    
    ent->color = color;
    
    return ent;
}

// Creates an entity, but uses sfVector2fs
// Pretty much just making this for when I can use vector2fs that are already made (Like other entities I guess, but I could probably just make a function that copies the attributes of the entity to be copied onto another)
struct entity* createEntityVector2f(sfVector2f size, sfVector2f pos, sfVector2f vel, sfColor color){
    struct entity* ent = (struct entity*) malloc(sizeof(struct entity));
    
    //entSetSize(ent, sizeX, sizeY);
    ent->size = size;
    //entSetPos(ent, posX, posY);
    ent->pos = pos;
    //entSetVel(ent, velX, velY);
    ent->vel = vel;
    
    ent->color = color;
    
    return ent;
}

// Draws an entity
void drawEntity(sfRenderWindow* window, sfRectangleShape* rect, struct entity* ent) {
    sfRectangleShape_setPosition(rect, ent->pos);
    sfRectangleShape_setSize(rect, ent->size);
    sfRectangleShape_setFillColor(rect, ent->color);
    
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
}

// Linked list stuff

struct entListNode* entListHead = NULL;
struct entListNode* entListTail = NULL;
struct entListNode* entListCurrent= NULL;

void pushToEntityList(struct entity* ent){
    // If not already initialized, set the head of the list to the given entity
    if(entListHead == NULL){
        entListHead = (struct entListNode*) malloc(sizeof(struct entListNode));
        entListTail = entListHead;
        entListHead->ent = ent;
        entListHead->next = NULL;
        entListHead->prev = NULL;
    } else {
        entListCurrent = entListTail;
        entListCurrent->next = (struct entListNode*) malloc(sizeof(struct entListNode));
        entListCurrent->next->ent = ent;
        entListCurrent->next->next = NULL;
        entListCurrent->next->prev = entListCurrent;
        entListTail = entListCurrent->next;
    }
}


// Loop through the entity list and remove the one specified from the list and free it's memory
void removeFromEntityList(struct entity* ent){
    for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
        if(entListCurrent->ent == ent){
            printf("Freeing entity %p\n", entListCurrent->ent);
            entListCurrent->prev->next = entListCurrent->next;
            free(entListCurrent->ent);
            free(entListCurrent);
            printf("Done\n");
            return; /* Shouldn't need to keep going through the list if the entity has already been found */
        }
    }
}
