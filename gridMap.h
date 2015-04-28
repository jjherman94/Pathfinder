#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <vector>
#include "path.h"

class gridMap
{
public:
   //resize the grid to the given height
   void resize(unsigned width, unsigned height);
   //returns the tile at the given x, y position
   Tile& getTile(int x, int y);
   const Tile& getTile(int x, int y) const;
   //returns the tile at the given location
   Tile& getTile(const Location& loc);
   const Tile& getTile(const Location& loc) const;
   //returns the width
   unsigned getWidth() const;
   //returns the height
   unsigned getHeight() const;
   //resets all tiles to having no status
   void reset();

private:
   //tiles, width, and height
   std::vector<Tile> tiles;
   unsigned width;
   unsigned height;
};

#endif // GRIDMAP_H
