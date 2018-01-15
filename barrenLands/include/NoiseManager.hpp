//
// Created by natshez on 09/12/2017.
//

#ifndef BARRENLANDSMASTER_NOISEMANAGER_H
#define BARRENLANDSMASTER_NOISEMANAGER_H

#include "../../fastnoise/FastNoise.h"
#include <math.h>

class NoiseManager {
private:
    FastNoise noise;
    float seed;

public:
    NoiseManager(float _seed);
    float** getElevationMap(const int width, const int height,const float frequency = 0.05,const float elevationMax = 5);

};


#endif //BARRENLANDSMASTER_NOISEMANAGER_H
