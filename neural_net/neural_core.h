#ifndef NEURAL_NET_CORE_H_
#define NEURAL_NET_CORE_H_
#include <vector>
namespace neural {
struct Sigmoid {
  std::vector<double> weights;
  double bias, output;
};
struct Image {
  int label, index;
  std::vector<double> pixels;
};
extern std::vector<Image> trainingset;
extern std::vector<Image> testingset;
extern std::vector<std::vector<Sigmoid>> neurons;
void MainLoop();
void LoadingFrame(int position);
void GenorateNetwork(std::vector<int> layerneurons);
}
#endif
