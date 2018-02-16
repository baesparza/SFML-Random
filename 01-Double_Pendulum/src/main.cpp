#include <SFML/Graphics.hpp>
#include <math.h>

#define Sin(x) std::sin(x)
#define Cos(x) std::cos(x)
#define Pow2(x) std::pow(x, 2)
#define PI 3.14159265358979323846

using namespace sf;


/////options/////
// window
const unsigned int WIDTH = 900, HEIGHT = 600;

// first object
float L1 = 200;
float M1 = 30;
float A1 = 3 * PI / 4;
float A1_v = 0;
float A1_a = 0;

// second object
float L2 = 200;
float M2 = 70;
float A2 = 7 * PI / 8;
float A2_v = 0;
float A2_a = 0;

// enviroment
float G = 0.98; // gravity

// tracing
const int trace = 300;

int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Double Pendulum");
	window.setFramerateLimit(60);


	// center plane
	float x = WIDTH / 2;
	float y = 100;


	//figure 1 setup
	Vertex line1[2];
	line1[0] = Vertex(Vector2f(x, y));

	CircleShape circle1(M1 / 2);
	circle1.setOrigin(M1 / 2, M1 / 2); // set origin the center of circle


	//figure 2 setup
	Vertex line2[2];

	CircleShape circle2(M2 / 2);
	circle2.setOrigin(M2 / 2, M2 / 2); // set origin the center of circle


	//////tracing///////
	CircleShape point;
	point.setRadius(1);
	Vertex points[trace];
	int count = 0; // for trace
	for (Vertex p : points)
		p.position = {-100,-100}; // initialize points


	/////window loop///////
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		////figure 1/////
		// get new ending of line 1
		float x1 = L1 * Sin(A1);
		float y1 = L1 * Cos(A1);

		// update ending and circle position
		line1[1].position.x = x + x1;
		line1[1].position.y = y + y1;
		circle1.setPosition(line1[1].position); // update position of circle

		// calculate angular aceleration
		A1_a = -2 * Sin(A1 - A2) * M2 * (Pow2(A2_v) * L2 + Pow2(A1_v) * L1 * Cos(A1 - A2));
		A1_a += -M2 * G * Sin(A1 - 2 * A2);
		A1_a += -G * (2 * M1 + M2) * Sin(A1);
		A1_a /= L1 * (2 * M1 + M2 - M2 * Cos(2 * A1 - 2 * A2));

		// calculare angular distance
		A1_v += A1_a;
		A1 += A1_v;


		////figure 2////
		// ending of line 2
		float x2 = L2 * Sin(A2);
		float y2 = L2 * Cos(A2);

		// update begining, ending and circle position
		line2[0].position = line1[1].position;
		line2[1].position.x = line1[1].position.x + x2;
		line2[1].position.y = line1[1].position.y + y2;
		circle2.setPosition(line2[1].position);

		// calculate angular aceleration
		A2_a = Pow2(A1_v) * L1 * (M1 + M2);
		A2_a += G * (M1 + M2) * Cos(A1);
		A2_a += Pow2(A2_v) * L2 * M2 * Cos(A1 - A2);
		A2_a *= 2 * Sin(A1 - A2);
		A2_a /= L2 * (2 * M1 + M2 - M2 * Cos(2 * A1 - 2 * A2));

		// calculare angular distance
		A2_v += A2_a;
		A2 += A2_v;


		////Tracing///
		points[count++] = line2[1].position;
		if (count >= trace) // override old points
			count = 0;


		//////Stoping/////
		A1_v *= 0.999;
		A2_v *= 0.999;

		////DRAWING/////
		window.clear();
		window.draw(line1, 2, Lines);
		window.draw(circle1);
		window.draw(line2, 2, Lines);
		window.draw(circle2);

		for (Vertex p : points)
		{
			point.setPosition(p.position);
			window.draw(point);
		}


		window.display();

	}
	return 0;
}