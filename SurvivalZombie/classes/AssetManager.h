#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class AssetManager
{
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textureCatche;

public:
	
	static std::shared_ptr<sf::Texture> GetTexture(const std::string& name)
	{
		const auto i = textureCatche.find(name);
		if (i != textureCatche.end())
		{
			return i->second;
		}
		else
		{
			auto newTex = std::make_shared<sf::Texture>();
			newTex->loadFromFile(name);
			textureCatche.insert({ name,newTex });
			return newTex;
		}
	}
	static void Clear()
	{
		for (auto i = textureCatche.begin(); i != textureCatche.end(); )
		{
			if (i->second.unique())
			{
				i = textureCatche.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
};

