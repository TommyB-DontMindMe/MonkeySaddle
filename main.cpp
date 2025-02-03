#include <iostream>
#include <fstream>
#include <string>
#include "Vertex.h"
using namespace std;

static float CalculateValue(float x, float y) { return x * x * y; }

Vertex DeterminePoint(float x, float y)
{
	Vertex Point;
	Point.x = x;
	Point.z = y;
	Point.y = CalculateValue(Point.x, Point.z);
	return Point;
}

void SetColor(Vertex& Target)
{
	Target.r = 0.5 + Target.y * 0.01;
	Target.g = 0.5 + Target.z * 0.25;
	Target.b = 0.5 + Target.x * 0.25;
}

int main()
{
	fstream MyFile;
	int Resolution = 0;
	string Input;

	std::cout << "Select resolution in X/Unit space: ";
	while (Resolution == 0)
	{
		cin >> Input;

		try
		{
			Resolution = stoi(Input);
		}
		catch (const std::exception&)
		{
			std::cout << "Unable to parse, please try again." << endl;
		}
		if (Resolution < 1)
		{
			std::cout << "Invalid value Please try again" << endl;
			Resolution = 0;
		}
	}

	float Increment = 1.0f / Resolution;

	MyFile.open("Test.txt", ios::out);
	if (MyFile.is_open())
	{
		// 6 Lines per point 8 * resolution points in each direction
		float LineCount = 384 * Resolution * Resolution;
		MyFile << LineCount << endl;
		for (size_t i = 0; i < 8.0f * Resolution; i++)
		{
			for (size_t j = 0; j < 8.0f * Resolution; j++)
			{
				Vertex vA = DeterminePoint(-4 + i * Increment, -4 + j * Increment);
				Vertex vB = DeterminePoint(-4 + (i + 1) * Increment, -4 + j * Increment);
				Vertex vC = DeterminePoint(-4 + i * Increment, -4 + (j + 1) * Increment);
				Vertex vD = DeterminePoint(-4 + (i + 1) * Increment, -4 + (j + 1) * Increment);
				SetColor(vA);
				SetColor(vB);
				SetColor(vC);
				SetColor(vD);

				MyFile << vA << endl;
				MyFile << vB << endl;
				MyFile << vC << endl;

				MyFile << vD << endl;
				MyFile << vB << endl;
				MyFile << vC << endl;
			}
		}
	}

	MyFile.close();
}