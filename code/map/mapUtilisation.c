afficherMap(map, pSurface, screen);

SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 0, 0));
SDL_GetMouseState(&mouseX,&mouseY);
afficherMapMieux(map, camera, screen);
afficher_perso_map(perso, pos.coord.x, pos.coord.y, camera, screen);
//printf("mouseX : %i\nmouseY : %i\n camera x : %i\ncamera y : %i\n", mouseX, mouseY, camera.x, camera.y);

SDL_UpdateWindowSurface(screen);

deplacement(e, &camera, mouseX, mouseY, map->v, &pos);
