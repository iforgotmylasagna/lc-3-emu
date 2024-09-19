#pragma once
#include <vector>
#include <stdexcept>
#include <concepts>


namespace lc3vm{

class pixbuff{
public:

pixbuff():height_(0),width_(0),size_(0){}
pixbuff(size_t height, size_t width):height_(height),width_(width),size_(height_*width_){
  buff_.reserve(size_);
  buff_.resize(size_);
}

  class pixel{
    public:
    pixel():data_(0x00){
    }
    void setr(char);
    void setg(char);
    void setb(char);
    char& getchar();
    private:
    char data_;
  };

pixel& operator[](std::size_t index){
  if (index>=size_) [[unlikely]] {
    throw std::out_of_range("Index out of range");
  }
  return buff_[index];
}

const pixel& operator[](std::size_t index) const{
  if (index>=size_) [[unlikely]] {
    throw std::out_of_range("Index out of range");
  }
  return buff_[index];
}

pixel& operator[](std::integral auto index){
  return (*this)[static_cast<std::size_t>(index)];
}
const pixel& operator[](std::integral auto index) const{
  return (*this)[static_cast<std::size_t>(index)];
}

std::vector<pixel>::iterator begin(){
  return buff_.begin();
}
std::vector<pixel>::iterator end(){
  return buff_.end();
}

private:
std::size_t height_;
std::size_t width_;
std::size_t size_;
std::vector<pixel> buff_;

};

}
