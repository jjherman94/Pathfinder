#include "gridMap.h"

#include <algorithm>

void gridMap::resize(unsigned width, unsigned height)
{
   //put old and sizes in an older map
   auto oldMap = std::move(*this);
   //set new size
   this->width = width;
   this->height = height;
   //resize for new tiles
   tiles.resize(width*height);
   //copy old tile statuses and weights
   for(auto x = 0u; x < width; ++x)
   {
      for(auto y = 0u; y < height; ++y)
      {
         //only copy if the old map was big enough
         if(x < oldMap.width && y < oldMap.height)
         {
            getTile(x, y) = oldMap.getTile(x, y);
         }
      }
   }
}

Tile& gridMap::getTile(int x, int y)
{
   //tile is at x + y * width
   return tiles[x + y * width];
}

const Tile& gridMap::getTile(int x, int y) const
{
   return tiles[x + y * width];
}

Tile& gridMap::getTile(const Location& loc)
{
   return getTile(loc.x, loc.y);
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
