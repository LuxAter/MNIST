#ifndef NEURAL_NET_EXECUTE_H_
#define NEURAL_NET_EXECUTE_H_
#include <vector>
#include "neural_core.h"
namespace neural {
namespace execute {
struct Neuron {
  std::vector<double> weights;
  double bias, value;
};
extern std::vector<neural::Image> executionset;
extern std::vector<std::vector<Neuron>> neuralnet;
extern int batchsize, epochs, learningrate;
extern bool testing;
bool ExecutionCore();
double Sigmoid(double z);
std::vector<double> FeedForward(std::vector<double> pixeldata);
bool ShuffleData();
bool GradientDecent(std::vector<neural::Image> batch);
void BackProp(std::vector<std::vector<double>>& nablaB,
              std::vector<std::vector<std::vector<double>>>& nablaW, int index);
std::vector<double> Dot(std::vector<double> a, std::vector<double> b);
bool GenorateNetwork(std::vector<int> neurons);
double drand();
}
}
#endif
