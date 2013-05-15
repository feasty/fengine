/**
*  main.cpp
*  
*  Copyright 2012  <feasty@digitaldrugs.co.uk>
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*  MA 02110-1301, USA.
*  
**/ 

#include <cstdlib>

#include "fengine.hpp"

using namespace fengine;

int main(int argc, char *argv[])
{
    //Set intiial values for the server port and number of threads to
    //initialise
    int port = 1234;
    int numThreads = 5;

    //Assign port number and number of threads if passed into the program
    if (argc > 1 )
    {
        port = atoi(argv[1]);
        if (argc > 2)
        {
            numThreads = atoi(argv[2]);
        }
    }

    Fengine *my_fengine_p = new Fengine();

    my_fengine_p->run();

    delete my_fengine_p;

    my_fengine_p = 0;

    return 0;
}
