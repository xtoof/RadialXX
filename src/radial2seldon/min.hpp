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
 /***************************************************************************
 * This file has been written to Radial++ in spirit to incorporate
 * the classical binary operations between vectors and matrices
 * in the library called Seldon.
 *
 ***************************************************************************/



//
//! scalar <-- min(Vector)
//
template<typename T>
T min(Vector<T> &X)
{
   T* ptr_x   = X.GetData();
   int m      = X.GetSize();
   T     mini = ptr_x[0];
   
   for( int i=1;  i<m;  i++)
   {
     if(ptr_x[i]<mini)
       mini = ptr_x[i];   
   }
 return mini;  
}



