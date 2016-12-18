#include <aequus_headers.h>
#include <pessum_headers.h>
#include <iostream>
#include <vector>
#include "display.h"
#include "execute.h"
#include "load.h"
#include "neural_core.h"

namespace neural {
std::vector<Image> trainingset;
std::vector<Image> testingset;
}

void neural::MainLoop() {
  bool running = true;
  int framecounter = 0;
  aequus::video::win->windowrenderer.SetColor(0.9, 0.9, 0.9, 1);
  display::InitializeDisplay();
  while (running == true && aequus::video::AllClose() == false) {
    if (framecounter <= 10) {
      LoadingFrame(framecounter);
    }
    if (framecounter == 11) {
      execute::ExecutionCore();
    }
    display::Display();
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
    display::AddTerminalText("Loading Training Image Data Set");
  } else if (frame == 1) {
    load::LoadImageSet(false);
    display::AddTerminalText("Loading Training Label Data Set");
  } else if (frame == 2) {
    load::LoadImageLabels(false);
    display::AddTerminalText("Loading Testing Image Data Set");
  } else if (frame == 3) {
    load::LoadImageSet(true);
    display::AddTerminalText("Loading Testing Label Data Set");
  } else if (frame == 4) {
    load::LoadImageLabels(true);
    display::AddTerminalText("Genorating Neural Network");
  } else if (frame == 5) {
    std::vector<int> neurons = {784, 15, 10};
    execute::GenorateNetwork(neurons);
  }
}
