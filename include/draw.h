#pragma once

#include "dimensions.h"
#include "tile.h"

#include <cairo/cairo.h>

void draw(cairo_t *cr, const struct tile *tiles, int n_tiles, const struct dimensions *dims);
