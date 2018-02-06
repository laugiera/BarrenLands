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
ProceduralMap::ProceduralMap() : ProceduralObject(), sea(nullptr){
    generateVertices();
    generateIndices();
    generateNormals();
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
    std::cout << "delete map ok" << std::endl;
}

/**
 * Generate map vertices to form a plannar shape with a set number of subdivisions
 * Uses a noise map to handle height
 * Vector must be cleared first to avoid conflict with superClass implementation
 * @param noise
 */
void ProceduralMap::generateVertices() {
    vertices.clear();
    float width = Tools::width;
    int i, j;
    //test génération bruit
    float** terrain = NoiseManager::getInstance().heightMap;
    float ** humidite = NoiseManager::getInstance().moistureMap;
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


    //Affectation des valeurs
    float rockLevel = 0.3;
    float grassLevel = 0.7;

    try {
        for (int i = 0; i < vertices.size(); i++) {
            if (NoiseManager::getInstance().heightMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] > Tools::seaLevel) {
                if (vertices[i].position.y < 1) {
                    if (vertices[i].moisture <= 0.1) {
                        //desert = small roundrocks
                        if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] > rockLevel - 0.2) { //roundrock
                            biomes[0]->createElement(glm::vec3(vertices[i].position.x +
                                                               NoiseManager::getInstance().getRandomFloat() *
                                                               1.5, //big random
                                                               vertices[i].position.y,
                                                               vertices[i].position.z +
                                                               NoiseManager::getInstance().getRandomFloat()),
                                                     "rock");

                        }
                    } else {
                        //herbe = grass + trees + roundrocks

                        if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] > rockLevel) { //roundrock
                            biomes[1]->createElement(glm::vec3(vertices[i].position.x +
                                                               NoiseManager::getInstance().getRandomFloat() *
                                                               1.5, //big random
                                                               vertices[i].position.y,
                                                               vertices[i].position.z +
                                                               NoiseManager::getInstance().getRandomFloat()),
                                                     "rock");
                        }

                        if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] > grassLevel)
                            biomes[1]->createElement(vertices[i].position, "grass");

                        if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] > grassLevel)
                            biomes[1]->createElement(vertices[i].position, "tree");

                    }

                } else if (vertices[i].position.y < 2) {
                    if (vertices[i].moisture < 0.5) {
                        //savane = mehnir rocks
                        if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] >
                            rockLevel) {
                            biomes[2]->createElement(
                                    glm::vec3(vertices[i].position.x + NoiseManager::getInstance().getRandomFloat(),
                                              vertices[i].position.y,
                                              vertices[i].position.z + NoiseManager::getInstance().getRandomFloat()),
                                    "rock");
                        }
                    }
                } else if (vertices[i].position.y < 5) {
                        //rocks = roundrock
                        if (vertices[i].moisture < 0.1) {
                            if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] > rockLevel) {
                                biomes[3]->createElement(glm::vec3(vertices[i].position.x +
                                                                   NoiseManager::getInstance().getRandomFloat() *
                                                                   1.5,
                                                                   vertices[i].position.y,
                                                                   vertices[i].position.z +
                                                                   NoiseManager::getInstance().getRandomFloat()),
                                                         "rock");
                            }
                        } else {
                            //toundra = crystal rock
                            if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] >
                                rockLevel) {
                                biomes[4]->createElement(
                                        glm::vec3(vertices[i].position.x + NoiseManager::getInstance().getRandomFloat(),
                                                  vertices[i].position.y,
                                                  vertices[i].position.z + NoiseManager::getInstance().getRandomFloat()),
                                        "rock");
                            }
                            if (objectMap[i / (Tools::nbSub + 1)][i % (Tools::nbSub + 1)] > grassLevel)
                                biomes[4]->createElement(vertices[i].position, "tree");
                            }
                } else {
                    //toundra neige - no elements
                }
            }
        }
        ElementManager::getInstance().scatter();

    } catch(std::runtime_error & e) {
        std::cerr << e.what() << std::endl;
    }

}

