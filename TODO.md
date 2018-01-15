# Sprint 1

Mise en place la structure de base de l'application.

- [ ] Classe principale "Application" qui contient l'initialisation de toutes les ressources OpenGL ainsi que la boucle principale de rendu.

Mise en place de la partie rendu OpenGL :

- [ ] Classe "GPUProgram" permettant de loader, compiler et linker des Vertex Shader et des Fragment Shaders.
- [ ] Classe "RenderObject" avec ses fonctions "fillData" et "render"
- [ ] Une ou plusieurs classes dérivées de "RenderObject" (RenderMap, RenderBiome, RenderElement) qui implémentent les fonctions fillData et render.

Mise en place de la partie Génération Prodécurale :

- [ ] Classe de base "ProceduralObject", possédant son équivalent en RenderObject, ainsi qu'une liste de sous éléments de type ProceduralObject. Implémenter la fonction draw() qui sera sensiblement la même pour tous les objets procéduraux (?).
- [ ] Une ou plusieurs classes dérivées de "ProceduralObject" (ProceduralMap, ProceduralBiome, ProceduralElement) qui implémentent les fonctions generate() et createRenderObject.
- [ ] Dans la classe Application, créer des ProceduralObjects (en fonction d'une seed) hiérarchiquement, et appelez la fonction draw() sur l'objet principal.

Mise en place des fonctions utilitaires :

- [ ] Trackball caméra
- [ ] Freefly caméra
- [ ] Implémenter les fonctions qui renvoient la matrice modelview de chacune des caméras
- [ ] Créer un manager CameraManager permettant de switcher de caméras

Objectif à la fin du sprint 1 :
- [ ] Pouvoir créer rapidement des ProceduralObjects et les RenderObjects correspondants via la démarche suivante :
1. Créer une nouvelle classe ProceduralXXX, dérivée de ProceduralObject (à minima) et réimplémenter sa fonction generate()
2. Créer une nouvelle classe RenderXXX, dérivée de RenderObject (à minima) avec des paramètres spéciaux propres à cet objet (texture, uniform, etc.)
3. Réimplémenter la fonction createRenderObject() de la classe ProceduralXXX en créant un nouvel objet RenderXXX
 Note : il est probable qu'on doive passer à un moment par du rendu instancié, auquel cas il faudra revoir l'implémentation des classes RenderObject (en passant par exemple par un manager).
 
- [ ] Pouvoir visualiser directement ces nouveaux objets / nouvelles zones dans l'application.
- [ ] Pouvoir recompiler les shaders à la volée.
- [ ] Pouvoir se déplacer facilement sur la carte.
