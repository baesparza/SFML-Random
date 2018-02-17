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
const unsigned int SIZE = 800;

float angle = 0.001;

// trace
struct Trace
{
	Vector3f position;
	Trace * next;

	Trace(Vector3f v) : position(v)
	{
	}

	Vector2f getPosition()
	{
		// simulate 3d
		float pxz = sqrt(pow(position.x, 2) + pow(position.z, 2));
		// get angle with both pos
		float a = atan(position.x / position.z);
		float px = pxz * cos(a + angle);
		return {SIZE / 2 + px * 5, SIZE / 2 + position.y * 5};
	}
};



int main()
{
	RenderWindow window(VideoMode(SIZE, SIZE), "Lorenz Attractor");

	window.setFramerateLimit(60);

	CircleShape circle;
	circle.setRadius(2);

	// tracing
	Trace * trace = nullptr;

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
			if (e.type == Event::Closed)
				window.close();

		// get data 
		float dt = 0.01;
		float dx = a * (y - x);
		float dy = x * (b - z) - y;
		float dz = x * y - c * z;

		x += dx * dt;
		y += dy * dt;
		z += dz * dt;

		// store trace
		Trace * t = new Trace({x, y, z});
		t->next = trace; // replace origin
		trace = t;

		///drawing///
		window.clear();
		// draw all cicle
		for (Trace * curr = trace; curr != nullptr; curr = curr->next)
		{
			circle.setPosition(curr->getPosition());
			window.draw(circle);
		}

		window.display();
		angle += 0.01;
	}



	return 0;
}