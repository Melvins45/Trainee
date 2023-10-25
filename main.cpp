
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int main ( int argc, char** argv )
{
    SDL_Surface *ecran=NULL;
    SDL_Surface *zozor=NULL;
    SDL_Event event;
    bool continuer=true;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL ");
            exit(EXIT_FAILURE);
        }

    ecran=SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    zozor=SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(zozor,SDL_SRCCOLORKEY,SDL_MapRGB(zozor->format,0,0,255));
    SDL_Rect position[10];
    position[0].x=ecran->w/2 - zozor->w/2;
    position[0].y=ecran->h/2 - zozor->h/2;


    int i=0;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer=false;
                break;
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        if(i<10)
                        {
                            position[i].x=event.button.x;
                            position[i].y=event.button.y;
                            SDL_BlitSurface(zozor,NULL,ecran,&position[i]);
                            i++;
                        }
                        break;
                }
                break;
        }

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();
    return EXIT_SUCCESS;
}
