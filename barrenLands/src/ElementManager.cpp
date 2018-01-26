#include "ElementManager.hpp"

ElementManager * ElementManager::instance = nullptr;


/**
 * Constructeur
 * Créée tous les models en utilisant createAllElements()
 */
ElementManager::ElementManager() {
    //createAllElements();
}

/**
 * crée tous les models utilisés pour le rendu instancié et les ajoute dans les différents attributs du manager par famille
 */
void ElementManager::createAllElements() {
    rocks.push_back(new RoundRock);
    rocks.push_back(new MenirRock);
    rocks.push_back(new CrystalRock);
    feuillages.push_back(new ProceduralFeuillage);
    branches.push_back(new ProceduralBranche);
    trees.push_back(new ProceduralTree);

    //cas spécial pour l'herbe qui n'est pas en rendu instancié
}

/**
 * createProceduralObject()
 * renvoie un pointer vers un des models de rock créé par le manager précédemment (dans createAllElements() )
 * @return ProceduralObject*
 */
ProceduralObject* ElementManager::createProceduralRock(const std::string &name){
    if(name == "sand")
        return rocks[0];
    else if(name == "toundra")
        return rocks[1];
    else
        return rocks[2];
}

/**
 * Détruit tous les éléments
 */
ElementManager::~ElementManager() {
    std::vector<ProceduralObject *> elements = getAllElements();
    for(ProceduralObject * el : elements){
        delete el;
    }
}

/**
 * Renvoie un vector des tous les models crées par le manager (rendu instancié ou non)
 * @return
 */
std::vector<ProceduralObject *> ElementManager::getAllElements() {
    std::vector<ProceduralObject *> elements;
    elements.insert( elements.end(), rocks.begin(), rocks.end());
    elements.insert( elements.end(), grass.begin(), grass.end());
    elements.insert( elements.end(), branches.begin(), branches.end());
    elements.insert( elements.end(), feuillages.begin(), feuillages.end());
    elements.insert( elements.end(), trees.begin(), trees.end());

    return elements;
}

/**
 * Créée les models d'herbe.
 * Comme le rendu de l'herbe n'est pas instancié, à chaque appel, un nouvel éléments est créé.
 * (au lieu de retourner un model préexistant)
 * @param position
 * @return
 */
ProceduralObject *ElementManager::createProceduralGrass(const glm::vec3 & position) {
    ProceduralObject * g = new ProceduralGrass(position);
    grass.push_back(g);
    return g;
}

ProceduralObject *ElementManager::createProceduralTree() {
    return trees[0];
}

ProceduralBranche *ElementManager::createProceduralBranche() {
    return branches[0];
}

ProceduralFeuillage *ElementManager::createProceduralFeuillage() {
    return feuillages[0];
}

