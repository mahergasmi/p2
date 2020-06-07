#ifndef ENNEMI_H_INCLUDED
#define ENNEMI_H_INCLUDED
#include<SDL/SDL.h>
/**
*@brief to get the state of the ennemy
*/
typedef enum STATE STATE;
enum STATE {waiting,following,attacking};
/**
*@struct ennemi
*@brief struct for the ennemy
*/
struct Ennemi
{
int direction,num,at,aff,mort;
STATE etat_ennemi;
SDL_Surface *warning;
SDL_Rect pos;
SDL_Surface *e[10];
SDL_Surface *attaque[10];

};
typedef struct Ennemi ennemi;
/**
*@brief to initalize the ennemy
*@param ennemy
*/
void init_ennemi(ennemi *enn);
/**
*@brief to get the state of the ennemy: waiting/following/attacking
*@param ennemy
*@param hero position
*/
void etat_ennemi(ennemi *enn,SDL_Rect poshero);
/**
*@brief to blit the image of the ennemy
*@param the screen 
*@param ennemy
*@param hero position
*/
void afficher_ennemi(SDL_Surface *ecran,ennemi *enn,SDL_Rect poshero);
/**
*@brief to mouve the ennemy
*@param ennemy
*@param hero position
*/
void deplacement_ennemi(ennemi *enn,SDL_Rect poshero);
/**
*@brief to animate the ennemy: get state+mouvement+blit
*@param the screen
*@param ennemy
*@param hero position
*/
void animer_ennemi(SDL_Surface *ecran,ennemi *enn,SDL_Rect poshero);
/**
*@brief to free the ennemy
*@param ennemy
*/
void free_ennemi(ennemi *enn);




#endif
