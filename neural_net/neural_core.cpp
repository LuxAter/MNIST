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
  aequus::video::win->windowrenderer.SetColor(0.8, 0.8, 0.8, 1);
  display::InitializeDisplay();
  while (running == true && aequus::video::AllClose() == false) {
    if (framecounter <= 1000) {
      aequus::framework::Timmer(true);
      LoadingFrame(framecounter);
      display::Display();
      std::cout << "F:" << aequus::framework::Timmer(false) << "\n";
    }
    aequus::framework::Timmer(true);
    aequus::Frame();
    if (aequus::input::events.size() > 0) {
      if (aequus::input::events[0].type == aequus::input::KEYBOARD &&
          aequus::input::events[0].key == 113) {
        aequus::video::TerminateWindow();
      }
    }
    framecounter++;
    std::cout << "A:" << aequus::framework::Timmer(false) << "\n";
    std::cout << aequus::video::win->objects.size() << "\n";
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
  } else if (frame % 10 == 0) {
    display::SetImage(round(frame / 10) - 1, false);
    display::AddTerminalText(
        "#" + std::to_string(round(frame / 10) - 1) + " = " +
        std::to_string(testingset[round(frame / 10) - 1].label));
    // display::AddTerminalText(std::to_string(rand()));
  }
}
