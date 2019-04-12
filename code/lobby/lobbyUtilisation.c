SDL_PollEvent(&event);



SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

switch (etat){
  case 0 : if(!inv_vide(inv)){echange(screen, inv, &argent, &points);} break;
  case 1 : type_expedition = expedition(screen); break;
  case 2 : commerce(screen, inv, &argent); break;

}
etat++;

printf("test2\n");

if(etat == 3){
  etatProg = creationMap;
}
