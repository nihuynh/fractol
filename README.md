# fractol
Links :
http://mrob.com/pub/muency/speedimprovements.html
http://mrob.com/pub/comp/logcpu/index.html

TODO :
Rule for the makefile (debug flags of optimisation)
More color  => HSV to fix
Multi-core  => split mon image et chaque thread fait une bande
chaque thread a son buffer l'iter count.

Take a screen shot :
https://www.carnetdumaker.net/articles/dessiner-la-fractale-de-mandelbrot-en-python-et-en-cc/
You read your image buffer and built the image.
image .xpm   => https://fr.wikipedia.org/wiki/X_PixMap
image .ppm  => https://fr.wikipedia.org/wiki/Portable_pixmap
image .tga  => https://fr.wikipedia.org/wiki/Truevision_Targa

More fractal :
Newton
Tricorn
Apollonius circle
http://www.fil.univ-lille1.fr/~L2S3API/CoursTP/Projets/Apollonius/sujet_apollonius.html
flame

Coloring :
https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
https://www.carnetdumaker.net/articles/dessiner-la-fractale-de-mandelbrot-en-python-et-en-cc/

Boundary :
https://bisqwit.iki.fi/jutut/kuvat/programming_examples/mandelbrotbtrace.pdf


Profil:
http://www.math.utah.edu/docs/info/gprof_toc.html
Man pages :
man pthread
man sem_open
man sem_close
man sem_unlink

Hors sujet :
Plein de flag sanitize
 -fsanitize=undefined -fsanitize=bounds -fsanitize=null -fno-omit-frame-pointer
http://www.icosaedro.it/c-modules.html
Semaphores:
http://hacksoflife.blogspot.com/2010/12/performance-of-semaphore-vs-condition.html
reverse engineer :
strings fractol
nm fractol
otools -tv fractol

DONE :
optimisation for mandelbrot remove point of the cardoide & first bulbe
Zoom on mouse
arrow for moving

JUNKYARD :
int     static_palette(int iter)
{
    int colors[] = {
    0xf7df, 0xff5a, 0x07ff, 0x7ffa, 0xf7ff, 0xf7bb, 0xff38, 0xff59, 0x001f, 0x895c,
    0xa145, 0xddd0, 0x5cf4, 0x7fe0, 0xd343, 0xfbea, 0x64bd, 0xffdb, 0xd8a7, 0x07ff,
    0x0011, 0x0451, 0xbc21, 0xad55, 0x0320, 0xbdad, 0x8811, 0x5345, 0xfc60, 0x9999,
    0x8800, 0xecaf, 0x8df1, 0x49f1, 0x2a69, 0x067a, 0x901a, 0xf8b2, 0x05ff, 0x6b4d,
    0x1c9f, 0xd48e, 0xb104, 0xffde, 0x2444, 0xf81f, 0xdefb, 0xffdf, 0xfea0, 0xdd24,
    0x8410, 0x0400, 0xafe5, 0xf7fe, 0xfb56, 0xcaeb, 0x4810, 0xfffe, 0xf731, 0xe73f,
    0xff9e, 0x7fe0, 0xffd9, 0xaedc, 0xf410, 0xe7ff, 0xffda, 0xd69a, 0x9772, 0xfdb8,
    0xfd0f, 0x2595, 0x867f, 0x839f, 0x7453, 0xb63b, 0xfffc, 0x07e0, 0x3666, 0xff9c,
    0xf81f, 0x8000, 0x6675, 0x0019, 0xbaba, 0x939b, 0x3d8e, 0x7b5d, 0x07d3, 0x4e99,
    0xc0b0, 0x18ce, 0xf7ff, 0xff3c, 0xff36, 0xfef5, 0x0010, 0xffbc, 0x8400, 0x6c64,
    0xfd20, 0xfa20, 0xdb9a, 0xef55, 0x9fd3, 0xaf7d, 0xdb92, 0xff7a, 0xfed7, 0xcc27,
    0xfe19, 0xdd1b, 0xb71c, 0x8010, 0xf800, 0xbc71, 0x435c, 0x8a22, 0xfc0e, 0xf52c,
    0x2c4a, 0xffbd, 0xa285, 0xc618, 0x867d, 0x6ad9, 0x7412, 0xffdf, 0x07ef, 0x4416,
    0xd5b1, 0x0410, 0xddfb, 0xfb08, 0x471a, 0xec1d, 0xd112, 0xf6f6, 0xffff, 0xf7be,
    0xffe0, 0x9e66, 0x0000
	};

    return (colors[iter % 142]);
}

int     static_palette(int iter)
{
    int colors[16] = {
        0x000000,
        0x19071a,
        0x09012f,
        0x040449,
        0x000764,
        0x0c2c8a,
        0x1852b1,
        0x397dd1,
        0x86b5e5,
        0xd3ecf8,
        0xf1e9bf,
        0xf8c95f,
        0xffaa00,
        0xcc8000,
        0x995700,
        0x6a3403
    };

    return (colors[iter % 16]);
}