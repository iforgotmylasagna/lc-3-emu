#pragma once


#ifdef __linux__
//linux headers in here
#include <termios.h>
#include <unistd.h>
#endif

#ifdef _WIN32
//linux headers in here
#include <Windows.h>
#include <conio.h>
#endif

namespace lc3vm{

//linux code after this
#ifdef __linux__
//linux code in here

class term_disable{
public:
  term_disable();
  term_disable(const term_disable&)=delete;
  term_disable& operator=(const term_disable&)=delete;
  term_disable(term_disable&&) = delete;
  term_disable& operator=(term_disable&&)=delete;
  ~term_disable();
  int disable();


private:
  struct termios term_;
  struct termios term_orig_;
  bool is_disabled_=0;
  static term_disable* instance_;;
  static void sig_han(int sig);

};
#endif //linux
}//end namespace






namespace lc3vm{

#ifdef _WIN32


class term_disable{
public:
  term_disable();
  term_disable(const term_disable&)=delete;
  term_disable& operator=(const term_disable&)=delete;
  term_disable(term_disable&&) = delete;
  term_disable& operator=(term_disable&&)=delete;
  ~term_disable();
  int disable();

private:
  bool is_disabled_;
};


#endif//windows
}//end namespace

