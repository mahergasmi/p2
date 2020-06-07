#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"pers.h"
void initialiserperso(perso2 *perso,vie2 *v)
{
   SDL_Color couleur={0,255,0};
int i;
char ch[40];
perso->numd=0;
perso->numg=0;
perso->at=0;
perso->atg=0;
perso->attaque=0;
perso->devant=1;
perso->arriere=0;
perso->pos.x = 50 ;
perso->pos.y = 445 ;
   v->num=0;//ce compteur va augmenter lorsque le personnage sera blessé (v->num)++ pour afficher l'image de la vie quand elle diminue
   v->pos.x=0;
   v->pos.y=0;
   perso->score=0;
   perso->posscore.x=0;
   perso->posscore.y=0;
   perso->texte=NULL;
   perso->police=NULL;

perso->debout_droite=IMG_Load("../GAME/characters/hero2/deboutdroite.png");
perso->debout_gauche=IMG_Load("../GAME/characters/hero2/deboutgauche.png");
for(i=0;i<5;i++)
{
perso->marche_droite[i]=NULL;
sprintf(ch,"../GAME/characters/hero2/%dd.png",i+1);
perso->marche_droite[i]=IMG_Load(ch);
}
for(i=0;i<5;i++)
{
perso->marche_gauche[i]=NULL;
sprintf(ch,"../GAME/characters/hero2/%dg.png",i+1);
perso->marche_gauche[i]=IMG_Load(ch);
}
for(i=0;i<11;i++)
{
perso->attaque_droite[i]=NULL;
sprintf(ch,"../GAME/characters/hero2/at%d.png",i+1);
perso->attaque_droite[i]=IMG_Load(ch);
}
for(i=0;i<5;i++)
{
perso->attaque_gauche[i]=NULL;
sprintf(ch,"../GAME/characters/hero2/atg%d.png",i+1);
perso->attaque_gauche[i]=IMG_Load(ch);
}

for(i=0;i<5;i++)
	{
            v->vi[i]=NULL;
	    sprintf(ch,"../GAME/characters/vie/vie%d.png",i+1);
	    v->vi[i]=IMG_Load(ch);
	}
   perso->police=TTF_OpenFont("../GAME/font/labo.ttf",60);
   sprintf(ch,"Score: %d",perso->score);
   perso->texte=TTF_RenderText_Blended(perso->police,ch,couleur);
}

void freefurfaceperso(perso2 *perso,vie2 *v)
{
int i;
TTF_CloseFont(perso->police);
for(i=0;i<5;i++)
{
SDL_FreeSurface(perso->marche_droite[i]);
SDL_FreeSurface(perso->marche_gauche[i]);
SDL_FreeSurface(perso->attaque_gauche[i]);
SDL_FreeSurface(v->vi[i]);
}
for(i=0;i<11;i++)
{
SDL_FreeSurface(perso->attaque_droite[i]);
}

SDL_FreeSurface(perso->debout_droite);
SDL_FreeSurface(perso->debout_gauche);
SDL_FreeSurface(perso->texte);
}


void animer_perso(int d,int q,int e,SDL_Surface *ecran,SDL_Surface *fond,SDL_Rect camera,perso2 *perso,vie2 *v)
{
int i;
if((d==0)&&(q==0)&&(e==0))
{
if(perso->arriere==1)
SDL_BlitSurface(perso->debout_gauche,NULL,ecran,&perso->pos);
else
SDL_BlitSurface(perso->debout_droite,NULL,ecran,&perso->pos);
}


else
if(d==1)
{
perso->devant=1;perso->arriere=0;
if(perso->numd==5) perso->numd=0;
SDL_BlitSurface(perso->marche_droite[perso->numd],NULL,ecran,&perso->pos);
//if(perso->pos.x<=550) (perso->pos.x)+=2;
(perso->numd)++;
}

else if(q==1)
{
perso->devant=0;perso->arriere=1;
if(perso->numg==5) perso->numg=0;
SDL_BlitSurface(perso->marche_gauche[perso->numg],NULL,ecran,&perso->pos);
if(perso->pos.x>0) (perso->pos.x)-=2;
(perso->numg)++;
}

else if(e==1)
{
if(perso->devant==1)
{
if(perso->at==11) perso->at=0;
SDL_BlitSurface(perso->attaque_droite[perso->at],NULL,ecran,&perso->pos);
(perso->at)++;
}else
{
if(perso->arriere==1)
{
if(perso->atg==5) perso->atg=0;
SDL_BlitSurface(perso->attaque_gauche[perso->atg],NULL,ecran,&perso->pos);
(perso->atg)++;
}
}
}

SDL_BlitSurface(perso->texte,NULL,ecran,&perso->posscore);
SDL_BlitSurface(v->vi[v->num],NULL,ecran,&v->pos);


}

