#include "display.h"
#include "neural_core.h"
#include <aequus_headers.h>
#include <iostream>
#include <math.h>
#include <pessum_headers.h>

namespace neural {
namespace display {
int logloc = 0;
int firstpixel = 0, lastpixel = 0, imagesize;
int indexcounter = 0, labelobj = 0;
}
}

void neural::display::InitializeDisplay() {
  // logloc = pessum::logging::AddLogLocation("neural_net/display.cpp/");
  indexcounter = aequus::video::win->objects.size();
  aequus::video::NewObject();
  labelobj = aequus::video::win->objects.size();
  aequus::video::NewObject();
}

void neural::display::DrawImage(int index, bool testset, int size) {
  imagesize = size;
  int pixelsize = round(size / 28.0);
  std::vector<double> pixeldata;
  if (testset == false) {
    pixeldata = trainingset[index].pixels;
  } else if (testset == true) {
    pixeldata = testingset[index].pixels;
  }
  if (pixeldata.size() == 784) {
    firstpixel = aequus::video::win->objects.size();
    lastpixel = firstpixel + 784;
    int x = 0, y = 0;
    for (int i = 0; i < pixeldata.size(); i++) {
      double color = fabs((pixeldata[i] / (double)255) - 1);
      aequus::video::NewObject();
      aequus::video::win->obj->CreateImgObj("pixel.png");
      aequus::video::win->obj->SetPos(x, y);
      aequus::video::win->obj->Scale(pixelsize, pixelsize);
      aequus::video::win->obj->SetColor(color, color, color, 1);
      x += pixelsize;
      if (x >= pixelsize * 28) {
        x = 0;
        y += pixelsize;
      }
    }
  } else {
    pessum::logging::Log(pessum::logging::LOG_WARNING, "Incorrect images size");
  }
}

void neural::display::SetImagePosition(int ix, int iy) {
  int x = ix, y = iy;
  int pixelsize = round(imagesize / 28.0);
  for (int i = firstpixel; i < lastpixel; i++) {
    aequus::video::win->objects[i].SetPos(x, y);
    x += pixelsize;
    if (x >= ix + (pixelsize * 28)) {
      x = ix;
      y += pixelsize;
    }
  }
}

void neural::display::EraseImage() {
  aequus::video::win->objects.erase(
      aequus::video::win->objects.begin() + firstpixel,
      aequus::video::win->objects.begin() + lastpixel);
}

void neural::display::DrawImageData(int index, bool testset) {
  aequus::video::win->objects[indexcounter].CreateTextObj(
      "#: " + std::to_string(index), 20, 0, 0, 0, 1);
  if (testset == false) {
    aequus::video::win->objects[labelobj].CreateTextObj(
        "Value: " + std::to_string(trainingset[index].label), 20, 0, 0, 0, 1);
  } else if (testset == true) {
    aequus::video::win->objects[labelobj].CreateTextObj(
        "Value: " + std::to_string(testingset[index].label), 20, 0, 0, 0, 1);
  }
  aequus::video::win->objects[indexcounter].SetPos(0, 110);
  aequus::video::win->objects[labelobj].SetPos(0, 130);
}
