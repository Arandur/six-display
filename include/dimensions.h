#pragma once

#include "tile.h"

struct dimensions
{
  double x_offset;
  double y_offset;
  double x_scale;
  double y_scale;
};

struct dimensions calculate_dimensions(
    const struct tile *tiles, int n_tiles, int img_width, int img_height);
