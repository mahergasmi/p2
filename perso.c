#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
#include "perso.h"
#include"scrolling.h"
#include"ennemi.h"
#include"collisionbb.h"
#include"minimap.h"
#include"collisionpp.h"
#include"fc.h"
#include"object.h"
void init_perso(perso *p,vie *v)
{
   int i;
   p->devant=1;
   p->arriere=0;
   p->cache=0;
   p->attaquer=0;
   p->pos.x=0;
   p->pos.y=467;
   v->num=0;
   v->pos.x=0;
   v->pos.y=0;
   p->score=0;
   p->posscore.x=0;
   p->posscore.y=0;
   p->debout=NULL;
   p->texte=NULL;
   p->police=NULL;
   for(i=0;i<9;i++)
	{
	    p->marche_dev[i]=NULL;
	}

   for(i=0;i<9;i++)
	{
	    p->marche_arr[i]=NULL;
	}
   for(i=0;i<7;i++)
	{
	    p->cacher[i]=NULL;
	}
   for(i=0;i<26;i++)
	{
	    p->attaque_droite[i]=NULL;
	}
   for(i=0;i<8;i++)
	{
	    p->attaque_gauche[i]=NULL;
	}
   for(i=0;i<5;i++)
	{
	    v->vi[i]=NULL;
	}
}

void load_perso(perso *p,vie *v)
{
   int i;
   char nom_image[60],ch[10];
   SDL_Color couleur={0,255,0};
   for(i=0;i<9;i++)
	{   
	    sprintf(nom_image,"../GAME/characters/hero1/md%d.png",i+1);
	    p->marche_dev[i]=IMG_Load(nom_image);
	}
   for(i=0;i<9;i++)
	{   
	    sprintf(nom_image,"../GAME/characters/hero1/ma%d.png",i+1);
	    p->marche_arr[i]=IMG_Load(nom_image);
	}
   for(i=0;i<7;i++)
	{   
	    sprintf(nom_image,"../GAME/characters/hero1/cache%d.png",i+1);
	    p->cacher[i]=IMG_Load(nom_image);
	}
   for(i=0;i<26;i++)
	{   
	    sprintf(nom_image,"../GAME/characters/hero1/attaqued%d.png",i+1);
	    p->attaque_droite[i]=IMG_Load(nom_image);
	}
   for(i=0;i<8;i++)
	{   
	    sprintf(nom_image,"../GAME/characters/hero1/attaqueg%d.png",i+1);
	    p->attaque_gauche[i]=IMG_Load(nom_image);
	}
   for(i=0;i<5;i++)
	{
	    sprintf(nom_image,"../GAME/characters/vie/vie%d.png",i+1);
	    v->vi[i]=IMG_Load(nom_image);
	}
   p->police=TTF_OpenFont("../GAME/font/labo.ttf",60);
   sprintf(ch,"Score: %d",p->score);
   p->texte=TTF_RenderText_Blended(p->police,ch,couleur);
}

