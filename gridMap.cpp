#include "gridMap.h"

#include <algorithm>

void gridMap::resize(unsigned width, unsigned height)
{
   //just set width/height and resize for now
   this->width = width;
   this->height = height;
   tiles.resize(width*height);
}

Tile& gridMap::getTile(int x, int y)
{
   //tile is at x + y * width
   return tiles[x + y * width];
}

unsigned gridMap::getWidth() const
{
   return width;
}

unsigned gridMap::getHeight() const
{
   return height;
}

void gridMap::reset()
{
   std::for_each(tiles.begin(),
                 tiles.end(),
                 [](Tile& t){t.status = Tile::Status::nothing;});
}
