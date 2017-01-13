#ifndef PLAYER_H
#define PLAYER_H  

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <vector>
#include <String>
#include "Terrain.h"

using namespace std;

class Player {
private:
	std::vector<std::string> playerSprite;
	double xPos;
	double yPos;
	double maxX;
	double maxY;
	double jumpSpeed;
	bool isRight;
	bool isJump;
	bool isAttack;
	int index; 
	int delay;
	int time;
	int size;
	int health;
	int speedOrigin;
	sf::FloatRect boundBox;
	sf::FloatRect boundBoxAttack;
public:
	Player(sf::RenderWindow &window, double xPos, double yPos, double jumpSpeed);
	void move(vector<Terrain> stuff, vector<Terrain> &enemies);
	void drawPlayer(sf::RenderWindow &window);
	int getHealth();
	sf::FloatRect getBoundBox();
	void setHealth(int change);
	void setXPosition(int change);

};

#endif