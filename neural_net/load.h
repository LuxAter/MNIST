#ifndef NEURAL_NET_LOAD_H_
#define NEURAL_NET_LOAD_H_
namespace neural {
namespace load {
void LoadImages();
void LoadImageSet(bool testset);
void LoadImageLabels(bool testset);
int ReverseInt(int i);
}
}
#endif
