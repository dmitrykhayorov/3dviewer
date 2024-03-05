
#include "s21_controller.h"

void S21ViewerController::ReadFileController(std::string input_str) {
  S21ViewerBack tmp;
  tmp.SetFilename(input_str);
  tmp.ReadFile();
  points_controller_ = tmp.GetVectorWithVertexes();
  polygons_controller_ = tmp.GetVectorWithPolygons();
  vertexes_num_controller_ = tmp.GetVertexesNum();
}

std::vector<int> S21ViewerController::GetVectorWithPolygonsController() {
  return polygons_controller_;
}

std::vector<point> S21ViewerController::GetVectorWithVertexesController() {
  return points_controller_;
}

size_t S21ViewerController::GetVertexesNumController() {
  return vertexes_num_controller_;
}