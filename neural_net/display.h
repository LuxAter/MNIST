#ifndef NEURAL_NET_DISPLAY_H_
#define NEURAL_NET_DISPLAY_H_
namespace neural {
namespace display {
extern int firstpixel, lastpixel, imagesize;
void DrawImage(int index, bool testset, int size = 280);
void SetImagePosition(int ix, int iy);
}
}
#endif
