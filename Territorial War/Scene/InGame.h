#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "../Map.h"
#include "../Entities/NPC.h"
#include "../Entities/Player.h"
#include "../Inputs.h"


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

	void WaveInfini();
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


	int waveNumber = 0;
	int targetNpcCount = 0;


	int score = 0;
	int pointsPerNpc = 10;
	int waveBonusMultiplier = 50;
	int maxNpcs = 100;


	sf::Font font;
	std::optional<sf::Text> scoreText;
};