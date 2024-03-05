#ifndef CPP4_3DVIEWER_BACK_PARSER_H_
#define CPP4_3DVIEWER_BACK_PARSER_H_

#include <OpenGL/gl.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Структура с координатами точек по всем осям
 *
 */
typedef struct Point {
  // GLfloat x;
  // GLfloat y;
  // GLfloat z;
  GLfloat mas[3];
} point;

/**
 * @brief класс по работе с файлом
 *
 */
class S21ViewerBack {
 public:
  /**
   * @brief функция для передачи имени файла в класс
   *
   * @param input_string строка-путь к файлу из корневой директории
   */
  void SetFilename(std::string input_string);

  /**
   * @brief функция для чтения строк из файла
   *
   */
  void ReadFile();

  /**
   * @brief функция, что возвращает вектор с точками
   *
   * @return std::vector<point> вектор точек
   */
  std::vector<point> GetVectorWithVertexes();

  /**
   * @brief функция, что возвращает вектор с полигонами
   *
   * @return std::vector<int> вектор полигонов
   */
  std::vector<int> GetVectorWithPolygons();

  /**
   * @brief функция, что возвращает количество точек
   *
   * @return size_t количество точек
   */
  size_t GetVertexesNum();

 private:
  std::string filename_;         // путь к файлу
  std::vector<point> vertexes_;  // вершины
  std::vector<int> polygons_;    // полигоны
  size_t count_vertexes_;        // количество верщин

  /**
   * @brief функция считывает координаты точки
   *
   * @param str строка из файла
   * @return point структура координат точки
   */
  point GetVNumFromStr_(std::string str);

  /**
   * @brief функция считывает значения полигона
   *
   * @param str строка из файла
   */
  void GetFNumFromStr_(std::string str);
};

#endif