#include <SFML/Graphics.hpp>

using namespace sf;

// declarations
void setup(RenderWindow &);
void draw(RenderWindow &, bool &);


// window
const int SIZE = 800;

bool finished = false;

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow app(VideoMode(SIZE, SIZE), "Traversing Salesman Problem", Style::Default, settings);
	app.setFramerateLimit(60);

	setup(app);

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
			if (e.type == Event::Closed)
				app.close();

		if (finished) // stop searching
			break;

		app.clear();

		draw(app, finished);

		app.display();
	}

	return 0;
}
