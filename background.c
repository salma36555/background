
#include "background.h"

void initBackground(Background *B, int diff)
{

  B->PositionBg.x = 0;
  B->PositionBg.y = 0;

  B->camera.x = 0;
  B->camera.y = 0;
  B->camera.w = 1500;
  B->camera.h = 700;

  B->frame = 1;

  char string[20];
  int i;

  for (i = 1; i <= 8; i++)
  {
    sprintf(string, "background/b%d.png", i);

    B->BgImg[i] = IMG_Load(string);
  }

  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  B->music = Mix_LoadMUS("music.mp3");
  Mix_PlayMusic(B->music, -1);

  B->vies = IMG_Load("HEARTS.png");
  B->posVie1.x = 0;
  B->posVie1.y = 0;
  B->vie = 100;

  B->posVie2.x = 0;
  B->posVie2.y = 0;
  B->posVie2.h = 26;
  B->posVie2.w = 116;

  TTF_Init();
  B->police = TTF_OpenFont("font.ttf", 40);

  B->score = 10;
  B->posScore.x = 0;
  B->posScore.y = 50;
}

void affBackground(Background *B, SDL_Surface *screen, int diff)
{
  SDL_BlitSurface(B->BgImg[B->frame], &(B->camera), screen, &(B->PositionBg));

  SDL_BlitSurface(B->vies, &(B->posVie2), screen, &(B->posVie1));

  if (B->vie >= 100)
  {
    B->posVie2.y = 0;
  }
  if (B->vie >= 75 && B->vie < 100)
  {
    B->posVie2.y = 25;
  }
  if (B->vie >= 50 && B->vie < 75)
  {
    B->posVie2.y = 50;
  }
  if (B->vie >= 25 && B->vie < 50)
  {
    B->posVie2.y = 77;
  }
  if (B->vie >= 0 && B->vie < 25)
  {
    B->posVie2.y = 103;
  }

  SDL_Color couleur = {255, 255, 255};
  char s[20];
  sprintf(s, "Score: %d", B->score);

  B->scores = TTF_RenderText_Blended(B->police, s, couleur);
  SDL_BlitSurface(B->scores, NULL, screen, &(B->posScore));
}

void animerBack(Background *B)
{
  if (B->frame == 8)
    B->frame = 1;

  B->frame++;
}

void scrolling(Background *B, SDL_Rect posPerso, int direction)
{
  const int speed = 20;
  if (direction == 1)
  {
    if ((B->camera.x < 10000 - B->camera.w) && (posPerso.x >= 750))
    {
      B->camera.x = B->camera.x + speed;
    }
  }
  else if (direction == 0)
  {
    if (B->camera.x > 0)
    {
      B->camera.x -= speed;
    }
  }
}
void freeBackground(Background *B)
{
  // SDL_FreeSurface(B->BgImg);
  SDL_FreeSurface(B->vies);
  SDL_FreeSurface(B->scores);
  Mix_FreeMusic(B->music);
}

void sauvegarder(ScoreInfo s, char *file)
{
  FILE *f = fopen(file, "a");
  fprintf(f, "%s %d %d \n", s.name, s.score, s.time);
  fclose(f);
}

void bestScore(ScoreInfo s[], int n, char *file)
{
  int max1 = 0;

  int i;
  for (i = 0; i < n; i++)
  {
    if (s[i].score > max1)
      max1 = s[i].score;
  }

  int max2 = 0;
  for (i = 0; i < n; i++)
  {
    if ((s[i].score > max2) && (s[i].score != max1))
      max2 = s[i].score;
  }

  int max3 = 0;
  for (i = 0; i < n; i++)
  {
    if ((s[i].score > max3) && (s[i].score != max1) && (s[i].score != max2))
      max3 = s[i].score;
  }
}
