do{
  if(map != NULL) free(map);
  caseCount = 1;
  map = creerMap(type_expedition);
  pathfinding(map);
}
while(!valeurPath(map) || valeurPath(map) < 5);

etatProg = UtilisationMap;
