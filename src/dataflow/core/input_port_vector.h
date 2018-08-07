/*
 *   libdataflow
 *   Copyright (C) 2018
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DF_INPUTPORT_VECTOR_H
#define DF_INPUTPORT_VECTOR_H

#include "input_port.h"

namespace df {
  
  /*!
   * \class InputPortVector
   *
   */
  
  template <typename T>
  class InputPortVector: public IPort {
    
  private:
    std::vector<InputPort<T> *> inputs;
    std::vector<int> portNumbers;

  public:
	  
    InputPortVector<T>(std::string name) : IPort(name) {
        port_cap = std::string(typeid(T).name());
    }
    
    int arity() {
	    return inputs.size();
    }

    InputPort<T> * at(int i) {
	    return inputs[i];
    }

    void setArity(int r) {
	for (int i=0; i<r; i++) {
		InputPort<T> * in = new InputPort<T>(name+"."+std::to_string(i));
		inputs.push_back(in);
	}
    }

    virtual void accept() {
	while (!portNumbers.empty()) {
		sock->accept();
		int p = portNumbers.back();
    		portNumbers.pop_back();
		std::cout << "sending port for connection " << p << "\n";
		sock->recvsend("port", std::to_string(p));
		sock->clnclose();
	}
    }

    virtual void listen(int portnb) {
	distributed = true;
        sock->listen(portnb);

	int i = 1;
       	for (auto in : inputs) {
		int p = portnb + i;
		portNumbers.insert(portNumbers.begin(), p);
		in->listen(p);
	    	i++;
	}
    }

    virtual void startAccept() {
	    for (auto in : inputs)
		    in->startAccept();
            taccept = std::thread(&InputPortVector<T>::accept, this);
    }

    virtual void waitAccept() {
	    for (auto in : inputs)
		    in->waitAccept();
	    taccept.join();
    }

    virtual ~InputPortVector() {
    }
    
  };
  
}
#endif // DF_INPUTPORT_VECTOR_H
