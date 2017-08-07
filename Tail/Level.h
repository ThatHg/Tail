#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <map>
#include "lua.hpp"
#include "GameTime.h"
#include "EntityFactory.h"
#include "ParticleSystem.h"

class Entity;

class Level
{
public:
    typedef std::vector<Entity*> Entities;

    Level(const char* filename);
    ~Level();

    void Initialize();
    void Update(sf::RenderWindow& window);
    void Spawn(const std::string& filename);
    int GetTypeToSpawn();
    int GetEnemyPerLevelCount();
    int GetStartEnemyCount();
    const Entities& GetEntities() const { return m_entities; }
    const Entity* GetPlayer() const { return m_player; }
private:
    void LoadLevel(const std::string& filename);
    void Render(sf::RenderWindow& window);

    int m_enemiesPerLevelCount;
    int m_startEnemyCount;
    Entities m_entities;
    Entity* m_player;
    lua_State* m_state;
    std::stack<int> m_types; // Pushes type of enemy to spawn on stack
    GameTime m_gameTime;
    bool m_loading;
    sf::Font m_font;
    EntityFactory m_entityFactory;
    ParticleSystem m_particleSystem;
};

#endif