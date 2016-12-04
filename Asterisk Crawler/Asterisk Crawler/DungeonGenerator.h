//MIT License
//
//Copyright (c) 2016 Roberto Campbell
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

struct Seed
{
	int x;
	int y;
};

class DungeonGenerator
{
private:
	std::vector<int> dungeon;
	int height;
	int width;
	int mapSeed;
	void smoothing();
	Seed generate_room(int passes);
	void connect_rooms(Seed& seedOne,Seed& seedTwo);
public:
	DungeonGenerator(int mSeed=0, int new_height=20, int new_width=20);
	std::vector<int> get_dungeon() {return dungeon;}
	int get_height() {return height;}
	int get_width()  {return width;}
	int get_mapSeed() {return mapSeed;}
	void set_dungeon(std::vector<int> new_dungeon);
	void set_height(int new_height);
	void set_width(int new_width);
	void set_mapSeed(int new_mapSeed);
	void generate_dungeon(int passes,int rooms, int smoothing_passes);
};

#endif
