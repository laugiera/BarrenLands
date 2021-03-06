//
// Created by natshez on 09/12/2017.
//

#include <glm/geometric.hpp>
#include <Tools.hpp>
#include "../include/NoiseManager.hpp"

NoiseManager * NoiseManager::instance = nullptr;

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
    heightMap = getElevationMap(Tools::nbSub+1, Tools::nbSub+1);
    moistureMap = getMoistureMap(Tools::nbSub+1, Tools::nbSub+1);
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
    noise.SetNoiseType(FastNoise::PerlinFractal);
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
    noise.SetNoiseType(FastNoise::PerlinFractal);
    noise.SetFractalOctaves(1);

    float** moistureMap = 0;
    float e = 0;
    moistureMap = new float*[width];

    for (int x = 0; x < width; x++)
    {
        moistureMap[x] = new float[height];
        for (int y = 0; y < height; y++){
           e = (noise.GetNoise(x,y)
                 + 0.75 * noise.GetNoise(2*x,2*y)
                 + 0.5 * noise.GetNoise(4*x,3*y));

            moistureMap[x][y] = e;
            //std::cout << moistureMap[x][y] <<std::endl;
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
    noise.SetNoiseType(FastNoise::Cellular);

    float** rockMap = 0;
    float e = 0;
    rockMap = new float*[width];

    for (int x = 0; x < width; x++)
    {
        rockMap[x] = new float[height];
        for (int y = 0; y < height; y++){
            rockMap[x][y] = noise.GetNoise(x,y);
        }
    }
    return rockMap;
}
/**
 * getRandomFloat()
 * return a random number
 * @return float
 */
float NoiseManager::getRandomFloat() {
    noise.SetFrequency(0.05);
    noise.SetNoiseType(FastNoise::PerlinFractal);
    //counter += seed / 10000;
    counter += 5;
    float e = noise.GetNoise(counter, counter);
    //std::cout << e <<std::endl;
    /*
    float low = -1.0;
    float high = 1.0;
    float random = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
    */
    //return random;
    return e;
};
/**
 * setSeed()
 * parse a name into a seed number
 * @param name std::string
 */
void NoiseManager::setSeed(const std::string name){
    float seed = 0;
    for (int i = 0; i < name.size(); ++i) {
        seed += name[i]*i;
    }
    setSeed(seed);
    seedName = name;
}
/**
 * setSeed()
 * set the noise lib seed and initialise height and moisture maps
 * @param _seed float
 */
void NoiseManager::setSeed(const float _seed){
    seed = _seed;
    noise.SetSeed(_seed);
    heightMap = getElevationMap(Tools::nbSub+1, Tools::nbSub+1);
    moistureMap = getMoistureMap(Tools::nbSub+1, Tools::nbSub+1);
    srand(seed);
}
/*float NoiseManager::getVerticesDisturbation(const int x, const int y, const int z){
    noise.SetFrequency(0.05);
    noise.SetNoiseType(FastNoise::PerlinFractal);
    float disturb = noise.GetNoise(2*x,2*y,2*z)*10;
    return disturb;

}*/
