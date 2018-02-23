#include <SFML/Graphics.hpp>
#include <time.h>

// options
const int TS = 10;
const int COL = 90, ROW = 90;

bool grid[ROW][COL];
bool t_grid[ROW + 2][COL + 2];

void updateGrid()
{
	// clone main grid
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			t_grid[i + 1][j + 1] = grid[i][j];

	// verify every grid if alive
	for (int i = 1; i <= ROW; i++)
		for (int j = 1; j <= COL; j++)
		{
			int n = 0;

			// counter near alive
			if (t_grid[i - 1][j - 1]) n++; // top left
			if (t_grid[i - 1][j]) n++; // top
			if (t_grid[i - 1][j + 1]) n++; // top right
			if (t_grid[i][j + 1]) n++; // right
			if (t_grid[i + 1][j + 1]) n++; // bottom right
			if (t_grid[i + 1][j]) n++; // bottom
			if (t_grid[i + 1][j - 1]) n++; // bottom left
			if (t_grid[i][j - 1]) n++; // left

			// cell die
			if (t_grid[i][j]) // cell alive
				t_grid[i][j] = (n == 2 || n == 3) ? true : false;



			// cell gets alive
			if (!t_grid[i][j]) // cell dead
				if (n == 3)
					t_grid[i][j] = true;
		}

	// actualizar main grid
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			grid[i][j] = t_grid[i + 1][j + 1];
}

int main()
{
	srand(time(0));

	sf::RenderWindow app(sf::VideoMode(TS * COL, TS * ROW), "Game of life");

	// rectangle
	sf::RectangleShape rectangle(sf::Vector2f(TS, TS));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);

	// initialize grid
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			grid[i][j] = (rand() % 10 == 2) ? true : false;

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
		}

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

		// update grid
		updateGrid();

		app.display();
	}

	return 0;
}