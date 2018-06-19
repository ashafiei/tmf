/*
 *   DF
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

#include "convolution.h"

using namespace df;
using namespace std;

ActorRegister<Convolution> Convolution::reg("Convolution");

Convolution::Convolution(const string& name) : Actor(name) {
  input = createInputPort<cv::Mat>("input");
  output = createOutputPort<cv::Mat>("output");
}

void Convolution::init() {

  if (!propEmpty("kernel_size"))
    kernel_size = getPropInt("kernel_size");
  else
    kernel_size = 3;

  anchor = cv::Point(0,0);
  delta = 0;
  ddepth = -1;

  kernel = cv::Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);

  // Filter2D computes correlation.
  // To get a convolution, the kernel 
  // needs to be flipped and the anchor
  // needs to be set.
  cv::flip(kernel, kernel, 1);
}

void Convolution::run() {

  anchor = cv::Point(kernel.cols - anchor.x - 1, kernel.rows - anchor.y -1);
  cv::Mat * in = consume(input);	
  cv::Mat * out = produce(output);
  cv::filter2D(*in, *out, ddepth, kernel, anchor, delta, cv::BORDER_DEFAULT);
  log("sending frame "+to_string(stepno));
  release(input);
  release(output);

}

Convolution::~Convolution() {
  destroyPort(input);
  destroyPort(output);
}