#ifndef DFS_H
#define DFS_H

#include "algorithmClass.h"
#include "gridMap.h"
#include<stack>
class DFS : public Algorithm
{
  virtual std::string name() const override;
  
  // finds a path from two points
  virtual Path findPath(const Location& start,
                       const Location& end,
                       const gridMap& grid) const override;
   
  // Recursively finds the path from loc to end
  bool getPath(Path& dfsPath, const Location& loc, const Location& end,
               const gridMap& grid) const;

  // Returns the neighbors that are within the grid, aren't walls,
  // and haven't been visited yet
  std::stack<Location> getNeighbors(const Location& loc, const gridMap& grid,
                                    Path& dfsPath) const;

};

#endif // DFS_H

