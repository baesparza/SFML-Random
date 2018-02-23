#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

// define pi
const double PI = std::acos(-1);

// options
const int angle_increment = 45;
const float magn_dec = 0.6;


struct Tree
{
	sf::Vector2f start, end;
	float angle;

	Tree *left, *right;

	Tree(sf::Vector2f strt, int alpha, int magnitude) :
		start(strt)
	{
		angle = alpha * PI / 180; // measured in radians

		// calculate end
		float end_x = magnitude * std::cos(angle);
		float end_y = magnitude * std::sin(angle);
		end = {start.x - end_x, start.y - end_y};

		// initialize child
		if (magnitude > 2)
		{
			right = new Tree(end, alpha - angle_increment, magnitude * magn_dec);
			left = new Tree(end, alpha + angle_increment, magnitude * magn_dec);
			return;
		}
		left = right = nullptr;
	}

	void show(sf::RenderWindow & app)
	{
		// line obj
		sf::Vertex line[2] = {start, end};
		app.draw(line, 2, sf::Lines);

		// print child recursively
		if (right) right->show(app);
		if (left) left->show(app);
	}
};

int main()
{
	sf::RenderWindow app(sf::VideoMode(800, 800), "Fractal Tree");

	// main tree
	Tree * root = new Tree(
		sf::Vector2f{float(app.getSize().x / 2), float(app.getSize().y)}, // beging center bottom
		90,
		app.getSize().y * 0.35
	);


	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
			if (e.type == sf::Event::Closed)
				app.close();


		/////draw/////
		app.clear();

		root->show(app);

		app.display();
	}

	return 0;
}