#include <iostream>
#include <sstream>
#include "Level.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include "Helper.h"
#include "Breed.h"
#include "SFMLClockWrapper.h"
#include "Components\AnimationComponent.h"
#include "AssetsManager.h"

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
    m_gameTime(0.01, new SFMLClockWrapper()),
    m_loading(true)
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

    m_font.loadFromFile("Assets/Fonts/consola.ttf");
    m_player = new Player();
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
    m_loading = false;
}

const static int FPS_SAMPLE = 100;
static double fps_samples[FPS_SAMPLE];
static int curr_pos(0);
void Level::Render(sf::RenderWindow& window)
{
    stringstream ss;
    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color(0, 0, 0));
    fps_samples[curr_pos] = m_gameTime.DeltaTime();
    curr_pos = (curr_pos + 1) % FPS_SAMPLE;
    double average = 0.0;
    for (size_t i = 0; i < FPS_SAMPLE; ++i) {
        average += fps_samples[i];
    }
    average *= (1.0 / FPS_SAMPLE);
    ss << "FPS: " << 1 / (average == 0.0 ? 1 : average);
    text.setPosition(sf::Vector2f(10.0f,10.0f));
    text.setString(ss.str());
    window.draw(text);

    window.draw(m_player->GetComponent<GraphicsComponent>()->GetSprite());
    for (const auto entity : m_entities) {
        window.draw(entity->GetComponent<GraphicsComponent>()->GetSprite());
    }
}

void Level::Update(sf::RenderWindow& window)
{
    if (m_loading) {
        return;
    }

    m_player->Update();
    for (const auto entity : m_entities) {
        entity->Update();
    }

    // Accumulate time from last frame
    m_gameTime.Accumulate();
    float sim_step_size = (float)m_gameTime.StepSize();
    while (m_gameTime.StepForward()) {
        m_player->FixedUpdate(window, sim_step_size, *this);
        for (const auto entity : m_entities) {
            entity->FixedUpdate(window, sim_step_size, *this);
        }
    }
    Render(window);
}

void Level::Spawn(const std::string& filename)
{
    Breed* breed = GetBreed(filename);

    // Factorize a new enemy from breed and set spawn.
    Entity* entity = breed->NewEnemy();

    const auto graphics = entity->AddComponent<GraphicsComponent>();
    const auto physics = entity->AddComponent<PhysicsComponent>();

    graphics->SetTexture(AssetsManager::Ref().GetTexture("enemy.png"));

    physics->EnableGravity(false);
    physics->SetPosition(sf::Vector2f(
        Random(0, 1280),
        Random(0, 720)));

    AnimationSheetInfo info;
    info.m_count = 16;
    info.m_duration = 0.04f;
    info.m_height = 64;
    info.m_width = 64;
    info.m_playback_type = PlaybackType::Loop;
    info.m_name = "ball_bounce_animation.png";
    const auto animation = entity->AddComponent<AnimationComponent>();
    animation->Init(info);
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
        float health = (float)enemyConfig.GrabReal("HEALTH");
        float walkingSpeed = (float)enemyConfig.GrabReal("WALKING_SPEED");
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