#pragma once
template <class Type>
class Inp
{
protected:
  Type lx; //предыдущий вес
  Type w; //вес
  Type x; //вход
public:
  Inp();
  Inp(Type xi, Type wes = 0);
  ~Inp();
  Inp(const Inp& i);

  Type getW();
  Type getLX();
  Type getX();
  void ChangeW(Type a);
  void ChangeXW(Type a, Type b); 
  /*Type getXW();*/
  /*friend std::ostream& operator<<(ostream& out, const Inp& a){
    cout << "Ёлемент ввода равен- " << a.getX() << ", его вес-" << a.w << ", а предыдущий вес " << a.lw  << "."<< endl;
    return out;
  }*/
  Inp<Type>& operator= (const Inp<Type>& v); 
  bool operator==(const Inp<Type>& v);
};
