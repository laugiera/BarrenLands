//
// Created by natshez on 09/12/2017.
//

#include <glm/geometric.hpp>
#include "../include/NoiseManager.hpp"

float NoiseManager::seed = 1200;

NoiseManager::NoiseManager(){
    noise.SetNoiseType(FastNoise::PerlinFractal);
    noise.SetInterp(FastNoise::Quintic);
   // noise.SetFractalType(FastNoise::RigidMulti);
   // noise.SetFractalOctaves();
    noise.SetSeed(NoiseManager::getSeed());
}

float** NoiseManager::getElevationMap(const int width, const int height,const float frequency,const float elevationMax){
    noise.SetFrequency(frequency);

    float** elevationMap = 0;
    float e = 0, b = 0.1, c = 0.5, distance_carre =0, distance = 0;
    elevationMap = new float*[width];

    for (int x = 0; x < width; x++)
    {
        elevationMap[x] = new float[height];
        for (int y = 0; y < height; y++){
            e = (noise.GetNoise(x,y)
                 + 0.5 * noise.GetNoise(2*x,2*y) //hills
                 + 0.25 * noise.GetNoise(4*x,3*y))*elevationMax; //moutains
            e = pow(e,2);//push up mountains and make down valley
            distance_carre =((width/2)-x) * ((width/2)-x) + ((height/2)-y)* ((height/2)-y);
            distance = 2 * sqrt(distance_carre);
            if(distance > height -15)
                e = e -( b*pow(distance,c));
            if(distance > height -10)
                e = e -( b*pow(distance,c+0.1));
            if(distance > height -5)
                e = e -( b*pow(distance,c+0.5));
            elevationMap[x][y] = e;

        }
    }
    return elevationMap;
};
