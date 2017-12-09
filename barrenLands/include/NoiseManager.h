//
// Created by natshez on 09/12/2017.
//

#ifndef BARRENLANDSMASTER_NOISEMANAGER_H
#define BARRENLANDSMASTER_NOISEMANAGER_H

#include "../../fastnoise/FastNoise.h"

class NoiseManager {
public:
    NoiseManager();

    static float** getElevationMap(const int width, const int height, const float elevationMax, const float frequency = 0.01 ){
        FastNoise noise;
        noise.SetFrequency(frequency);

        float** elevationMap = 0;
        elevationMap = new float*[width];

        for (int x = 0; x < width; x++)
        {
            elevationMap[x] = new float[height];
            for (int y = 0; y < height; y++)
                elevationMap[x][y] = noise.GetPerlinFractal(x,y)*elevationMax;
        }
        return elevationMap;
    };
};


#endif //BARRENLANDSMASTER_NOISEMANAGER_H
