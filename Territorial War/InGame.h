#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Inputs.h"


class InGame
{
public:
	InGame(sf::RenderWindow* inWindow);
	void run();

private:
	void npcsUpdate(float dt);
	void npcsInit(Map* map);
	void checkHits(Player* player);
	bool circleIntersectsRect(const sf::CircleShape& circle, const sf::FloatRect& rect);
	void npcsDraw();
	void draw();
	void checkEndGame();
	void endScreen(bool win);

	sf::RenderWindow* window;
	sf::Texture endTex;
	sf::Texture homeTex;
	std::optional<sf::Sprite> end;
	std::optional<sf::Sprite> home;
	bool running = true;
	std::vector<Npc*> npcs;
	Map* map;
	Player* player;
	Inputs input;
};

