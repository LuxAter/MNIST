#include "display.h"
#include "execute.h"
#include "neural_core.h"
#include <aequus_headers.h>
#include <iostream>
#include <math.h>
#include <pessum_headers.h>

double e = 2.7182818284590452353602874713;

namespace neural {
namespace execute {
Network neuralnet;
int batchsize, epochs, learningrate;
bool testing;
}
}

bool neural::execute::ExecutionCore() {
  for (int i = 0; i < epochs; i++) {
  }
  return (true);
}

double neural::execute::Sigmoid(double z) { return (1.0 / (1.0 + pow(e, -z))); }

std::vector<double> neural::execute::Sigmoid(std::vector<double> z) {
  for (int i = 0; i < z.size(); i++) {
    z[i] = Sigmoid(z[i]);
  }
  return (z);
}

std::vector<double> neural::execute::FeedForward(std::vector<double> a) {
  for (int i = 0; i < Network.weights.size(); i++) {
    a = Sigmoid()
  }
  return (a);
}

bool neural::execute::ShuffleData() { return (true); }

bool neural::execute::GradientDecent() { return (true); }

bool neural::execute::GenorateNetwork(std::vector<int> neurons) {
  neuralnet.numlayers = neurons.size();
  neuralnet.neurons = neurons;
  for (int i = 0; i < neurons.size(); i++) {
    for (int j = 0; j < neurons[i]; j++) {
      neuralnet.weights.push_back(drand());
      if (i > 0) {
        neuralnet.biases.push_back(drand());
      }
    }
  }
  return (true);
}

double neural::execute::drand() { return ((double)rand() / RAND_MAX); }
