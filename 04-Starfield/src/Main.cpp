#include <SFML/Graphics.hpp>
#include <array>

using namespace sf;

// declarations
void setup(RenderWindow &);
void draw(RenderWindow &);

// window
const int SIZE = 800;

// take one value in one range, and return its value in the second range
float map(float num, float start1, float stop1, float start2, float stop2)
{
	return (num - start1) / (stop1 - start1) * (stop2 - start2) + start2;
}

struct Star
{
	float x, y, z;

	void start()
	{
		x = rand() % SIZE - (SIZE / 2);
		y = rand() % SIZE - (SIZE / 2);
		z = rand() % SIZE;
	}
};


int main()
{
	srand(time(0));

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow app(VideoMode(SIZE, SIZE), "Starfield", Style::Default, settings);
	//	app.setFramerateLimit(60);

	////setup////
	std::array<Star, 400> stars;

	// initialize with random positions
	for (int i = 0; i < stars.size(); i++)
		stars[i].start();

	CircleShape circle;
	circle.setRadius(1);

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
			if (e.type == Event::Closed)
				app.close();

		app.clear();

		for (int i = 0; i < stars.size(); i++)
		{
			float sx = map(stars[i].x / stars[i].z, 0, 1, 0, SIZE);
			float sy = map(stars[i].y / stars[i].z, 0, 1, 0, SIZE);

			stars[i].z -= 10;
			if (stars[i].z < 1)
				stars[i].start();

			float r = map(stars[i].z, 0, SIZE, 4, 0);
			circle.setRadius(r);

			circle.setPosition(SIZE / 2 + sx, SIZE / 2 + sy);
			app.draw(circle);
		}

		app.display();
	}

	return 0;
}
