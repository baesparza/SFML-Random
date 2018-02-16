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
const unsigned int SIZE = 800;

// trace
struct Trace
{
	Vector3f position3D;
	Vector2f position2D;
	Trace * next;
	Trace(Vector3f v) : position3D(v)
	{
		float pyz = 3 * SIZE / 4 - sqrt(pow(position3D.y, 2) + pow(position3D.z, 2)) * 8;
		position2D = {SIZE / 2 + x * 8, pyz};
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
			circle.setPosition(curr->position2D);
			circle.setFillColor(Color(curr->position2D.x, 0, curr->position2D.y));
			window.draw(circle);
		}

		window.display();
	}



	return 0;
}