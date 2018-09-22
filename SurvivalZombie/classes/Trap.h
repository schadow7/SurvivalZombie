#include "StaticBody.h"

class BasicEntanglements :
	public StaticBody
{
public:
	BasicEntanglements(b2World* world, b2Vec2 position, sf::Texture* ntexture = AssetManager::GetTexture("grad2"));
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
	int sizey; //rozmiar Obstacle w pikselach
	int sizex;
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
	sf::Time				attack_timer;
	sf::Time				attack_cooldown;
private:
	sf::Texture* textureDead;
};

class Door :
	public BasicEntanglements
{
public:
	Door(b2World* world, b2Vec2 position, sf::Texture* ntexture = AssetManager::GetTexture("grad2"));
	~Door();
};

