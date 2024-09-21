#pragma once
#include <cstddef>

namespace lc3vm::constants{


class reg{
public:
  using reg_type = size_t;
  static constexpr std::size_t r0 = 0;
  static constexpr std::size_t r1 = 1;
  static constexpr std::size_t r2 = 2;
  static constexpr std::size_t r3 = 3;
  static constexpr std::size_t r4 = 4;
  static constexpr std::size_t r5 = 5;
  static constexpr std::size_t r6 = 6;
  static constexpr std::size_t r7 = 7;
  static constexpr std::size_t pc = 8;
  static constexpr std::size_t cond = 9; //use three right bits for nzp

  static constexpr std::size_t max(){
    return 10;
  }
};

class op{
public:
  using op_type = size_t;
  static constexpr std::size_t add = 0b0001;
  static constexpr std::size_t AND = 0b0101;
  static constexpr std::size_t br = 0b0000;
  static constexpr std::size_t jmp = 0b1100;
  static constexpr std::size_t jsr = 0b0100;
  static constexpr std::size_t jsrr = 0b0100;
  static constexpr std::size_t ld = 0b0010;
  static constexpr std::size_t ldi = 0b1010;
  static constexpr std::size_t ldr = 0b0110;
  static constexpr std::size_t lea = 0b1110;
  static constexpr std::size_t NOT = 0b1001;
  static constexpr std::size_t ret = 0b1100;
  static constexpr std::size_t rti = 0b1000;
  static constexpr std::size_t st = 0b0011;
  static constexpr std::size_t sti = 0b1011;
  static constexpr std::size_t str = 0b0111;
  static constexpr std::size_t trap = 0b1111;
  static constexpr std::size_t reserved = 0b1101;

  static constexpr std::size_t max(){
    return 16;
  }
};

class flag{
public:
  using flag_type = size_t;
  static constexpr std::size_t pos = 0b001;
  static constexpr std::size_t zro = 0b010;
  static constexpr std::size_t neg = 0b100;
};

class trap{
public:
  using trap_type = size_t;
  static constexpr std::size_t getc = 0x20;//get character
  static constexpr std::size_t out = 0x21;//output character
  static constexpr std::size_t puts = 0x22;//print string one character per word
  static constexpr std::size_t in = 0x23;//inter input with prompt
  static constexpr std::size_t putsp = 0x24;//print string two character per word
  static constexpr std::size_t halt = 0x25;//halt program
};

struct addr{
  using addr_type = size_t;
  const std::size_t tvp = 0x0000; //trap vector table begin address
  const std::size_t ivt = 0x0100; //interupt vector table begin address
  const std::size_t os = 0x0200;  //os begin address
  const std::size_t p = 0x3000; //program begin address
  const std::size_t dra = 0xFE00; //device or io register begin address requres superuser priv to access
  //USP and SSP might not be defined idk
  const std::size_t kbsr = 0xFE00; //keyboard status register
  const std::size_t kbdr = 0xFE02; //keyboard data register
  const std::size_t dsr = 0xFE04; //display data register
  const std::size_t ddr = 0xFE06; //display data register
  const std::size_t psr = 0xFFFC; //process status register  pg654
  const std::size_t mcr = 0xFFFE; //master control register
  //from FF03 to FFFC
};


}//end namespace
