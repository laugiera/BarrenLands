//
// Created by Lou Landry on 16/01/2018.
//

#include <NoiseManager.hpp>
#include <ProgramManager.hpp>
#include <TextureManager.hpp>
#include "ProceduralMap.hpp"
/**
 * Constructor
 * @param NoiseManager * noise
 */
ProceduralMap::ProceduralMap(NoiseManager *noise) : ProceduralObject(), sea(nullptr){
    generateVertices(noise);
    generateIndices();
    generateNormals();
    createMoistureMap();
    createBiomes();
    createSea();
}
/**
 * Destructor
 */
ProceduralMap::~ProceduralMap() {
    delete sea;
    for( ProceduralObject * b : biomes){
        delete b;
    }
}

/**
 * Generate map vertices to form a plannar shape with a set number of subdivisions
 * Uses a noise map to handle height
 * Vector must be cleared first to avoid conflict with superClass implementation
 * @param noise
 */
void ProceduralMap::generateVertices(NoiseManager *noise) {
    vertices.clear();
    int width = Tools::width;
    int i, j;
    //test génération bruit
    float** terrain = noise->getElevationMap(Tools::nbSub+1, Tools::nbSub+1);
    float ** humidite = NoiseManager::getInstance().getMoistureMap(Tools::nbSub +1, Tools::nbSub +1);
    for(i=0; i<Tools::nbSub+1; ++i){
        for(j=0; j<Tools::nbSub+1; j++){
            vertices.push_back(glimac::ShapeVertex(
                    glm::vec3(-width*Tools::nbSub/2.0+j*width, terrain[i][j], -width*Tools::nbSub/2.0+i*width),
                    glm::vec3(0, 0, 0),
                    glm::vec2(i, j),
                    humidite[i][j]
            ));
        }
    }
}

/**
 * Generates indices according to map geometry
 */
void ProceduralMap::generateIndices() {
    indices.clear();
    int i, j;
    for(i=0; i<Tools::nbSub; ++i){
        for(j=0; j<Tools::nbSub; ++j){
            indices.push_back(i*Tools::nbSub + j + i); //0
            indices.push_back(i*Tools::nbSub + j + 1 + i); //1
            indices.push_back((i+1)*Tools::nbSub + j + 1 + i);  //2
            indices.push_back(i*Tools::nbSub + j + 1 + i); //1
            indices.push_back((i+1)*Tools::nbSub + j + 1 + i); //2
            indices.push_back((i+1)*Tools::nbSub + j + 2 + i); //3
        }
    }
}

/**
 * Generates normals according to map geometry
 */
void ProceduralMap::generateNormals() {
    int i, j;
    glm::vec3 dir1;
    glm::vec3 dir2;
    glm::vec3 norm;

    for(i=0; i < Tools::nbSub*Tools::nbSub*2; ++i){
        if(i%2 == 0){
            dir1 = vertices[indices[3*i+1]].position - vertices[indices[3*i]].position;
            dir2 = vertices[indices[3*i+2]].position - vertices[indices[3*i]].position;
        }
        else{
            dir1 = vertices[indices[3*i]].position - vertices[indices[3*i+1]].position;
            dir2 = vertices[indices[3*i+2]].position - vertices[indices[3*i+1]].position;
        }
        norm = glm::normalize(glm::cross(dir2, dir1));
        vertices[indices[3*i]].normal += norm;
        vertices[indices[3*i+1]].normal += norm;
        vertices[indices[3*i+2]].normal += norm;


    }

    for(i=0; i < vertices.size(); ++i){
        vertices[indices[i]].normal = glm::normalize(vertices[indices[i]].normal);
    }
}

/**
 * Create a render object for the map and for the sea and the biomes by calling their create function
 * @param programManager
 * @param textureManager
 */
void ProceduralMap::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    for(ProceduralBiome * b : biomes){
        b->createRenderObject(programManager, textureManager);
        //b->setPosition();
    }
    renderObject = new RenderMap(programManager->getMapProgram(), chooseTextures(textureManager));
    renderObject->fillData(vertices, indices);
    sea->createRenderObject(programManager, textureManager);
}

/**
 * Return the vertex designated by the coordinates i, j
 * @param i
 * @param j
 * @return
 */
glimac::ShapeVertex ProceduralMap::getVertex(int i, int j){
    return vertices[i*(Tools::nbSub+1)+j];
}

/**
 * Returns all the vertices of the map
 * @return
 */
std::vector<glimac::ShapeVertex> ProceduralMap::getVertices(){
    return vertices;
}

/**
 * Creates the biomes
 * Uses the moisture map and height to define biomes
 * Pushes elements to the biomes using a scattering map for each Family of element
 */
