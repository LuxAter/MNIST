#ifndef NEURAL_NET_EXECUTE_H_
#define NEURAL_NET_EXECUTE_H_
#include <vector>
namespace neural {
namespace execute {
struct Neuron {
  std::vector<double> weights;
  double bias, value;
};
struct Network {
  int numlayers;
  std::vector<std::vector<Neuron>> neurons;
};
extern Network neuralnet;
extern int batchsize, epochs, learningrate;
extern bool testing;
bool ExecutionCore();
double Sigmoid(double z);
std::vector<double> Sigmoid(std::vector<double> z);
std::vector<double> FeedForward(std::vector<double> pixeldata);
bool ShuffleData();
bool GradientDecent();
bool GenorateNetwork(std::vector<int> neurons);
double Dot(std::vector<double> a, std::vector<Neuron> b);
double drand();
}
}
#endif
