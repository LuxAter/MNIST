#include <aequus_headers.h>
#include <math.h>
#include <pessum_headers.h>
#include <algorithm>
#include <iostream>
#include "display.h"
#include "execute.h"
#include "neural_core.h"

double e = 2.7182818284590452353602874713;

namespace neural {
namespace execute {
std::vector<neural::Image> executionset;
std::vector<std::vector<Neuron>> neuralnet;
int batchsize = 10, epochs = 1, learningrate = 3;
bool testing;
}
}

bool neural::execute::ExecutionCore() {
  executionset = trainingset;
  display::AddTerminalText("Running for \'" + std::to_string(epochs) +
                           "\' epoch");
  for (int i = 0; i < epochs; i++) {
    ShuffleData();
    for (int j = 0; j < trainingset.size(); j += batchsize) {
    }
  }
  display::AddTerminalText("Compleated epochs");
  return (true);
}

double neural::execute::Sigmoid(double z) {
  return (1.0 / (double)(1.0 + pow(e, z)));
}

std::vector<double> neural::execute::FeedForward(
    std::vector<double> inputdata) {
  std::cout << "Running\n";
  std::vector<double> returndata;
  for (int i = 0; i < neuralnet[0].size() && i < inputdata.size(); i++) {
    neuralnet[0][i].value = inputdata[i];
  }
  for (int i = 1; i < neuralnet.size(); i++) {
    for (int j = 0; j < neuralnet[i].size(); j++) {
      double z = 0;
      for (int k = 0; k < neuralnet[i][j].weights.size(); k++) {
        z += neuralnet[i - 1][k].value * neuralnet[i][j].weights[k];
      }
      z += neuralnet[i][j].bias;
      neuralnet[i][j].value = Sigmoid(z);
    }
  }
  for (int i = 0; i < neuralnet[neuralnet.size() - 1].size(); i++) {
    returndata.push_back(neuralnet[neuralnet.size() - 1][i].value);
  }
  return (returndata);
}

bool neural::execute::ShuffleData() {
  std::random_shuffle(executionset.begin(), executionset.end());
  return (true);
}

bool neural::execute::GradientDecent(std::vector<neural::Image> batch) {
  std::vector<std::vector<double>> nablaB, deltanablaB;
  std::vector<std::vector<std::vector<double>>> nablaW, deltanablaW;
  for (int l = 0; l < neuralnet.size(); l++) {
    std::vector<double> zeroB;
    std::vector<std::vector<double>> zeroW;
    for (int n = 0; n < neuralnet[l].size(); n++) {
      std::vector<double> zeroWB;
      zeroB.push_back(0);
      for (int w = 0; w < neuralnet[l][n].weights.size(); w++) {
        zeroWB.push_back(0);
      }
      zeroW.push_back(zeroWB);
    }
    nablaB.push_back(zeroB);
    nablaW.push_back(zeroW);
  }
  deltanablaW = nablaW;
  deltanablaB = nablaB;
  for (int i = 0; i < batch.size(); i++) {
    BackProp(deltanablaB, deltanablaW, batch[i].index);
    for (int l = 0; l < neuralnet.size(); l++) {
      for (int n = 0; n < neuralnet[l].size(); n++) {
        nablaB[l][n] += deltanablaB[l][n];
        for (int w = 0; w < neuralnet[l][n].weights.size(); w++) {
          nablaW[l][n][w] += deltanablaW[l][n][w];
        }
      }
    }
  }
  for (int l = 0;
       l < neuralnet.size() && l < nablaB.size() && l < nablaW.size(); l++) {
    for (int n = 0; n < neuralnet[l].size() && n < nablaB[l].size() &&
                    n < nablaW[l].size();
         n++) {
      neuralnet[l][n].bias -=
          (learningrate / (double)batch.size()) * nablaB[l][n];
      for (int w = 0;
           w < neuralnet[l][n].weights.size() && w < nablaW[l][n].size(); w++) {
        neuralnet[l][n].weights[w] -=
            (learningrate / (double)batch.size()) * nablaW[l][n][w];
      }
    }
  }
  return (true);
}

void neural::execute::BackProp(
    std::vector<std::vector<double>>& nablaB,
    std::vector<std::vector<std::vector<double>>>& nablaW, int index) {
  std::vector<double> input = trainingset[index].pixels;
  std::vector<double> expectedoutput;
  for (int i = 0; i < neuralnet[neuralnet.size() - 1].size(); i++) {
    expectedoutput.push_back(0);
    if (i == trainingset[index].label) {
      expectedoutput[i] = 1;
    }
  }

  std::vector<std::vector<double>> activations, zs;
  activations.push_back(input);
  for (int l = 1; l < neuralnet.size(); l++) {
    std::vector<double> lactivations, lzs;
    for (int n = 0; n < neuralnet[l].size(); n++) {
      double z = 0;
      for (int w = 0;
           w < neuralnet[l][n].weights.size() && w < activations[l - 1][w];
           w++) {
        z += activations[l - 1][w] * neuralnet[l][n].weights[w];
      }
      z += neuralnet[l][n].bias;
      lzs.push_back(z);
      lactivations.push_back(Sigmoid(z));
    }
    activations.push_back(lactivations);
    zs.push_back(lzs);
  }

  std::vector<double> delta;
  for (int i = 0; i < expectedoutput.size(); i++) {
    delta.push_back(
        (activations[activations.size() - 1][i] - expectedoutput[i]) *
        (Sigmoid(zs[zs.size() - 1][i]) * (1 - Sigmoid(zs[zs.size() - 1][i]))));
  }
  nablaB[nablaB.size() - 1] = delta;
  for (int i = 0; i < delta.size(); i++) {
    for (int j = 0; j < activations[activations.size() - 2].size(); j++) {
      nablaW[nablaW.size() - 1][i][j] =
          delta[i] * activations[activations.size() - 2][j];
    }
  }

  for (int l = neuralnet.size() - 2; l >= 0; l--) {
  }
}

bool neural::execute::GenorateNetwork(std::vector<int> neurons) {
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
    neuralnet.push_back(layer);
  }
  return (true);
}

double neural::execute::drand() { return ((double)rand() / RAND_MAX); }
