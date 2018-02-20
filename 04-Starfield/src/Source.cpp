#include <SFML\Graphics.hpp>
#include <array>


using namespace sf;

std::array<Vector3f, 500> stars;

CircleShape circle;

void setup(RenderWindow & app)
{
	srand(time(0));

	// initialize with random positions
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i].x = rand() % app.getSize().x;
		stars[i].y = rand() % app.getSize().y;
		stars[i].z = rand() % 3;
	}

}

void draw(RenderWindow & app)
{
	for (Vector3f s : stars)
	{
		circle.setRadius(s.z);
		circle.setPosition(s.x, s.y);
		app.draw(circle);
	}
}