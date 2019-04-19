deb = SDL_GetTicks();

SDL_Rect dest;
dest.x = 0;
dest.y = 0;

SDL_PumpEvents();
const Uint8 *state = SDL_GetKeyboardState(NULL);

SDL_Surface * img;
img = IMG_Load("code/menu/logomenu.jpg");
SDL_BlitSurface(img, NULL, pSurface, &dest);
SDL_FreeSurface(img);
SDL_UpdateWindowSurface(screen);

int quit2 = 0;

while(!quit2){
  for(int i = 0; i < 322; i++){
    if(state[i]){
      quit2=1;
      fondu(pSurface, screen);
    }
  }
  SDL_PumpEvents();
  fonctionQuitter();
  if(quit)break;
}

while(etatProg == nouvelleEtat){

  afficher(tab, tailletab, pSurface, screen, police);

  if(recupCurs-- < 0){ //permet la gestion de l'appuie des touches

    if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]){
      nbChoix++;
      if(nbChoix == 3) nbChoix = 0;

      tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT2/2-((tailletab-1)*decallageBouton/2);
      afficher(tab, tailletab, pSurface, screen, police);
      recupCurs = DELAI_CURSEUR;
    }

    if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]){
      nbChoix--;
      if(nbChoix == -1) nbChoix = 2;

      tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT2/2-((tailletab-1)*decallageBouton/2);
      afficher(tab, tailletab, pSurface, screen, police);
      recupCurs = DELAI_CURSEUR;
    }

    if(state[SDL_SCANCODE_BACKSPACE] || state[SDL_SCANCODE_ESCAPE]){
      quit2 = 0;
      //backgroundmenu = 0;
      nouvelleEtat--;
      recupCurs = DELAI_CURSEUR;
    }

    if(state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE]){
      while(state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE]) {SDL_PumpEvents(); state = SDL_GetKeyboardState(NULL);};
      switch(nbChoix){
        case 0 : fonctionJeu(pSurface, screen, police); break;
        case 1 : fonctionOption(pSurface, screen, police); break;
        case 2 : quit = 2; break;
      }
    }
  }
  fonctionFin();
  fonctionQuitter();
  if(quit) break;
}
