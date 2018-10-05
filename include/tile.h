#pragma once

#include <stdint.h>

struct tile
{
  enum { BLACK, RED } color;
  int16_t x, y;
};
