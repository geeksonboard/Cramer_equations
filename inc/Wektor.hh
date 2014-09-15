#ifndef WEKTOR_HH
#define WEKTOR_HH

/*!
 * \file
 * \brief Definition of class Wektor
 *
 * Contains definitions of atributes, methods and befriended functions with Wektor class
 */

#include "lzespolona.hh"
#include "opcje.hh"
#include <math.h>
#include <stdlib.h>

int licznik = 0;

using namespace std;
/*! \brief Definition of class Wektor

    Shapes the concept of operations on vectors of size ROZMIAR.
    Friend with functions to read and write to/from stdin/stdout.
 */
template < class TYP > 
class Wektor {

  /*! \brief Multiplying number times vector

      Overload of * accomplishing multiplication number times vector

      \param LZespolona liczba - number.
      \param const Wektor Wek - vector.
      \pre none.
      \return Multiplied vector.
   */
  template < typename Typ > 
  friend Wektor<Typ> operator * (Typ liczba, const Wektor<Typ> Wek);

  /*! \brief Loading vector from stdin.

      Overload of >>, enabling reading vector from stdin.

      \param std::istream &Strm - standard input stream.
      \param Wektor &Wek - vectorof type wektor.
      \pre none.
      \return Stdin.
   */
  template < typename Typ > 
  friend std::istream& operator >> (std::istream &Strm, Wektor<Typ> &Wek);


  /*! \brief Writing vector to stdout.

      Overload of <<, enabling writing vector to stdout.

      \param std::ostream &Strm - standard output stream.
      \param Wektor &Wek - vector of type wektor.
      \pre none.
      \return Stdout;
   */
  template < typename Typ > 
  friend std::ostream& operator << (std::ostream &Strm, const Wektor<Typ> &Wek);

  /*! \brief Befriended class Macierz

      To befriend Macierz class enables it to directly use Wektor.
   */
  template < typename Typ> 
  friend class Macierz;

  /* private */

  /*! \brief Vector lenght */
  int ROZMIAR;
  /*! \brief Vector Definition

      Vector definition as a table of numbers
  */
  TYP * Wek;

  /* public*/
  public:
  /*! \brief Default constructor
      \param None.
  */
  Wektor<TYP>(){
    Wek=NULL;
    ROZMIAR=0;
  }
  /*! \briefConstructor

      Defines vector's lenght and resets it
      (fills with zeros)
      \param iROZMIAR - vector's lenght
  */
  Wektor<TYP>(int iROZMIAR)
   :ROZMIAR(iROZMIAR)
  {
    int i;
    Wek=new TYP[ROZMIAR];
    for(i=0; i<ROZMIAR; i++) {
      Wek[i]=0;
    }
  }

  /*! \brief Copying constructor

    Copies one vector to the new one.
    Used implicitly. 
  */
  Wektor<TYP>(const Wektor<TYP>& Wek2) {

    ++licznik;
    int i;
    this->ROZMIAR = Wek2.ROZMIAR;
    this->Wek = new TYP[ROZMIAR];
    for(i=0;i<ROZMIAR;i++) {this->Wek[i] = Wek2.Wek[i];}
  }

  /*! \brief Destructor */
  ~Wektor() {
    delete [] Wek;
  }

  /*! \brief Vector indexing

      Overload of [] to index vector as a table of complex numbers.
      \param int Line - index of element in vector.
      \return vector component.
   */
  const TYP& operator[ ] (int Line) const { if(Line<ROZMIAR) return Wek[Line]; else exit(0); }
  TYP& operator[ ] (int Line) { if(Line<ROZMIAR) return Wek[Line]; else exit(0); }

  /*! \brief Vectors addition

      Overload of + adding 2 vectors one to another.
      \param Wektor Wek2 - Vector of type wektor.
      \pre Brak.
      \return sum of 2 vectors (Wektor type).
   */
  Wektor operator + (Wektor Wek2);

  /*! \brief Vectors subtraction

      Overload of -  subtracting 2 vectors.
      \param Wektor Wek2 - Sybtracted vector.
      \pre none.
      \return difference between 2 vectors.
   */
  Wektor operator - (Wektor Wek2);

