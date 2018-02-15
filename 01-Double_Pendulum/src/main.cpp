#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{

	RenderWindow window(VideoMode(400, 400), "Double Pendulum");

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		window.display();

	}
	return 0;
}