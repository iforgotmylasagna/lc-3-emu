#ifdef __linux__
#include "lc3vm/term_format.hpp"
#include <csignal>
#include <iostream>

using namespace lc3vm;
term_disable* term_disable::instance_ = nullptr;

term_disable::term_disable():is_disabled_(0){
}

term_disable::~term_disable(){
  std::cout << "RESTORING TERMINAL..." << std::endl;
  if(is_disabled_==1){
    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig_);
    std::cout << std::flush;
  }
}

int term_disable::disable(){
  std::cout << "DISABLING TERMINAL.." << std::endl;
  if(is_disabled_==0){
  if(tcgetattr(STDIN_FILENO,&term_) !=0){
      return -1;
    }

  term_orig_ = term_;

  term_.c_lflag &= ~(ECHO | ICANON);
  if (tcsetattr(STDIN_FILENO, TCSANOW, &term_) != 0) {
    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig_);
    return -1;
  }
  is_disabled_=1;
  signal(SIGINT,sig_han);
  instance_=this;
  }

  return 0;
}


void term_disable::sig_han(int sig){
  if ( sig==SIGINT && instance_!=nullptr ){
    std::cout << "SIGINT, RESTORING TERM STATE" << std::endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &instance_->term_orig_);
    _exit(0);

  }
}



#endif//linux