  /*! \brief Vectors multiplication

      Overload of * multiplying 2 vectors.
      \param Wektor Wek2 - Vector of type wektor.
      \pre none.
      \return product from 2 vectors.
   */
  TYP operator & (const Wektor Wek2);

  /*! \brief Multiplication vector times number (NOT number times vector!)

      Multiplication vector times number 
      \param TYP liczba - number
      \pre none.
      \return product of Wektor type;
   */
  Wektor operator * (TYP liczba);

  /*!
   *  \brief Dividing vector by a number
   *
   *  dividing in shape vector/number. Divides each component of vector by number.
   *
   *  \param TYP liczba - divisor.
   *  \pre none.
   *  \return product (type of Wektor).
   */
  Wektor operator / (TYP liczba);

  Wektor& operator = (const Wektor& Wek2);


};

  /* ------------------- function definitions ------------------------ */

  /* Vector assignment */
  template <typename TYP >
  Wektor<TYP>& Wektor<TYP>::operator = (const Wektor<TYP>& Wek2) {

    int i;

    if (this == &Wek2) {return *this;} //protection not to delete itself
    delete [] Wek;
    this->ROZMIAR = Wek2.ROZMIAR;
    this->Wek = new TYP[ROZMIAR];
    for(i=0;i<ROZMIAR;i++) {this->Wek[i] = Wek2.Wek[i];}
    return *this;
  }


  /*Vector addition
   */
  template < class TYP > 
  Wektor<TYP> Wektor<TYP>::operator + (Wektor<TYP> Wek2) {

    int i;
    for(i=0; i<this->ROZMIAR; i++) {
      Wek2.Wek[i]=Wek2.Wek[i]+Wek[i];
    }
    return Wek2;
  }

  /* Vector subtraction
   */
  template < class TYP > 
  Wektor<TYP> Wektor<TYP>::operator - (Wektor<TYP> Wek2) {

    int i;
    for(i=0; i<this->ROZMIAR; i++) {
      Wek2.Wek[i]=Wek2.Wek[i]-Wek[i];
    }
    return Wek2;
  }

  /* Vector scalar multiplication
   */
  template < class TYP> 
  TYP Wektor<TYP>::operator & (const Wektor<TYP> Wek2) {

    int i;
    TYP Iloczyn = 0;

    for(i=0; i<this->ROZMIAR; i++) {
      Iloczyn=Iloczyn+Wek2.Wek[i]*Wek[i];
    }
    return Iloczyn;
  }

  /* Multiplication Vector times number
   */
  template < class TYP > 
  Wektor<TYP> Wektor<TYP>::operator * (TYP liczba) {

    int i;
    Wektor<TYP> Wek2(this->ROZMIAR);

    for(i=0; i<this->ROZMIAR; i++) {
      Wek2.Wek[i]=Wek[i]*liczba;
    }
    return Wek2;
  }

  /* Division Vector by numer
   */
  template < class TYP > 
  Wektor<TYP> Wektor<TYP>::operator / (TYP liczba) {

    int i;
    Wektor<TYP> Wek2(this->ROZMIAR);

    for(i=0; i<this->ROZMIAR; i++) {
      Wek2.Wek[i]=Wek[i]/liczba;
    }
    return Wek2;
  }

  /* --- Friends --- */

  /* Multiplication number times Vector
   */
  template < typename Typ >  
  Wektor<Typ> operator * (Typ liczba, const Wektor<Typ> wek) {

    int i;
    Wektor<Typ> Wek2(wek.ROZMIAR);

    for(i=0; i<wek.ROZMIAR; i++) {
      Wek2.Wek[i]=wek.Wek[i]*liczba;
    }
    return Wek2;
  }

  /* Reading Vector from stdin */
  template < typename Typ> 
  std::istream& operator >> (std::istream &Strm, Wektor<Typ> &Wek) {

    int i;
    for(i=0; i<Wek.ROZMIAR; i++) {
      std::cin >> Wek.Wek[i];
    }
    return Strm;
  }

  /* Writting Vector to stdout */
  template < typename Typ > 
  std::ostream& operator << (std::ostream &Strm, const Wektor<Typ> &Wek) {

    int i;
    for(i=0; i<Wek.ROZMIAR; i++) {
      std::cout << Wek.Wek[i] << " ";
    }
    std::cout << std::endl;
    return Strm;
  }



#endif
