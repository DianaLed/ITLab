#include "Inp.h"
template <class Type>
Inp<Type>::Inp(){
    w = 0;
    x = 0;
    lx = 0;
  }

template<class Type>
Inp<Type>::Inp(Type xi, Type wes)
{
  w = wes;
  lx = 0;
  x = xi;
}

template<class Type>
Inp<Type>::~Inp()
{
  w = 0;
  x = 0;
  lx = 0;
}

template<class Type>
Inp<Type>::Inp(const Inp& i)
{
  lx = i.lx;
  w = i.w;
  x = i.x;
}

template<class Type>
Type Inp<Type>::getW()
{
  return w;
}

template<class Type>
Type Inp<Type>::getLX()
{
  return lx;
}

template<class Type>
Type Inp<Type>::getX()
{
  return x;
}

template<class Type>
void Inp<Type>::ChangeW(Type a)
{
  w = a;
}

template<class Type>
void Inp<Type>::ChangeXW(Type a, Type b)
{  
  lx = x;
  x = a;
  w = b;
}

//template<class Type>
//Type Inp<Type>::getXW()
//{
//  Type a = x * w;
//  return (a);
//}



template<class Type>
Inp<Type>& Inp<Type> ::operator=(const Inp<Type>& v)
{
  lx = v.lx;
  w = v.w;
  x = v.x;
  return (*this);
}
template<class Type>
bool Inp<Type>::operator==(const Inp<Type>& v)
{
  if (!(this->getW() == v.w)) return 0;
  if (!(this->getX() == v.x)) return 0;
  return 1;
}
template class Inp<double>;
template class Inp<Inp<double>>;