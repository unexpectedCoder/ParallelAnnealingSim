#ifndef BOUNDS_H
#define BOUNDS_H

#include <iostream>


struct Bounds
{
  // Saves boundaries of target function arguments.
  double *bmin, *bmax;		// Minimum and maximum values
  size_t dim;             // Dimension of target function

  Bounds(const double *bmin, const double *bmax, size_t dim);
  Bounds(const Bounds &b);
  ~Bounds();

  bool isEmpty() const;

  friend std::ostream& operator<<(std::ostream &os, const Bounds &b);
};

#endif // BOUNDS_H
