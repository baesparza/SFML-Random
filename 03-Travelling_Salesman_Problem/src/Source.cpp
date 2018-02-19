#include <array>
#include <iostream>

#include <SFML\Graphics.hpp>

# define num_points 4 // number of points

using namespace sf;

/////////////////////code//////////////////////////////

int bestDistance = 0; // min distance

std::array<Vector2f, num_points> points; // points
std::array<Vector2f, num_points> bestPoints; // store best distance points
std::array<int, num_points> permutations; // permutations

CircleShape circle;
Vertex line[2];

// function to get distance using pitagoras
int getDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// store best distance
void storeBestDistance(int tempDist, int ofset)
{
	bestDistance = tempDist; // save best distance
	for (int i = 0; i < points.size(); i++)
	{
		bestPoints[i].x = points[i].x;
		bestPoints[i].y = points[i].y + ofset; // middle down
	}
	std::cout << bestDistance << "\n";
}

// draw best distance
void drawBestDistance(RenderWindow & app)
{
	// draw circle
	for (int i = 0; i < bestPoints.size(); i++)
	{
		circle.setPosition(bestPoints[i].x, bestPoints[i].y);
		app.draw(circle);
	}
	// conect with lines
	for (int i = 0; i < bestPoints.size() - 1; i++)
	{
		line[0].position = {bestPoints[i].x, bestPoints[i].y};
		line[1].position = {bestPoints[i + 1].x, bestPoints[i + 1].y};
		app.draw(line, 3, Lines);
	}
}

// return actual distance, and draw actual route
int drawActualPoints(RenderWindow & app)
{
	int tempDist = 0; // distance

	// display points
	for (int i = 0; i < points.size(); i++)
	{
		circle.setPosition(points[i].x, points[i].y);
		app.draw(circle);
	}

	for (int i = 0; i < points.size() - 1; i++)
	{
		// calc distance between points
		tempDist += getDistance(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);

		// conect points with lines
		line[0].position = {points[i].x, points[i].y};
		line[1].position = {points[i + 1].x, points[i + 1].y};
		app.draw(line, 2, Lines);
	}

	return tempDist;
}

void setup(RenderWindow & app)
{
	srand(time(0));

	circle.setRadius(4);
	circle.setOrigin(2, 2);

	// initialize with random positions
	for (int i = 0; i < points.size(); i++)
	{
		// generate point middle height
		points[i].x = bestPoints[i].x = rand() % app.getSize().x;
		points[i].y = rand() % (app.getSize().y / 2); // middle top
		bestPoints[i].y = points[i].y + app.getSize().y / 2; // middle down

		// initialize permutations
		permutations[i] = i;
	}

	// calculate best distance for first time
	for (int i = 0; i < points.size() - 1; i++)
		bestDistance += getDistance(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
}

void draw(RenderWindow & app)
{
	int tempDist = drawActualPoints(app); // draw points, and get distance

	drawBestDistance(app); // draw best distance

	if (tempDist < bestDistance) // if found a better distance, store it
		storeBestDistance(tempDist, app.getSize().y / 2);
}

