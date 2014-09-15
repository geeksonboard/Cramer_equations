#ifndef UKLADROWNANLINIOWYCH_HH
#define UKLADROWNANLINIOWYCH_HH

/*! \file
    \brief Definition of class UkladRownanLiniowych

    File contains definition of class UkladRownanLiniowych. It defines equation system and overloads
    of operations to be performed on it.
*/

#include <iomanip> 
#include <stdlib.h>
#include "Macierz.hh"


/*! \brief Definition of class UkladRownanLiniowych.

 Shapes the concept of operations on equation system.
 Friend with functions to load nad print the eq. system.
*/
template < typename TYP > 
class UkladRownanLiniowych {

  /*! \brief Loads the eq. system from stdin.

       Overload of >>, enabling loading system from stdin.

       \param std::istream &Strm - standard input stream.
       \param UkladRownanLiniowych &UklRown - System declared as private.
       \pre None.
       \return stdin.
   */
  template < typename Typ > 
  friend std::istream& operator >> (std::istream &Strm,
                                    UkladRownanLiniowych<Typ> &UklRown);

  /*! \brief  Prints the eq. system on the stdout

      Overload of <<, enabling printing system on stdout.

      \param std::ostream &Strm - standard output stream.
      \param UkladRownanLiniowych &UklRown - System declared as private.
      \pre none.
      \return stdout.
   */
  template < typename Typ> 
  friend std::ostream& operator << ( std::ostream &Strm,
                                     const UkladRownanLiniowych<Typ> &UklRown);

  /* objects */
  /*! \brief vector of free words */
  Wektor<TYP> *b;
  /*! \brief vektor of answers */
  Wektor<TYP> *x;
  /*! \brief matrix of factors */
  Macierz<TYP> *A;
  /*! \brief size of eq. system */
  int ROZMIAR;

  /* methods */

  public:

  /*! \brief Constructor
      \param None.
  */
  UkladRownanLiniowych(int iROZMIAR)
   :ROZMIAR(iROZMIAR)
   { 
     b = new Wektor<TYP>(ROZMIAR);
     x = new Wektor<TYP>(ROZMIAR);
     A = new Macierz<TYP>(ROZMIAR);
   }

   /*! \brief Destructor */
  ~UkladRownanLiniowych() 
   { 
     delete b;
     delete x;
     delete A;
   }

  /*! \brief Counting the calculation inaccuracy

      Counting the calculation inaccuracy caused by processor's float type interpretation.

      \pre none.
      \return nothing. Prints results and errors on stdout.
   */
  void BladNiedokladnosciObliczen();

  /*! \brief Calculating determinant by Gauss elimination method

      Calculating matrix determinant by Gauss elimination method

      \param const int n - next natural number from range [0, ROZMIAR]. Determines where
       to substitute the column of free values. 0 = nowwhere. 1 - to first column etc.
      \pre None.
      \return value of determinant.
   */
  TYP WyznacznikGaussa(const int n);

  /*! \brief Calculation of coefficients by Cramer method

      Calculation of coefficients by Cramer determinant method, basing on determinants
      calculated by WyznacznikGaussa()

      \pre Function uses WyznacznikGaussa();
      \return prints warning mesages when the main determinant equals 0 and returns 0.
       Otherwise returns 1.
   */
  bool Cramer();
  
};

/* --- from class UkladRownanLiniowych --- */

/* Counting the calculation inaccuracy
 */
template < class TYP >
void UkladRownanLiniowych<TYP>::BladNiedokladnosciObliczen() {

  Wektor<TYP> wekEpsilon(ROZMIAR);
  TYP Epsilon;
  int n, k=1, i;
  double blad=0;

  std::cout << "Rozwiązanie x = (";
  for(i=0; i<ROZMIAR; i++, k++) { std::cout << "x" << k <<", ";}
  std::cout << "):"<<std::endl;
  std::cout << std::endl <<"     " << *x <<std::endl;
  
  wekEpsilon=(*A**x-*b);
  std::cout.setf( std::ios::scientific );
  std::cout << "Wektor bledu: Ax-b = ( ";

  for(n=0; n<ROZMIAR; n++) {
    std::cout << wekEpsilon[n] << ", ";
  }
  std::cout << " )" << std::endl;

  //calculate the length of the error vector

  for(i=0; i<ROZMIAR; i++) {
    blad+= wekEpsilon[i].mod()*wekEpsilon[i].mod(); 
    Epsilon = sqrt(blad*blad);
  }

  std::cout.setf( std::ios::scientific );
  std::cout << "Dlugosc wektora bledu: ||Ax-b|| = " << Epsilon << std::endl;
}


