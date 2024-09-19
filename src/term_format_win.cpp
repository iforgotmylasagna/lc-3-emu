#ifdef _WIN32
#include "lc3vm/term_format.hpp"
//windows incldes inside ifdef

using namespace lc3vm;



term_disable::term_disable():is_disabled_(0){
}

term_disable::~term_disable(){
}

int term_disable::disable(){
  return 0;
}


//all code must be in #ifdef
//implement these functions
/*
term_disable();
~term_disable();
int disable();
*/

#endif//windows
