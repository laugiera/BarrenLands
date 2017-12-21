//
// Created by natshez on 09/12/2017.
//

#include "../include/NoiseManager.h"

NoiseManager::NoiseManager(float _seed): seed(_seed) {
    noise.SetNoiseType(FastNoise::PerlinFractal);
    noise.SetSeed(seed);
}

float** NoiseManager::getElevationMap(const int width, const int height,const float frequency,const float elevationMax){
    noise.SetFrequency(frequency);

    float** elevationMap = 0;
    float e = 0;
    elevationMap = new float*[width];

    for (int x = 0; x < width; x++)
    {
        elevationMap[x] = new float[height];
        for (int y = 0; y < height; y++){
            e = (noise.GetNoise(x,y)
                 + 0.5 * noise.GetNoise(2*x,2*y)
                 + 0.25 * noise.GetNoise(4*x,4*y))*elevationMax;
            elevationMap[x][y] = pow(e,2);
        }
    }
    return elevationMap;
};
