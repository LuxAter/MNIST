#include "display.h"
#include "execute.h"
#include "load.h"
#include "neural_core.h"
#include <aequus_headers.h>
#include <iostream>
#include <pessum_headers.h>
#include <vector>

namespace neural {
std::vector<Image> trainingset;
std::vector<Image> testingset;
}

void neural::MainLoop() {
  bool running = true;
  int framecounter = 0;
  aequus::video::win->windowrenderer.SetColor(0.8, 0.8, 0.8, 1);
  display::InitializeDisplay();
  while (running == true && aequus::video::AllClose() == false) {
    if (framecounter <= 2000) {
      LoadingFrame(framecounter);
    }
    aequus::Frame();
    if (aequus::input::events.size() > 0) {
      if (aequus::input::events[0].type == aequus::input::KEYBOARD &&
          aequus::input::events[0].key == 113) {
        aequus::video::TerminateWindow();
      }
    }
    framecounter++;
  }
}

void neural::LoadingFrame(int frame) {
  if (frame == 0) {
    aequus::video::NewObject();
    aequus::video::win->obj->CreateTextObj("Loading Training Image Data Set",
                                           12, 0, 0, 0, 1);
    aequus::video::win->obj->SetPos(10, 10);
  } else if (frame == 1) {
    load::LoadImageSet(false);
    aequus::video::NewObject();
    aequus::video::win->obj->CreateTextObj("Loading Training Image Label Set ",
                                           12, 0, 0, 0, 1);
    aequus::video::win->obj->SetPos(10, 30);
  } else if (frame == 2) {
    load::LoadImageLabels(false);
    aequus::video::NewObject();
    aequus::video::win->obj->CreateTextObj("Loading Testing Image Data Set", 12,
                                           0, 0, 0, 1);
    aequus::video::win->obj->SetPos(10, 50);
  } else if (frame == 3) {
    load::LoadImageSet(true);
    aequus::video::NewObject();
    aequus::video::win->obj->CreateTextObj("Loading Testing Image Label Set",
                                           12, 0, 0, 0, 1);
    aequus::video::win->obj->SetPos(10, 70);
  } else if (frame == 4) {
    load::LoadImageLabels(true);
    for (int i = 0; i < 4; i++) {
      // aequus::video::win->objects[i].TerminateObject();
    }
    aequus::video::win->objects.clear();
  } else if (frame % 10 == 0) {
    if (frame > 10) {
      // display::EraseImage();
    }
    // display::DrawImage((frame / 10) - 1, false, 100);
    // display::DrawImageData((frame / 10) - 1, false);
  }
}
