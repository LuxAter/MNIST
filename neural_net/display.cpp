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
int firstpixel = -1, lastpixel = -1, imagesize;
int firstterminal = -1, lastterminal = -1;
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
    DrawImage(imageindex, testset, previewsize);
  } else {
    imagesize = previewsize;
  }
  if (terminaltext.size() > 0) {
    DisplayTerminal(terminalsize);
  }
}

void neural::display::DrawImage(int index, bool test, int size) {
  if (firstpixel == -1 && lastpixel == -1) {
    aequus::video::NewObject();
    aequus::video::win->obj->CreateImgObj("pixel.png");
    aequus::video::win->obj->SetPos(0, 0);
    aequus::video::win->obj->Scale(size, size);
    aequus::video::win->obj->SetColor(0.2, 0.2, 0.2, 1);
    firstpixel = aequus::video::win->objects.size();
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
    lastpixel = firstpixel + 784;
    int x = 0, y = 0;
    for (int i = 0; i < pixeldata.size(); i++) {
      double color = fabs((pixeldata[i] / (double)255) - 1);
      if (i + firstpixel >= aequus::video::win->objects.size()) {
        aequus::video::NewObject();
        aequus::video::win->objects[i + firstpixel].CreateImgObj("pixel.png");
        aequus::video::win->objects[i + firstpixel].SetPos(x, y);
        aequus::video::win->objects[i + firstpixel].Scale(pixelsize, pixelsize);
      }
      aequus::video::win->objects[i + firstpixel].SetColor(color, color, color,
                                                           1);
      x += pixelsize;
      if (x >= pixelsize * 28) {
        x = 0;
        y += pixelsize;
      }
    }
    SetImagePosition((size % 28) / 2, (size % 28) / 2);
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

void neural::display::EraseImage() {}

void neural::display::DrawImageData(int index, bool testset) {}

void neural::display::DisplayTerminal(int size) {
  if (firstterminal == -1 && lastterminal == -1) {
    aequus::video::NewObject();
    aequus::video::win->obj->CreateImgObj("pixel.png");
    aequus::video::win->obj->SetPos(0, imagesize);
    aequus::video::win->obj->Scale(size, size * 2);
    aequus::video::win->obj->SetColor(0.2, 0.2, 0.2, 1);
    firstterminal = aequus::video::win->objects.size();
    for (int i = 0; i < (size / 8); i++) {
      aequus::video::NewObject();
      aequus::video::win->objects[i + firstterminal].CreateTextObj(" ", 12, 1,
                                                                   1, 1, 1);
    }
  }
  for (int i = 0; i < terminaltext.size() && i < (size / 8); i++) {
    aequus::video::win->objects[i + firstterminal].TerminateObject();
    aequus::video::win->objects[i + firstterminal].CreateTextObj(
        terminaltext[i], 12, 1, 1, 1, 1);
    aequus::video::win->objects[i + firstterminal].SetPos(0,
                                                          imagesize + (16 * i));
  }
}

void neural::display::AddTerminalText(std::string text) {
  terminaltext.insert(terminaltext.begin(), text);
}

void neural::display::ClearTerminal() {}
