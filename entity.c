#include "entity.h" 
#include <stdlib.h>
#include <stdio.h>

// Linked list stuff

struct entListNode* entListHead = NULL;
struct entListNode* entListTail = NULL;
struct entListNode* entListCurrent= NULL;

void pushToEntityList(struct entity* ent){
    // If not already initialized, set the head of the list to the given entity
    if(entListHead == NULL){
        printf("Initializing entity list\n");
        entListHead = (struct entListNode*) malloc(sizeof(struct entListNode));
        entListTail = entListHead;
        entListHead->ent = ent;
        entListHead->next = NULL;
        entListHead->prev = NULL;
        entListCurrent = entListHead;
    } else {
        printf("Pushing entity at %p to list\n", ent);
        entListCurrent = entListTail;
        entListCurrent->next = (struct entListNode*) malloc(sizeof(struct entListNode));
        entListCurrent->next->ent = ent;
        entListCurrent->next->next = NULL;
        entListCurrent->next->prev = entListCurrent;
        entListTail = entListCurrent->next;
    }
    printf("Entity %p pushed to list to node %p\n", ent, entListCurrent);
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
// Might be better to just do the same thing SFML does and just have functions to set everything seperately so you dont have super long function calls
struct entity* createEntity(float sizeX, float sizeY, float posX, float posY, float velY, float velX, sfColor color, void* drawFunc, void* updateFunc){
    struct entity* ent = (struct entity*) malloc(sizeof(struct entity));
    
    entSetSize(ent, sizeX, sizeY);
    entSetPos(ent, posX, posY);
    entSetVel(ent, velX, velY);
    
    ent->color = color;
    
    ent->draw   = drawFunc;
    ent->update = updateFunc;
    
    pushToEntityList(ent);
    
    return ent;
}

// Creates an entity, but uses sfVector2fs
// Pretty much just making this for when I can use vector2fs that are already made (Like other entities I guess, but I could probably just make a function that copies the attributes of the entity to be copied onto another)
struct entity* createEntityVector2f(sfVector2f size, sfVector2f pos, sfVector2f vel, sfColor color, void* drawFunc, void* updateFunc){
    struct entity* ent = (struct entity*) malloc(sizeof(struct entity));
    
    ent->size   = size;
    ent->pos    = pos;
    ent->vel    = vel;
    
    ent->color  = color;
    
    ent->draw   = drawFunc;
    ent->update = updateFunc;
    
    return ent;
}


// Removes all entities
void removeAllEntities(){
    struct entListNode* next = entListHead->next;
    for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = next){
        next = entListCurrent->next;
        printf("Freeing entity %p\n", entListCurrent->ent);
        free(entListCurrent->ent);
        free(entListCurrent);
        printf("Done\n");
    }
    return;
}
