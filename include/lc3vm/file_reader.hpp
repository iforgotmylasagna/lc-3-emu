#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>


namespace lc3vm{



class file_reader{
public:
  file_reader() = default;
  file_reader(const file_reader&)=delete;
  file_reader& operator=(const file_reader&)=delete;
  file_reader(file_reader&&) = delete;
  file_reader& operator=(file_reader&&)=delete;

  file_reader(const std::string& filename);
  int open(const std::string& filename);
  int read();
  int close();

  bool is_open() const;
  size_t get_file_size();
  size_t get_data_size();

  std::vector<uint16_t> get_data();

  void print();

private:
  std::string filename_;
  std::ifstream file_;
  bool is_read_data_=false;
  std::vector<uint16_t> data_;
};













} //end namespace
