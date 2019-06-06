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

#include "image_show_join.h"

using namespace df;
using namespace std;

ActorRegister<ImageShowJoin> ImageShowJoin::reg("ImageShowJoin");

ImageShowJoin::ImageShowJoin(const string& name) : Actor(name) {
  inputMat = createInputPortVector<df::Mat>("opencv input");
}

void ImageShowJoin::init() {
 

}

void ImageShowJoin::run() {

  auto in = consume(inputMat);
  for (int i=0; i<in.size(); i++) {
      frame = in[i]->clone();
 
      log("showing frame "+to_string(stepno));
      
      cv::imshow("ImageShowJoin", frame);
      cv::waitKey(50);
  }
  release(inputMat);
}

ImageShowJoin::~ImageShowJoin() {
  destroyPort(inputMat);
  cv::destroyAllWindows();
}
