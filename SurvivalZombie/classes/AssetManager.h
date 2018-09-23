#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
//#include<memory>
/*!
 * Klasa do wspó³dzielenia assetów (w tej chwili:tekstur)
 * 
 */
class AssetManager
{
private:
	static std::unordered_map<std::string, sf::Texture*> textureCatche;
	static std::unordered_map<std::string, sf::SoundBuffer*> soundsCatche;


public:
	
	static bool AddTexture(const std::string &name, const std::string &filename)
	{

		sf::Texture * newTex = new sf::Texture();
		if ( !newTex->loadFromFile( filename ) )
			return false;
		else
		{
			newTex->setSmooth( true );
			textureCatche.insert( std::pair<std::string, sf::Texture*>( name, newTex ) );
		}
		return true;

	}

	static bool AddTexture( const std::string& name, sf::Texture * newTex )
	{
		textureCatche.insert( std::pair<std::string, sf::Texture*>( name, newTex ) );
		return true;
	}

	static sf::Texture* GetTexture( std::string name )
	{
		const auto i = textureCatche.find( name );
		if ( i != textureCatche.end() )
			return i->second;
		else
			return nullptr;
	}

	static bool AddSound( const std::string &name, const std::string &filename )
	{

		sf::SoundBuffer * newSound = new sf::SoundBuffer();
		if ( !newSound->loadFromFile( filename ) )
			return false;
		else
		{
			soundsCatche.insert( std::pair<std::string, sf::SoundBuffer*>( name, newSound ) );
		}
		return true;

	}

	static sf::SoundBuffer* GetSound( std::string name )
	{
		const auto i = soundsCatche.find( name );
		if ( i != soundsCatche.end() )
			return i->second;
		else
			return nullptr;
	}
	/*!
	 * Sprawdza czy tekstura jest ju¿ w pamiêci.Jeœli nie, wczytuje do mapy.
	 * 
	 * \param name- scie¿ka do pliku tekstury, u¿ywana jako klucz do mapy
	 * \return shared_ptr do tekstury
	 */
	/*
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
	*/
	/*!
	 * Usuwa z pamiêci nieu¿ywane tekstury.
	 * 
	 */
	/*
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
	*/
};