void ProceduralMap::createBiomes() {

    createBiomeColors();
    
    biomes.push_back(new ProceduralBiome(RenderMap::sand,"sand"));
    biomes.push_back(new ProceduralBiome(RenderMap::grass,"grass"));
    biomes.push_back(new ProceduralBiome(RenderMap::savannah,"savannah"));
    biomes.push_back(new ProceduralBiome(RenderMap::rock,"rock"));
    biomes.push_back(new ProceduralBiome(RenderMap::toundra,"toundra"));
    biomes.push_back(new ProceduralBiome(RenderMap::snow,"snow"));


    //ObjectMap
    std::vector <float> objectVec;
    float** objectMap = NoiseManager::getInstance().getRockMap(Tools::nbSub +1, Tools::nbSub +1, 0.5);
    for(int i = 0; i < Tools::nbSub +1; i++){
        for(int j = 0 ; j < Tools::nbSub +1; j++){
            objectVec.push_back(objectMap[i][j]);
        }
    }


    //Affectation des valeurs
    for(int i = 0; i<vertices.size(); i++){
        if (vertices[i].position.y < 1){
            if (vertices[i].moisture <= 0.1){
                biomes[0]->addVertex(&vertices[i]); // desert
                if(objectVec[i] >= 0.4){
                    biomes[0]->createElements(vertices[i].position, "rock");
                }
            } else {
                biomes[1]->addVertex(&vertices[i]); //herbe
                if(objectVec[i] >= 0.4){
                    biomes[1]->createElements(vertices[i].position, "rock");
                }
            }

        } else if (vertices[i].position.y < 2){
            if (vertices[i].moisture < 0.5){
                biomes[2]->addVertex(&vertices[i]); //savane
                if(objectVec[i] >= 0.4){
                    biomes[2]->createElements(vertices[i].position, "rock");
                }
            } else {
                biomes[1]->addVertex(&vertices[i]); //herbe
                if(objectVec[i] >= 0.4){
                    biomes[1]->createElements(vertices[i].position, "rock");
                }
            }

        } else if (vertices[i].position.y < 5){
            if (vertices[i].moisture < 0.1){
                biomes[3]->addVertex(&vertices[i]); //roche
                if(objectVec[i] >= 0.4){
                    biomes[3]->createElements(vertices[i].position, "rock");
                }
            } else {
                biomes[4]->addVertex(&vertices[i]); //toundra
                if(objectVec[i] >= 0.4){
                    biomes[4]->createElements(vertices[i].position, "rock");
                }
            }
        } else {
            biomes[5]->addVertex(&vertices[i]); //toundra neige - no elements
        }

    }
}

/**
 * Chooses textures in the texture Manager to pass to the renderModel
 * Also creates the moistureTexture from the MoistureMap and adds it to the vector
 * @param textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralMap::chooseTextures(TextureManager *textureManager) {
    glcustom::Texture * moistureTexture = new glcustom::Texture(Tools::nbSub +1, Tools::nbSub +1, moistureMap.data(), GL_RED);
    std::vector<glcustom::Texture *> textures;
    textures.push_back(moistureTexture);
    textures.push_back(textureManager->getRandomTexture("sand"));
    textures.push_back(textureManager->getRandomTexture("rock"));
    return textures;
}


/**
 * Creates the moistureMap using the noiseManager
 */
void ProceduralMap::createMoistureMap() {
    float ** humidite = NoiseManager::getInstance().getMoistureMap(Tools::nbSub +1, Tools::nbSub +1);
    for(int i = 0; i < Tools::nbSub +1; i++){
        for(int j = 0 ; j < Tools::nbSub +1; j++){
            moistureMap.push_back(humidite[i][j]);
        }
    }
}

/**
 * Creates the procedural Element for the sea
 */
void ProceduralMap::createSea() {
    sea = new ProceduralSea();
}

/**
 * Draw the map and calls draw for the sea and the biomes
 * @param viewMatrix
 */
void ProceduralMap::draw(const glm::mat4 &viewMatrix) {
    //draw the sea
    sea->draw(viewMatrix);
    //draw the map vertex
    renderObject->transform(position, 0, glm::vec3(0,1,0), glm::vec3(1));
    renderObject->render(viewMatrix);
    //draw the elements
    for(ProceduralObject * biome : biomes){
        biome->draw(viewMatrix);
    }
}

void ProceduralMap::createBiomeColors() {
    Color baseColor = Color();
    Color derivedColor = baseColor;

    derivedColor.lighten(0.2);  derivedColor.red(0.2); derivedColor.green(0.1);
    RenderMap::sand = new Color(&derivedColor);

    derivedColor = baseColor; derivedColor.lighten(0.2);  derivedColor.green(0.2); derivedColor.blue(0.1);
    RenderMap::grass = new Color(&derivedColor);

    derivedColor = baseColor; derivedColor.lighten(0.5);
    RenderMap::snow = new Color(&derivedColor);

    derivedColor = baseColor; derivedColor.lighten(0.3); derivedColor.blue(0.3);
    RenderMap::rock = new Color(&derivedColor);

    derivedColor = baseColor; derivedColor.darken(0.1); derivedColor.blue(0.3); derivedColor.randomSimilarColor(0.2);
    RenderMap::toundra = new Color(&derivedColor);

    derivedColor = baseColor; derivedColor.darken(0.1); derivedColor.red(0.3); derivedColor.randomSimilarColor(0.2);
    RenderMap::savannah = new Color(&derivedColor);


}

