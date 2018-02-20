#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>

using namespace sf;


CircleShape circle;

int SIZE;

// take one value in one range, and return its value in the second range
float map(float num, float start1, float stop1, float start2, float stop2)
{
	return (num - start1) / (stop1 - start1) * (stop2 - start2) + start2;
}

struct Star
{
	float x, y, z;

	void star(RenderWindow & app)
	{
		x = rand() % SIZE - (SIZE / 2);
		y = rand() % SIZE - (SIZE / 2);
		z = rand() % SIZE;
	}

	void update(RenderWindow & app)
	{
		z--;
		if (z < 1)
			z = app.getSize().x;
	}

	void draw(RenderWindow & app)
	{
		float sx = map(x / z, 0, 1, 0, SIZE);
		float sy = map(y / z, 0, 1, 0, SIZE);
		//circle.setRadius(2);
		circle.setPosition(SIZE/2 + sx, SIZE / 2 + sy);
		app.draw(circle);
	}
};

std::array<Star, 500> stars;

void setup(RenderWindow & app)
{
	SIZE = app.getSize().x;

	srand(time(0));

	circle.setRadius(2);

	// initialize with random positions
	for (int i = 0; i < stars.size(); i++)
		stars[i].star(app);
}

void draw(RenderWindow & app)
{
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i].update(app);
		stars[i].draw(app);
	}
}