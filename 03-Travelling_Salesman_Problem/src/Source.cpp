#include <array>
#include <iostream>

#include <SFML\Graphics.hpp>

# define num_points 7 // number of points

using namespace sf;


int bestDistance = 0; // min distance

std::array<Vector2f, num_points> positions; // points
std::array<int, num_points> bestPemutation; // store best permutations points
std::array<int, num_points> permutations; // permutations

CircleShape circle;
Vertex line[2];

// function to get distance using pitagoras
int getDistance(const Vector2f &  v1, const Vector2f & v2 )
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

// store best distance
void storeBestPermutation(int tempDist)
{
	bestDistance = tempDist; // save best distance
	for (int i = 0; i < permutations.size(); i++)
	{
		bestPemutation[i] = permutations[i];
	}
	std::cout << bestDistance << "\n";
}

// draw best distance
void drawBestPermutation(RenderWindow & app)
{
	// draw circle
	for (int i = 0; i < positions.size(); i++)
	{
		circle.setPosition(positions[bestPemutation[i]].x, positions[bestPemutation[i]].y + app.getSize().y / 2);
		app.draw(circle);
	}
	// conect with lines
	for (int i = 0; i < positions.size() - 1; i++)
	{
		line[0].position = {positions[bestPemutation[i]].x, positions[bestPemutation[i]].y + app.getSize().y / 2};
		line[1].position = {positions[bestPemutation[i + 1]].x, positions[bestPemutation[i + 1]].y + app.getSize().y / 2};
		app.draw(line, 3, Lines);
	}
}

// return actual distance, and draw actual route
int drawActualPoints(RenderWindow & app)
{
	int tempDist = 0; // distance

	// display points
	for (int i = 0; i < positions.size(); i++)
	{
		circle.setPosition(positions[permutations[i]]);
		app.draw(circle);
	}

	for (int i = 0; i < positions.size() - 1; i++)
	{
		// calc distance between points
		tempDist += getDistance(positions[permutations[i]], positions[permutations[i + 1]]);

		// conect points with lines
		line[0].position = positions[permutations[i]];
		line[1].position = positions[permutations[i + 1]];
		app.draw(line, 2, Lines);
	}
	//	std::cout << "[temp]: " << tempDist << "\n";
	return tempDist;
}

void permutate(bool & finished)
{
	// print array
	//	for (int n : permutations)
	//		std::cout << n << ", ";
	//	std::cout << "\n";

	// 1. Find the largest x such that P[x]<P[x+1].
	// (If there is no such x, P is the last permutation.)
	int smalestX = -1;
	for (int i = 0; i < permutations.size() - 1; i++)
		if (permutations[i] < permutations[i + 1])
			smalestX = i;
	if (smalestX == -1)
	{
		finished = true;
		return;
	}

	// 2.Find the largest y such that P[x]<P[y].
	int smalestY = -1;
	for (int i = 0; i < permutations.size(); i++)
		if (permutations[smalestX] < permutations[i])
			smalestY = i;

	// 3.Swap P[x] and P[y].
	int temp = permutations[smalestX];
	permutations[smalestX] = permutations[smalestY];
	permutations[smalestY] = temp;

	// 4.Reverse P[x + 1 ..n].
	std::reverse(std::begin(permutations) + smalestX + 1, std::end(permutations));
}

void setup(RenderWindow & app)
{
	srand(time(0));

	circle.setRadius(4);
	circle.setOrigin(4, 4);

	// initialize with random positions
	for (int i = 0; i < positions.size(); i++)
	{
		// generate point middle height
		positions[i].x = rand() % app.getSize().x;
		positions[i].y = rand() % (app.getSize().y / 2);

		// initialize permutations and best permutations
		permutations[i] = bestPemutation[i] = i;
	}

	// calculate best distance for first time
	for (int i = 0; i < positions.size() - 1; i++)
		bestDistance += getDistance(positions[permutations[i]], positions[permutations[i + 1]]);
}

void draw(RenderWindow & app, bool & finished)
{
	int tempDist = drawActualPoints(app); // draw points, and get distance

	drawBestPermutation(app); // draw best distance

	if (tempDist < bestDistance) // if found a better distance, store it
		storeBestPermutation(tempDist);

	permutate(finished);
}

