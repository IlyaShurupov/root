#pragma once

#include "Memory/Mem.h"

#define FOREACH_STACK(type, stack, iter) \
  for (StackNode<type>* iter = stack->first; iter; iter = iter->next)

template <typename Type>
class StackNode {
 public:
  StackNode<Type>* next;
  Type* data;

 public:
  StackNode(Type* data, StackNode<Type>* next) {
    this->next = next;
    this->data = data;
  }
  ~StackNode() {
    DELETE_DBG(Type, data);
  }
};

template <typename Type>
class Stack {
 private:
  long length;

 public:
  StackNode<Type>* first;

  Stack() {
    length = 0;
    first = nullptr;
  }
  ~Stack() {}

  inline int MemSize() { return sizeof(StackNode<Type>) * length; }

  inline long len() { return length; }

  inline void add(Type* data) {
    StackNode<Type>* NewNode = NEW_DBG(StackNode<Type>) StackNode<Type>(data, first);
    first = NewNode;
    length++;
  }

  inline void pop() {
    StackNode<Type>* del = first;
    first = first->next;
    DELETE_DBG(StackNode<Type>, del);
    length--;
  }

  inline void free() {
    StackNode<Type>* del = first;
    for (size_t i = 0; i < length; i++) {
      StackNode<Type>* next = del->next;
      DELETE_DBG(StackNode<Type>, del);
      del = next;
    }
  }
};