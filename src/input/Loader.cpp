#include "Loader.h"

#include <fstream>
#include <cmath>
#include <iostream>

#include "Data.h"
#include "Parameters.h"

using namespace std;

Loader::Loader() : data(Data::getInstance()), params(Parameters::getInstance()) {}

bool Loader::load()
{
	const string& fileName = params.inputFile;
	fin.open(fileName);
	if (!fin.is_open()) return false;

	while (true)
	{
		string str;
		fin >> str;

		if (str == "DIMENSION:")
			fin >> data.dimension;
		else if (str == "EDGE_WEIGHT_TYPE:")
			fin >> data.type;
		else if (str == "NODE_COORD_SECTION")
			readCoords();
		else if (str == "EOF")
			break;
	}

	buildEdges();
	data.name = fileName.substr(fileName.find_last_of('/') + 1, fileName.find_last_of('.') - fileName.find_last_of('/') - 1);

	readBKS();

    return true;
}

void Loader::readCoords()
{
	data.coords.reserve(data.dimension);
	for (int i = 0; i < data.dimension; i++)
	{
		int _;
		Point p;
		fin >> _ >> p.x >> p.y;
		data.coords.push_back(p);
	}
}

void Loader::buildEdges() const
{
	data.costs.resize(data.dimension);
	for (int i = 0; i < data.dimension; i++)
	{
		data.costs[i].resize(data.dimension);
		for (int j = 0; j < data.dimension; j++)
		{
			if (i == j)
				data.costs[i][j] = 0;
			else
			{
				if (data.type == "EUC_2D")
				{
					const double dx = data.coords[i].x - data.coords[j].x;
					const double dy = data.coords[i].y - data.coords[j].y;
					data.costs[i][j] = lround(sqrt(dx * dx + dy * dy));
				}
				else if (data.type == "GEO")
				{
					constexpr double PI = 3.141592;

					int deg =  lround(data.coords[i].x);
					double min = data.coords[i].x - deg;
					const double lat1 = PI * (deg + 5.0 * min / 3.0) / 180.0;
					deg = lround(data.coords[i].y);
					min = data.coords[i].y - deg;
					const double lon1 = PI * (deg + 5.0 * min / 3.0) / 180.0;

					deg = lround(data.coords[j].x);
					min = data.coords[j].x - deg;
					const double lat2 = PI * (deg + 5.0 * min / 3.0) / 180.0;
					deg = lround(data.coords[j].y);
					min = data.coords[j].y - deg;
					const double lon2 = PI * (deg + 5.0 * min / 3.0) / 180.0;

					constexpr double RRR = 6378.388;
					const double q1 = cos(lon1 - lon2);
					const double q2 = cos(lat1 - lat2);
					const double q3 = cos(lat1 + lat2);
					data.costs[i][j] = static_cast<int>(RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
				}
			}
		}
	}
}

void Loader::readBKS() const
{
	ifstream fin_bks("../data/bks.txt");
	if (!fin_bks.is_open()) return;

	while (true)
	{
		string str;
		fin_bks >> str;
		if (str == data.name)
		{
			fin_bks >> data.bks;
			break;
		}
		if (fin_bks.eof()) break;
	}
}
