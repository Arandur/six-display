#pragma once

#include "tile.h"

#include <stdio.h>

/**
 * Parses the file designated by `input` into a set of tiles.
 *
 * `tiles` must point to a buffer containing enough room to hold 42 tiles,
 * which is the maximum number of tiles which can be on the board at one time.
 * If the file contains more than 42 tile descriptions, only the first 42 are
 * parsed.
 *
 * Returns the number of tile descriptions parsed.
 */
int parse_tiles(FILE *input, struct tile *tiles);
