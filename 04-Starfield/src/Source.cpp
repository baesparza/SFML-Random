#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>

using namespace sf;


CircleShape circle;

// take one value in one range, and return its value in the second range
float map(float num, float start1, float stop1, float start2, float stop2)
{
	float res = (num - start1) / (stop1 - start1) * (stop2 - start2) + start2;
	// std::cout << res << " = " << (num - start1) << " / " << (stop1 - start1) << " * " << (stop2 - start2) << " + " << start2 << std::endl;
	return	res;
}

struct Star
{
	float x, y, z;

	void star(RenderWindow & app)
	{
		x = rand() % app.getSize().x;
		y = rand() % app.getSize().y;
		z = app.getSize().x;
	}

	void update(RenderWindow & app)
	{
		z--;
		if (z < 1)
			z = app.getSize().x;
	}

	void draw(RenderWindow & app)
	{
		float sx = map(x / z, 0, 1, 0, app.getSize().x);
		float sy = map(y / z, 0, 1, 0, app.getSize().y);
		//circle.setRadius(2);
		circle.setPosition(sx, sy);
		app.draw(circle);
	}
};

std::array<Star, 500> stars;

void setup(RenderWindow & app)
{
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