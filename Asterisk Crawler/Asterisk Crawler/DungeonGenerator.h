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
public:
	DungeonGenerator(int startWidth=10, int startHeight=10,int mSeed=0);
	std::vector<int> get_dungeon() {return dungeon;}
	int get_height() {return height;}
	int get_width()  {return width;}
	int get_mapSeed() {return mapSeed;}
	void set_dungeon(std::vector<int> new_dungeon);
	void set_height(int new_height);
	void set_width(int new_width);
	void set_mapSeed(int new_mapSeed);
	Seed generate_room(int passes);
	void generate_dungeon(int passes,int rooms, int smoothing_passes);
	void connect_rooms(Seed& seedOne,Seed& seedTwo);
};

#endif
