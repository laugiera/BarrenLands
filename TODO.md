# Sprint 1

Mise en place la structure de base de l'application.

- [x] Classe principale "Application" qui contient l'initialisation de toutes les ressources OpenGL ainsi que la boucle principale de rendu.

Mise en place de la partie rendu OpenGL :

- [x] Classe "GPUProgram" permettant de loader, compiler et linker des Vertex Shader et des Fragment Shaders.
- [x] Classe "RenderObject" avec ses fonctions "fillData" et "render"
- [x] Classe "Light" avec ses fonctions et deux lights pour le soleil et la lune
- [x] Une ou plusieurs classes dérivées de "RenderObject" (RenderMap, RenderBiome, RenderElement) qui implémentent les fonctions fillData et render.

Mise en place de la partie Génération Prodécurale :

- [x] Classe de base "ProceduralObject", possédant son équivalent en RenderObject, ainsi qu'une liste de sous éléments de type ProceduralObject. Implémenter la fonction draw() qui sera sensiblement la même pour tous les objets procéduraux (?).
- [x] Une ou plusieurs classes dérivées de "ProceduralObject" (ProceduralMap, ProceduralBiome, ProceduralElement) qui implémentent les fonctions generate() et createRenderObject.
- [x] Dans la classe Application, créer des ProceduralObjects (en fonction d'une seed) hiérarchiquement, et appelez la fonction draw() sur l'objet principal.

Mise en place des fonctions utilitaires :

- [x] Trackball caméra
- [x] Freefly caméra
- [x] Implémenter les fonctions qui renvoient la matrice modelview de chacune des caméras
- [x] Créer un manager CameraManager permettant de switcher de caméras

Objectif à la fin du sprint 1 :
- [x] Pouvoir créer rapidement des ProceduralObjects et les RenderObjects correspondants via la démarche suivante :
1. Créer une nouvelle classe ProceduralXXX, dérivée de ProceduralObject (à minima) et réimplémenter sa fonction generate()
2. Créer une nouvelle classe RenderXXX, dérivée de RenderObject (à minima) avec des paramètres spéciaux propres à cet objet (texture, uniform, etc.)
3. Réimplémenter la fonction createRenderObject() de la classe ProceduralXXX en créant un nouvel objet RenderXXX
 Note : il est probable qu'on doive passer à un moment par du rendu instancié, auquel cas il faudra revoir l'implémentation des classes RenderObject (en passant par exemple par un manager).
 
- [x] Pouvoir visualiser directement ces nouveaux objets / nouvelles zones dans l'application.
- [x] Pouvoir recompiler les shaders à la volée.
- [x] Pouvoir se déplacer facilement sur la carte.

Plus :
- [x] Eliminer les fuites mémoires (+ bug dans RenderSkybox Destructor)
- [x] Faire la factory et les maps de répartitions
- [x] Rendu instancié
- [x] Exterioriser la proj matrix
******************************************************************************************************************************

IL RESTE :
- [x] Répartition des rochers (faire des scale et des rotations, les regrouper un peu plus si besion) + les positionner correctement selon la hauteur du sol => ANNE
- [x] Répartition des "arbres" => ANNE
- [x] Modélisation des arbres => ETIENNE
- [x] Variations couleurs => LOU

- [ ] Faire des belles textures, blur à l'horizon, contours des objets => LOU
- [ ] Shadow mapping => ANNE
- [ ] interface pour choisir une seed (une interface "home" et une inferface "pause" pour sauvegarder/importer ?)
- [ ] Son
- [ ] Finir la doc
- [ ] Préparer la démo
