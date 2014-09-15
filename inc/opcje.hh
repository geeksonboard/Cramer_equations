#ifndef OPCJE_HH
#define OPCJE_HH

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;
/*! \file
    \brief Definition of class ProgramIO.

     File contains definition of class ProgramIO. It defines operations to load arguments and
     manages in and out streams.
 */

/*! \brief Definition of class Process Options

     It shapes operations to load arguments and manages in and out streams.
*/
class ProgramIO {

    /*! \brief size */
    int size;
    /*! \brief first letter of type */
    char type;
    /*! \brief output stream */
    ofstream fout;
    /*! \brief input stream */
    ifstream fin;

public:

    /*! \brief Constructor */
    ProgramIO(){
        size = 2;
        type = 'r';
    }

   /*! \brief Destructor */
   ~ProgramIO() {
        if(fout.is_open()) {
           fout.close();
        }
        if(fin.is_open()){
           fin.close();
        }
    }

    /*! \brief Size of equation system */
    int Rozmiar(){
        return size;
    }
    /*! \brief Type of equation system */
    char Typ() {
        return type;
    }

    /*! \brief Processing parameters from program call

    Loads program call options and checks their correctness.
    Saves them to variables size and type.

    \pre Uses BladOpcji() function
    \param int argc - number of arguments typed by user
    \param char *argv[] - tab of arguments
    \retval 1 if success
    \retval 0 if error while processing
    */
    bool PobierzOpcje(int argc, char *argv[]);

    /*! \brief Prints error message

    Prints error message on stdout, in case the parameters don't meet
    requrements.
    \pre none;
    \param char* nazwa - file name;
    \return none;
    */
    void BladOpcji(char* nazwa);

};

#endif
