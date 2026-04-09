#pragma once

#include <string>
#include <fstream>

class Data;

class Loader
{
public:
	Loader();

	bool load(const std::string& file_name);

private:
	Data& data;
	std::ifstream fin;

	void readCoords();
	void buildEdges();
};
