#include "neural_net/neural_core.h"
#include <aequus_headers.h>
#include <pessum_headers.h>

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Nerual MNIST Network");
  neural::MainLoop();
  aequus::framework::TerminateSdl();
  pessum::TerminatePessumComponents();
  return (1);
}
