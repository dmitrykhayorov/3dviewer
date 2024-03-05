#ifndef CPP4_3DVIEWER_BACK_ROTATION_H_
#define CPP4_3DVIEWER_BACK_ROTATION_H_

#include <math.h>

#include "s21_parser.h"

/**
 * @brief класс для работы с точками
 *
 */
class S21RotationMatrix {
 public:
  S21RotationMatrix();
  ~S21RotationMatrix();

  /**
   * @brief функция для сдвига фигуры
   *
   * @param points вектор точек для сдвига
   * @param x сдвиг по x
   * @param y сдвиг по y
   * @param z сдвиг по z
   */
  void TranslatePoints(std::vector<point> *points, GLfloat x, GLfloat y,
                       GLfloat z);

  /**
   * @brief функция для поворота фигуры
   *
   * @param points вектор точек для поворота
   * @param rotate_x угол поворота по x
   * @param rotate_y угол поворота по y
   * @param rotate_z угол поворота по z
   */
  void RotateMatrix(std::vector<point> *points, GLfloat rotate_x,
                    GLfloat rotate_y, GLfloat rotate_z);

 private:
};

#endif