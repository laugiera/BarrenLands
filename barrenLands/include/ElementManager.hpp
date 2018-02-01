#ifndef BARRENLANDS_ELEMENTMANAGER_HPP
#define BARRENLANDS_ELEMENTMANAGER_HPP
#include <RoundRock.hpp>
#include "MenirRock.hpp"
#include "CrystalRock.hpp"
#include "ExperienceRock.hpp"
#include "ProceduralGrass.hpp"
#include "ProceduralFeuillage.hpp"
#include "ProceduralTree.hpp"
#include "ProceduralBranche.hpp"
#include "FlatRock.hpp"
#include "PickRock.hpp"
#include "PreciousRock.hpp"
#include "RoundFlatRock.hpp"
#include "SharpedRock.hpp"
#include "SphereRock.hpp"
#include "TriangularRock.hpp"
#include "CurvedRock.hpp"
#include "LitchiRock.hpp"
#include "SapinFeuillage.hpp"
#include "SapinTree.hpp"


/**
 * Class ElementManager
 * Creates all sort of object for the map
 */
class ElementManager{
public:
    static ElementManager & getInstance(){
        if(!instance){
           instance = new ElementManager();
        }
        return *instance;
    }
    static void ResetInstance()
    {
        delete instance; // REM : it works even if the pointer is NULL (does nothing then)
        std::cout << "delete element manager ok"<<std::endl;
        instance = NULL; // so GetInstance will still work.
    }

    void createAllElements();
    ProceduralObject* createProceduralRock(const std::string &name, int elmt = 0);
    ProceduralObject* createProceduralTree(int elmt = 0);
    ProceduralBranche* createProceduralBranche(int elmt = 0);
    ProceduralFeuillage* createProceduralFeuillage(int elmt = 0);
    ProceduralObject* createProceduralGrass(const glm::vec3 & position);
    std::vector<ProceduralObject *> getAllElements();
    void scatter();

private:
    static ElementManager * instance;
    ElementManager();
    ~ElementManager();

    std::vector<ProceduralObject *> rocks;
    std::vector<ProceduralObject *> grass;
    std::vector<ProceduralFeuillage *> feuillages;
    std::vector<ProceduralObject *> trees;
    std::vector<ProceduralBranche *> branches;

};

#endif //BARRENLANDS_ELEMENTMANAGER_HPP
