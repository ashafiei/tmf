/*
 * 
 *  Tiny Multimedia Framework (tmf)
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This file is part of tmf.
 *
 *  tmf is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  tmf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with tmf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef INTPRODUCERFILTER_H_
#define INTPRODUCERFILTER_H_ 

#include "core/tmf.h"
#include "core/Filter.h"
#include "core/Port.h"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class IntProducerFilter: public tmf::Filter {
  
private:
  
  int number;
  int limit;
  
  tmf::OutputPort<int> * outputInt;
 
  static  tmf::FilterRegister<IntProducerFilter> reg;
public:
  
  IntProducerFilter(const string& name);
  
  virtual void init();
  
  virtual void run();
  
  virtual void runRT();
  
  virtual ~IntProducerFilter();
  
};

#endif /* INTPRODUCERFILTER_H_ */
