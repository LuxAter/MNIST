#include "display.h"
#include "load.h"
#include "neural_core.h"
#include <aequus_headers.h>
#include <iostream>
#include <pessum_headers.h>
#include <vector>

namespace neural {
std::vector<Image> trainingset;
std::vector<Image> testingset;
std::vector<std::vector<Sigmoid>> neurons;
}

void neural::MainLoop() {
  bool running = true;
  int framecounter = 0;
  aequus::video::win->windowrenderer.SetColor(0.8, 0.8, 0.8, 1);
  while (running == true && aequus::video::AllClose() == false) {
    if (framecounter <= 10) {
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
  } else if (frame == 5) {
    display::DrawImage(0, false, 100);
  } else if (frame == 10) {
    display::SetImagePosition(100, 100);
  }
}

void neural::GenorateNetwork(std::vector<int> layerneurons) {
  for (int i = 0; i < layerneurons.size(); i++) {
    std::vector<Sigmoid> layer;
    for (int j = 0; j < layerneurons[i]; j++) {
      Sigmoid neuron;
      neuron.bias = 0.5;
      neuron.output = 0;
      if (i > 0) {
        for (int k = 0; k < layerneurons[i - 1]; k++) {
          neuron.weights.push_back(1);
        }
      } else {
        neuron.weights.push_back(0);
      }
      layer.push_back(neuron);
    }
    neurons.push_back(layer);
  }
}
