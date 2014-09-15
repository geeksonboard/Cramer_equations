#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH

/*!
 \file
 \brief Definition of Class LZespolona

 File contains the definition of class LZespolona. It defines complex number and overloads
 operations which can be done.
*/

#include <iostream>
#include <iomanip> 
#include <math.h>
#include "opcje.hh"


/*! \brief Definition of Class LZespolona

   Shapes the idea of complex number and defines operations to be performed on it.
*/
class LZespolona {

   /*! \brief Printing complex numbers

       Friend function of class LZespolona. Enables printing the number on the output.
       \param std::ostream &Strm - output stream
       \param const LZespolona &W - complex number
       \return output stream
    */
   friend std::ostream&  operator << ( std::ostream &Strm, const LZespolona &W );

   /*! \brief Loading complex numbers

       Friend function of class LZespolona. Enables loading the number from the input.
       \param std::istream &Strm - input stream
       \param LZespolona &Z - complex number in form of {a+-ib}
       \return input stream
   */
   friend std::istream& operator >> (std::istream &Strm, LZespolona &Z);

   /*! \brief Real part of complex number
    */
   double _re;
   /*! \brief Imaginary part of complex number
    */
   double _im;

 public:

   /*! \brief Constructor 1

       Resets complex number.
       \param None.
   */
   LZespolona();
   /*! \brief Constructor 2

       Gives specified values to the complex number.
       \param double r - Real part of the new complex number.
       \param double i - Imaginary part of the new complex number.
   */
   LZespolona(double r, double i);

   /*! \brief Real part of the complex number

       Returns the real part of the complex number

       \param none.
       \pre none.
       \return real part of the complex number
    */
   double  Re() const;
   /*! \brief Real part of the complex number

       Returns the real part of the complex number

       \param none.
       \pre none.
       \return real part of the complex number
    */
   double& Re();

   /*! \brief Imaginary part of the complex number

       Returns the imaginary part of the complex number

       \param none.
       \pre none.
       \return imaginary part of the complex number
    */
   double  Im() const;
   /*! \brief Imaginary part of the complex number

       Returns the imaginary part of the complex number

       \param none.
       \pre none.
       \return imaginary part of the complex number
    */
   double& Im();

   /*! \brief Modulus of complex number

       Counts modulus of specified complex number

       \param none.
       \pre none.
       \return result.
    */
   virtual double mod() const;

   /*! \brief Adding 2 complex numbers 

       Overload of + adding 2 complex numbers.

       \param const LZespolona&  Arg2 - added number
       \pre none.
       \return result.
    */
   LZespolona  operator + (const LZespolona&  Arg2) const;

   /*! \brief Subtracting 2 complex numbers 

       Overload of - subtracting 2 complex numbers.

       \param const LZespolona&  Arg2 - subtracted number
       \pre none.
       \return result.
    */
   LZespolona  operator - (const LZespolona&  Arg2) const;

   /*! \brief Multiplying 2 complex numbers 

       Overload of * multiplying 2 complex numbers.

       \param const LZespolona&  Arg2 - multiplier
       \pre none.
       \return result.
    */
   LZespolona  operator * (const LZespolona&  Arg2) const;

   /*! \brief Dividing 2 complex numbers 

       Overload of / dividing 2 complex numbers.

       \param const LZespolona&  Arg2 - divisor
       \pre none.
       \return result.
    */
   LZespolona  operator / (const LZespolona&  Arg2) const;

   /*! \brief Assigning 2 complex numbers

       Assignment of one complex number to another

       \param const LZespolona& Wynik - assigned number
       \pre none.
       \return result.
    */
   LZespolona& operator = (const LZespolona& Wynik);

   /*! \brief Assigning integer number to complex

       Assignment of integer number to complex number

       \param const int& dana - assigned number
       \pre none.
       \return complex result.
    */
   LZespolona& operator = (const int& dana);

   /*! \brief Assigning floating number to complex

       Assignment of floating number to complex number

       \param const double& dana - assigned number
       \pre none.
       \return complex result.
    */
   LZespolona& operator = (const double& dana);

   /*! \brief Comparing 2 complex numbers

       Comparision between 2 complex numbers and statement whether they are equal.

       \param LZespolona dana - compared number
       \pre none.
       \return returns flag of success or failure.
       \retval 1 when numbers are the same.
       \retval 0 when numbers are different.
    */
   bool operator == (LZespolona dana);

  /*! \brief Comparing 2 complex numbers

       Comparision between 2 complex numbers and statement whether they are equal.

       \param LZespolona dana - compared number
       \pre none.
       \return returns flag of success or failure.
       \retval 0 when numbers are the same.
       \retval 1 when numbers are different.
    */
   bool operator != (LZespolona dana);

};

/*! \brief Class Real
  
   Enables making mod() operation on real type.*/
class Real {

  public:
  /*! atribute - real number */
  double _x;
  /*! modulus of real number */
  double mod() const {
     return sqrt(_x*_x);
  }

  Real& operator = (const Real& dana)  {

  _x = dana._x;
  return *this;
  }

  Real& operator = (const int &dana) {

    _x = dana;
    return *this;
  }

  Real& operator = (const double &dana) {

    _x = dana;
    return *this;
  }

  bool operator == (Real dana) {

    if( _x == dana._x ) return 1;
    else return 0;
  }

  bool operator != (Real dana) {

    if( _x == dana._x) return 0;
    else return 1;
  }

  Real operator + (const Real&  Arg2) const {

   Real w;
   w._x = _x + Arg2._x;

   return w;
  }

  Real operator - (const Real&  Arg2) const {

   Real w;
   w._x = _x - Arg2._x;

   return w;
  }

  Real operator * (const Real&  Arg2) const {

   Real w;
   w._x = _x * Arg2._x;

   return w;
  }


  Real operator / (const Real&  Arg2) const {
 
   Real w;
   w._x = _x/Arg2._x;
   return w;
  }

  friend std::ostream&  operator << ( std::ostream& Strm, const Real &W ) {

  std::cout << W._x;
  return Strm;

  } 

  friend std::istream& operator >> (std::istream &Strm, Real &Z) {

  std::cin >> Z._x;
  return Strm;
  }

};


#endif
