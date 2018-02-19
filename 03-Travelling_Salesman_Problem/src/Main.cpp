#include <SFML/Graphics.hpp>

using namespace sf;

// declarations
void setup(RenderWindow &);
void draw(RenderWindow &);


// window
const int SIZE = 800;

int main()
{
	RenderWindow app(VideoMode(SIZE, SIZE), "Traversing Salesman Problem");
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
