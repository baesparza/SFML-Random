#include <array>

// dependencies
#include <SFML\Graphics.hpp>

using namespace sf;

// point
std::array<Vector2i, 5> points;

CircleShape circle;

void setup(RenderWindow & app)
{
	srand(time(0));

	circle.setRadius(2);

	// initialize with random positions
	for (int i = 0; i < points.size(); i++)
	{
		points[i].x = rand() % app.getSize().x;
		points[i].y = rand() % app.getSize().y;
	}
}

void draw(RenderWindow & app)
{
	// display points
	for (int i = 0; i < points.size(); i++)
	{
		circle.setPosition(points[i].x, points[i].y);
		app.draw(circle);
	}
}