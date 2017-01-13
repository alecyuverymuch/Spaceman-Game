#include "Terrain.h"
#include <iostream>

using namespace std;

Terrain::Terrain(int xPos, int yPos, string picName):xPos(xPos), yPos(yPos), picName(picName) {
	if (!texture.loadFromFile(picName))
	{
		// error...
	}
	movement = 1;
	sprite.setTexture(texture);
	sprite.setOrigin(xPos, yPos);
	boundBox = sprite.getGlobalBounds();
}

sf::FloatRect Terrain::getBoundBox() {
	return boundBox;
}

void Terrain::drawTerrain(sf::RenderWindow &window) {
	window.draw(sprite);
}

int Terrain::getYPos()
{
	return yPos;
}

int Terrain::getXPos()
{
	return xPos;
}

void Terrain::moveEnemy()
{
	if (xPos == -740) {
		movement = -1;
	}
	else if (xPos == -940) {
		movement = 1;
	}
	xPos += movement;
	sprite.setPosition(xPos + 840, yPos + 274);
	boundBox = sprite.getGlobalBounds();
}