void blit_debout(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{

if((p->attaquer==0)&&(p->cache==0))
{
   if(p->devant==1)
         p->debout=IMG_Load("../GAME/characters/hero1/we9ef.png");
   if(p->arriere==1)
         p->debout=IMG_Load("../GAME/characters/hero1/we9efa.png");

   fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
   SDL_BlitSurface(p->debout,NULL,ecran,&p->pos);
   SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
   SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
   SDL_Flip(ecran);
}else {
if(p->cache==1) {
		   fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
		   SDL_BlitSurface(p->cacher[6],NULL,ecran,&p->pos);
	           SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
    		   SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
    		   SDL_Flip(ecran);
                }
                     
if(p->attaquer==1)
      {
        if(p->devant==1)
        {
        fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
	SDL_BlitSurface(p->attaque_droite[7],NULL,ecran,&p->pos);
	SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
        SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
        SDL_Flip(ecran);
        }
	if(p->arriere==1)
        {
        fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
	SDL_BlitSurface(p->attaque_gauche[7],NULL,ecran,&p->pos);
	SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
        SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
        SDL_Flip(ecran);
        }
      }
      }
}
void blit_marche_perso(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,int d,int g,int h,int jump,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{ 
   int i; 
   if(p->devant==1) {
		      for(i=0;i<4;i++)
	                { 
                           fonctions_jeux2(ecran,camera,fond,d,g,h,jump,enn,texte_temps,pos_temps,minimap,&p->pos,obj);
			   if((p->pos.x<590)&&(h==0))  p->pos.x=p->pos.x+10;
			   if((p->pos.x<590)&&(h==1))  p->pos.x=p->pos.x+17;
	    		   SDL_BlitSurface(p->marche_dev[i],NULL,ecran,&p->pos);
                           SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
			   SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
                           SDL_Flip(ecran);
	                }
		      }

   if(p->arriere==1) {
		      for(i=0;i<4;i++)
	                {
                           fonctions_jeux2(ecran,camera,fond,d,g,h,jump,enn,texte_temps,pos_temps,minimap,&p->pos,obj);
			   if((p->pos.x>10)&&(h==0))   p->pos.x=p->pos.x-10;
                           if((p->pos.x>10)&&(h==1))   p->pos.x=p->pos.x-17;
	    		   SDL_BlitSurface(p->marche_arr[i],NULL,ecran,&p->pos);
                           SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
                           SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
                           SDL_Flip(ecran);
	                }
		     }
}
void blit_cacher(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{

   int i;
   for(i=0;i<7;i++)
   {  
      fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
      SDL_BlitSurface(p->cacher[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);
   }		      
}

void blit_plus_cacher(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{
   int i;
   for(i=6;i>=0;i--)
   {  
      fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
      SDL_BlitSurface(p->cacher[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);
   }
}

void charger_attaque(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{
   int i;
if(p->devant==1)
{
   for(i=0;i<8;i++)
   {  
      fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
      SDL_BlitSurface(p->attaque_droite[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);
   }
}
if(p->arriere==1)
{
   for(i=0;i<8;i++)
   {  
      fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
      SDL_BlitSurface(p->attaque_gauche[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);
   }
}

}

void decharger_attaque(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{
   int i;
if(p->devant==1)
{
   for(i=7;i>=0;i--)
   {  
      fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
      SDL_BlitSurface(p->attaque_droite[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);
   }
}
if(p->arriere==1)
{
   for(i=7;i>=0;i--)
   {  
      fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
      SDL_BlitSurface(p->attaque_gauche[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);
   }
}
}

void blit_attaquer(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{

   int i;
   SDL_Color couleur={0,255,0};
   char ch[10];
if(p->devant==1)
{
   for(i=8;i<26;i++)
   {  
      fonctions_jeux1(ecran,camera,fond,enn,texte_temps,pos_temps,minimap,p->pos,obj);
      SDL_BlitSurface(p->attaque_droite[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);

      if((collision_attaque(p,enn)==1)&&(i>=15)&&(enn->mort==0))
                                     {
                                        enn->aff=0;
					enn->mort=1;
                                        p->score+=30;
					sprintf(ch,"Score: %d",p->score);
                                        p->texte=TTF_RenderText_Blended(p->police,ch,couleur);
				     }
   }
}
}

void deplacer_attaque(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,int d,int g,int h,int jump,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{
   if(p->devant)
   {
   fonctions_jeux2(ecran,camera,fond,d,g,h,jump,enn,texte_temps,pos_temps,minimap,&p->pos,obj);
   if(p->pos.x<590) p->pos.x=p->pos.x+10;
   SDL_BlitSurface(p->attaque_droite[7],NULL,ecran,&p->pos);
   SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
   SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
   SDL_Flip(ecran);
   }
  
   if(p->arriere==1)
   {
   fonctions_jeux2(ecran,camera,fond,d,g,h,jump,enn,texte_temps,pos_temps,minimap,&p->pos,obj);
   if(p->pos.x>10) p->pos.x=p->pos.x-10;
   SDL_BlitSurface(p->attaque_gauche[7],NULL,ecran,&p->pos);
   SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
   SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
   SDL_Flip(ecran);
   }
}
void animation_jeu(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v,int d,int g,int b,int a,int espace,int h,int jump,ennemi *enn,SDL_Surface *texte_temps,SDL_Rect pos_temps,mini *minimap,OBJECT *obj)
{
   if(d==1)  {
                           if(p->cache==1)
			   blit_plus_cacher(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
                           if(p->attaquer==1)
			   {
                               if((p->devant==0)&&(p->arriere==1))
                               {
                                  p->devant=1;p->arriere=0;
                                  charger_attaque(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
                               }

                               p->devant=1;p->arriere=0;
                               deplacer_attaque(ecran,camera,fond,p,v,d,g,h,jump,enn,texte_temps,pos_temps,minimap,obj);
                              
			   }else
				{
				   p->devant=1;p->arriere=0;p->cache=0;p->attaquer=0;
				   blit_marche_perso(ecran,camera,fond,p,v,d,g,h,jump,enn,texte_temps,pos_temps,minimap,obj);
			        }
             }

   if(g==1)   {
                           if(p->cache==1)
			   blit_plus_cacher(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
                           if(p->attaquer==1)
			   {
                               if((p->devant==1)&&(p->arriere==0))
                               {
                                  p->devant=0;p->arriere=1;
                                  charger_attaque(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
                               }
                               p->devant=0;p->arriere=1;
                               deplacer_attaque(ecran,camera,fond,p,v,d,g,h,jump,enn,texte_temps,pos_temps,minimap,obj);
                               
			   }else
				{
				   p->arriere=1;p->devant=0;p->cache=0;p->attaquer=0;
				   blit_marche_perso(ecran,camera,fond,p,v,d,g,h,jump,enn,texte_temps,pos_temps,minimap,obj);
			        }
               }

   if(b==1)   {
		p->cache=1;p->attaquer=0;
		blit_cacher(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
              }

   if(a==1)   {
		if(p->attaquer==1)
		{
		decharger_attaque(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
		p->attaquer=0;p->cache=0;
		}else
		{ 
		charger_attaque(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
		p->attaquer=1;p->cache=0;
		}
              }

   if(espace==1)   {
		      if(p->attaquer==1)
		      blit_attaquer(ecran,camera,fond,p,v,enn,texte_temps,pos_temps,minimap,obj);
                   }

}
void fin_jeu_animation(SDL_Surface *ecran,SDL_Rect *camera,SDL_Surface *fond,perso *p,vie *v)
{
   int i;
   char nom_image[30];
   SDL_Surface *fin[9];
   for(i=0;i<9;i++)
   {
      fin[i]=NULL;
   }
   for(i=0;i<9;i++)
   {
	    sprintf(nom_image,"../GAME/characters/hero1/fin%d.png",i+1);
	    fin[i]=IMG_Load(nom_image);
   }
   for(i=0;i<9;i++)
   {  
      SDL_BlitSurface(fond,camera,ecran,NULL);
      SDL_BlitSurface(fin[i],NULL,ecran,&p->pos);
      SDL_BlitSurface(p->texte,NULL,ecran,&p->posscore);
      SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);
      SDL_Flip(ecran);
   }
   for(i=0;i<9;i++)
   {
      SDL_FreeSurface(fin[i]);
   }
}

void free_perso(perso *p,vie *v)
{
   int i;
   TTF_CloseFont(p->police);
   for(i=0;i<9;i++)
   {
      SDL_FreeSurface(p->marche_dev[i]);
      SDL_FreeSurface(p->marche_arr[i]);
   }
   for(i=0;i<7;i++)
   {
      SDL_FreeSurface(p->cacher[i]);
   }
   for(i=0;i<26;i++)
   {
      SDL_FreeSurface(p->attaque_droite[i]);
   }
   for(i=0;i<8;i++)
   {
      SDL_FreeSurface(p->attaque_gauche[i]);
   }  
   for(i=0;i<5;i++)
   {
      SDL_FreeSurface(v->vi[i]);
   }
   SDL_FreeSurface(p->texte);
   
}


