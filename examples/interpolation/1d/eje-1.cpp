//-------------------------------------------------------------------------
//
//  Copyright (C) 2009   Jose Antonio Munoz Gomez
//
//  This file is part of Radial++
//  http://sourceforge.net/projects/radial/
//
//  Radial++ is free software;  you can redistribute it and/or it under the
//  terms of the GNU Lesser General Public License as published by the Free 
//  Software Foundation; either version 3 of the License, or (at your option)
//  any later version.
//
//  Radial++ is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public 
//  License for more details.
//
//-------------------------------------------------------------------------

//
// With the MQ kernel we interpolate the function f(x) = sin(x), the maximum 
// error was determined on a finer grid. 
//

#include "radial.h"

//---------------------------------------------------------
int main(void)
{
  MQ<double>        rbf;  // RBF as kernel we can use : MQ, IMQ, GAU, TPS, POT
  Polinomio<double> pol;
  LU<double>       lu;
  double            c;
  Matrix<double>    A;   
  Vector<double>    x,f,b,lambda;
  Vector<double>    x_new,f_new;
  double            e_max;   
  int               n,m;
   
//define the number of nodes
   n = 20;   
   
//make the 1d data
   x = linspace( 0.0 , 2*M_PI , n );
   f = sin(x);
      
//define the shape parameter for MQ kernel
   c = 1;
   
//optional: define the degree of the polynomial
   rbf.set_degree_pol(1);
  
//configure the associate polynomial
// pol.make( data_dimension, degree_pol)
   pol.make(1, rbf.get_degree_pol());
      
//show rbf and pol info
   cout<<rbf;
   cout<<pol<<endl;   
   
//get the number of elements in the polynomial base  
   m = pol.get_M();
   
//make aditional data for:  Ax=b   
   b.Reallocate( n + m ); b = 0.0;
   
//fill the expanded vector b = [f 0]
   for( int i=0;  i<n;  i++)   
       b(i) = f(i);
       
//fill the Gramm matrix   
   fill_gram(rbf,pol,c,x,A);
 
//solve the linear system by LU factorization
   lambda = lu.gauss(A, b); 

//make a new grid to interpolate the data
   x_new = linspace( 0.0 , 2*M_PI , 2*n );

//interpolate the data   
   f_new = interpolate(rbf, pol,c, lambda ,x,x_new); 

//determine the maximum error   
   e_max = 0.0;
   for(int i=0;i<2*n; i++)
   {   
     e_max = max(e_max, fabs( sin(x_new(i)) - f_new(i) ) );
   }
   
   cout<<"Testing 1-d interpolation"<<endl;
   cout<<" f(x) = sin(x)"<<endl;
   cout<<"we build the interpolation with n-centers = "<<n<<endl;
   cout<<"determine the error in 2*n centers = "<<2*n<<endl;
   cout<<"e_max = "<<e_max<<endl;
   
//salvo los datos interpolados a archivo ASCII
   save_gnu_data("data_in.dat",x,f);
   save_gnu_data("data_out.dat",x_new,f_new);

   
#ifdef WITH_GNUPLOT
    int pausa;
    GNUplot plotter;
    plotter("reset");
    plotter("set pointsize 2");
    plotter("plot \"data_in.dat\" w p 7, \"data_out.dat\"  w p 3");
    std::cout << "\n\n >---> Press any key and then <enter> to finish " ;
    std::cin >> pausa;
#endif

  return 0;
}
