#include <utility>

#include <fstream>
#include <sstream>
#include <Rating.h>

#include "Rating.h"

Rating::Rating(uint32_t id, std::string name, uint8_t capacity) : id(id), name(std::move(name)), capacity(capacity) {
  choices = new std::string*[capacity];
  statistics = new uint32_t[capacity];
}

bool Rating::serialise(const std::string &path) {
  std::stringstream i_to_str;
  i_to_str >> id;

  std::ofstream file(path + i_to_str.str());
  file << name << std::endl;
  file << capacity << ' ' << size << state << std::endl;
  for (int i = 0; i < size; i++) {
    file << choices[i] << std::endl;
    file << statistics[i] << std::endl;
  }
  file.close();
  return false;
}

bool Rating::add_choice(std::string &choice) {
  if (size == capacity) return false;
  choices[size] = new std::string(choice);
  statistics[size] = 0;
  size++;
  return true;
}

Rating *Rating::createRating(std::string &filename) {
  int id = std::stoi(filename);
  std::ifstream file(filename);
  std::string name;
  uint8_t size, capacity;
  std::getline(file, name);
  file >> capacity >> size;
  Rating *rating = new Rating(id, name, capacity);
  uint8_t state;
  file >> state;
  rating->state = (State) state;
  for (int i = 0; i < size; i++) {
    std::string choice;
    std::getline(file, choice);
    uint8_t statistic;
    file >> statistic;
    rating->add_choice(choice);
    rating->statistics[size - 1] = statistic;
  }
}

Rating::~Rating() {
  for (int i = 0; i < size; i++) {
    delete choices[i];
  }
}
