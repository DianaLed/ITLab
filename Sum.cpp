#pragma once
#include "Sum.h"
#include "Inp.h"
#include "Layer.h"
template <class Type1>
Sum<Type1>::Sum() {
  sizeSum = 0;
  size_one = 0;
  vect = 0;
}
template <class Type1>
Sum<Type1>::Sum(int size_vec, bool zapoln)
{
  sizeSum = size_vec;
  if (zapoln) size_one = size_vec;
  else size_one = 0;
  vect = new bool[sizeSum];
  for (int i = 0; i < sizeSum; i++) {
    vect[i] = zapoln;
  }
}
template <class Type1>
Sum<Type1>::Sum(const Sum& a)
{
  if (sizeSum != 0) delete[] vect;
  sizeSum = a.sizeSum;
  vect = new bool[sizeSum];
  size_one = a.size_one;
  for (int i = 0; i < sizeSum; i++) {
    vect[i] = a.vect[i];
  }
}
template <class Type1>
Sum<Type1>::~Sum()
{
  if (sizeSum != 0) delete[] vect;
  sizeSum = 0;
  size_one = 0;
}
template <class Type1>
void Sum<Type1>::change(int nom, bool a)
{
    if ((vect[nom] != a)&&(nom < sizeSum)) {
      if (a == 1) size_one++;
      else size_one--;
      vect[nom] = a;
    }
}
template <class Type1>
bool Sum<Type1>::check_el(int nom)
{
  if (nom < sizeSum) return vect[nom];
  return 0;
}

template<class Type1>
Type1 Sum<Type1>::Summator(Layer<Type1> l)
{
  Type1 res=0;
  int dop = 0;
  Inp<Type1> a;
  for (int i = 0; i < sizeSum; i++) {
    if (vect[i]) {
      a = l[i];
      res = res + (a.getW()*a.getX());
      dop++;
      if (dop == size_one) break;
    } 
  }
  return res;
}

template class Sum<int>;
//template class Sum<Sum<int>>;