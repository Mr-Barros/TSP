#include "Loader.h"

#include <fstream>

#include "Data.h"

using namespace std;

Loader::Loader() : data(Data::getInstance()) {}

bool Loader::load(const string& file_name)
{
	fin.open(file_name);
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
	data.name = file_name.substr(file_name.find_last_of('/') + 1, file_name.find_last_of('.') - file_name.find_last_of('/') - 1);

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

void Loader::buildEdges()
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
					double dx = data.coords[i].x - data.coords[j].x;
					double dy = data.coords[i].y - data.coords[j].y;
					data.costs[i][j] = (int)(sqrt(dx * dx + dy * dy) + 0.5);
				}
				else if (data.type == "GEO")
				{
					double PI = 3.141592;

					int deg = (int)(data.coords[i].x + 0.5);
					double min = data.coords[i].x - deg;
					double lat1 = PI * (deg + 5.0 * min / 3.0) / 180.0;
					deg = (int)(data.coords[i].y + 0.5);
					min = data.coords[i].y - deg;
					double lon1 = PI * (deg + 5.0 * min / 3.0) / 180.0;

					deg = (int)(data.coords[j].x + 0.5);
					min = data.coords[j].x - deg;
					double lat2 = PI * (deg + 5.0 * min / 3.0) / 180.0;
					deg = (int)(data.coords[j].y + 0.5);
					min = data.coords[j].y - deg;
					double lon2 = PI * (deg + 5.0 * min / 3.0) / 180.0;

					double RRR = 6378.388;
					double q1 = cos(lon1 - lon2);
					double q2 = cos(lat1 - lat2);
					double q3 = cos(lat1 + lat2);
					data.costs[i][j] = (int)(RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
				}
			}
		}
	}
}
