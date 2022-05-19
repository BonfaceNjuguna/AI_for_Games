#pragma once
#include <string>
#include <vector>
#include <raylib.h>
#include <fstream>
#include <sstream>

struct MapObject
{
	int x;
	int y;
	std::vector<char> info;

	Texture tile_atlas;
	Rectangle* rectanglemap;
	int tilesize;

	MapObject(const char* filename);

	unsigned int GetIDAtPosition(float x_, float y_) const {
		const int tilex = x_ / tilesize;
		const int tiley = y_ / tilesize;
		return tilex + tiley * x;
	}

	//draw map
	void Draw() {
		const int scale = 2;
		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < y; ++j) {
				int id = i + j * x;
				int mapinfo = info[id];
				Rectangle src = rectanglemap[mapinfo];
				Rectangle dest{ i * tilesize, j * tilesize,tilesize,tilesize };
				DrawTexturePro(tile_atlas, src, dest, Vector2{ 0,0 }, 0, Color{ 255,255,255,255 });
			}
		}

	}
};

MapObject::MapObject(const char* filename) {
	std::ifstream filein(filename);
	if (!filein.is_open())
		throw std::runtime_error("Map file not found");

	std::string line;
	std::getline(filein, line);

	tile_atlas = LoadTexture(line.c_str());

	//Get rect sizes
	std::getline(filein, line);
	std::istringstream is{ line };

	is >> tilesize;
	is >> tilesize;

	//get header for the size values
	std::getline(filein, line);
	is.clear();
	is.str(line);

	int n;//number of tiles
	is >> n;

	rectanglemap = new Rectangle[n];
	for (int i = 0; i < n; ++i) {
		auto& r = rectanglemap[i];
		r.width = tilesize;
		r.height = tilesize;
		filein >> r.x;
		r.x *= tilesize;
		filein >> r.y;
		r.y *= tilesize;
	}

	//dimension variable for the map
	filein >> x;
	filein >> y;
	info.reserve(x * y);

	while (std::getline(filein, line)) {
		std::istringstream is{ line };
		std::string tv;
		while (is >> tv) {
			info.push_back(atoi(tv.c_str()));
		}
	}
}

