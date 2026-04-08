#pragma once
#include <string>

namespace powersim::models {

class Switch {
 public:
  Switch(std::string name, bool isClosed = true)
      : name_(std::move(name)), isClosed_(isClosed) {}
      
  virtual ~Switch() = default;

  virtual void open() { isClosed_ = false; }
  virtual void close() { isClosed_ = true; }
  
  bool isClosed() const { return isClosed_; }
  std::string getName() const { return name_; }

 protected:
  std::string name_;
  bool isClosed_;
};
}  // namespace powersim::models