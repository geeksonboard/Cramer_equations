/*! \file
    \brief Definitions of method from class LZespolona and befriended functions

    Methods belonging to class LZespolona and functions operating on it's atributes
 */

#include "../inc/lzespolona.hh"

LZespolona::LZespolona() {

 _re = _im = 0;

}

LZespolona::LZespolona(double r, double i) {

  _re = r;
  _im = i;
}

double  LZespolona::Re() const {

  return _re;
}

double& LZespolona::Re() {

  return _re;
}

double  LZespolona::Im() const {

  return _im;
}

double& LZespolona::Im() {

  return _im;
}


double LZespolona::mod() const {
  return sqrt( Re()*Re() + Im()*Im() );
}

LZespolona  LZespolona::operator + (const LZespolona&  Arg2) const {

 LZespolona w;
 w._re = _re + Arg2._re;
 w._im = _im + Arg2._im;

 return w;
}


LZespolona  LZespolona::operator - (const LZespolona&  Arg2) const {

 LZespolona w;
 w._re = _re - Arg2._re;
 w._im = _im - Arg2._im;

 return w;
}

LZespolona  LZespolona::operator * (const LZespolona&  Arg2) const {

 LZespolona w;
 w._re = (_re * Arg2._re) - (_im * Arg2._im);
 w._im = (_im * Arg2._re) + (_re * Arg2._im);

 return w;
}


LZespolona  LZespolona::operator / (const LZespolona&  Arg2) const {

 LZespolona sprzezenie(Arg2._re, -Arg2._im),          //sprzężenie (feedback)
            z(_re , _im),                             //this
            g( (1 / (Arg2.mod() * Arg2.mod() ) ), 0); //dzielenie przez kwadrat modułu
 
 return (z * sprzezenie) * g;

}


LZespolona& LZespolona::operator = (const LZespolona& dana)  {

  _re = dana._re;
  _im = dana._im;
  return *this;
}

LZespolona& LZespolona::operator = (const int &dana) {

  _re = dana;
  _im = 0;
  return *this;
}

LZespolona& LZespolona::operator = (const double &dana) {

  _re = dana;
  _im = 0;
  return *this;
}


bool LZespolona::operator == (LZespolona dana) {

  if( _re == dana._re && _im == dana._im) return 1;
  else return 0;
}

bool LZespolona::operator != (LZespolona dana) {

  if( _re == dana._re && _im == dana._im) return 0;
  else return 1;
}

std::ostream&  operator << ( std::ostream& Strm, const LZespolona &W ) {

  std::cout << "{" << W._re << std::showpos << W._im << std::noshowpos << "i}";
  return Strm;

} 

std::istream& operator >> (std::istream &Strm, LZespolona &Z) {

  char znak;
  std::cin >> znak; //{
  std::cin >> Z._re;
  std::cin >> Z._im;
  std::cin >> znak; //i
  std::cin >> znak; //}
  return Strm;
}


