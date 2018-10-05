#include "dimensions.h"
#include "draw.h"
#include "parser.h"
#include "tile.h"

int main(int argc, char** argv)
{
  struct tile tiles[42];
  const int width = 320;
  const int height = 320;

  int n_tiles = parse_tiles(stdin, tiles);

  /* We don't check the set of tiles to make sure that they're legal —
   * notably, we don't even check to ensure that no two tiles share a space.
   * Homework: add code here to warn the user if two tiles share a space.
   */

  struct dimensions dims = calculate_dimensions(tiles, n_tiles, width, height);

  cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
  cairo_t *cr = cairo_create(surface);

  draw(cr, tiles, n_tiles, &dims);

  cairo_surface_write_to_png(surface, "hexes.png");

  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  return 0;
}
