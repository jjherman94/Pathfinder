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

// the location
struct Location
{
   int x, y;
   Location operator=(Location rhs)
   {
    x=rhs.x;
    y=rhs.y;
    return *this;
   }
   
   bool operator==(Location rhs) const
   {
      return (x == rhs.x && y == rhs.y);
   }
   
   Location(int a, int b)
   {
      x=a;
      y=b;
   }
   
   Location(){}
};

struct Path
{
   std::vector<Location> visited;
   std::vector<Location> path;
};

#endif // PATH_H
