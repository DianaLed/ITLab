#pragma once
#include "Inp.h"
template <class Type2>
class Layer
{
protected:
  Inp<Type2>* entry;
  int size;
public:
  Layer();
  Layer(int size1);
  Layer(const Layer& a);
  ~Layer();
  int get_size();
  int nom_max_perceptron();
  void view_x();
  void view_w();
  Inp<Type2>& operator[](int nom);
  void input_inp(int nom, Type2 chislo, Type2 wes);
  Inp<Type2> get_imp(int nom);
  Type2 get_XW(int nom);
};

