#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Point {
  void (*vPrint)(struct Point *);
  int x;
  int y;
} Point;

void Point_move(Point *self, int dx, int dy) {
  self->x += dx;
  self->y += dy;
}

void Point_print(Point *self) {
  printf("P.print: %d, %d\n", self->x, self->y);
}

void Point_vPrint(Point *self) {
  printf("P.vPrint: %d, %d\n", self->x, self->y);
}

void Point_init(Point *self, int x, int y) {
  self->x = x;
  self->y = y;
  self->vPrint = &Point_vPrint;
}

typedef struct ColorPoint {
  void (*vPrint)(struct ColorPoint *);
  int x;
  int y;
  int color;
} ColorPoint;

void ColorPoint_setColor(ColorPoint *self, int c) {
  self->color = c;
}

void ColorPoint_print(ColorPoint *self) {
  printf("CP.print: %d, %d, %d\n", self->x, self->y, self->color);
}

void ColorPoint_vPrint(ColorPoint *self) {
  printf("CP.print: %d, %d, %d\n", self->x, self->y, self->color);
}

void ColorPoint_init(ColorPoint *self, int x,
                     int y, int color) {
  Point_init((Point *)self, x, y); // Casting works like magic
  self->color = color;
  self->vPrint = &ColorPoint_vPrint;
}

int main() {
  srand(time(NULL));
  int r = rand();

  Point *p;
  if (r % 2 == 0) {
    Point *temp = (Point *)malloc(sizeof(Point));
    Point_init(temp, 0, 0);
    p = (Point *)temp;
  } else {
    ColorPoint *temp = (ColorPoint *)malloc(sizeof(ColorPoint));
    ColorPoint_init(temp, 6, 9, 255);
    p = (Point *)temp;
  }

  Point_print(p);      // static dispatch
  p->vPrint(p);        // dynamic dispatch
  Point_move(p, 5, 4); // static dispatch
  Point_print(p);      // static dispatch
  p->vPrint(p);        // dynamic dispatch
  
  return 0;
}
