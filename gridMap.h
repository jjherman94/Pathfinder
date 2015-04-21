#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <vector>

struct Tile
{
   //enum for knowing what happened to the tile
   enum class Status
   {
      nothing = 0,
      visited = 1,
      path = 2,
   };
   //weight of the tile (-1 for wall)
   int weight;
   //the status of the tile
   Status status;
};

class gridMap
{
public:
   //resize the grid to the given height
   void resize(unsigned width, unsigned height);
   //returns the tile at the given x, y position
   Tile& getTile(int x, int y);
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
