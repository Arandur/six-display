#include "dimensions.h"

#include <limits.h>
#include <math.h>

struct dimensions calculate_dimensions(
    const struct tile *tiles, int n_tiles, int img_width, int img_height)
{
  /* We calculate the dimensions in hex-space first, because it's faster and
   * somewhat less complicated due to only needing to deal with integers.
   *
   * Hex-space is a space in which each hex is four units tall and four units
   * wide. Obviously these aren't equilateral hexes, but it's a simple linear
   * transformation to make them equilateral after all the math is done.
   */

  int min_x = INT_MAX;
  int max_x = INT_MIN;
  int min_y = INT_MAX;
  int max_y = INT_MIN;

  for (int i = 0; i < n_tiles; ++i)
  {
    const int hx =  3 * tiles[i].x;
    const int hy = -2 * tiles[i].x + 4 * tiles[i].y;

    min_x = fmin(min_x, hx - 2);
    max_x = fmax(max_x, hx + 2);
    min_y = fmin(min_y, hy - 2);
    max_y = fmax(max_y, hy + 2);
  }

  /* We now have a box in hex-space within which all our hexes will fit. We
   * will use this to determine how big our hexes will be.
   */
  struct dimensions dims;

  const double x_scale = img_width  / (double) (max_x - min_x);
  const double y_scale = img_height / (double) (max_y - min_y) / (sqrt(3.0) / 2.0);
  dims.x_scale = fmin(x_scale, y_scale);
  dims.y_scale = dims.x_scale * sqrt(3.0) / 2.0;

  dims.x_offset = (img_width  - dims.x_scale * (max_x - min_x)) / 2.0 - dims.x_scale * min_x;
  dims.y_offset = (img_height - dims.y_scale * (max_y - min_y)) / 2.0 - dims.y_scale * min_y;

  return dims;
}
