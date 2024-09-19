#include "lc3vm/vm.hpp"
#include <cstdio>

using namespace lc3vm;
using namespace lc3vm::constants;

int vm::add(const memory_type& instr){ //memory_type is uint16_t
    memory_type dr = (instr >> 9) & 0x7;
    //source1
    memory_type sr1 = (instr >> 6) & 0x7;
    memory_type imm = (instr >> 5) & 0x1;

    if(static_cast<bool>(imm)){
      memory_type imm5 = sign_ext(instr & 0x15, 5);
      reg_[dr] = reg_[sr1] + imm5;
    }else {
      memory_type sr2 = instr & 0x7;
      reg_[dr] = reg_[sr1] + reg_[sr2];
    }

  return update_flags(dr); //add can only fail inside update_flags
                           //so it will reuturn -3 if update flag fail return 0 if success
}



int vm::AND(const memory_type& instr){
  memory_type dr = (instr >> 9) & 0x7;
  memory_type sr1 = (instr >> 6) & 0x7;
  memory_type imm = (instr >> 5) & 0x1;

  if(static_cast<bool>(imm)){
    memory_type imm5 = sign_ext(instr & 0x15, 5);
    reg_[dr] = reg_[sr1] & imm5;
  }else {
    memory_type sr2 = instr & 0x7;
    reg_[dr] = reg_[sr1] & reg_[sr2];
  }

  return update_flags(dr); //add can only fail inside update_flags
                           //so it will reuturn -3 if update flag fail return 0 if success
}



int vm::br(const memory_type& instr){
  memory_type pcoffset9 = instr & 0xFF;
  memory_type nzp = (instr >> 9) & 0x7;
  if(nzp & reg_[reg::cond]){
    reg_[reg::pc] =  reg_[reg::pc] + sign_ext(pcoffset9,8);
  }
  return 0;
}

int vm::jmp(const memory_type& instr){
  memory_type reg_loc = (instr >> 6) & 0x7;
  reg_[reg::pc] = reg_[reg_loc];
  return 0;
}


int vm::jsr(const memory_type& instr){
  reg_[reg::r7] = reg_[reg::pc];
  if((instr>>11)&0x1){
    reg_[reg::pc] += sign_ext(instr & 0x7FF,11);
  }else{reg_[reg::pc] = reg_[(instr >> 6) & 0x7];
  }
  return 0;
}


int vm::ld(const memory_type& instr){
  memory_type dr = (instr >> 9) & 0x7;
  reg_[dr] += mem_[reg_[reg::pc] + sign_ext(instr & 0xFF,9)];
  update_flags(dr);
  return 0;
}




//implement:
/*

  int AND(const memory_type& instr); //pierce write this function and the ones below it
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
  int str(const memory_type& instr); // all the way to here

  */
