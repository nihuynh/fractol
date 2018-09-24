# fractol
Links :
http://mrob.com/pub/muency/speedimprovements.html
https://joseph-long.com/writing/app-bundles-with-a-makefile/

TODO :
Format this file :
_description
_keymap
_screenshot
_changelog

Add function :
REDUCE COMPLEXITY
RENAMING
change define to val reduce overhead in loops
Optimize ft_bzero

Rule for the makefile (debug flags of optimisation)
More color  => HSV to fix
Multi-core  => split mon image et chaque thread fait une bande
chaque thread a son buffer l'iter count.

Take a screen shot :
https://www.carnetdumaker.net/articles/dessiner-la-fractale-de-mandelbrot-en-python-et-en-cc/
You read your image buffer and built the image.
https://people.cs.clemson.edu/~dhouse/courses/405/notes/ppm-files.pdf
image .xpm   => https://fr.wikipedia.org/wiki/X_PixMap
image .ppm  => https://fr.wikipedia.org/wiki/Portable_pixmap
image .tga  => https://fr.wikipedia.org/wiki/Truevision_Targa

More fractal :
Newton
Tricorn
Apollonius circle
http://www.fil.univ-lille1.fr/~L2S3API/CoursTP/Projets/Apollonius/sujet_apollonius.html
flame

palette :
https://colourco.de/

Coloring :
https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
https://www.carnetdumaker.net/articles/dessiner-la-fractale-de-mandelbrot-en-python-et-en-cc/

Boundary :
https://bisqwit.iki.fi/jutut/kuvat/programming_examples/mandelbrotbtrace.pdf

Man pages :
man pthread
man sem_open
man sem_close
man sem_unlink

Hors sujet :
cpu load : http://mrob.com/pub/comp/logcpu/index.html
Plein de flag sanitize
 -fsanitize=undefined -fsanitize=bounds -fsanitize=null -fno-omit-frame-pointer
http://www.icosaedro.it/c-modules.html
app with makefile :
https://joseph-long.com/writing/app-bundles-with-a-makefile/

reverse engineer :
strings fractol
nm fractol
otools -tv fractol

DONE :
optimisation for mandelbrot remove point of the cardoide & first bulbe
Zoom on mouse
arrow for moving
Multi-threading
.app
hud
handle close

DATA :
julia center on 1000*1000
O3 : 200 ms
O0 : 450 ms

CREDIT :
Thanks to skeeto for his advices on multi-threading.
You can check is website nullprogram.com where there is ...