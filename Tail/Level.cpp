#include <iostream>
#include <sstream>
#include "Level.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include "Helper.h"
#include "Breed.h"
#include "SFMLClockWrapper.h"
#include "Transform.h"
#include "Components\PhysicsComponent.h"
#include "Components\PlayerInputComponent.h"

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

static int lua_GetStartEnemyCount(Level* level)
{
    return level->GetStartEnemyCount();
}

static int lua_GetStartEnemyCountWrapper(lua_State* state)
{

    const int arguments = lua_gettop(state);
    if(arguments != 1)
        cerr << "\nERROR: Invalid amount of arguments on stack. [" << arguments << "]";

    Level* level = (Level*)(lua_touserdata(state, 1));
    int number = lua_GetStartEnemyCount(level);
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
    m_enemiesPerLevelCount(0),
    m_startEnemyCount(0),
    m_entities(),
    m_types(),
    m_gameTime(0.01, new SFMLClockWrapper())
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
    lua_register(m_state, "get_startenemycount", lua_GetStartEnemyCountWrapper);
    lua_register(m_state, "get_typetospawn", lua_GetTypeToSpawnWrapper);

    m_player = new Player();
    m_player->AddComponent<PlayerInputComponent>();
    auto c = m_player->AddComponent<PhysicsComponent>();
    c->EnableGravity(true);
    m_player->SetPosition(sf::Vector2f(300,300));
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
    delete m_player;
}

void Level::Initialize()
{
    // Initialize first wave of enemies
    LoadLevel("level1.lua");
    CallLua(m_state, "initialize", this);
}

void Level::Render(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("Assets/Fonts/consola.ttf");
    stringstream ss;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color(0, 0, 0));
    double delta = m_gameTime.DeltaTime();
    ss << "FPS: " << 1 / (delta == 0.0 ? 1 : delta);
    text.setPosition(sf::Vector2f(10.0f,10.0f));
    text.setString(ss.str());
    window.draw(text);
   
    // Draw entities
    window.draw(m_player->GetSprite());
    for (int i = 0; i < m_entities.size(); ++i)
    {
        window.draw(m_entities[i]->GetSprite());
    }
}

void Level::Update(sf::RenderWindow& window)
{
    // Accumulate time from last frame
    m_gameTime.Accumulate();
    while (m_gameTime.StepForward()) {
        m_player->FixedUpdate(window, m_gameTime.StepSize(), *this);

        for (int i = 0; i < m_entities.size(); ++i) {
            m_entities[i]->FixedUpdate(window, m_gameTime.StepSize(), *this);
        }
    }
    m_player->Update();
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

int Level::GetEnemyPerLevelCount()
{
    return m_enemiesPerLevelCount;
}

int Level::GetStartEnemyCount()
{
    return m_startEnemyCount;
}

void Level::LoadLevel(const std::string& filename) {
    // Load level variables from lua file
    Config levelConfig(filename);
    m_startEnemyCount = levelConfig.GrabInteger("START_ENEMY_COUNT");
    m_enemiesPerLevelCount = levelConfig.GrabInteger("ENEMY_PER_LEVEL_COUNT");
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