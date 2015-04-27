#ifndef DFS_H
#define DFS_H

#include "algorithmClass.h"

class DFS : public Algorithm
{
   virtual std::string name() const override;
   //finds a path from two points
   virtual Path findPath(const Location& start,
                         const Location& end,
                         const gridMap& grid) const override;
   
};

#endif // DFS_H

