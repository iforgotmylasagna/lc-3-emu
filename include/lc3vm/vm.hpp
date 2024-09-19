#pragma once

#include "lc3vm/constants.hpp"
#include "lc3vm/generic_memory.hpp"
#include "lc3vm/file_reader.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <limits>
#include <bitset>
#include <iostream>



namespace lc3vm{

struct mode{
  static constexpr std::size_t normal = 0;
  static constexpr std::size_t debug = 1;
  using mode_type = std::size_t;
};

class vm{
public:

  using memory = generic_memory<uint16_t,std::numeric_limits<uint16_t>::max()>; //this creates the memory lc3 will use 16 bit address
  using memory_type = memory::memory_type;                            // this is unsigned 16 bit integer, its used everywhere in the class
  using registor = generic_memory<memory_type,constants::reg::max()>; //this creates registors , same mem type as memory

  vm(){};
  vm(constants::addr addr_p): addr_(addr_p){};
  //int load_os(const std::string& os_path);
  int load_program(const std::string& program_path);
  void print_memory();
  void print_registry();
  void print_memory(std::size_t,std::size_t);
  int run(const mode::mode_type m = mode::normal);


private:
  memory mem_;
  registor reg_;
  constants::addr addr_;
  int running_;
  int deco_instr(const memory_type& instr);
  int deco_trap(const memory_type& instr);
  int add(const memory_type& instr);
  int AND(const memory_type& instr);
  int br(const memory_type& instr);
  int jmp(const memory_type& instr);
  int jsr(const memory_type& instr);
  int ld(const memory_type& instr);
  int ldi(const memory_type& instr);
  int ldr(const memory_type& instr);
  int lea(const memory_type& instr);
  int NOT(const memory_type& instr);
  int rti(const memory_type& instr);
  int st(const memory_type& instr);
  int sti(const memory_type& instr);
  int str(const memory_type& instr);

  inline int trap(const memory_type& instr);
  inline int reserved(const memory_type& instr);

  inline int getc();
  inline int out();
  inline int puts();
  inline int in();
  inline int putsp();

  inline memory_type sign_ext(const std::size_t data,const std::size_t count) const {
    memory_type x = static_cast<memory_type>(data);
    if((x >> (count-1)) & 1){
      x |= ( 0xFFFF << count);
    }
    return static_cast<memory_type>(x);
  }

  int update_flags(const memory_type& reg_loc);
  memory_type swap(const memory_type& a);


};

} // end namespace lc3vm
