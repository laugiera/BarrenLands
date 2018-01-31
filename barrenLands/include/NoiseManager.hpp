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

/**
 * Class NoiseManager
 * manage fast noise lib
 * Singleton
 */
class NoiseManager {
private:
    FastNoise noise;
    static float seed;
    float counter;
    NoiseManager();
    ~NoiseManager(){}
public:
    float** heightMap;
    float** moistureMap;


    /**
     * getInstance()
     * @return NoiseManager & unique instance
     */
    static NoiseManager & getInstance(){
        static NoiseManager instance;
        return instance;
    }

    void setSeed(const float _seed);
     float getSeed(){
        return noise.GetSeed();
    }
    void setSeed(const std::string name){
        float seed = 0;
        for (int i = 0; i < name.size(); ++i) {
            seed += name[i];
        }
        setSeed(seed);
    }
    /**
     * functions to get noise maps
     */
    float** getElevationMap(const int width, const int height,const float frequency = 0.05,const float elevationMax = 5);
    float** getMoistureMap(const int width, const int height,const float frequency = 0.05);
    float** getRockMap(const int width, const int height,const float frequency = 0.05);

    float getVerticesDisturbation(const int x, const int y, const int z);
    float getRandomFloat();
};


#endif //BARRENLANDSMASTER_NOISEMANAGER_H
