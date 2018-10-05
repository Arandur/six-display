#include "parser.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_tiles(FILE *input, struct tile *tiles)
{
  int buf_sz = 20;
  char *buffer = (char *) malloc(buf_sz);

  int i = 0;
  for (; i < 42; ++i)
  {
    if (!fgets(buffer, buf_sz, input))
    {
      break;
    }

    /* At this point, it's possible that we haven't read the whole line. Need
     * to check for the presence of a newline.
     */
    while (1)
    {
      /* Slightly more efficient to use strchrnul here, but I want to stick to
       * standard C for pedagogical reasons. Homework: find out what strchrnul 
       * does, and figure out how to use it to make this function more 
       * efficient.
       */

      if (strchr(buffer, '\n'))
      {
        break;
      }

      /* This is the typical "buffer not big enough? Double the size until it
       * is!" pattern.
       */
      buffer = realloc(buffer, 2 * buf_sz);
      buf_sz *= 2;

      int len = strlen(buffer);
      if (!fgets(buffer + len, buf_sz - len, input))
      {
        break;
      }
    }

    /* Now we are assured that buffer contains the entire line, possibly
     * including a terminating newline character, definitely including a
     * terminating null byte.
     */

    char *color = strtok(buffer, " \t\r\n");

    if (!color)
    {
      fprintf(stderr, "Could not parse line %d: \"%s\"\n", i + 1, buffer);
      return -1;
    }

    /* Homework: make these comparisons case-insensitive.
     */

    if (strcmp(color, "black") == 0)
    {
      tiles[i].color = BLACK;
    }
    else if (strcmp(color, "red") == 0)
    {
      tiles[i].color = RED;
    }
    else
    {
      fprintf(stderr, "Unrecognized color on line %d: \"%s\"\n", i + 1, color);
      return -2;
    }

    char *sx = strtok(NULL, " \t\r\n");

    if (!sx)
    {
      fprintf(stderr, "Could not parse line %d: expected x value\n", i + 1);
      return -3;
    }

    char *endptr;
    errno = 0;
    long x = strtol(sx, &endptr, 10);

    if (errno)
    {
      fprintf(stderr, "Could not parse line %d: %s\n", i + 1, strerror(errno));
      return -4;
    }

    if (x < INT32_MIN || x > INT32_MAX)
    {
      fprintf(stderr, "Could not parse line %d: value %ld out of range\n", i + 1, x);
      return -5;
    }

    if (*endptr)
    {
      fprintf(stderr, "Could not parse line %d: \"%s\" is not an integer\n", i + 1, sx);
      return -6;
    }

    tiles[i].x = (int) x;

    char *sy = strtok(NULL, " \t\r\n");

    if (!sy)
    {
      fprintf(stderr, "Could not parse line %d: expected y value\n", i + 1);
      return -7;
    }

    errno = 0;
    long y = strtol(sy, &endptr, 10);

    if (errno)
    {
      fprintf(stderr, "Could not parse line %d: %s\n", i + 1, strerror(errno));
      return -8;
    }

    if (y < INT32_MIN || y > INT32_MAX)
    {
      fprintf(stderr, "Could not parse line %d: value %ld out of range\n", i + 1, x);
      return -9;
    }

    if (*endptr)
    {
      fprintf(stderr, "Could not parse line %d: \"%s\" is not an integer\n", i + 1, sy);
      return -10;
    }

    tiles[i].y = (int) y;

    char *extra = strtok(NULL, " \t\r\n");

    if (extra)
    {
      fprintf(stderr, "Warning: extra junk on line %d\n", i + 1);
    }
  }

  return i;
}
