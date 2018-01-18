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

class NoiseManager {
private:
    FastNoise noise;
    static float seed;
    NoiseManager();
    ~NoiseManager(){}
public:
    static NoiseManager & getInstance(){
        static NoiseManager instance;
        return instance;
    }
    static void setSeed(const float _seed){
        NoiseManager::seed = _seed;
    }
    static float getSeed(){
        return NoiseManager::seed;
    }
    float** getElevationMap(const int width, const int height,const float frequency = 0.05,const float elevationMax = 5);

};


#endif //BARRENLANDSMASTER_NOISEMANAGER_H
