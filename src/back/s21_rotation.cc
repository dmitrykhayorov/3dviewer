
#include "s21_rotation.h"

S21RotationMatrix::S21RotationMatrix(/* args */) {}

S21RotationMatrix::~S21RotationMatrix() {}

void S21RotationMatrix::TranslatePoints(std::vector<point> *points, GLfloat x,
                                        GLfloat y, GLfloat z) {
  for (std::vector<point>::iterator it = points->begin(); it != points->end();
       it++) {
    it->mas[0] += x;
    it->mas[1] += y;
    it->mas[2] += z;
  }
}

void S21RotationMatrix::RotateMatrix(std::vector<point> *points,
                                     GLfloat rotate_x, GLfloat rotate_y,
                                     GLfloat rotate_z) {
  if (rotate_x != 0) {
    for (std::vector<point>::iterator it = points->begin(); it != points->end();
         it++) {
      it->mas[1] = it->mas[1] * cos(rotate_x) - it->mas[2] * cos(rotate_x);
      it->mas[2] = it->mas[1] * cos(rotate_x) + it->mas[2] * cos(rotate_x);
    }
  }
  if (rotate_y != 0) {
    for (std::vector<point>::iterator it = points->begin(); it != points->end();
         it++) {
      it->mas[0] = it->mas[0] * cos(rotate_y) + it->mas[2] * cos(rotate_y);
      it->mas[2] =
          (-1) * it->mas[0] * cos(rotate_y) + it->mas[2] * cos(rotate_y);
    }
  }
  if (rotate_z != 0) {
    for (std::vector<point>::iterator it = points->begin(); it != points->end();
         it++) {
      it->mas[1] = it->mas[0] * cos(rotate_z) - it->mas[1] * cos(rotate_z);
      it->mas[2] = it->mas[0] * cos(rotate_z) + it->mas[1] * cos(rotate_z);
    }
  }
}