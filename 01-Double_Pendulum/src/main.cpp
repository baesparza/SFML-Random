#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;


/////options/////
// window
const unsigned int WIDTH = 600, HEIGHT = 600;

// first object
float L1 = 200;
float M1 = 40;
float A1 = 0;

// second object
float L2 = 300;
float M2 = 50;
float A2 = 0;

// enviroment
float G = 9.8; // gravity


int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 0;

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Double Pendulum", Style::Default, settings);
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
		float x1 = L1 * std::sin(A1);
		float y1 = L1 * std::cos(A1);

		// update ending and circle position
		line1[1].position.x = x + x1;
		line1[1].position.y = y + y1;
		circle1.setPosition(line1[1].position); // update position of circle

		A1 += 0.05f;


		////figure 2////
		// ending of line 2
		float x2 = L2 * std::sin(A2);
		float y2 = L2 * std::cos(A2);

		// update begining, ending and circle position
		line2[0].position = line1[1].position;
		line2[1].position.x = line1[1].position.x + x2;
		line2[1].position.y = line1[1].position.y + y2;
		circle2.setPosition(line2[1].position);

		A2 -= 0.03f;

		////DRAWING/////
		window.clear();
		window.draw(line1, 2, Lines);
		window.draw(circle1);
		window.draw(line2, 2, Lines);
		window.draw(circle2);
		window.display();

	}
	return 0;
}