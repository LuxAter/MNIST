#include <aequus_headers.h>
#include <math.h>
#include <pessum_headers.h>
#include <iostream>
#include "display.h"
#include "neural_core.h"

namespace neural {
namespace display {
int logloc = 0, layout = 1;
int imageindex = -1;
bool testset = false;
int firstpixel = 0, lastpixel = 0, imagesize;
int firstterminal = 0, lastterminal = 0;
int windowwidth = 0, windowheight = 0;
std::vector<std::string> terminaltext;
}
}

void neural::display::InitializeDisplay() {
  logloc = pessum::logging::AddLogLocation("neural_net/display.cpp/");
  windowwidth = aequus::video::win->sizex;
  windowheight = aequus::video::win->sizey;
}

void neural::display::Display() {
  int previewsize = 100, networkwidth = 100, terminalsize = 100,
      graphwidth = 100, graphheight = 100;
  if (layout == 1) {
    previewsize = 3 * (windowwidth / 10.0);
    terminalsize = 3 * (windowwidth / 10.0);
    networkwidth = 7 * (windowwidth / 10.0);
    graphwidth = 3 * (windowwidth / 10.0);
    graphheight = windowheight - (6 * (windowwidth / 10.0));
  }
  if (imageindex != -1) {
    pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Drawing preview",
                            logloc, "Display");
    DrawImage(imageindex, testset, previewsize);
  } else {
    imagesize = previewsize;
  }
  if (terminaltext.size() > 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION,
                            "Drawing terminal", logloc, "Display");
    DisplayTerminal(terminalsize);
  }
}

void neural::display::DrawImage(int index, bool test, int size) {
  if (firstpixel != lastpixel) {
    EraseImage();
  }
  imagesize = size;
  int pixelsize = round(size / 28.0);
  std::vector<double> pixeldata;
  if (test == false) {
    pixeldata = trainingset[index].pixels;
  } else if (test == true) {
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

void neural::display::SetImage(int index, bool test) {
  imageindex = index;
  testset = test;
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
  for (int i = firstpixel; i < lastpixel; i++) {
    aequus::video::win->objects[i].TerminateObject();
  }
  aequus::video::win->objects.erase(
      aequus::video::win->objects.begin() + firstpixel,
      aequus::video::win->objects.begin() + lastpixel);
  firstpixel = 0;
  lastpixel = 0;
}

void neural::display::DrawImageData(int index, bool testset) {}

void neural::display::DisplayTerminal(int size) {
  if (firstterminal != -1 && lastterminal != -1) {
    ClearTerminal();
  }
  firstterminal = aequus::video::win->objects.size();
  aequus::video::NewObject();
  aequus::video::win->obj->CreateImgObj("pixel.png");
  aequus::video::win->obj->SetPos(0, imagesize);
  aequus::video::win->obj->Scale(size, size);
  aequus::video::win->obj->SetColor(0.2, 0.2, 0.2, 1);
  int j = 0;
  for (int i = terminaltext.size() - 1; i >= 0; i--) {
    aequus::video::NewObject();
    aequus::video::win->obj->CreateTextObj(terminaltext[i], 10, 1, 1, 1, 1);
    aequus::video::win->obj->SetPos(0, imagesize + (13 * j));
    j++;
  }
  lastterminal = aequus::video::win->objects.size() - 1;
}

void neural::display::AddTerminalText(std::string text) {
  terminaltext.push_back(text);
}

void neural::display::ClearTerminal() {
  if (firstterminal >= 0 && lastterminal >= 0 &&
      firstterminal < aequus::video::win->objects.size() &&
      lastterminal < aequus::video::win->objects.size()) {
    for (int i = firstterminal; i <= lastterminal; i++) {
      aequus::video::win->objects[i].TerminateObject();
    }
    if (firstterminal == 0) {
      firstterminal++;
    }
    aequus::video::win->objects.erase(
        aequus::video::win->objects.begin() + firstterminal,
        aequus::video::win->objects.begin() + lastterminal);
    firstterminal = -1;
    lastterminal = -1;
  }
}