/**
 * Chooses textures in the texture Manager to pass to the renderModel
 * Also creates the moistureTexture from the MoistureMap and adds it to the vector
 * @param textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralMap::chooseTextures(TextureManager *textureManager) {
    std::vector<glcustom::Texture *> textures;
    textures.push_back(textureManager->getRandomTexture("sand"));
    textures.push_back(textureManager->getRandomTexture("snow"));
    textures.push_back(textureManager->getRandomTexture("grass"));
    textures.push_back(textureManager->getRandomTexture("grass"));
    textures.push_back(textureManager->getRandomTexture("shadowMap"));
    return textures;
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
    renderObject->transform(glm::vec3(0,0,0), 0, glm::vec3(0,1,0), glm::vec3(1));
    renderObject->render(viewMatrix);
    //draw the elements
    std::vector<ProceduralObject *> elements = ElementManager::getInstance().getAllElements();
    for(ProceduralObject * el : elements){
        el->draw(viewMatrix);
    }
}

void ProceduralMap::createBiomeColors() {
    Color baseColor = Color();
    baseColor.lighten(0.3);
    baseColor.randomSimilarColor(NoiseManager::getInstance().getRandomFloat()*4);
    baseColor.saturate(-0.3);
    std::cout <<"base Color : "<< baseColor << std::endl;
    Color derivedColor = baseColor;

    //derivedColor.lighten(0.3);  derivedColor.red(0.2); derivedColor.green(0.2); derivedColor.saturate(0.3);
    //derivedColor.complementaryColor();
    derivedColor.randomSimilarColor(0.6);
    derivedColor.randomSimilarColor(0.2);
    derivedColor.lighten(NoiseManager::getInstance().getRandomFloat()*2);
    derivedColor.randomSimilarColor(0.1);
    derivedColor.saturate(-0.4);
    RenderMap::sand = new Color(&derivedColor);
    std::cout <<"sand Color : "<< *RenderMap::sand << std::endl;

    //derivedColor = baseColor; derivedColor.complementaryColor(); derivedColor.lighten(-0.05); derivedColor.blue(0.1);
    derivedColor = baseColor;
    derivedColor.randomSimilarColor(0.3);
    RenderMap::grass = new Color(&derivedColor);
    std::cout <<"grass Color : "<< *RenderMap::grass << std::endl;

    derivedColor = baseColor;
    derivedColor.lighten(0.4);
    derivedColor.saturate(-0.5);
    RenderMap::snow = new Color(&derivedColor);
    std::cout <<"snow Color : "<< *RenderMap::snow << std::endl;

    //derivedColor = baseColor; derivedColor.lighten(0.1); /*derivedColor.blue(0.05);*/ derivedColor.complementaryColor();
    derivedColor = baseColor;
    derivedColor.lighten(NoiseManager::getInstance().getRandomFloat()*2);
    derivedColor.randomSimilarColor(0.3);
    RenderMap::rock = new Color(&derivedColor);
    std::cout <<"rock Color : "<< *RenderMap::rock << std::endl;

    //derivedColor = baseColor; derivedColor.lighten(0.2);  derivedColor.red(0.2); //derivedColor.randomSimilarColor(0.1);
    derivedColor = baseColor;
    //derivedColor.complementaryColor();
    derivedColor.randomSimilarColor(0.6);
    derivedColor.randomSimilarColor(0.3);
    derivedColor.randomSimilarColor(NoiseManager::getInstance().getRandomFloat());
    derivedColor.saturate(-0.3);
    derivedColor.lighten(0.1);
    RenderMap::toundra = new Color(&derivedColor);
    std::cout <<"toundra Color : "<< *RenderMap::toundra << std::endl;

    //derivedColor = baseColor; derivedColor.lighten(0.1); derivedColor.blue(0.3); derivedColor.complementaryColor(); /*derivedColor.saturate(0.2);*/
    derivedColor = baseColor;
    derivedColor.lighten(NoiseManager::getInstance().getRandomFloat());
    derivedColor.randomSimilarColor(0.1);
    derivedColor.saturate(-0.4);
    RenderMap::savannah = new Color(&derivedColor);
    std::cout <<"savannah Color : "<< *RenderMap::savannah << std::endl;



}

