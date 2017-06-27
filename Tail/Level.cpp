#include <iostream>
#include "Level.h"
#include "Enemy.h"
#include "Entity.h"
#include "Helper.h"
#include "Breed.h"
#include <sstream>

using namespace std;

void CallLua(lua_State* state, char* funcName, void* userData) {
    lua_getglobal(state, funcName);
    if (!lua_isfunction(state, -1))
        cerr << "\nERROR: Invalide function name [spawn_enemy]";

    lua_pushlightuserdata(state, userData);
    lua_call(state, 1, 0);
}

static void lua_Spawn(Level* level, const std::string& filename)
{
    level->Spawn(filename);
}

static int lua_SpawnWrapper(lua_State* state) {
    const int arguments = lua_gettop(state);
    if (arguments != 2) {
        cerr << "\nERROR: Invalid amount of arguments on stack. [" << arguments << "]";
    }
    if (!lua_islightuserdata(state, 1)) {
        cerr << "\nERROR: First argument is not of type [light user data].";
    }
    if (!lua_isstring(state, 2)) {
        cerr << "\nERROR: Second argument is not of typ [string].";
    }

    Level* level = (Level*)(lua_touserdata(state, 1));
    const char* filename = lua_tostring(state, 2);
    lua_Spawn(level, filename);

    return 0;
}

static int lua_GetMaxEnemiesSpawned(Level* level)
{
    return level->GetMaxEnemiesSpawend();
}

static int lua_GetMaxEnemiesSpawnedWrapper(lua_State* state)
{

    const int arguments = lua_gettop(state);
    if(arguments != 1)
        cerr << "\nERROR: Invalid amount of arguments on stack. [" << arguments << "]";

    Level* level = (Level*)(lua_touserdata(state, 1));
    int number = lua_GetMaxEnemiesSpawned(level);
    lua_pushnumber(state, number);

    return 1;
}

static int lua_GetTypeToSpawn(Level* level)
{
    return level->GetTypeToSpawn();
}

static int lua_GetTypeToSpawnWrapper(lua_State* state)
{
    const int arguments = lua_gettop(state);
    if(arguments != 1)
        cerr << "\nERROR: Invalid amount of arguments on stack. [" << arguments << "]";

    Level* level = (Level*)(lua_touserdata(state, 1));
    int type = lua_GetTypeToSpawn(level);

    if(type == -1)
        cerr << "\nERROR: There are no types ready to spawn from stack.";

    lua_pushnumber(state, type);

    return 1;
}

Level::Level(const char* filename) :
    m_state(luaL_newstate()),
    m_maxEnemiesPerLevel(100),
    m_maxEnemiesSpawend(6),
    m_entities(),
    m_types(),
    m_gameTime(0.01)
{
    if(m_state == 0)
        cerr << "\nERROR: Unable to create lua state." << endl;

    luaL_openlibs(m_state);
 
    if(luaL_dofile(m_state, filename))
    {
        const char* err = lua_tostring(m_state, -1);
        cerr << "\nERROR: " << err;
    }

    lua_register(m_state, "spawn", lua_SpawnWrapper);
    lua_register(m_state, "get_maxenemies", lua_GetMaxEnemiesSpawnedWrapper);
    lua_register(m_state, "get_typetospawn", lua_GetTypeToSpawnWrapper);
}

Level::~Level()
{
    while(!m_entities.empty())
    {
        delete m_entities.back();
        m_entities.pop_back();
    }
    lua_close(m_state);
    m_state = 0;
}

void Level::Initialize()
{
    // Initialize first wave of enemies
    CallLua(m_state, "initialize", this);
}

void Level::Render(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("Assets/Fonts/consola.ttf");

    for(Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end(); eItr++)
    {
        // Debug text for entities
        stringstream ss;
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color(0,200,0));
        ss << "LookAt: (" << (*eItr)->GetLookAt().x << ", " << (*eItr)->GetLookAt().y << ")" << endl;
        ss << "Position: (" << (*eItr)->GetPosition().x << ", " << (*eItr)->GetPosition().y << ")" << endl;
        ss << "Rotation: " << (*eItr)->GetRotation() << endl;
        ss << "Target: (" << (*eItr)->GetTarget().x << ", " << (*eItr)->GetTarget().y << ")" << endl;
        text.setPosition((*eItr)->GetPosition());
        text.setString(ss.str());
        window.draw(text);

        // Draw entities
        window.draw((*eItr)->GetSprite());
    }
}

void Level::Update(sf::RenderWindow& window)
{
    m_gameTime.Accumulate();

    while (m_gameTime.StepForward()) {
        for (Entities::iterator eItr = m_entities.begin(); eItr != m_entities.end(); eItr++) {
            (*eItr)->Update(window, m_gameTime.DeltaTime());
        }
    }

    Render(window);
}

void Level::Spawn(const std::string& filename)
{
    Breed* breed = GetBreed(filename);

    // Factorize a new enemy from breed and set spawn.
    Entity* entity = breed->NewEnemy();
    entity->SetPosition(
        sf::Vector2f(
            (float)Random(0, 1280), 
            (float)Random(0, 720)));

    m_entities.push_back(entity);
}

int Level::GetMaxEnemiesPerLevel()
{
    return m_maxEnemiesPerLevel;
}

int Level::GetMaxEnemiesSpawend()
{
    return m_maxEnemiesSpawend;
}

Breed* Level::GetBreed(const std::string& filename) {
    EnemyBreeds::iterator itr = m_breeds.find(filename);
    if (itr != m_breeds.end()) {
        return itr->second;
    }
    else {
        // Load enemy variables from lua file
        Config enemyConfig(filename);
        double health = enemyConfig.GrabReal("HEALTH");
        double walkingSpeed = enemyConfig.GrabReal("WALKING_SPEED");
        const char* followingSprite = enemyConfig.GrabString("FOLLOWING_SPRITE");
        const char* idlingSprite = enemyConfig.GrabString("IDLING_SPRITE");

        Breed *breed = new Breed(
            health,
            walkingSpeed,
            idlingSprite,
            followingSprite
            );

        // Create an enemy breed
        m_breeds[filename] = breed;
        return breed;
    }
}

int Level::GetTypeToSpawn()
{
    if(m_types.empty())
        return -1;

    int type = m_types.top();
    m_types.pop();

    return type;
}