
#include "s21_parser.h"

void S21ViewerBack::SetFilename(std::string input_string) {
  count_vertexes_ = 0;
  filename_ = input_string;
}

void S21ViewerBack::ReadFile() {
  std::ifstream file(this->filename_);
  if (!file) {
    throw std::invalid_argument("Invalid filename");
  }

  std::string buf_string_from_file;

  while (getline(file, buf_string_from_file)) {
    if (buf_string_from_file[0] == 'v' && buf_string_from_file[1] == ' ') {
      count_vertexes_ += 1;
      vertexes_.push_back(GetVNumFromStr_(buf_string_from_file));
    } else if (buf_string_from_file[0] == 'f' &&
               buf_string_from_file[1] == ' ') {
      GetFNumFromStr_(buf_string_from_file);
    }
  }

  file.close();
}

point S21ViewerBack::GetVNumFromStr_(std::string str) {
  point return_value;

  for (int i = 0; i < 3; i++) {
    str = str.substr(str.find(' ') + 1, str.size() - str.find(' ') - 1);
    while (*str.begin() == ' ') {
      str = str.substr(1, str.size() - 1);
    }
    return_value.mas[i] = std::stof(str);
  }

  return return_value;
}

void S21ViewerBack::GetFNumFromStr_(std::string str) {
  size_t counter = 0;
  std::string::iterator it_buf;
  std::string numbers("0123456789");
  bool flag = 1;
  str = str.substr(str.find(' ') + 1, str.size() - str.find(' ') - 1);

  while (flag) {
    if (counter != 0 && str.find_first_of(numbers) != std::string::npos) {
      polygons_.push_back(std::stof(str) - 1);
    }
    it_buf = std::find(str.begin(), str.end(), ' ');
    if (it_buf == str.end() ||
        str.find_first_of(numbers) == std::string::npos) {
      flag = 0;
    } else {
      polygons_.push_back(std::stof(str) - 1);
      str = str.substr(str.find(' ') + 1, str.size() - str.find(' ') - 1);
    }
    counter++;
  }
}

std::vector<point> S21ViewerBack::GetVectorWithVertexes() { return vertexes_; }

std::vector<int> S21ViewerBack::GetVectorWithPolygons() { return polygons_; }

size_t S21ViewerBack::GetVertexesNum() { return count_vertexes_; }