// I honestly don't really remember exactly what this is for, I just remember needing to do it in other projects when including in seperate files I think. I'm an awful programmer
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.h>

struct entity{
    sfVector2f pos;
    sfVector2f vel;
    sfVector2f size; // Will probably need to change this to something else if I ever decide to make things not just simple boxes
    sfColor color;
    
    void (*draw)(struct entity*, sfRenderWindow*, sfRectangleShape*); // Function pointer to the function to draw the entity
    void (*update)(struct entity*, double); // Function pointer to the function to update the entity (Probably should be called every frame)
};

// Creates an entity
struct entity* createEntity(float sizeX, float sizeY, float posX, float posY, float velX, float velY, sfColor color, void* drawFunc, void* updateFunc);
struct entity* createEntityVector2f(sfVector2f size, sfVector2f pos, sfVector2f vel, sfColor color, void* drawFunc, void* updateFunc);

// Removes all entities
void removeAllEntities();

//  Sets values to an entity
void entSetPos(struct entity* ent, float x, float y);
void entSetVel(struct entity* ent, float x, float y);
void entSetSize(struct entity* ent, float x, float y);

// Linked list for every entity
struct entListNode{
    struct entity* ent;
    struct entListNode* next;
    struct entListNode* prev;
};
extern struct entListNode* entListHead;
extern struct entListNode* entListCurrent;
extern struct entListNode* entListTail;

// Pushes an entity to the linked list
void pushToEntityList(struct entity* ent);
// Removes an entity from the linked list
void removeFromEntityList(struct entity* ent);

#endif
