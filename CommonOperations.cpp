#include "cv_utils.h"

using namespace std;

namespace cv_utils
{
  std::vector<int> findNeighbors(const int pixel, const int WIDTH, const int HEIGHT, const bool USE_PANORAMA, const int NEIGHBOR_SYSTEM)
  {
    int x = pixel % WIDTH;
    int y = pixel / WIDTH;
    std::vector<int> neighbors;
    if (x > 0)
      neighbors.push_back(pixel - 1);
    if (x < WIDTH - 1)
      neighbors.push_back(pixel + 1);
    if (y > 0)
      neighbors.push_back(pixel - WIDTH);
    if (y < HEIGHT - 1)
      neighbors.push_back(pixel + WIDTH);
    
    if (USE_PANORAMA && x == 0)
      neighbors.push_back(pixel + (WIDTH - 1));
    if (USE_PANORAMA && x == WIDTH - 1)
      neighbors.push_back(pixel - (WIDTH - 1));
    
    if (NEIGHBOR_SYSTEM == 8) {
      if (x > 0 && y > 0)
	neighbors.push_back(pixel - 1 - WIDTH);
      if (x > 0 && y < HEIGHT - 1)
	neighbors.push_back(pixel - 1 + WIDTH);
      if (x < WIDTH - 1 && y > 0)
	neighbors.push_back(pixel + 1 - WIDTH);
      if (x < WIDTH - 1 && y < HEIGHT - 1)
	neighbors.push_back(pixel + 1 + WIDTH);

      if (USE_PANORAMA && x == 0) {
	if (y > 0)
	  neighbors.push_back(pixel + (WIDTH - 1) - WIDTH);
        if (y < HEIGHT - 1)
	  neighbors.push_back(pixel + (WIDTH - 1) + WIDTH);
      }
      if (USE_PANORAMA && x == WIDTH - 1) {
	if (y > 0)
          neighbors.push_back(pixel - (WIDTH - 1) - WIDTH);
        if (y < HEIGHT - 1)
          neighbors.push_back(pixel - (WIDTH - 1) + WIDTH);
      }
    }
    return neighbors;
  }
  
  std::vector<std::vector<int> > findNeighborsForAllPixels(const int WIDTH, const int HEIGHT, const int NEIGHBOR_SYSTEM)
  {
    vector<vector<int> > pixel_neighbors(WIDTH * HEIGHT);
    for (int pixel = 0; pixel < WIDTH * HEIGHT; pixel++)
      pixel_neighbors[pixel] = findNeighbors(pixel, WIDTH, HEIGHT, NEIGHBOR_SYSTEM);
    return pixel_neighbors;
  }
}
