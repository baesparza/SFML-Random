#include <SFML/Graphics.hpp>
#include <time.h>

// options
const int TS = 10;
const int COL = 90, ROW = 90;

bool grid[ROW][COL];
bool t_grid[ROW][COL];

void updateGrid()
{
	// clone main grid
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			t_grid[i][j] = grid[i][j];

	// verify every grid if alive
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			int n = 0;

			// counter near alive
			if (t_grid[(i - 1 + ROW) % ROW][(j - 1 + COL) % COL]) n++; // top left
			if (t_grid[(i - 1 + ROW) % ROW][(j + 1 + COL) % COL]) n++; // top right
			if (t_grid[(i + 1 + ROW) % ROW][(j + 1 + COL) % COL]) n++; // bottom right
			if (t_grid[(i + 1 + ROW) % ROW][(j - 1 + COL) % COL]) n++; // bottom left
			if (t_grid[(i - 1 + ROW) % ROW][j]) n++; // top
			if (t_grid[(i + 1 + ROW) % ROW][j]) n++; // bottom
			if (t_grid[i][(j + 1 + COL) % COL]) n++; // right
			if (t_grid[i][(j - 1 + COL) % COL]) n++; // left

			// cell die
			if (t_grid[i][j]) // cell alive
				grid[i][j] = (n == 2 || n == 3) ? true : false;

			// cell gets alive
			if (!t_grid[i][j]) // cell dead
				if (n == 3)
					grid[i][j] = true;
		}
}

int main()
{
	srand(time(0));

	sf::RenderWindow app(sf::VideoMode(TS * COL, TS * ROW), "Game of life");
	app.setFramerateLimit(60);

	// rectangle
	sf::RectangleShape rectangle(sf::Vector2f(TS, TS));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);

	// initialize grid
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			grid[i][j] = (rand() % 10 == 2) ? true : false;
	//	grid[10][10] = grid[11][11] = grid[12][11] = grid[10][12] = grid[11][12] = true; // test

	while (app.isOpen())
	{

		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
		}

		// update grid
		updateGrid();

		/////draw/////
		app.clear(sf::Color::White);

		// draw all rects
		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
			{
				rectangle.setPosition(j * TS, i * TS);
				rectangle.setFillColor((grid[i][j]) ? sf::Color::Black : sf::Color::White); // live -> brack, else white
				app.draw(rectangle);
			}


		app.display();
	}

	return 0;
}