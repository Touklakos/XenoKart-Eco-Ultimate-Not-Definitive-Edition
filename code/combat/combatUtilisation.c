
      //////////////////////////////////////FONCTIONS D'AFFICHAGE DES FPS, DU BACKGROUND////////////////////////////////////////////


      deb = SDL_GetTicks();

      SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255)); //on nettoye l'�cran en affichant un grand rectangle blanc


      //////////////////////////////////////FONCTIONS ++&+ SUR CANAL+////////////////////////////////////////////



      SDL_PumpEvents();
      const Uint8 *state = SDL_GetKeyboardState(NULL);      //Vérification de quelles sont les touche qui sont enfoncé sur le clavier

      for(int i = 0; i < 1000; i++) {

        if(state[i]) {

           clavier[i].enfonce = 1;

         } else {

           clavier[i].enfonce = 0;

         }

      }


      //////////////////////////////////////FONCTIONS AUTOMATIQUE DURANT LE COMBAT////////////////////////////////////////////
      mortalKombat();

      afficherCombat();


      gererTexte(camera);

      gererEnnemis();

      if(nbEnnemi == 0) {

        victoire();

        if(pos->subtype == ENNEMI) pos->subtype = BASE;

        etatProg = UtilisationMap;

      }


      if(equipe[0]->PV <= 0 && equipe[1]->PV <= 0 && equipe[2]->PV <= 0) {

        defaite();

        etatProg = UtilisationMap;

      }





      SDL_UpdateWindowSurface(screen);

      for(int i = 0; i < 1000; i++) {

        if(state[i]) clavier[i].relache = 0;
        else clavier[i].relache = 1;

      }

      if(clavier[SDL_SCANCODE_N].enfonce) quit = 1;

      SDL_PollEvent(&event);

      switch(event.type) {

        case SDL_QUIT:
          quit = 1;
          break;

      }

      int delai;

      fin = SDL_GetTicks();

      printf("\nfps = %lld\n", (fpsCount++)*1000/SDL_GetTicks());

      printf("fpsCount = %lld\n", fpsCount);

      printf("fin = %lld\n", fin);

      delai = ((1000/FPS)-(fin-deb));

      do {

        if(coop) {

          pthread_mutex_lock(&mutex); /* On verrouille le mutex */

          pthread_cond_signal(&condition); /* On délivre le signal : condition remplie */

          pthread_mutex_unlock(&mutex); /* On déverrouille le mutex */

        }

        fin = SDL_GetTicks();

        delai = ((1000/FPS)-(fin-deb));


      } while(delai > 0);

      system("clear");
