#include "dfs.h"

std::string DFS::name() const
{
   return "Depth First Search";
}

//finds a path from two points
Path DFS::findPath(const Location& start,
                   const Location& end,
                   const gridMap& grid) const
{
  Path dfsPath;
  getPath(dfsPath, start, end, grid);
  return dfsPath;
}

// Recursively finds the path from loc to end
bool DFS::getPath(Path& dfsPath, const Location& loc,
                  const Location& end, const gridMap& grid) const
{
  dfsPath.visited.push_back(loc);
  if( loc == end )
  {
    dfsPath.path.push_back(loc);
    return true;
  }
  std::stack<Location> neighbors = getNeighbors(loc, grid, dfsPath);
  while(!neighbors.empty())
  {
    if(getPath(dfsPath, neighbors.top(), end, grid))
    {
      dfsPath.path.push_back(loc);
      return true;
    }
    else
    {
      neighbors.pop();
    }
  }
  if(neighbors.size()==0)
  {
    return false;
  }
}

// Returns the neighbors that are within the grid, aren't walls,
// and haven't been visited yet
std::stack<Location> DFS::getNeighbors(const Location& loc, const gridMap& grid,
                                       Path& dfsPath) const
{
  std::stack<Location> neighbors;
  Location tempLoc;
  bool isVisited=false;
  tempLoc = Location(loc.x+1,loc.y);
  if(tempLoc.x < grid.getWidth() && tempLoc.x >= 0
     && tempLoc.y < grid.getHeight()&& tempLoc.y >= 0
     && grid.getTile(tempLoc.x,tempLoc.y).weight != -1)
  {
    for(int i = 0; i < dfsPath.visited.size(); i++)
    {
      if(dfsPath.visited.at(i)==tempLoc )
      {
        isVisited = true;
        break;
      }
    }
    if(isVisited == false)
    {
      neighbors.push(tempLoc);
    }
  }

  tempLoc = Location(loc.x-1, loc.y);
  if(tempLoc.x < grid.getWidth() && tempLoc.x >= 0
     && tempLoc.y < grid.getHeight() && tempLoc.y >= 0
     && grid.getTile(tempLoc.x,tempLoc.y).weight != -1)
  {
    for(int i =0; i<dfsPath.visited.size(); i++)
    {
      if(dfsPath.visited.at(i)==tempLoc)
      {
        isVisited = true;
        break;
      }
    }
    if(isVisited == false)
    {
      neighbors.push(tempLoc);
    }
  }

  tempLoc = Location(loc.x, loc.y+1);
  if(tempLoc.x < grid.getWidth() && tempLoc.x >= 0
     && tempLoc.y < grid.getHeight() && tempLoc.y >= 0
     && grid.getTile(tempLoc.x,tempLoc.y).weight != -1)
  {
    for(int i =0; i<dfsPath.visited.size(); i++)
    {
      if(dfsPath.visited.at(i)==tempLoc)
      {
        isVisited = true;
        break;
      }
    }
    if(isVisited == false)
    {
      neighbors.push(tempLoc);
    }
  }

  tempLoc = Location(loc.x, loc.y-1);
  if(tempLoc.x < grid.getWidth() && tempLoc.x >= 0
     && tempLoc.y < grid.getHeight() && tempLoc.y >= 0
     && grid.getTile(tempLoc.x,tempLoc.y).weight != -1)
  {
    for(int i =0; i<dfsPath.visited.size(); i++)
    {
      if(dfsPath.visited.at(i)==tempLoc)
      {
        isVisited = true;
        break;
      }
    }
    if(isVisited == false)
    {
      neighbors.push(tempLoc);
    }
  }

  return neighbors;
}

int main()
{
  return 0;
}