#include "lc3vm/vm.hpp"
#include "lc3vm/term_format.hpp"
#include <algorithm>
#include <cstdio>
#include <chrono>
#include <thread>

using namespace lc3vm;
using namespace lc3vm::constants;


int vm::deco_instr(const memory_type& instr){
  op::op_type oper = instr >> 12;

  switch (oper){
    case(op::add):
      return add(instr);
      break;
    case(op::AND):
      return AND(instr);
      break;
    case(op::br):
      return br(instr);
      break;
    case(op::jmp): //or ret
      return jmp(instr);
      break;
    case(op::jsr): //or jsrr
      return jsr(instr);
      break;
    case(op::ld):
      return ld(instr);
      break;
    case(op::ldi):
      return ldi(instr);
      break;
    case(op::ldr):
      return ldr(instr);
      break;
    case(op::lea):
      return lea(instr);
      break;
    case(op::NOT):
      return NOT(instr);
      break;
    case(op::rti):
      return 0; //does nothing, trap implemented in c++
      break;
    case(op::st):
      return st(instr);
      break;
    case(op::sti):
      return sti(instr);
      break;
    case(op::str):
      return str(instr);
      break;
    case(op::trap):
      return deco_trap(instr);
      break;
    case(op::reserved):
      return -1;
      break;
    default:
      return -1;
      break;
  }
  return 0;
}

int vm::deco_trap(const memory_type& instr){
  trap::trap_type trap = instr & 0xFF;
  switch(trap){
    case(trap::getc):
      return getc();
      break;
    case(trap::out):
      return out();
      break;
    case(trap::puts):
      return puts();
      break;
    case(trap::in):
      return in();
      break;
    case(trap::putsp):
      return putsp();
      break;
    case(trap::halt):
      std::cout << "HALT" << std::endl;
      running_=0;
      return 0;
      break;
    default:
      std::cout << "TRAP ERROR"  << std::endl;
      return -1;
  }
  return -1;
}

int vm::update_flags(const memory_type& reg_loc){ //reg_loc must be register address
  if(reg_[reg_loc]==0){
    reg_[reg::cond] = static_cast<memory_type>(flag::zro);
    return 0;
  } else if(reg_[reg_loc] >> 15){
    reg_[reg::cond] = static_cast<memory_type>(flag::neg);
    return 0;
  } else {
    reg_[reg::cond] = static_cast<memory_type>(flag::pos);
    return 0;
  }
 return -3; //update flag failure
}


int vm::load_program(const std::string& program_path){
  file_reader reader;
  reader.open(program_path);
  if(reader.read()==0){
    std::vector<uint16_t> temp = reader.get_data();
    if(temp.size()-1+temp[0]>0xFFFF){
      return -6; //program too big failure
    }
    std::copy(temp.begin()+1,temp.end(),mem_.begin()+temp[0]);
    }else {return -2;} //read failrue
  return 0;
}

void vm::print_memory(){
    for(size_t i=0;i!=mem_.size();i++){
      std::cout << i << " "<<mem_[i] << std::endl;
      }
}

void vm::print_memory(size_t b,size_t e){
  std::cout << "MEMORY " << b << " to " << e << std::endl;
    for(size_t i=b;i!=e && i<mem_.size();i++){
      std::cout << i << " "<<mem_[i] << std::endl;
      }
}

void vm::print_registry(){
  std::cout << "REGISTERS:" << std::endl;
    for(size_t i=0;i!=reg_.size();i++){
      std::cout << i << " " << std::hex <<reg_[i] << std::dec << std::endl;
      }
}


int vm::run(const mode::mode_type m){
  term_disable disabler; //no need to restore terminal, at object destruction terminal will restore automatically
  if(m!=mode::debug){ //restore this on release
    disabler.disable();
  }

  try{// all register,memory acces might throw out of range, which should never happen
    reg_[reg::cond] = flag::zro; //set initial flag to 0

    reg_[reg::pc] = static_cast<memory_type>(addr_.p);     //set pc register to userspace start address

    running_ = 1;

    if(m==mode::debug){
      std::cout << "INITIAL REGISTRY:" << std::endl;
      print_registry();
    }

    while(running_){
      memory_type instr =  mem_[reg_[reg::pc]++];//must copy to avoid changing memory

      if(m==mode::debug){
        std::cout << "\n"<< "INSTR: " << std::bitset<16>{instr} << std::endl;
        print_registry();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //slows down the loop
      }

      int decoret = deco_instr(instr);
      std::cout << std::flush;
      if(decoret<0){//if failure return
        std::cout << "PROGRAM ERROR: " << decoret <<" RETURN" << std::endl;
        return -1;
      }
    }
  }catch(const std::out_of_range& ex){std::cout << "PROGRAM ERROR: OUT OF RANGE EXCEPTION"<< std::endl;return -1;}


  return 0;
}

vm::memory_type vm::swap(const memory_type& a){
  return (a >> 8) | (a << 8);
}


inline int vm::getc(){
  reg_[reg::r0] = static_cast<memory_type>(std::getchar());
  update_flags(reg::r0);
  return 0;
}

inline int vm::out(){
  std::putchar(static_cast<char>(reg_[reg::r0]));
  return 0;
}

inline int vm::puts(){
  memory_type mem_beg = reg_[reg::r0];
  for(int i=0;static_cast<char>(mem_[mem_beg+i]) != 0;i++){
    std::putchar(static_cast<char>(mem_[mem_beg+i]));
  }
  return 0;
}

inline int vm::in(){
  std::cout << "ENTER INPUT: ";
  char c = static_cast<char>(std::getchar());
  std::cout << c;
  reg_[reg::r0] = static_cast<memory_type>(c);
  update_flags(reg::r0);
  return 0;
}

inline int vm::putsp(){
  memory_type mem_beg = reg_[reg::r0];
  for(int i=0;static_cast<char>(mem_[mem_beg+i] & 0x00FF) != 0;i++){
    std::putchar(static_cast<char>(mem_[mem_beg+i]));
    if(static_cast<char>(mem_[mem_beg+i] >> 8) == 0){
      break;
    }
    std::putchar(static_cast<char>(mem_[mem_beg+i] >> 8));
  }
  return 0;
}
