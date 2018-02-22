#include <SFML/Graphics.hpp>
#include <cmath>

// define pi
const double PI = std::acos(-1);

struct Tree
{
	sf::Vector2f start, end;
	float angle;

	//	Tree *left, *right;

	Tree(sf::Vector2f strt, int alpha, int magnitude) :
		start(strt)
	{
		angle  = alpha * PI / 180; // measured in radians

		// calculate end
		float end_x = magnitude * std::cos(angle);
		float end_y = magnitude * std::sin(angle);
		end = {start.x - end_x, start.y - end_y};
	}
};

int main()
{
	sf::RenderWindow app(sf::VideoMode(800, 800), "Fractal Tree");

	// main tree
	Tree * root = new Tree(
		//	sf::Vector2f{app.getSize().x / 2, app.getSize().y}, // beging center bottom
		{400, 800},
		90,
		400
	);

	// line obj
	sf::Vertex line[2] =
	{
		root->start,
		root->end
	};

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
			if (e.type == sf::Event::Closed)
				app.close();


		/////draw/////
		app.clear();

		app.draw(line, 2, sf::Lines);

		app.display();
	}

	return 0;
}