#ifndef ALGORITHMCLASS_H
#define ALGORITHMCLASS_H

#include <string>
#include "path.h"
#include "gridMap.h"

class Algorithm
{
public:
   //returns the name of the function
   virtual std::string name() const = 0;
   //finds a path from two points
   virtual Path findPath(const std::pair<int, int>& start,
                         const std::pair<int, int>& end,
                         const gridMap& grid) const = 0;
};

#endif // ALGORITHMCLASS_H
