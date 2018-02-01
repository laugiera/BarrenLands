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
    //DESERT   rocks[3] à rocks[10]
    float random = NoiseManager::getInstance().getRandomFloat()*3;
/*    int done = 0;
    while (done !=5){
        float random = NoiseManager::getInstance().getRandomFloat()*2;
        std::cout << "RANDOM : " << random << std::endl;
        done ++;
    }*/
    std::cout << "RANDOM : " << random << std::endl;
    if(random <0){
        rocks.push_back(new FlatRock);
        rocks.push_back(new FlatRock);
        rocks.push_back(new FlatRock);
        rocks.push_back(new FlatRock);
        rocks.push_back(new FlatRock);
        rocks.push_back(new FlatRock);
        rocks.push_back(new PreciousRock);
        rocks.push_back(new PreciousRock);
    }
    else if(random < 0.2){
        rocks.push_back(new FlatRock);
        rocks.push_back(new FlatRock);
        rocks.push_back(new SphereRock);
        rocks.push_back(new SphereRock);
        rocks.push_back(new SphereRock);
        rocks.push_back(new SphereRock);
        rocks.push_back(new SphereRock);
        rocks.push_back(new SphereRock);
    }
    else{
        rocks.push_back(new PreciousRock);
        rocks.push_back(new PreciousRock);
        rocks.push_back(new PreciousRock);
        rocks.push_back(new PreciousRock);
        rocks.push_back(new PreciousRock);
        rocks.push_back(new PreciousRock);
        rocks.push_back(new SphereRock);
        rocks.push_back(new SphereRock);
    }
    //SAVANE de rocks[11] à rocks[14]
    rocks.push_back(new CurvedRock);
    rocks.push_back(new CurvedRock);
    rocks.push_back(new CurvedRock);
    rocks.push_back(new CurvedRock);
    //TOUNDRA de rocks[15] à rocks[22]
    rocks.push_back(new PickRock);
    rocks.push_back(new PickRock);
    rocks.push_back(new PickRock);
    rocks.push_back(new PickRock);
    rocks.push_back(new TriangularRock);
    rocks.push_back(new TriangularRock);
    rocks.push_back(new TriangularRock);
    rocks.push_back(new TriangularRock);
    //GRASS de rocks[23] à rocks[30]
    random = NoiseManager::getInstance().getRandomFloat();
    if(random < 0){
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new SharpedRock);
        rocks.push_back(new SharpedRock);
    }
    else if(random < 0.2){
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new RoundFlatRock);
        rocks.push_back(new RoundRock);
        rocks.push_back(new RoundRock);
        rocks.push_back(new RoundRock);
        rocks.push_back(new RoundRock);
        rocks.push_back(new RoundRock);
        rocks.push_back(new RoundRock);
    }
    else{
        rocks.push_back(new SharpedRock);
        rocks.push_back(new SharpedRock);
        rocks.push_back(new LitchiRock);
        rocks.push_back(new LitchiRock);
        rocks.push_back(new LitchiRock);
        rocks.push_back(new LitchiRock);
        rocks.push_back(new LitchiRock);
        rocks.push_back(new LitchiRock);
    }
    //NATURE
    feuillages.push_back(new ProceduralFeuillage);
    feuillages.push_back(new ProceduralFeuillage);
    feuillages.push_back(new ProceduralFeuillage);
    feuillages.push_back(new ProceduralFeuillage);
    feuillages.push_back(new SapinFeuillage);
    branches.push_back(new ProceduralBranche);
    branches.push_back(new ProceduralBranche);
    branches.push_back(new ProceduralBranche);
    branches.push_back(new ProceduralBranche);
    branches.push_back(new ProceduralBranche);
    trees.push_back(new ProceduralTree);
    trees.push_back(new ProceduralTree);
    trees.push_back(new ProceduralTree);
    trees.push_back(new ProceduralTree);
    trees.push_back(new SapinTree);
    //cas spécial pour l'herbe qui n'est pas en rendu instancié
}

/**
 * createProceduralObject()
 * renvoie un pointer vers un des models de rock créé par le manager précédemment (dans createAllElements() )
 * @return ProceduralObject*
 */
