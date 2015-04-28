#ifndef PATH_H
#define PATH_H

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

struct Location
{
   // the location
   int x, y;
};

struct Path
{
   std::vector<Location> visited;
   std::vector<Location> path;
};

#endif // PATH_H
