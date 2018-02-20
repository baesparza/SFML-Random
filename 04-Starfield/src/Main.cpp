#include <SFML/Graphics.hpp>
//	#include <_04_Starfield/Graphics.hpp>

using namespace sf;

// declarations
void setup(RenderWindow &);
void draw(RenderWindow &);

// window
const int SIZE = 800;

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow app(VideoMode(SIZE, SIZE), "Starfield", Style::Default, settings);
	app.setFramerateLimit(60);

	setup(app);

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
			if (e.type == Event::Closed)
				app.close();

		app.clear();

		draw(app);

		app.display();
	}

	return 0;
}