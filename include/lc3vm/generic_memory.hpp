#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <concepts>
#include <limits>


//
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>
#include <lc3vm/constants.hpp>
#include <cstdio>
//

namespace lc3vm{

template<std::integral T, std::size_t N>//this used to be an array lol,bad idea
class generic_memory{
public:
  using memory_type = T;
  using reference = T&;

  static constexpr std::size_t max_index(){                 //size maximum is maximum value of pointer address
    if constexpr (N > std::numeric_limits<memory_type>::max()) {
      static_assert(false,"size of generic_memory too big");
    } else{return N;}
  }
  using iterator = std::vector<memory_type>::iterator;

  generic_memory(){mem_vec_.resize(max_index()+1);} //otherwise can be filled with random stuff in memory

  std::size_t size() const{
    return mem_vec_.size();
  }

  memory_type& operator[](std::size_t index){
    index = static_cast<memory_type>(index);// this is neccessary because unsigned + unsigned = int results operator[int]
    //
    if(index==0xFE00){
      if(check_key()){
        mem_vec_[0xfe00] =(1 << 15);
        mem_vec_[0xfe02] = getchar();
      }else{
        mem_vec_[0xfe00] = 0;
      }
    }
    //

    if (index>max_index()) [[unlikely]] {
      throw std::out_of_range("Index out of range");
    }
    return mem_vec_[index];
  }

  const memory_type& operator[](std::size_t index) const{
    index = static_cast<memory_type>(index);
    //
    if(index==0xFE00){
      if(check_key()){
        mem_vec_[0xfe00] =(1 << 15);
        mem_vec_[0xfe02] = getchar();
      }else{
        mem_vec_[0xfe00] = 0;
      }
    }
    //
    if (index>max_index()) [[unlikely]] {
        throw std::out_of_range("Index out of range");
    }
    return mem_vec_[index];
  }

  memory_type& operator[](std::integral auto index){
    return (*this)[static_cast<std::size_t>(index)];
  }
  const memory_type& operator[](std::integral auto index) const{
    return (*this)[static_cast<std::size_t>(index)];
  }

  std::vector<memory_type>::iterator begin(){
    return mem_vec_.begin();
  }
  std::vector<memory_type>::iterator end(){
    return mem_vec_.end();
  }

private:
  std::vector<memory_type> mem_vec_;
  //
  uint16_t check_key()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(1, &readfds, NULL, NULL, &timeout) != 0;
}
  //
};


}
