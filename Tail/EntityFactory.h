#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <string>
#include <map>

class Config;
class Entity;

class EntityFactory {
public:
    EntityFactory();
    ~EntityFactory();
    Entity* CreatePlayer(const std::string& breed_type);
    Entity* CreateEnemy(const std::string& breed_type);
private:
    typedef std::map<const std::string, const Config*> BreedConfigs;
    const Config* GetBreedConfig(const std::string& breed_type);
    BreedConfigs m_breeds;
};

#endif // !EntityFactory

