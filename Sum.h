#pragma once
#include "Inp.h"
#include "Layer.h"
template <class Type1>
class Sum
{
protected:
  int size_one, sizeSum;
  bool* vect;
public:
  Sum();
  Sum(int size_vec, bool zapoln = 0); 
  Sum(const Sum& a);
  //Для создания вектора
  ~Sum();
  void change(int nom, bool a);
  bool check_el(int nom);
  Type1 Summator(Layer<Type1> l);
};
