#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(sf::RenderWindow &window, double xPos, double yPos, double jumpSpeed) :
	xPos(xPos), yPos(yPos), jumpSpeed(jumpSpeed)
{
	maxX = window.getSize().x;
	maxY = window.getSize().y;
	isRight = true;
	isJump = false;
	isAttack = false;
	index = 0;
	size = 10;
	delay = 0;
	time = 6;
	health = 6;
	speedOrigin = this->jumpSpeed;
}

void Player::move(vector<Terrain> stuff, vector<Terrain> &enemies)
{
	for (int i = 0; i < enemies.size(); i++) {
		if (boundBoxAttack.intersects(enemies[i].getBoundBox())) {
			enemies.erase(enemies.begin() +i);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		bool cando = true;

		for (int i = 0; i < enemies.size(); i++) {
			if (boundBox.intersects(enemies[i].getBoundBox())) {
				cando = false;
				health--;
				xPos -= 50;
				cout << health << endl;
			}
		}
		for (int i = 0; i < stuff.size(); i++) {
			if (stuff[i].getBoundBox().intersects(boundBox)) {
				cando = false;
				yPos -= 1;
			}
			
		}
		if (cando) {
			isRight = true;

			xPos += 2;
			if (xPos >= maxX)
				xPos -= 2;
			delay++;
			if (delay > time)
			{
				index++;
				delay = 0;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		bool cando = true;
		for (int i = 0; i < enemies.size(); i++) {
			if (boundBox.intersects(enemies[i].getBoundBox())) {
				cando = false;
				health--;
				xPos += 50;
				cout << health << endl;
			}
		}
		for (int i = 0; i < stuff.size(); i++) {
			if (stuff[i].getBoundBox().intersects(boundBox)) {
				cando = false;
				yPos -= 1;
			}

		}
		if (cando) {
			isRight = false;

			xPos -= 2;
			if (xPos <= 0)
				xPos += 2;
			delay++;
			if (delay > time)
			{
				index++;
				delay = 0;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (isJump == false)
			isJump = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		isAttack = true;
	}

	if (isJump)
	{
		bool cando = true;
		bool trigger = false;
		int floatPlat = 0;

		for (int i = 0; i < enemies.size(); i++) {
			if (boundBox.intersects(enemies[i].getBoundBox())) {
				if (enemies[i].getBoundBox().top >= 104) {
					floatPlat = enemies[i].getBoundBox().top - 100;
				}
				cando = false;
				trigger = true;
				health--;
				cout << health << endl;
			}
		}

		for (int i = 0; i < stuff.size(); i++) {
			if (stuff[i].getBoundBox().intersects(boundBox)) {
				if (stuff[i].getBoundBox().top >= 104) {
					floatPlat = stuff[i].getBoundBox().top;
				}
				cando = false;
			}
		}
		if(cando) {
		jumpSpeed = jumpSpeed - 0.2;
		yPos -= jumpSpeed;
		if (yPos >= maxY - 104)
		{
			isJump = false;
			yPos = maxY - 104;
			jumpSpeed = speedOrigin;
		}
		Sleep(1);
	}
		else {
			if (floatPlat != 0) {
				yPos = floatPlat - 36;
			}
			if (!trigger) {
				isJump = false;
				jumpSpeed = speedOrigin;
			}
			else {
				jumpSpeed = 2;
			}
		}
	}
	Sleep(1);
}

void Player::drawPlayer(sf::RenderWindow &window)
{
	vector<string> playerSprite = { "p1_walk01.png","p1_walk02.png","p1_walk03.png","p1_walk04.png","p1_walk05.png","p1_walk06.png","p1_walk07.png","p1_walk08.png","p1_walk09.png",
		"p1_walk10.png", "p1_walk11.png" };
	sf::Texture texture;
	sf::Sprite sprite;

	if (isJump)
	{
		//load the jumping picture
		if (!texture.loadFromFile("p1_jump.png"))
		{
			// error...
		}

	}
	else
	{
		//load sprite from the walking vector
		if (index >= size)
			index = 0;
		if (!texture.loadFromFile(playerSprite.at(index)))
		{
			// error...
		}
	}
	if (isRight)
	{
		//set the sprite to jump right
		sprite.setTexture(texture);
	}
	else
	{
		//set the sprite to jump left
		sprite.setTexture(texture);
		sprite.scale(-1.f, 1.f);
	}
	//draw the sprite
	sprite.setOrigin(36, 58);
	sprite.setPosition(xPos, yPos);
	boundBox = sprite.getGlobalBounds();
	window.draw(sprite);

	if (isAttack) {
		sf::Texture attackTexture;
		sf::Sprite attackSprite;

		if (isRight) {
			attackTexture.loadFromFile("attack.png");
			attackSprite.setTexture(attackTexture);
			attackSprite.setOrigin(36, 58);
			if (isJump) {
				attackSprite.setPosition(xPos + 65, yPos + 47);
			}
			else {
				attackSprite.setPosition(xPos + 65, yPos + 62);
			}
		}
		else {
			attackTexture.loadFromFile("attack.png");
			attackSprite.setTexture(attackTexture);
			attackSprite.scale(-1.f, 1.f);
			attackSprite.setOrigin(36, 58);
			if (isJump) {
				attackSprite.setPosition(xPos - 67, yPos + 47);
			}
			else {
				attackSprite.setPosition(xPos - 67, yPos + 62);
			}
		}

		boundBoxAttack = attackSprite.getGlobalBounds();
		window.draw(attackSprite);
		isAttack = false;
	}
}

int Player::getHealth()
{
	return health;
}

void Player::setHealth(int change)
{
	health += change;
}

void Player::setXPosition(int change)
{
	xPos += change;
}

sf::FloatRect Player::getBoundBox()
{
	return boundBox;
}
