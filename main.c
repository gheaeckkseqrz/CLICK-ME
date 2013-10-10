//
// main.cpp for POINT&CLICK in /home/wilmot_p/POINT&CLICK
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Oct 10 20:55:15 2013 WILMOT Pierre
//

#include	<stdlib.h>
#include	<stdio.h>
#include	<time.h>
#include	<SDL/SDL.h>

#define	WIN_WIDTH		500
#define	WIN_HEIGHT		500

#define	TARGET_WIDTH		25
#define	TARGET_HEIGHT		25

SDL_Surface		*initSDL();
void			game();
void			refreshDisplay(SDL_Surface *win, SDL_Surface *target, SDL_Rect *position;);
int			clickHitTarget(int x, int y, SDL_Rect *pos);

int			main(int ac, char **av)
{
  (void)ac;
  (void)av;
  srand(time(NULL));

  SDL_Surface *window = NULL;
  if ((window = initSDL()) == NULL)
    return 1;

  game(window);

  SDL_Quit();
  return 0;
}

SDL_Surface		*initSDL()
{
  SDL_Surface *window = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
      return NULL;
    }

  if ((window = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE)) == NULL)
    {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
      return NULL;
    }

  SDL_WM_SetCaption("POINT&CLICK", NULL);
  SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 255, 255, 255));
  SDL_Flip(window);
  return window;
}

void			game(SDL_Surface *win)
{
  SDL_Surface		*target = NULL;
  SDL_Rect		targetPosition;
  SDL_Event		event;
  int			score = 0;

  target = SDL_CreateRGBSurface(SDL_HWSURFACE, 25, 25, 32, 0, 0, 0, 0);
  SDL_FillRect(target, NULL, SDL_MapRGB(win->format, 255, 0, 0));
  refreshDisplay(win, target, &targetPosition);
  while (SDL_WaitEvent(&event))
    {
      switch(event.type)
        {
	case SDL_QUIT:
	  return SDL_FreeSurface(target);
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (clickHitTarget(event.button.x, event.button.y, &targetPosition))
	    {
	      refreshDisplay(win, target, &targetPosition);
	      ++score;
	      printf("Score : %d\n", score);
	    }
	  break;
        }
    }
}

void			refreshDisplay(SDL_Surface *win, SDL_Surface *target, SDL_Rect *position)
{
  position->x = rand() % (WIN_WIDTH - TARGET_WIDTH);
  position->y = rand() % (WIN_HEIGHT - TARGET_HEIGHT);

  SDL_FillRect(win, NULL, SDL_MapRGB(win->format, 255, 255, 255));
  SDL_BlitSurface(target, NULL, win, position);
  SDL_Flip(win);
}

int			clickHitTarget(int x, int y, SDL_Rect *pos)
{
  return (x >= pos->x && x <= pos->x + TARGET_WIDTH && y >= pos->y && y <= pos->y + TARGET_HEIGHT);
}
