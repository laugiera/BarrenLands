//
// Created by natshez on 09/12/2017.
//
#define GLEW_STATIC
#ifndef BARRENLANDSMASTER_NOISEMANAGER_H
#define BARRENLANDSMASTER_NOISEMANAGER_H

#include "../../fastnoise/FastNoise.h"
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <Tools.hpp>

/**
 * Class NoiseManager
 * manage fast noise lib
 * Singleton
 */
class NoiseManager {
private:
    FastNoise noise;
    float seed;
    std::string seedName;
    float counter;
    NoiseManager();
    ~NoiseManager(){
        for (int i = 0; i <  Tools::nbSub+1; ++i) {
            delete heightMap[i];
        }
        delete heightMap;
        for (int i = 0; i <  Tools::nbSub+1; ++i) {
            delete heightMap[i];
        }
        delete moistureMap;
        std::cout << "delete noise manager ok" << std::endl;
    }
    static NoiseManager * instance;

public:
    float** heightMap;
    float** moistureMap;

    static NoiseManager & getInstance(){
        if(!instance){
            instance = new NoiseManager();
        }
        return *instance;
    }

    static void ResetInstance()
    {
        delete instance;
        std::cout << "delete noise manager ok"<<std::endl;
        instance = NULL;
    }

    /**getters and setters**/
    const std::string &getSeedName() const {
        return seedName;
    }
    void setSeed(const std::string name);
    void setSeed(const float _seed);

    float getSeed(){
        return noise.GetSeed();
    }
    /**
     * functions to get noise maps
     */
    float** getElevationMap(const int width, const int height,const float frequency = 0.05,const float elevationMax = 5);
    float** getMoistureMap(const int width, const int height,const float frequency = 0.05);
    float** getRockMap(const int width, const int height,const float frequency = 0.05);
    float getRandomFloat();
};


#endif //BARRENLANDSMASTER_NOISEMANAGER_H
