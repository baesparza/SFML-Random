#include <SFML/Graphics.hpp>

using namespace sf;


// variables
float x = 0.01;
float y = 0.01;
float z = 0.01;

// constant
float a = 10;
float b = 28;
float c = 8.f / 3.f;

// window
const unsigned int WIDTH = 800, HEIGHT = 800;

// trace
const unsigned int TRACE = 5000;

int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Lorenz Attractor");

	window.setFramerateLimit(60);

	CircleShape circle;
	circle.setRadius(2);

	// tracing
	Vector2f point[TRACE];
	int count = 0;

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
			if (e.type == Event::Closed)
				window.close();

		// get data 
		float dt = 0.01;
		float dx = (a * (y - x)) * dt;
		float dy = (x * (b - z) - y) * dt;
		float dz = (x * y - c * z) * dt;

		x += dx;
		y += dy;
		z += dz;

		point[count].x = WIDTH / 2 + x * 10;
		point[count].y = HEIGHT / 2 + y * 10;
		count++;
		if (count >= TRACE)
			count = 0;

		///drawing///
		window.clear();
		// draw all cicle
		for (Vector2f p : point)
		{
			circle.setPosition(p);
			window.draw(circle);
		}

		window.display();
	}



	return 0;
}