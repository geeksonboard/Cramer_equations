Cramer_equations
================

App solves Cramer equations for any number of variables.
Uses Gauss elimination method in order to count matrix determinant, and also Cramer method to find unknowns.

Main facilities:

Equations are loaded in transposed way what significantly simplify the construction of input overload.
Number of equations and unknowns to be processed is typed by user as program call parameter.
Program takes following call parameters:
  -i [input_file] - name of the file from the equations system will be loaded. Default: stdin
  -o [output_file] - name of the file to save results. Default: stdout 
  -r [int] - System size. Default: 2 
  -t [r|z] - data type [r - real, z - complex]. Default: r
  
In case parameter is not specified it takes default value. Loading matrix of size not matching the specified one causes undefined behavior.
Complex numbers are given in form {a+-bi}, where: a - real part, b - imaginary part.  Both parts need to be specified explicitly.
