#ifndef MACIERZ_HH
#define MACIERZ_HH
#include "Wektor.hh"
using namespace std;

/*! \file
    \brief Definition of class Macierz

     File contains definition of class Macierz, which defines matrix, methods and overloads
     of operations that can be performed.
 */

/*! \brief Definition of class Macierz
 
   It shapes operations on matrix of size ROZMIARxROZMIAR specified by user in program call.
   For proper work must be friend with class Wektor (needed to multiply matrix and vector.)
   Is friend with functions printing and loading matrix.
*/
template < typename TYP>
class Macierz {

  /*! \brief Loads matrix from stdin.

      Overload of operator >>, enables reading matrix from stdin.

      \param std::istream &Strm - standard input stream.
      \param Macierz &Mac - matrix declared as private in class.
      \pre none.
      \return input stream.
   */
  template < typename Typ>
  friend std::istream& operator >> (std::istream &Strm, Macierz<Typ> &Mac);

  /*! \brief Prints matrix on stdout.

      Overload of operator <<, enables printing matrix to stdout.

      \param std::ostream &Strm - standard output stream.
      \param Macierz &Mac - matrix declared as private in class.
      \pre none.
      \return output stream.
   */
  template < typename Typ >
  friend std::ostream& operator << (std::ostream &Strm, const Macierz<Typ> &Mac);

  /* private */

  /*! \brief Definition of atribute Matrix

      Matrix as table of columns.
  */
  Wektor<TYP> ** Matrix;
  /*! \brief Matrix's size */
  int ROZMIAR;

  /* public*/
  public:

  /*! \brief Default constructor

      Restets matrix.
      \param none.
  */
  Macierz<TYP>(){
      Matrix=NULL;
      ROZMIAR=0;
  }
  /*! \brief Constructor

      Resets matrix.
      \param iROZMIAR - matrix's size.
  */
  Macierz<TYP>(int iROZMIAR)
    :ROZMIAR(iROZMIAR)
  {
     int j;

     Matrix=new Wektor<TYP>*[iROZMIAR];
     for(j=0; j<iROZMIAR; j++) {
        Matrix[j] = new Wektor<TYP>(iROZMIAR);
     }
  }

  /*! \brief Copying constructor

      Copies matrix one to another.
      Used implicitly.
  */
  Macierz<TYP>(const Macierz<TYP>& Mac) {
      int j;
      //creating new matrix
      this->ROZMIAR = Mac.ROZMIAR;
      this->Matrix=new Wektor<TYP>*[ROZMIAR];
      for(j=0; j<ROZMIAR; j++) {
         Matrix[j] = new Wektor<TYP>(ROZMIAR);
      }
      //filling
      for(j=0; j<ROZMIAR; j++) {
        *Matrix[j] = Mac[j];
      }
  }

  /*! \brief Destructor
      Removes atributes created dinamically
  */
  ~Macierz() {
     int j;
     for(j=0; j<ROZMIAR; j++) {
       delete Matrix[j];
     }
     delete [] Matrix;
  }

  /*! \brief Indeksing of macierzy.

      Overload of metrix indexing as a table of vectors
      \param int Line - matrix's column.
      \pre none.
      \return Matrix's column (Wektor type).
      
   */
  const Wektor<TYP>& operator[ ] (int Line) const { if(Line<ROZMIAR) return *(Matrix[Line]); else exit(0); }
  Wektor<TYP>& operator[ ] (int Line) { if(Line<ROZMIAR) return *(Matrix[Line]); else exit(0); }

  
  /*! \brief Multiplication matrix times vector

      Multiplying matrix times vector (NOT vector times matrix!)

      \param const Wektor Wek - vector
      \pre sizes of vector and matrix must be the same
      \return vector created via multiplication.
   */
  Wektor<TYP> operator * (const Wektor<TYP> Wek);

  /*! \brief Assignment matrix to matrix

      Assignment of matrix. Works, regardless if the sizes match.

      \param Mac - assigned matrix.
      \pre none.
      \return Reference to matrix.
   */
  Macierz<TYP>& operator = (const Macierz<TYP> &Mac);


};

/* --- From class matrix --- */

template <typename TYP >
Macierz<TYP>& Macierz<TYP>::operator = (const Macierz<TYP>& Mac) {

     int j=1;

     if(this == &Mac) {return *this;}
     //removing leftovers

     for(j=0; j<ROZMIAR; j++) {
       delete Matrix[j];
     }
     delete [] Matrix;
     //creating new matrix
     this->ROZMIAR = Mac.ROZMIAR;
     this->Matrix=new Wektor<TYP>*[ROZMIAR];
     for(j=0; j<ROZMIAR; j++) {

        Matrix[j] = new Wektor<TYP>(ROZMIAR);
     }
     //filling
     for(j=0; j<ROZMIAR; j++) {
             *Matrix[j] = Mac[j];
     }
     return *this;
}

/* Multiplication matrix times vector (NOT vector times matrix!)
 */
template < typename TYP>
Wektor<TYP> Macierz<TYP>::operator * (Wektor<TYP> Wek1) {

  int i,j;
  Wektor<TYP> Wek2(ROZMIAR);
  
  for(i=0;i<this->ROZMIAR;i++) {
    for(j=0;j<this->ROZMIAR;j++) {
       Wek2.Wek[i]=Wek2.Wek[i]+(*Matrix[j])[i]*Wek1.Wek[j];
    }
  }
  return Wek2;
}

/* --- Friends --- */

/* Loading matrix from stdin
   */
template < typename Typ>
std::istream& operator >> (std::istream &Strm, Macierz<Typ> &Mac) {

    int i, j;
    for(i=0; i<Mac.ROZMIAR; i++) {
      for(j=0; j<Mac.ROZMIAR; j++) {
        std::cin >> (*Mac.Matrix[i])[j]; /* automatic transposition: Matrix[j][i] */
      }
    }
    return Strm;
}

/*  Printing matrix to stdout
 */
template < typename Typ>
std::ostream& operator << (std::ostream &Strm, const Macierz<Typ> &Mac) {

    int i, j;
    for(i=0; i<Mac.ROZMIAR; i++) {
      for(j=0; j<Mac.ROZMIAR; j++) {
        std::cout << (*Mac.Matrix[i])[j] << "  ";
      }
      std::cout << std::endl;
    }
    return Strm;
}


#endif
