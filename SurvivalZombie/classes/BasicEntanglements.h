#include "StaticBody.h"
#include <random>

class BasicEntanglements :
	public StaticBody
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="BasicEntanglements"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">The position in b2World.</param>
	/// <param name="size">The size in px.</param>
	/// <param name="ntexture">The new texture.</param>
	BasicEntanglements(b2World* world, b2Vec2 position, sf::Vector2i size = sf::Vector2i(25, 50), sf::Texture* ntexture = AssetManager::GetTexture("grad2"));
	~BasicEntanglements();
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Presolve(Entity*);
	void Render(sf::RenderWindow* window);
	void RenderInactive(sf::RenderWindow* window);
	void Update(sf::Time);
	void TakeDamage(float32 damage) override;
	/// <summary>
	/// Attacks the specified entity. Uses TakeDamege()
	/// </summary>
	/// <param name="entity">The entity.</param>
	virtual void Attack(Entity * entity);
	/// <summary>
	/// Ustawia iloœæ zadawanych obra¿eñ
	/// </summary>
	/// <param name="">Obra¿enia .</param>
	void SetDamage(float32);
	/// <summary>
	/// Ustawia k¹t jaki obiekt obiekt na mapie
	/// </summary>
	/// <param name="">The .</param>
	void SetAngle(float32);
	/// <summary>
	/// Zwraca rozmiar w pikselach
	/// </summary>
	/// <returns></returns>
	b2Vec2 GetPxSize();
	/// <summary>
	/// Podnosi wytrzyma³oœæ o podan¹ liczba albo do maksimum
	/// </summary>
	/// <param name=""> .</param>
	void Repair(int);
	/// <summary>
	/// Wstawia maksymaln¹ wytrzyma³oœæ barykady
	/// </summary>
	/// <param name=""> .</param>
	void SetMaxHP(int);
	/// <summary>
	/// Ustawia obra¿enia jakie barykada zadaje atakuj¹cym j¹ obiektom
	/// </summary>
	/// <param name=""> .</param>
	void SetDamage(int);
	/// <summary>
	/// Aktywuje obiekt jeœli jest nieaktywny.
	/// </summary>
	void MakeActive();
	/// <summary>
	/// Pobiera stan wytrzyma³oœci.
	/// </summary>
	/// <returns></returns>
	int getHitpoints();
	/// <summary>
	/// Pobiera maksymaln ¹wytrzyma³oœæ.
	/// </summary>
	/// <returns></returns>
	int getMaxHitpoints();

protected:
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
	sf::Time				attack_timer;
	sf::Time				attack_cooldown;
	sf::Texture*			textureDead;
	std::vector<sf::Sound>	hitSounds;
	std::default_random_engine				engine;
	std::uniform_int_distribution<int>		soundDistribution{ 0, 10 };
	int soundsCount;
private:
	
};

/// <summary>
/// Przeszkoda pozwalaj¹ca przejœæ tylko graczowi
/// </summary>
/// <seealso cref="BasicEntanglements" />
class Door :
	public BasicEntanglements
{
public:
	Door(b2World* world, b2Vec2 position, sf::Vector2i size = sf::Vector2i(25, 50), sf::Texture* ntexture = AssetManager::GetTexture("grad2"));
	~Door();
};

class Bounds : public BasicEntanglements
{
public:
	Bounds( b2World* world, b2Vec2 position, sf::Vector2i size = sf::Vector2i( 25, 50 ), sf::Texture* ntexture = AssetManager::GetTexture( "no_texture" ) );
	~Bounds();

};
