#include <SFML/Graphics.hpp>

const int COLS = 90;
const int ROWS = 90;
const int TS = 10;

int grid[ROWS][COLS];

sf::Color getColor(int n)
{
	if (n == 0) return sf::Color::White; // empty
	if (n == 1) return sf::Color::Black; // occupated
	if (n == 2) return sf::Color::Cyan; // path
	if (n == 3) return sf::Color::Blue; // head
}

int main()
{
	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(COLS * TS, ROWS * TS), "Pathfinding Algorithm");
	app.setFramerateLimit(10);

	// rectangle
	sf::RectangleShape rectangle(sf::Vector2f(TS, TS));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);

	// initialize grid
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < ROWS; j++)
			grid[i][j] = rand() % 4; // (rand() % 5 == 1) ? 1 : 0;

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
			if (e.type == sf::Event::Closed)
				app.close();
		/////draw/////
		app.clear();

		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < ROWS; j++)
			{
				rectangle.setPosition(j*TS, i*TS);
				rectangle.setFillColor(getColor(grid[i][j]));
				app.draw(rectangle);
			}

		app.display();
	}

	return 0;
}