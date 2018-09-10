#include <stdio.h>

/*
** Usage : gcc -Wextra -Wall -Werror palettegenrator.c && ./a.out
*/

int		bernstein(int iter, int iter_max)
{
	float	t;
	int		rgb;

	t = (float)iter / (float)iter_max;
	rgb = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
	rgb += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
	rgb += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (rgb);
}

int main (void)
{
    int i;
    int limit;

    i = 0;
    limit = 1000;
    while (++i < limit)
        printf("\nPalette (%d/%d) is %d",i, limit, bernstein(i, limit));
    return (0);
}
