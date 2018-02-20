#include <SFML\Graphics.hpp>
#include <array>

using namespace sf;


std::array<Star, 500> stars;

CircleShape circle;

float map(float val, float start, float end, float min, float max)
{

}

struct Star
{
	int x, y, z;

	void star(RenderWindow & app)
	{
		x = rand() % app.getSize().x;
		y = rand() % app.getSize().y;
		z = app.getSize().x;
	}

	void update()
	{

	}

	void draw(RenderWindow & app)
	{
		float sx = map(x / z, 0, 1, 0, app.getSize().x);
		float sy = map(y / z, 0, 1, 0, app.getSize().y);
		//	circle.setRadius(s.z);
		circle.setPosition(sx, sy);
		app.draw(circle);
	}
};


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
	for (Star s : stars)
	{
		s.update();
		s.draw(app);
	}
}