#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Line.hpp"
#include "Load.hpp"

namespace powersim::models {

class Bus {
 public:
  Bus(int id, std::string name, double nominalVoltage)
      : id_(id), name_(std::move(name)), nominalVoltage_(nominalVoltage) {}

  void addLoad(std::shared_ptr<models::Load> load) {
    loads_.push_back(std::move(load));
  }
  void addLine(std::shared_ptr<models::Line> line) {
    lines_.push_back(std::move(line));
  }

  int getId() const { return id_; }
  std::string getName() const { return name_; }
  double getNominalVoltage() const { return nominalVoltage_; }

  const std::vector<std::shared_ptr<models::Load>>& getLoads() const {
    return loads_;
  }
  const std::vector<std::shared_ptr<models::Line>>& getLines() const {
    return lines_;
  }

 private:
  int id_;
  std::string name_;
  double nominalVoltage_;

  std::vector<std::shared_ptr<models::Load>> loads_;
  std::vector<std::shared_ptr<models::Line>> lines_;
};
}  // namespace powersim::models