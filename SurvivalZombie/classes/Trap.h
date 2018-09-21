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

protected:
	int sizey; //rozmiar Obstacle w pikselach
	int sizex1;
	int sizex2;
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
	sf::Time				attack_timer;
	sf::Time				attack_cooldown;
private:
	sf::Texture* textureDead;
};
