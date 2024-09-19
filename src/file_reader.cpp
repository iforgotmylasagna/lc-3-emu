#include "lc3vm/file_reader.hpp"
#include "lc3vm/endian_utils.hpp"


using namespace lc3vm;
//ugly class rewrite later
file_reader::file_reader(const std::string& filename):filename_(filename),file_(filename,std::ios::binary){
}
int file_reader::open(const std::string& filename){
  if(is_open()){
    close();
  }
  filename_=filename;
  file_.open(filename_,std::ios::binary);
  if(!is_open()){
    //open fail
    return -1;
  }
  return 0;
}

int file_reader::read(){
  if(!is_open()){
    return -1;
  }

  size_t size = get_file_size();
  if(size%2==1){
    size += 1;
  }
  data_.reserve(size);

  uint16_t val;

  while(file_.read(reinterpret_cast<char*>(&val), 2)){
    val = endian_utils::from_big_endianness(val);
    data_.push_back(val);
  }

  if(file_.gcount() ==1){
    uint8_t byte;
    file_.read(reinterpret_cast<char*>(&byte),1);
    val = static_cast<uint16_t>(byte);
    data_.push_back(val);
  }
  is_read_data_=true;

  if(get_data_size()!=(size/2)){
    data_={};
    return -1;
  }

  is_read_data_=true;
 return 0;
}

bool file_reader::is_open() const{
  return file_.is_open();
}

int file_reader::close(){
  filename_="";
  file_.close();
  is_read_data_=false;
  data_={};
  return 0;
}

size_t file_reader::get_file_size(){
  if(!is_open()){
    return 0;
  }
  file_.seekg(0,std::ios::end);
  auto filesize = file_.tellg();
  file_.seekg(0,std::ios::beg);
  return static_cast<size_t>(filesize);
};

size_t file_reader::get_data_size(){
  if(!is_open()){
    return 0;
  }
  if(!is_read_data_){
    return 0;
  }
  return data_.size();

};

void file_reader::print(){ //make better print function
  for(const auto& num : data_){
    std::cout << static_cast<int>(num) << std::endl;
  }
}



std::vector<uint16_t> file_reader::get_data(){
  return data_;
}
