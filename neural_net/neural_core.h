#ifndef NEURAL_NET_CORE_H_
#define NEURAL_NET_CORE_H_
#include <vector>
namespace neural {
struct Image {
  int label = -1, index = -1;
  std::vector<double> pixels;
};
extern std::vector<Image> trainingset;
extern std::vector<Image> testingset;
void MainLoop();
void LoadingFrame(int position);
}
#endif