ProceduralObject* ElementManager::createProceduralRock(const std::string &name, int elmt){
    //std::cout << rocks.size() << std::endl;
    if(name == "sand"){
        if(elmt == 0){
            return rocks[3];
        }
        else if(elmt == 1){
            return rocks[4];
        }
        else if(elmt == 2){
            return rocks[5];
        }
        else if(elmt == 3){
            return rocks[6];
        }
        else if(elmt == 4){
            return rocks[7];
        }
        else if(elmt == 5){
            return rocks[8];
        }
        else if(elmt == 6){
            return rocks[9];
        }
        else if(elmt == 7){
            return rocks[10];
        }
    }
    else if(name == "savannah") {
        if(elmt == 0){
            return rocks[11];
        }
        else if(elmt == 1){
            return rocks[12];
        }
        else if(elmt == 2){
            return rocks[13];
        }
        else if(elmt == 3){
            return rocks[14];
        }
    }
    else if(name == "rock"){
        if(elmt == 0){
            return rocks[15];
        }
        else if(elmt == 1){
            return rocks[16];
        }
        else if(elmt == 2){
            return rocks[17];
        }
        else if(elmt == 3){
            return rocks[18];
        }
        else if(elmt == 4){
            return rocks[19];
        }
        else if(elmt == 5){
            return rocks[20];
        }
        else if(elmt == 6){
            return rocks[21];
        }
        else if(elmt == 7){
            return rocks[22];
        }
    }
    else if(name == "toundra"){
        if(elmt == 0){
            return rocks[23];
        }
        else if(elmt == 1){
            return rocks[24];
        }
        else if(elmt == 2){
            return rocks[25];
        }
        else if(elmt == 3){
            return rocks[26];
        }
        else if(elmt == 4){
            return rocks[27];
        }
        else if(elmt == 5){
            return rocks[28];
        }
        else if(elmt == 6){
            return rocks[29];
        }
        else if(elmt == 7){
            return rocks[30];
        }
    }
    else{
        return rocks[0];
    }
}

/**
 * Détruit tous les éléments
 */
ElementManager::~ElementManager() {
    std::vector<ProceduralObject *> elements = getAllElements();
    for(ProceduralObject * el : elements){
        delete el;
    }
   // std::cout << "delete element manager ok" << std::endl;
}

/**
 * Renvoie un vector des tous les models crées par le manager (rendu instancié ou non)
 * @return
 */
std::vector<ProceduralObject *> ElementManager::getAllElements() {
    std::vector<ProceduralObject *> elements;
    elements.insert( elements.end(), rocks.begin(), rocks.end());
    //elements.insert( elements.end(), grass.begin(), grass.end());
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

void ElementManager::scatter(){
    for (int i = 0; i < rocks.size(); ++i) {
        rocks[i]->scatter();
    }
    for (int j = 0; j < trees.size(); ++j) {
        trees[j]->scatter();
    }
    /*for (int j = 0; j < sapinTree.size(); ++j) {
        sapinTree[j]->scatter();
    }*/
}

ProceduralObject *ElementManager::createProceduralTree(int elmt) {
    if(elmt == 0){
        return trees[0];
    }
    else if (elmt == 1){
        return trees[1];
    }
    else if (elmt == 2){
        return trees[2];
    }
    else if (elmt == 3){
        return trees[3];
    }
    else if (elmt == 4){
        return trees[4];
    }
}

ProceduralBranche *ElementManager::createProceduralBranche(int elmt) {
    if(elmt == 0){
        return branches[0];
    }
    else if (elmt == 1){
        return branches[1];
    }
    else if (elmt == 2){
        return branches[2];
    }
    else if (elmt == 3){
        return branches[3];
    }
    else if (elmt == 4){
        return branches[4];
    }
}

ProceduralFeuillage *ElementManager::createProceduralFeuillage(int elmt) {
    if(elmt == 0){
        return feuillages[0];
    }
    else if (elmt == 1){
        return feuillages[1];
    }
    else if (elmt == 2){
        return feuillages[2];
    }
    else if (elmt == 3){
        return feuillages[3];
    }
    else if (elmt == 4){
        return feuillages[4];
    }
}