/* Calculating determinant by Gauss elimination method
 */
template < class TYP>
TYP UkladRownanLiniowych<TYP>::WyznacznikGaussa(const int n) {

  int x0, y0, x, y, count=0;
  Wektor<TYP> change(ROZMIAR);
  Macierz<TYP> tmp(ROZMIAR);
  TYP W, wartosc, zero, przeciwna;
  W=1;
  zero = 0;
  przeciwna = -1;
  tmp = (*A);
  if(n!=0) {tmp[n-1] = *b;}
  beginning:
  for(x0=0, y0=0; x0 < ROZMIAR-1; x0++, y0++) {
    for(x=x0+1; x<ROZMIAR; x++) {
      y=y0; wartosc = tmp[y0][x];
      for(y=y0; y<ROZMIAR; y++) {
         if(tmp[y0][x0] == zero) {           //if divider is equal 0 -> vectors change place
           if(count==ROZMIAR-1) return zero; //if we changed as many times as the number of vectors-1
           change=tmp[y0];                   //it means that determinant = 0;
           if (y0<ROZMIAR-1) { tmp[y0] = przeciwna*tmp[y0+1]; tmp[y0+1]=change; }
           else { tmp[y0] = przeciwna*tmp[y0-1]; tmp[y0-1]=change; }
           count++;
           goto beginning; //"one tiny goto..."   //x - horizontal y-vertical
         }
         tmp[y][x] = tmp[y][x] - tmp[y][x0]*(wartosc/tmp[y0][x0]);
      }
    }
  }
  for(x0=0; x0<ROZMIAR; x0++) {
     W = W*tmp[x0][x0];
  }

  return W;
}

/* Calculation of coefficients by Cramer method
 */
template < class TYP >
bool UkladRownanLiniowych<TYP>::Cramer() {

  int n=0;
  bool a=0, d=0;
  Wektor<TYP> W(ROZMIAR+1);
  TYP zero;
  zero = 0;

  W[0] = WyznacznikGaussa(n);
  if(W[0]==zero) a=1;

  for(n=1; n<ROZMIAR+1; n++) {
    W[n] = WyznacznikGaussa(n);
    if(!a) {(*x)[n-1] = W[n]/W[0];}
    else if(W[n] != zero) {
      std::cout << "Macierz A^T: "<< std::endl << *A;
      std::cout << "Wektor wyrazow wolnych: "<< std::endl << *b;
      std::cout << "Rozwiazanie: brak." << std::endl;
      return 0;
    }
    else d=1;
  }

  if(d) {
   std::cout << "Macierz A^T: "<< std::endl << *A;
   std::cout << "Wektor wyrazow wolnych: "<< std::endl << *b;
   std::cout << "Rozwiazanie: nieskończona ilość rozwiązań." << std::endl;
   return 0;
  }
  else {
   return 1;
  }
}


/* --- friends --- */

template < typename Typ> 
std::istream& operator >> (std::istream &Strm, UkladRownanLiniowych<Typ> &UklRown) {

  std::cin >> *(UklRown.A);
  std::cin >> *(UklRown.b);

  return Strm;
}

template < typename Typ > 
std::ostream& operator << ( std::ostream &Strm, const UkladRownanLiniowych<Typ> &UklRown) {

  int i, j, d=1, k=1;

  std::cout << "Rownanie: " << std::endl;

  for(i=0; i<UklRown.ROZMIAR; i++) {
     std::cout << " |";
     for(j=0; j<UklRown.ROZMIAR; j++) {
         std::cout << " (" << (*UklRown.A)[j][i] << ")";
     }
     std::cout << " | | "<< "x"<< k++ << " | ";
     if( (UklRown.ROZMIAR/2 == i ) && d) { std::cout << "="; d=0; }
     else std::cout << " ";
     std::cout <<" | (" <<  (*UklRown.b)[i] << ") |" << std::endl;
  }
  std::cout <<std::endl;

  return Strm;
}


#endif
