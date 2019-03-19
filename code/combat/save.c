
    doublet clavier[3][1000];

    for(int i = 0; i< 1000; i++) {

      clavier[0][i].enfonce = 0;
      clavier[0][i].relache = 0;

      clavier[1][i].enfonce = 0;
      clavier[1][i].relache = 0;

      clavier[2][i].enfonce = 0;
      clavier[2][i].relache = 0;

    }

    while(!quit) {

      //////////////////////////////////////FONCTIONS D'AFFICHAGE DES FPS, DU BACKGROUND////////////////////////////////////////////


      debut = SDL_GetTicks();

      SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255)); //on nettoye l'�cran en affichant un grand rectangle blanc




      //////////////////////////////////////FONCTIONS ++&+ SUR CANAL+////////////////////////////////////////////



      SDL_PollEvent(&event);

      SDL_PumpEvents();
      const Uint8 *state = SDL_GetKeyboardState(NULL);      //Vérification de quelles sont les touche qui sont enfoncé sur le clavier

      for(int i = 0; i < 1000; i++) {

        if(state[i]) {

           clavier[indicePersonnage][i].enfonce = 1;

         } else {

           clavier[indicePersonnage][i].enfonce = 0;

         }

      }


      //////////////////////////////////////FONCTIONS RECEPTION ET EMISSIONS DES INPUTS////////////////////////////////////////////


      if(coop) {

        if(serveur) {

          recv(client_socket1, clavier[0], sizeof(clavier)/3, 0);

          send(client_socket1, clavier[2], sizeof(clavier)/3, 0);

      /*    lg2 = recv(client_socket2, clavierJ3, sizeof(clavierJ3),0);

          send(client_socket2, clavier, sizeof(clavier), 0);*/


        } else {

          send(to_server_socket, clavier[0], sizeof(clavier)/3, 0);

        	recv(to_server_socket, clavier[2], sizeof(clavier)/3, 0);

        }

      }






      //////////////////////////////////////FONCTIONS AUTOMATIQUE DURANT LE COMBAT////////////////////////////////////////////




          for(int i = 0; i < nbEnnemi; i++) {   //les ennemis en combat attaque les personnages

            if(ennemis[i].enCombat) {

              cibleEnnemi(&ennemis[i]);

              attaqueAllie(equipe, &ennemis[i], ennemis[i].cible, dgtsTxt, &nbDgtTxt);

            }

          }

          attaqueEnnemi(equipe, ennemis, dgtsTxt, &nbDgtTxt);  //les personnages attaques l'ennemi qu'ils ciblent


          //////////////////////////////////////FONCTIONS D'INPUTS POUR LE COMBAT////////////////////////////////////////////


          for(int i = 0; i < 3; i++) {


            switch(etatCombat[i]) {

              case 0:       //deplacement, choix et activations des arts, controle des personnages

                if(!coop) {

                  if(clavier[0][SDL_SCANCODE_3].enfonce) { //Si on appuie sur la gachette droite on donner des ordres au personnage le plus � droite ou bien le controller

                    if(testTouche(clavier[0][SDL_SCANCODE_R])) {  //si on appuie sur R on dit au personnage d'attaquer une cible

                      equipe[(indicePersonnage+1)%3]->cible = equipe[indicePersonnage]->cible;

                    }

                  }

                    if(clavier[0][SDL_SCANCODE_1].enfonce) {  //m�me chose pour la gachette gauche

                      if(testTouche(clavier[0][SDL_SCANCODE_R])) {  //si on appuie sur R on dit au personnage d'aataquer une cible

                        equipe[(indicePersonnage+2)%3]->cible = equipe[indicePersonnage]->cible;

                      }

                    }

                }




                if(recupCurseur[i]-- < 0) {

                  if(clavier[i][SDL_SCANCODE_RIGHT].enfonce) {     //deplacement du curseur dans un sens

                    positionCurseur[i] = (positionCurseur[i]+1)%8;

                    recupCurseur[i] = DELAI_CURSEUR;

                  } else if(clavier[i][SDL_SCANCODE_LEFT].enfonce) { //et dans l'autre

                    positionCurseur[i]--;

                    if(positionCurseur[i] < 0) positionCurseur[i] = 7;

                    recupCurseur[i] = DELAI_CURSEUR;

                  }


                }


              /*  printf("Octo izi no pas desu : %d\n", clavier[i][SDL_SCANCODE_E].enfonce && !clavier[i][SDL_SCANCODE_1].enfonce && !clavier[i][SDL_SCANCODE_3].enfonce);

                printf("OctoDad : %d\n", equipe[i]->delaiArt);

                printf("OctoBro : %d\n", ennemis[equipe[i]->cible].PV);*/


                if(testTouche(clavier[i][SDL_SCANCODE_E]) && !clavier[i][SDL_SCANCODE_1].enfonce && !clavier[i][SDL_SCANCODE_3].enfonce) { //si on appuie sur A sans appuiyer sur les gachette on utilise l'art sur lequel est positionn� notre curseur

                  if(equipe[i]->delaiArt < 0) {

                    if(ArtJeu[i][positionCurseur[i]]->BUT == attaque) {

                      utiliseArt(ArtJeu[i][positionCurseur[i]], equipe, &ennemis[equipe[i]->cible],i, dgtsTxt, &nbDgtTxt);

                    } else if(ArtJeu[i][positionCurseur[i]]->BUT == soutien) {

                      if(ArtJeu[i][positionCurseur[i]]->CIBLE_ALLIE == membreGroupe && ArtJeu[i][positionCurseur[i]]->recup < 0) {

                        etatCombat[i] = 1;

                      } else {

                        utiliseArtBuff(ArtJeu[i][positionCurseur[i]], equipe, i, pSurface, dgtsTxt, &nbDgtTxt);

                      }

                    }

                  }

                }


              break;

                case 1:         //choix de la cible d'un art de soutien



                  if(recupCible[i]-- < 0) {

                    if(clavier[i][SDL_SCANCODE_DOWN].enfonce) {

                      cible[i] += 1;
                      cible[i] %= 3;

                      recupCible[i] = DELAI_CIBLE;

                    } else if(clavier[i][SDL_SCANCODE_UP].enfonce) {

                      cible[i] -= 1;
                      if(cible[i] < 0) cible[i] = 2;

                      recupCible[i] = DELAI_CIBLE;

                    }

                    if(testTouche(clavier[i][SDL_SCANCODE_E])) {

                      utiliseArtBuff(ArtJeu[i][positionCurseur[i]], equipe, cible[i], pSurface, dgtsTxt, &nbDgtTxt);

                      etatCombat[i] = 0;

                    }

                  }




                break;

                }




                if(recupCibleEnn[i]-- < 0) {

                  if(clavier[i][SDL_SCANCODE_I].enfonce) {

                    equipe[i]->cible++;

                    equipe[i]->cible %= nbEnnemi;

                    equipe[i]->enChoixCible = 1;

                    recupCibleEnn[i] = DELAI_CIBLE_ENN;

                  }

                  if(clavier[i][SDL_SCANCODE_P].enfonce) {

                    equipe[i]->cible--;

                    if(equipe[i]->cible < 0) equipe[i]->cible = nbEnnemi-1;

                    equipe[i]->enChoixCible = 1;

                    recupCibleEnn[i] = DELAI_CIBLE_ENN;

                  }

                }


                if(testTouche(clavier[i][SDL_SCANCODE_SPACE])) {

                  for(int j = 0; j < 3; j++) {

                    equipe[j]->cible = equipe[i]->cible;

                    equipe[j]->enCombat = 1;

                    equipe[j]->enChoixCible = 0;

                  }


                }

              }



            if(!coop) {

              if(clavier[0][SDL_SCANCODE_3].enfonce) { //Si on appuie sur la gachette droite on donner des ordres au personnage le plus � droite ou bien le controller

                if(testTouche(clavier[0][SDL_SCANCODE_E])) {  //si on appuie sur E on controle le personnage

                  controlePerso(equipe, &indicePersonnage, droite);

                }

              }

              if(clavier[0][SDL_SCANCODE_1].enfonce) {  //m�me chose pour la gachette gauche

                if(testTouche(clavier[0][SDL_SCANCODE_E])) {

                  controlePerso(equipe, &indicePersonnage, gauche);

                }

              }

            }






            //////////////////////////////////////FONCTIONS D'INPUTS DE DEPLACEMENT////////////////////////////////////////////
