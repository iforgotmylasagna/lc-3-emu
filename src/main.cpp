#include "lc3vm/vm.hpp"
#include <iostream>
#include <string>
#include <filesystem>
//#include <SDL.h> //use this later for displaying screen and maybe input
using namespace lc3vm;

void runvm(const std::string& path){
vm test{};
if(test.load_program(path)){
  std::cout << "PROGRAM LOAD SUCCESS"<<std::endl;
 }
std::cout << "RUNNING..."<<std::endl;
if(test.run(mode::normal)){
  std::cout << "VM ERROR"<<std::endl;
 }
std::cout << "RUN SUCCESS" <<std::endl;
}



int main(int argc, char* argv[]){
if (argc < 2){
  std::cout << "No file: Use: " << argv[0] << " <file-path>\n";
  return -1;
}

std::string testpath = argv[1];
std::filesystem::path path = testpath;


if(std::filesystem::exists(testpath)){
  runvm(testpath);
  return 0;
 }

std::cout << "Invalid File Path" << std::endl;
return -1;
}
