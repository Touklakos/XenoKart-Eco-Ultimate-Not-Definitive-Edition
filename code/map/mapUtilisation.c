
SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));
SDL_GetMouseState(&mouseX,&mouseY);
afficherMap(map, pSurface, camera);
afficher_perso_map(perso, pos->coord.x*(HEX_WIDTH - HEX_WIDTH/4-0.5)+HEX_WIDTH/2, pos->coord.y*(HEX_HEIGHT - HEX_HEIGHT/2)+HEX_HEIGHT/2, camera, screen);

deplacement(e, &camera, mouseX, mouseY, map->v, &pos);




/////////////////////////////////// pos est la case_t sur laquelle on se trouve /////////////////////////////////////////
////////////////////////////////// switch en fonction de son subtype ////////////////////////////////////////////////////

if(pos->subtype == ENNEMI) etatProg = initialisationCombat;








SDL_UpdateWindowSurface(screen);
