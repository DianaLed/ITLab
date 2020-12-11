#include "Layer.h"
#include "Inp.h"
#include <iostream>
using namespace std;
template<class Type2>
inline Layer<Type2>::Layer()
{
  size = 0;
  entry = 0;
}

template<class Type2>
Layer<Type2>::Layer(int size1)
{
  size = size1;
  entry = new Inp<Type2>[size];
}

template<class Type2>
Layer<Type2>::Layer(const Layer<Type2>& a)
{ //???
  /*if (this->size > 0) delete[] entry;*/
  size = a.size;
  entry = new Inp<Type2>[size];
  for (int i = 0; i < size; i++) {
    entry[i] = a.entry[i];
  }
}

template<class Type2>
Layer<Type2>::~Layer()
{
  if (size > 0) delete[] entry;
  size = 0;
}

template<class Type2>
int Layer<Type2>::get_size()
{
  return size;
}

template<class Type2>
int Layer<Type2>::nom_max_perceptron()
{
  double res = entry[0].getX(), res_i = 0;
  for (int i = 1; i < size; i++) {
    if (entry[i].getX() > res) {
      res = entry[i].getX();
      res_i = i;
    }
  }
  return res_i;
}

template<class Type2>
void Layer<Type2>::view_x()
{
  if (size < 20) {
    for (int i = 0; i < size; i++) cout << entry[i].getX() << " ";
  }
  else {
    int dop = 0;
    while(dop<784) {
      for (int j = 0; j < 28; j++) {
        cout << entry[dop].getX() << " ";
        dop++;
      }
      cout << endl;
    }
  }
  cout << endl;
}

template<class Type2>
void Layer<Type2>::view_w()
{
  if (size < 20) {
    for (int i = 0; i < size; i++) cout << entry[i].getW() << " ";
  }
  else {
    int dop = 0;
    while (dop < 784) {
      for (int j = 0; j < 28; j++) {
        cout << entry[dop].getW() << " ";
          dop++;
      }
      cout << endl;
    }
  }
  cout << endl;
}


template<class Type2>
Inp<Type2>& Layer<Type2>::operator[](int nom)
{
  if (nom < size) return entry[nom];
  return entry[0];
}

template<class Type2>
void Layer<Type2>::input_inp(int nom, Type2 chislo, Type2 wes)
{
  if (nom < size) {
    entry[nom].ChangeXW(chislo, wes);
  }
}

template<class Type2>
Inp<Type2> Layer<Type2>::get_imp(int nom)
{
  if (nom < size) return entry[nom];
  return 0;
}

template<class Type2>
Type2 Layer<Type2>::get_XW(int nom)
{
  Type2 res = 0;
  if (nom < size)
    res = entry[nom].getW() * entry[nom].getX();
  return res;
}



template class Layer<double>;

