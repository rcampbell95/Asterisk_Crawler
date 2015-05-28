
//
// Dependencies
//

#include <vector>
#include <cstdlib>

#include <time.h>

#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator(int startWidth, int startHeight,int mSeed)
{
	mapSeed = mSeed;
	if(mapSeed == 0)
	{
		mapSeed = time(0);
	}
	srand(mapSeed);
	height = startHeight;
	width = startWidth;

	dungeon.resize(height * width);
}

void DungeonGenerator::set_dungeon(std::vector<int> new_dungeon)
{
	dungeon = new_dungeon;
}

void DungeonGenerator::set_height(int new_height)
{
	height = new_height;
	dungeon.resize(height * width);
}

void DungeonGenerator::set_width(int new_width)
{
	width = new_width;
	dungeon.resize(height * width);
}

Seed DungeonGenerator::generate_room(int passes)
{
	int x = 1 + (rand() % (width - 2));
	int y = 1 + (rand() % (height - 2));
	int pos;

	Seed roomSeed;
	roomSeed.x = x;
	roomSeed.y = y;

	for(int i = 0; i < passes; i++)
	{
		pos = y * width + x;
		dungeon[pos] = 1;
		int direction = rand() % 4;

		if(direction == 0)
		{
			if(y == 1)
			{
				continue;
			}
			y -= 1;
		}
		else if(direction == 1)
		{
			if(x == width - 2)
				continue;
			x += 1;
		}
		else if(direction == 2)
		{
			if(y == height - 2)
				continue;
			y += 1;
		}
		else
		{
			if(x == 1)
				continue;
			x -= 1;
		}
		//percentFilled = filled / (width * height);
	}
	return roomSeed;
}

void DungeonGenerator::generate_dungeon(int passes,int rooms)
{
	int roomsSubOne = rooms - 1;
	Seed seedOne = generate_room(passes);
	for(int i = 0; i < roomsSubOne; i++)
	{
		Seed seedTwo = generate_room(passes);
		connect_rooms(seedOne,seedTwo);
		seedOne = seedTwo;
	}
}

void DungeonGenerator::connect_rooms(Seed& seedOne,Seed& seedTwo)
{
	int x1,y1,x1Sub,y1Sub,x2,y2,x2Sub,y2Sub,pos,posSub;
	x1 = seedOne.x;
	y1 = seedOne.y;
	x2 = seedTwo.x;
	y2 = seedTwo.y;

	// For creating broader path when joining rooms
	// Additional seeds
	x1Sub = x1 > 1 ? x1 - 1: x1 + 1;
	y1Sub = y1 > 1 ? y1 - 1: y1 + 1;
	x2Sub = x2 > 1 ? x2 - 1: x2 + 1;
	y2Sub = y2 > 1 ? y2 - 1: y2 + 1;

	while(x1 != x2 || y1 != y2 && x1Sub != x2Sub || y1Sub != y2Sub)
	{
		if(x1 > x2)
			x1--;
		else if(x1 < x2)
			x1++;
		else if(y1 > y2)
			y1--;
		else if(y1 < y2)
			y1++;

		if(x1Sub > x2Sub)
			x1Sub--;
		else if(x1Sub < x2Sub)
			x1Sub++;
		else if(y1Sub > y2Sub)
			y1Sub--;
		else if(y1Sub < y2Sub)
			y1Sub++;

		pos = y1 * width + x1;
		posSub = y1Sub * width + x1Sub;
		dungeon[pos] = 1;
		dungeon[posSub] = 1;
	}
}

void DungeonGenerator::smoothing()
{
	int adHeight, adWidth, neighbors;
	neighbors = 0;
	adHeight = height - 1;
	adWidth = width - 1;
	std::vector<int> changes = dungeon;


	for(int i = 1;i < adHeight;i++)
	{
		for(int j = 1;j < adWidth;j++)
		{
			neighbors = dungeon[(i-1)*width + j-1] + 
			dungeon[(i-1)*width + j] + 
			dungeon[(i-1)*width + j+1] + 
			dungeon[i*width + j-1] + 
			dungeon[i*width + j+1] + 
			dungeon[(i+1)*width + j-1] + 
			dungeon[(i+1)*width + j] +
			dungeon[(i+1)*width + j+1];

			if(neighbors < 3)
			{
				changes[i*width + j] = 0;
			}
			else if(neighbors > 3)
			{
				changes[i*width + j] = 1;
			}
			neighbors = 0;
		}
	}
	dungeon = changes;
  //pos = y1 * width + x1;
}
