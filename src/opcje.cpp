/*! \file
    \brief Options processing
*/

#include "../inc/opcje.hh"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool ProgramIO::PobierzOpcje(int argc, char *argv[]) {

  char opt;


  while ((opt = getopt(argc, argv, "r:t:o:i:")) != -1) {
      switch (opt) {
      case 't':{
        if(*optarg == 'r') type = 'r';
        else if(*optarg == 'z') type = 'z';
        else { BladOpcji(argv[0]); return 0; }
        break;}
      case 'r':{
        size = atoi(optarg);
        break;}
      case 'o':{
        fout.open(optarg);
        if(fout.fail()) {
            std::cout << "Failed to open file for writing!"<<endl;
            return 0;
        }
        std::cout.rdbuf(fout.rdbuf());
        break;
      }
      case 'i': {
        fin.open(optarg);
        if(fin.fail()) {
            std::cout << "Failed to open file for reading!"<<endl;
            return 0;
        }
        std::cin.rdbuf(fin.rdbuf());
        break;
      }
      default:
        BladOpcji(argv[0]);
        return 0;
     }
  } //end of while

  return 1;

}

void ProgramIO::BladOpcji(char* nazwa) {

  cout << "Correct program call:" << endl;
  cout << nazwa << " -t [r|z] -r [0-inf] [-i input_file_name] [-o output_file_name]"
       <<endl;

}
