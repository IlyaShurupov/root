#pragma once

#include "Macros.h"

struct Str;

void to_string(Str* str, int val);
void to_string(Str* str, float val);
void to_string(Str* str, bool val);
void to_string(Str* str, char val);

template <typename Type>
inline void to_string(Str* str, Type val) {
  to_string(str, val);
}


bool str_from_string(Str* str, int& val);
bool str_from_string(Str* str, float& val);
bool str_from_string(Str* str, bool& val);


typedef long int str_idx;

struct Range {
  str_idx strt;
  str_idx end;

  str_idx len();
  bool valid();
  Range();
  Range(const Range& rng);
  Range(str_idx strt, str_idx end);
};

struct StrRef {
  struct Str *str;
  Range rng;
};

struct Str {

  Str(const char* str);
  Str();

  template <typename Type>
  Str(Type val) {
    to_string(this, val);
  }

  Str(const Str& val) {
    *this = val;
  }

  char* str = nullptr;
  str_idx length = 0;

  str_idx len() const;
  void alloc(str_idx len);
  void clear();

  void operator=(const Str& string);
  void operator=(const char* string);

  Str& operator+=(const Str& string);
  Str operator+(const Str& string);

  bool operator==(const char* cstring);
  bool operator==(const Str& string);
  bool operator!=(const char* cstring);
  bool operator!=(const Str& string);

  char operator[](str_idx idx);

  bool match(Range& range, Str& str2, Range& range2);
  
  void coppy(Str* str, Range range);

  str_idx find(const Str& string);
  str_idx find(const Str& string, Range range);
  str_idx find(const char character, Range range);
  str_idx rfind(const char character, Range range);

  void trim(Range range);

  template <typename Type>
  bool to_val(Type& val) {
    return str_from_string(this, val);
  }

  ~Str();
};

#ifdef _DEBUG
#define CLOG(text) cnsl(text)
#else
#define CLOG(text) 
#endif 

void cnsl(const Str& str);
