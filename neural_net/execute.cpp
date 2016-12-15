#include <aequus_headers.h>
#include <math.h>
#include <pessum_headers.h>
#include <iostream>
#include "display.h"
#include "execute.h"
#include "neural_core.h"

double e = 2.7182818284590452353602874713;

namespace neural {
namespace execute {
Network neuralnet;
int batchsize, epochs, learningrate;
bool testing;
}
}

bool neural::execute::ExecutionCore() {
  std::vector<double> output = FeedForward(trainingset[0].pixels);
  for (int i = 0; i < output.size(); i++) {
    std::cout << output[i] << ",";
  }
  std::cout << "\n";
  return (true);
}

double neural::execute::Sigmoid(double z) { return (1.0 / (1.0 + pow(e, -z))); }

std::vector<double> neural::execute::Sigmoid(std::vector<double> z) {
  for (int i = 0; i < z.size(); i++) {
    z[i] = Sigmoid(z[i]);
  }
  return (z);
}

std::vector<double> neural::execute::FeedForward(
    std::vector<double> pixeldata) {
  for (int i = 0; i < neuralnet.neurons[0].size() && i < pixeldata.size();
       i++) {
    neuralnet.neurons[0][i].value = pixeldata[i];
  }
  for (int i = 1; i < neuralnet.neurons.size(); i++) {
    for (int j = 0; j < neuralnet.neurons[i].size(); j++) {
      double z =
          Dot(neuralnet.neurons[i][j].weights, neuralnet.neurons[i - 1]) -
          neuralnet.neurons[i][j].bias;
      neuralnet.neurons[i][j].value = Sigmoid(z);
    }
  }
  std::vector<double> returndata;
  for (int i = 0; i < neuralnet.neurons[neuralnet.neurons.size() - 1].size();
       i++) {
    returndata.push_back(
        neuralnet.neurons[neuralnet.neurons.size() - 1][i].value);
  }
  return (returndata);
}

bool neural::execute::ShuffleData() { return (true); }

bool neural::execute::GradientDecent() { return (true); }

bool neural::execute::GenorateNetwork(std::vector<int> neurons) {
  neuralnet.numlayers = neurons.size();
  for (int i = 0; i < neurons.size(); i++) {
    std::vector<Neuron> layer;
    for (int j = 0; j < neurons[i]; j++) {
      Neuron newneuron;
      if (i > 0) {
        for (int k = 0; k < neurons[i - 1]; k++) {
          newneuron.weights.push_back(drand());
        }
        newneuron.bias = drand();
      }
      newneuron.value = 0;
      layer.push_back(newneuron);
    }
    neuralnet.neurons.push_back(layer);
  }
  return (true);
}

double neural::execute::Dot(std::vector<double> a, std::vector<Neuron> b) {
  double product = 0;
  for (int i = 0; i < a.size() && i < b.size(); i++) {
    product += (a[i] * b[i].value);
  }
  return (product);
}

double neural::execute::drand() { return ((double)rand() / RAND_MAX); }
