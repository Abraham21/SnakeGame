// SFMLTest.cpp : Defines the entry point for the console application.
// Abraham Yepremian

// changes I made to the original
//1. change image of the food
//2. change speed of snake as it grows
//3. add a second player


#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

//globals
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels
int w = size * num_horzBox; //background number of pixels in width
int h = size * num_vertBox; //background number of pixels in height

int direction, snake_length = 4;
int direction2, snake_length_2 = 4;
float timer = 0, delay = 0.15;

//Max size of snake
struct Snake
{
	int x, y;
}s[100], s2[100];

struct Fruit
{
	int x, y;
}food;

void Tick() {
	//Move remaining pieces of snake s[1] - s[99]
	for (int i = snake_length; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	for (int i = snake_length_2; i > 0; --i)
	{
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}

	//move direction of snake
	//user up
	if (direction == 3)
		s[0].y -= 1;
	//user down
	if (direction == 0)
		s[0].y += 1;
	//user left
	if (direction == 1)
		s[0].x -= 1;
	//user up
	if (direction == 2)
		s[0].x += 1;
	//user up
	if (direction2 == 3)
		s2[0].y -= 1;
	//user down
	if (direction2 == 0)
		s2[0].y += 1;
	//user left
	if (direction2 == 1)
		s2[0].x -= 1;
	//user up
	if (direction2 == 2)
		s2[0].x += 1;

	//If snake eats food, it should grow and speed should change
	if ((s[0].x) == food.x && (s[0].y) == food.y){
		snake_length++;
		delay *= 0.75;

		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	if ((s2[0].x) == food.x && (s2[0].y) == food.y) {
		snake_length_2++;
		delay *= 0.75;

		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	//Boundary checking
	if (s[0].x > num_horzBox)
		s[0].x = 0;
	if (s[0].x < 0)
		s[0].x = num_horzBox;
	//top and bottom
	if (s[0].y > num_vertBox)
		s[0].y = 0;
	if (s[0].y < 0)
		s[0].y = num_vertBox;
	//Boundary checking
	if (s2[0].x > num_horzBox)
		s2[0].x = 0;
	if (s2[0].x < 0)
		s2[0].x = num_horzBox;
	//top and bottom
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;
	if (s2[0].y < 0)
		s2[0].y = num_vertBox;

	//Checks if go over snake
	for (int i = 1; i < snake_length; i++)
	{
		//Cut snake in half from place eaten
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			snake_length = i;
	}

	for (int i = 1; i < snake_length; i++)
	{
		//Cut snake in half from place eaten
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y)
			snake_length_2 = i;
	}

}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//Textures
	Texture t1, t2, t3, t4;
	t1.loadFromFile("Image/white.png");
	t2.loadFromFile("Image/red.png");
	t3.loadFromFile("Image/green.png");
	t4.loadFromFile("Image/cookie.png");

	//Sprite
	//Has physical dimensions
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite spritePlayer2(t3);
	Sprite sprite3(t4);

	food.x = 10;
	food.y = 10;

	//set initial position for player 2
	for (int i = 0; i < snake_length_2; i++) {
		s2[i].x = 19;
	}


	Clock clock;
	float timer = 0, delay = 0.1;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something
		Event e;
		//Check when window is closed
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) {
				window.close();
			}
		}

		//user inputs
		if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;
		//player 2
		if (Keyboard::isKeyPressed(Keyboard::W)) direction2 = 3;
		if (Keyboard::isKeyPressed(Keyboard::S)) direction2 = 0;
		if (Keyboard::isKeyPressed(Keyboard::A)) direction2 = 1;
		if (Keyboard::isKeyPressed(Keyboard::D)) direction2 = 2;


		if (timer > delay) {
			timer = 0;
			Tick();
		}

		//Draw
		window.clear();

		//Draw background
		for (int i = 0; i < num_horzBox; i++)
			for (int j = 0; j < num_vertBox; j++)
			{
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}

		//Draw snake
		for (int i = 0; i < snake_length; i++) {
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}

		//Draw snake 2
		for (int i = 0; i < snake_length_2; i++) {
			spritePlayer2.setPosition((s2[i].x*size), (s2[i].y*size));
			window.draw(spritePlayer2);
		}

		//Draw fruit
		sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);

		window.display();
	}

    return 0;
}

