#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <map>
#include "lua.hpp"
#include "Config.h"
#include "GameTime.h"

class Entity;
class Breed;

class Level
{
public:
    Level(const char* filename);
    ~Level();

    void Initialize();
    void Update(sf::RenderWindow& window);
    void Spawn(const std::string& filename);
    int GetTypeToSpawn();
    int GetEnemyPerLevelCount();
    int GetStartEnemyCount();
private:
    typedef std::vector<Entity*> Entities;
    typedef std::map<std::string, Breed*> EnemyBreeds;

    Breed* GetBreed(const std::string& filename);
    void LoadLevel(const std::string& filename);
    void Render(sf::RenderWindow& window);

    int m_enemiesPerLevelCount;
    int m_startEnemyCount;
    Entities m_entities;
    Entity* m_player;
    EnemyBreeds m_breeds;
    lua_State* m_state;
    std::stack<int> m_types; // Pushes type of enemy to spawn on stack
    GameTime m_gameTime;
};

#endif