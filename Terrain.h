#ifndef TERRAIN_H
#define TERRAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <vector>
#include <String>

using namespace std;

//A class for terrain and basic enemy objects
class Terrain {
private:
	int xPos, yPos;
	sf::FloatRect boundBox;
	sf::Texture texture;
	sf::Sprite sprite;
	string picName;
	int movement;
public:
	Terrain(int x,int y, string picName);
	sf::FloatRect getBoundBox();
	void drawTerrain(sf::RenderWindow &window);
	int getYPos();
	int getXPos();
	void moveEnemy();
};
#endif
