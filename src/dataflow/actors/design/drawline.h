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

#ifndef DF_DRAWLINE_H_
#define DF_DRAWLINE_H_

#include "core/df.h"
#include "tokens/opencv/mat.h"
#include "tokens/basic/complex3d.h"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class DrawLine: public df::Actor {
  
private:
  
  cv::Mat img;
  cv::Point center;
 
  df::InputPort<df::Complex3D> * input;
  df::OutputPort<df::Mat> * output;
 
  static  df::ActorRegister<DrawLine> reg;
public:
  
  DrawLine(const string& name);
  
  virtual void init();
  
  virtual void run();
  
  virtual ~DrawLine();
  
};

#endif /* DF_DRAWLINE_H_ */
