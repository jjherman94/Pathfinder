#ifndef BFS_H
#define BFS_H

#include "algorithmClass.h"

class BFS : public Algorithm
{
   virtual std::string name() const override;
   //finds a path from two points
   virtual Path findPath(const Location& start,
                         const Location& end,
                         const gridMap& grid) const override;
};

#endif // BFS_H
