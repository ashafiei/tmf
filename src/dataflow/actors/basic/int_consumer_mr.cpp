/*
 *   TMF
 *   Copyright (C) TMF Team
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

#include "int_consumer_mr.h"

using namespace df;
using namespace std;

ActorRegister<IntConsumerMR> IntConsumerMR::reg("IntConsumerMR");

IntConsumerMR::IntConsumerMR(const string & name) : Actor(name) {
  input = createInputPort<Int>("input");
}

void IntConsumerMR::init() {

}

void IntConsumerMR::run() {
  vector<Int *> in = consumeMR(input);
  log("consuming ");
  for (auto t : in)
  	log(" "+t->to_string());
  sleep(200);
  
  releaseMR(input);
}

IntConsumerMR::~IntConsumerMR() {
  destroyPort(input);
}
