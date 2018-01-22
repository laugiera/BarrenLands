//
// Created by natshez on 09/12/2017.
//

#include <glm/geometric.hpp>
#include "../include/NoiseManager.hpp"

/****
Améliorations :
    Générer une map pour la répartition des objets qui va de 0 à 1 pour ses valeurs.
    Quand on génère un objet, on lui renvoie la valeur et, suivant cette dernière, l'objet aura une forme différente.

****/

/**
 * static seed default value
 */
float NoiseManager::seed = 1200;
/**
 * Constructor with default noise parameters
 */
NoiseManager::NoiseManager(){
    counter = 0;
    noise.SetNoiseType(FastNoise::PerlinFractal);
    noise.SetInterp(FastNoise::Quintic);
   // noise.SetFractalType(FastNoise::RigidMulti);
   // noise.SetFractalOctaves();
    noise.SetSeed(NoiseManager::getSeed());
}
/**
 * getElevationMap()
 * noise to make the hills and moutains on the map
 * @param width of the map
 * @param height of the map
 * @param frequency default = 0.05
 * @param elevationMax default = 5
 * @return float** double array of map vertices
 */
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
            distance_carre =((width/2)-x) * ((width/2)-x) + ((height/2)-y)* ((height/2)-y); //distance of the point from the center
            distance = 2 * sqrt(distance_carre);
            //makes coastlines on the edges of the map
            // c determines the speed of the decrease
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
/**
 * getMoistureMap()
 * Used to determines biomes positions
 * @param width of the map
 * @param height of the map
 * @param frequency default = 0.05
 * @return float** double array of map vertices
 */
float** NoiseManager::getMoistureMap(const int width, const int height,const float frequency){
    /*
     * Améliorations :
     *  -avoir plutôt du sable sur les bords
     * */
    noise.SetFrequency(frequency);

    float** moistureMap = 0;
    float e = 0, b = 0.1, c = 0.5, distance_carre =0, distance = 0;
    moistureMap = new float*[width];

    for (int x = 0; x < width; x++)
    {
        moistureMap[x] = new float[height];
        for (int y = 0; y < height; y++){
            e = (noise.GetNoise(x,y)
                 + 0.5 * noise.GetNoise(2*x,2*y)
                 + 0.25 * noise.GetNoise(4*x,3*y))*2;

            e = pow(e,2);
            moistureMap[x][y] = e;
        }
    }
    return moistureMap;
};
/**
 * getRockMap()
 * Used to determines rocks positions
 * @param width of the map
 * @param height of the map
 * @param frequency default = 0.05
 * @return float** double array of map vertices
 */
float** NoiseManager::getRockMap(const int width, const int height,const float frequency){

    noise.SetFrequency(frequency);

    float** rockMap = 0;
    float e = 0;
    rockMap = new float*[width];

    for (int x = 0; x < width; x++)
    {
        rockMap[x] = new float[height];
        for (int y = 0; y < height; y++){
            e = (noise.GetNoise(x,y)
                 + 0.25 * noise.GetNoise(4*x,3*y))*2;

            e = pow(e,2);
            rockMap[x][y] = e;
        }
    }
    return rockMap;
}

float NoiseManager::getRandomFloat() {
    counter ++;
    return noise.GetNoise(counter, counter);
};

float NoiseManager::getVerticesDisturbation(const int x, const int y, const int z){
    float disturb = noise.GetNoise(4*x,4*y,4*z)*10;
    return disturb;

}
