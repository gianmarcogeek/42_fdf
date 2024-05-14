# Fil'e ferru aka FDF
## My first computer graphics project!

This project is about creating a simple wireframe model representation of a 3D land-scape by linking various points (x, y, z) thanks to line segments (edges).

The coordinates of the landscape are stored in a .fdf file passed as a parameter to the program. Here is an example:
```
$> cat 42.fdf
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
Each number represents a point in space:
- **X** | The horizontal position corresponds to its axis.
- **Y** | The vertical position corresponds to its ordinate.
- **Z** | The value corresponds to its altitude.

# My roadmap!

For now a list of links that i have used to dive in the basics of computer graphics

## What is X11?

- https://it.wikipedia.org/wiki/X_Window_System
- https://www.youtube.com/watch?v=R-N-fgKWYGU

## What is MinilibX?
MinilibX is a simple X-Window (X11R6) programming API in C, designed for students and X-beginners.

- https://youtu.be/bYS93r6U0zg?si=4p-HYlHW3aehwx2d
- https://youtu.be/bYS93r6U0zg?si=4p-HYlHW3aehwx2d

**RTFM!** Read The Fucking Manual
https://harm-smits.github.io/42docs/libs/minilibx.html

## How to draw a line? | Bresenhem algorithm

- https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
- https://youtu.be/8gIhNSAXYcQ?si=AlTeqPOJvk8SJRbP
- https://youtu.be/RGB-wlatStc?si=6y6Goq9ZDjcm9y8G

## How to project 3D to points to a 2D display?
To create the isometric projection i have used the semplified formulas:
  
$x′ = (x - y) * cos(a);$
$y' = (x + y) * sen(a) - z;$

To (try) undestand this formulas you have to look at Linear Algebra and Trasformations Matrices
- https://www.youtube.com/watch?v=fNk_zzaMoSs&list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab
- http://learnwebgl.brown37.net/transformations2/transformations_matrices.html

## How to fade from a color to another?
- https://www.alanzucconi.com/2016/01/06/colour-interpolation/
