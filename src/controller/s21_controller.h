
#ifndef CPP4_3DVIEWER_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_CONTROLLER_CONTROLLER_H_

#include "../back/s21_parser.h"

class S21ViewerController {
 public:
  void ReadFileController(std::string input_str);
  std::vector<int> GetVectorWithPolygonsController();
  std::vector<point> GetVectorWithVertexesController();
  size_t GetVertexesNumController();

 private:
  std::vector<point> points_controller_;
  std::vector<int> polygons_controller_;
  size_t vertexes_num_controller_;
};

#endif