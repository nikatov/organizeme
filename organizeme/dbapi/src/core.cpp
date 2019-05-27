#include "core.h"
#include <iostream>

tuple& operator+=(tuple& left, const tuple& right) {
  left.fields += right.fields;
  left.parameters += right.parameters;
  return left;
}

str stringWrapper(uint64_t obj, enum fieldType type) {
  if(timestamp == type) {
    return str("timestamp '1970/01/01' + interval '") + std::to_string(obj) + str(" second', ");
  }
  else if(interval == type) {
    return str("'") + std::to_string(obj) + str(" second', ");
  }
  else if(boolean == type) {
    return obj ? str("true, ") : str("false, ");
  }
  else if(integer == type) {
    return std::to_string(obj) + str(", ");
  }
  else
  return str("");
}

str stringWrapper(str obj, fieldType type) {
  return str("'") + str(obj) + str("', ");
}

bool isEmpty(uint64_t obj) { return obj == 0 ? true : false; }
bool isEmpty(uint8_t obj) { return obj == 0 ? true : false; }
bool isEmpty(str obj) { return obj.empty(); }
bool isEmpty(bool obj) { return !obj; }

tuple setField(str field, uint64_t obj, enum fieldType type) {
  tuple t;
  if(!isEmpty(obj)){
      t.fields += str(field) + str(", ");
      t.parameters += stringWrapper(obj, type);
  }
  return t;
}
tuple setField(str field, uint8_t obj, enum fieldType type) {
  tuple t;
  if(!isEmpty(obj)){
      t.fields += str(field) + str(", ");
      t.parameters += stringWrapper(obj, type);
  }
  return t;
}
tuple setField(str field, str obj, enum fieldType type) {
  tuple t;
  if(!isEmpty(obj)){
      t.fields += str(field) + str(", ");
      t.parameters += stringWrapper(obj, type);
  }
  return t;
}
tuple setField(str field, bool obj, enum fieldType type) {
  tuple t;
  if(!isEmpty(obj)){
      t.fields += str(field) + str(", ");
      t.parameters += stringWrapper(obj, type);
  }
  return t;
}
