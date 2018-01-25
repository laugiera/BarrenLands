#ifndef BARRENLANDS_ELEMENTMANAGER_HPP
#define BARRENLANDS_ELEMENTMANAGER_HPP
#include <RoundRock.hpp>
#include "MenirRock.hpp"
#include "CrystalRock.hpp"
#include "ProceduralGrass.hpp"

/**
 * Class ElementManager
 * Creates all sort of object for the map
 */
class ElementManager{
public:
    static ElementManager & getInstance(){
        static ElementManager instance;
        return instance;
    }


    ProceduralObject* createProceduralRock(const std::string &name);
    ProceduralObject* createProceduralGrass(const glm::vec3 & position);
    std::vector<ProceduralObject *> getAllElements();

private:
    ElementManager();
    ~ElementManager();
    void createAllElements();
    std::vector<ProceduralObject *> rocks;
    std::vector<ProceduralObject *> grass;

};

#endif //BARRENLANDS_ELEMENTMANAGER_HPP
