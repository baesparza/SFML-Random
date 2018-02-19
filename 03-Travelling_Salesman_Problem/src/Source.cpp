#include <array>

// dependencies
#include <SFML\Graphics.hpp>

using namespace sf;

// point
std::array<Vector2f, 50> points;

CircleShape circle;
Vertex line[2];


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

	// conect points with lines
	for (int i = 0; i < points.size() - 1; i++)
	{
		line[0].position = {points[i].x, points[i].y};
		line[1].position = {points[i + 1].x, points[i + 1].y};
		app.draw(line, 2, Lines);
	}

}