#include "draw.h"

void draw(cairo_t *cr, const struct tile *tiles, int n_tiles, const struct dimensions *dims)
{
  /* We introduce shrinkage to make space between the individual hexes, so they
   * don't appear to all be part of the same mass.
   */
  const double shrinkage = 0.99;

  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);

  for (int i = 0; i < n_tiles; ++i)
  {
    cairo_set_source_rgb(cr, tiles[i].color, 0, 0);

    const double cx = ( 3 * tiles[i].x                 ) * dims->x_scale + dims->x_offset;
    const double cy = (-2 * tiles[i].x + 4 * tiles[i].y) * dims->y_scale + dims->y_offset;

    cairo_move_to(cr, cx + 2 * dims->x_scale * shrinkage, cy);
    cairo_line_to(cr, cx +     dims->x_scale * shrinkage, cy + 2 * dims->y_scale * shrinkage);
    cairo_line_to(cr, cx -     dims->x_scale * shrinkage, cy + 2 * dims->y_scale * shrinkage);
    cairo_line_to(cr, cx - 2 * dims->x_scale * shrinkage, cy);
    cairo_line_to(cr, cx -     dims->x_scale * shrinkage, cy - 2 * dims->y_scale * shrinkage);
    cairo_line_to(cr, cx +     dims->x_scale * shrinkage, cy - 2 * dims->y_scale * shrinkage);

    cairo_close_path(cr);
    cairo_fill(cr);
  }
}
