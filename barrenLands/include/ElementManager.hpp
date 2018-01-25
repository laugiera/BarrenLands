#ifndef BARRENLANDS_ELEMENTMANAGER_HPP
#define BARRENLANDS_ELEMENTMANAGER_HPP
#include <RoundRock.hpp>
#include "MenirRock.hpp"
#include "CrystalRock.hpp"
#include "ProceduralGrass.hpp"
#include "ProceduralFeuillage.hpp"
#include "ProceduralTree.hpp"
#include "ProceduralBranche.hpp"

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

    void createAllElements();
    ProceduralObject* createProceduralRock(const std::string &name);
    ProceduralObject* createProceduralTree();
    ProceduralBranche* createProceduralBranche();
    ProceduralFeuillage* createProceduralFeuillage();
    ProceduralObject* createProceduralGrass(const glm::vec3 & position);
    std::vector<ProceduralObject *> getAllElements();

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
