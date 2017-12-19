//
// Created by natshez on 09/12/2017.
//

#ifndef BARRENLANDSMASTER_NOISEMANAGER_H
#define BARRENLANDSMASTER_NOISEMANAGER_H

#include "../../fastnoise/FastNoise.h"
#include <Math.h>

class NoiseManager {
public:
    NoiseManager();

    static float** getElevationMap(const int width, const int height, const float elevationMax, const float frequency = 0.01 ){
        FastNoise noise;
        noise.SetFrequency(frequency);
        noise.SetNoiseType(FastNoise::PerlinFractal);
        //noise.SetNoiseType(FastNoise::Cellular);
       // noise.SetInterp(FastNoise::Hermite);
        //noise.SetFractalType(FastNoise::RigidMulti);
        //noise.SetCellularDistanceFunction(FastNoise::Natural);

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
                elevationMap[x][y] = pow(e,3);
            }
        }
        return elevationMap;
/*
        e =    1 * noise(1 * nx, 1 * ny);
        +  0.5 * noise(2 * nx, 2 * ny);
        + 0.25 * noise(4 * nx, 4 * ny);
        elevation[y][x] = Math.pow(e, 10.00);*/
    };
};


#endif //BARRENLANDSMASTER_NOISEMANAGER_H
