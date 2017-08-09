#include "AssetsManager.h"
#include <iostream>

using namespace std;

const static string PICTURE_PATH = "Assets/Pictures/";

AssetsManager AssetsManager::m_instance;
AssetsManager&	AssetsManager::Ref()
{
    return m_instance;
}

AssetsManager::AssetsManager(){}
AssetsManager::~AssetsManager()
{
    ReleaseTextures();
}

const sf::Texture& AssetsManager::GetTexture(const std::string& name)
{
    m_textureIterator = m_textures.find(name);

    if(m_textureIterator != m_textures.end())
        return *m_textureIterator->second;

    if(!AddTexture(name))
        cerr << "\nERROR: could not load texture [" << name << "]";

    m_textureIterator = m_textures.find(name);
    if(m_textureIterator == m_textures.end())
        cerr << "\nERROR: unable to find texture [" << name << "]";

    return *m_textureIterator->second;
}

const sf::Texture* AssetsManager::GetTexturePointer(const std::string& name) {
    m_textureIterator = m_textures.find(name);

    if (m_textureIterator != m_textures.end())
        return m_textureIterator->second;

    if (!AddTexture(name))
        cerr << "\nERROR: could not load texture [" << name << "]";

    m_textureIterator = m_textures.find(name);
    if (m_textureIterator == m_textures.end())
        cerr << "\nERROR: unable to find texture [" << name << "]";

    return m_textureIterator->second;
}

bool AssetsManager::AddTexture(std::string name)
{

    m_textures.insert(make_pair(name, new sf::Texture()));

    if(!m_textures[name]->loadFromFile(PICTURE_PATH + name))
        return false;

    m_textures[name]->setSmooth(false);

    return true;
}

void AssetsManager::ReleaseTextures()
{
    auto itr = m_textures.begin();
    const auto end = m_textures.end();
    for (; itr != end;itr++) {
        delete itr->second;
    }
    m_textures.clear();
}