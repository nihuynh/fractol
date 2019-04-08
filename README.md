# fractol

---
![Top](docs/screenshot/main.png)

## How to install

On mac, this command will built an app bundle:
```
git clone https://github.com/nihuynh/fractol && cd fractol
make built && open build
```
On linux :
```
git clone https://github.com/nihuynh/fractol && cd fractol
make run
```

## Summary
_This is a fractal render program written in C._

_This project is done during 42 graphic branch to learn about optimisation and computer graphics._

_Built and tested on mac OSX 10, it should work on linux (Untested)_

There is 6 fractals implemented :
- Mandelbrot
- Julia
- Burning ship
- Burning julia
- personal discover
- personal discover julia edition

#### Feature list :
- 6 type of fractal.
- Multi-threading
- Zoom on the mouse position.
- Multiple palette of colors.
- Partial render when the iteration count increase (Or decrease).


## How to use

### Keymap :

<kbd>ESC</kbd> | Quit the program

<kbd>1</kbd><kbd>2</kbd><kbd>3</kbd><kbd>4</kbd><kbd>5</kbd><kbd>6</kbd> | Select the fractal

<kbd>ARROWS</kbd> | Translate

<kbd>P</kbd> | Change the color palette

<kbd>spacebar</kbd> Lock/unlock the mouse on the fractal 2, 4, 6

<kbd>R</kbd> increase   ITERATION   decrease <kbd>F</kbd>

<kbd>R</kbd> increase   ITERATION (Small steps)   decrease <kbd>F</kbd>

<kbd>Q</kbd> in   ZOOM   out <kbd>E</kbd>

---

### Credits :
* Thanks to skeeto for the advices on multi-threading.
Check his awesome blog at [nullprogram.com](https://nullprogram.com/index/).

#### Wish list features :
- config file for the resolution
- screenshot
- video output from dezoom or zoom
- new fractal : Newton
- new fractal : Tricorn
- new fractal : Apollonius circle
- new fractal : flame
- http://mrob.com/pub/muency/speedimprovements.html

#### Licence:
_This repository is under no license._