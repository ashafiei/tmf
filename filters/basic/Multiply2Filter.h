/*
 * 
 *  Tiny Multimedia Framework
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MULTIPLY2FILTER_H_
#define MULTIPLY2FILTER_H_

#include "core/Filter.h"

class Multiply2Filter: public Filter {
private:
  InputPort<int> * input;
  OutputPort<int> * output;
  
public:
  
  Multiply2Filter(const string & name) :
  Filter(name) {
    input = createInputPort<int>("int input");
    output = createOutputPort<int>("int output");
  }
  
  void run() {
    
    input->lock();
    int * inputData = input->get();
    int outputint = *inputData * 2;
    if (input->getStatus() == SampleStatus::EOS)
      status = FilterStatus::EOS; 
    input->unlock();
    
    output->lock();
    int * outputData = output->get();
    *outputData = outputint;
    if (status == FilterStatus::EOS)
      output->setStatus(SampleStatus::EOS);
    output->unlock();
    
  }
  
  ~Multiply2Filter() {
    delete input;
    delete output;
  }
  
};

#endif /* MULTIPLY2FILTER_H_ */