#include "StaticBody.h"

class BasicEntanglements :
	public StaticBody
{
public:
	BasicEntanglements(b2World* world, b2Vec2 position, sf::Vector2i size = sf::Vector2i(25,50), sf::Texture* ntexture = AssetManager::GetTexture("grad2"));
	~BasicEntanglements();
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Presolve(Entity*);
	void Render(sf::RenderWindow* window);
	void RenderInactive(sf::RenderWindow* window);
	void Update(sf::Time);
	void TakeDamage(float32 damage) override;
	virtual void Attack(Entity * entity);
	void SetDamage(float32);
	void SetAngle(float32);
	b2Vec2 GetPxSize();
	void Repair(int);
	void SetMaxHP(int);
	void SetDamage(int);
	void MakeActive();

protected:
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
	sf::Time				attack_timer;
	sf::Time				attack_cooldown;
	sf::Texture* textureDead;
private:
	
};

class Door :
	public BasicEntanglements
{
public:
	Door(b2World* world, b2Vec2 position, sf::Vector2i size = sf::Vector2i(25, 50), sf::Texture* ntexture = AssetManager::GetTexture("grad2"));
	~Door();
};


