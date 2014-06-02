//
//     PELESS TABBED TEXT FILE LISTER.
//     Copyright (C) 2004,2007 Paul Elliott
//     
//     This file is part of peless.
// 
//     peless is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.
// 
// 
//     peless is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
// 
//     You should have received a copy of the GNU General Public License
//     along with peless; if not, write to the Free Software
//     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#ifndef _INITTIME_
#define _INITTIME_ 1
#include  <boost/utility.hpp>

// Am I reinventing the wheel here? If there is a publicly released
// class that does the same thing, email pelliott@io.com.

namespace InitTime {

  // functional object returns true first time
  // false thereafter.
  // Use:
  // Declare one of these static scope, then
  // use as test to call initialization code.
  // static InitTime::FirstTime my_first;
  //  ...code
  // if (my_first() ) my_init();
  //

  class FirstTime: boost::noncopyable
  {
  public:
    FirstTime():
      not_first(true)   // initial value true: will return false first time.
    {
    };
    // firsttime true, false forevermore.
    bool operator()()
    {
      bool result = not_first;   // first call?
      not_first = false;         // false forevermore.
      return result;             // was this the first
    };
  private:
    bool not_first;
  };

};

#endif // _INITTIME_
