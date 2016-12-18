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
  FeedForward(trainingset[0].pixels);
  for (int i = 0; i < -1; i++) {
  }
  return (true);
}

double neural::execute::Sigmoid(double z) {
  return (1.0 / (double)(1.0 + pow(e, z)));
}

std::vector<double> neural::execute::FeedForward(
    std::vector<double> inputdata) {
  std::cout << "Running\n";
  std::vector<double> returndata;
  for (int i = 0; i < neuralnet.neurons[0].size() && i < inputdata.size();
       i++) {
    neuralnet.neurons[0][i].value = inputdata[i];
  }
  for (int i = 1; i < neuralnet.neurons.size(); i++) {
    for (int j = 0; j < neuralnet.neurons[i].size(); j++) {
      double z = 0;
      for (int k = 0; k < neuralnet.neurons[i][j].weights.size(); k++) {
        z += neuralnet.neurons[i - 1][k].value *
             neuralnet.neurons[i][j].weights[k];
      }
      z += neuralnet.neurons[i][j].bias;
      neuralnet.neurons[i][j].value = Sigmoid(z);
    }
  }
  for (int i = 0; i < neuralnet.neurons[neuralnet.neurons.size() - 1].size();
       i++) {
    returndata.push_back(
        neuralnet.neurons[neuralnet.neurons.size() - 1][i].value);
    std::cout << returndata[i] << ",";
  }
  std::cout << "\n";
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

double neural::execute::drand() { return ((double)rand() / RAND_MAX); }
