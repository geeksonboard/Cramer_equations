/*! \file
    \brief The main loop

    The programs main loop. Loading program call options. Creating object UkladRownanLiniowych.
 */

#include "../inc/UkladRownanLiniowych.hh"
#include "../inc/opcje.hh"

using namespace std;

int main(int argc, char *argv[]) {

  /*Handling of program's input and output */
  ProgramIO Opcje;

  if(Opcje.PobierzOpcje( argc, argv)==0) return 1;

  switch(Opcje.Typ()) {
     case 'r': {
       UkladRownanLiniowych<Real> UklRown(Opcje.Rozmiar());
       cin >> UklRown;
       if( UklRown.Cramer() ) {
         cout << UklRown;
         UklRown.BladNiedokladnosciObliczen();
       }
       break;

     }
     case 'z': {
      UkladRownanLiniowych<LZespolona> UklRown(Opcje.Rozmiar());
      cin >> UklRown;
      if( UklRown.Cramer() ) {
        cout << UklRown;
        UklRown.BladNiedokladnosciObliczen();
      }
      break;
    }

    default:
        {
         Opcje.BladOpcji(argv[0]);
         return 1;
        }
  }
  return 0;

}
