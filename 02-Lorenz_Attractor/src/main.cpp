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
const unsigned int TRACE = 1000;

int main()
{
	RenderWindow window(VideoMode(SIZE, SIZE), "Lorenz Attractor");

	window.setFramerateLimit(60);

	CircleShape circle;
	circle.setRadius(2);

	// tracing
	Vector3f point[TRACE];
	int count = 0;

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
		point[count++] = {x, y, z};

		if (count >= TRACE)
			count = 0;

		///drawing///
		window.clear();
		// draw all cicle
		for (Vector3f p : point)
		{
			// simulate 3d on 2d
			float pxy = SIZE / 2 + sqrt(p.x*p.x + p.y*p.y) * 5;
			float pxz = SIZE / 2 + sqrt(p.x*p.x + p.z*p.z) * 5;
			float pyz = SIZE / 2 + sqrt(p.y*p.y + p.z*p.z) * 5;

			float px = SIZE / 2 + p.x * 5;
			float py = SIZE / 2 + p.y * 5;
			float pz = SIZE / 2 + p.z * 5;

			circle.setPosition(pxz, py);
			window.draw(circle);
		}

		window.display();
	}



	return 0;
}