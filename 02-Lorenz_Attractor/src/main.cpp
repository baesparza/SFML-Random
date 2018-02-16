#include <SFML/Graphics.hpp>
#include <iostream>

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
const int WIDTH = 600, HEIGHT = 500;

int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Lorenz Attractor");

	window.setFramerateLimit(60);

	CircleShape circle;
	circle.setRadius(2);

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

		circle.setPosition(WIDTH / 2 + x, HEIGHT / 2 + y);
		window.draw(circle);

		///drawing///
		window.display();


		std::cout << x << ", " << y << ", " << z << "\n";
	}



	return 0;
}