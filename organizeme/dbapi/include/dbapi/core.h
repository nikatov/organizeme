#pragma once

#include <string>

#define str std::string

enum fieldType {
  integer = 0,
  boolean,
  timestamp,
  interval,
  text
};

struct tuple {
  str fields;
  str parameters;
  tuple(){}
  tuple(str f, str p) : fields(f), parameters(p) {}
  friend tuple& operator+=(tuple& left, const tuple& right);
  void delLastComma() {
    fields.erase(fields.end()-2, fields.end());
    parameters.erase(parameters.end()-2, parameters.end());
  }
};

str stringWrapper(uint64_t obj, fieldType type);
str stringWrapper(str obj, fieldType type);

bool isEmpty(uint64_t obj);
bool isEmpty(uint8_t obj);
bool isEmpty(str obj);
bool isEmpty(bool obj);

tuple setField(str field, uint64_t obj, fieldType type);
tuple setField(str field, uint8_t obj, fieldType type);
tuple setField(str field, str obj, fieldType type);
tuple setField(str field, bool obj, fieldType type);
