#ifndef NEURAL_NET_EXECTUE_H_
#define NEURAL_NET_EXECUTE_H_
#include <vector>
namespace neural {
namespace execute {
struct Network {
  int numlayers;
  std::vector<int> neurons;
  std::vector<double> weights;
  std::vector<double> biases;
};
extern Network neuralnet;
extern int batchsize, epochs, learningrate;
extern bool testing;
bool ExecutionCore();
double Sigmoid(double z);
std::vector<double> Sigmoid(std::vector<double> z);
std::vector<double> FeedForward(std::vector<double> a);
bool ShuffleData();
bool GradientDecent();
bool GenorateNetwork(std::vector<int> neurons);
double drand();
}
}
#endif
