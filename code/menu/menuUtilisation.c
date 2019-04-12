afficher(tab, tailletab, pSurface, screen, police);

deb = SDL_GetTicks();

SDL_PumpEvents();
const Uint8 *state = SDL_GetKeyboardState(NULL);


if(recupCurs-- < 0){ //permet la gestion de l'appuie des touches

  if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]){
    nbChoix++;
    if(nbChoix == 3) nbChoix = 0;

    tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2);

    afficher(tab, tailletab, pSurface, screen, police);

    recupCurs = DELAI_CURSEUR;
  }
  if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]){
    nbChoix--;
    if(nbChoix == -1) nbChoix = 2;

    tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2);

    afficher(tab, tailletab, pSurface, screen, police);

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
