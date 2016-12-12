#ifndef NEURAL_NET_DISPLAY_H_
#define NEURAL_NET_DISPLAY_H_
namespace neural {
namespace display {
extern int logloc;
extern int firstpixel, lastpixel, imagesize;
extern int indexcounter, labelobj;
void InitializeDisplay();
// Image display
void DrawImage(int index, bool testset, int size = 280);
void SetImagePosition(int ix, int iy);
void EraseImage();
// Data display
// Image data
void DrawImageData(int index, bool testset);
}
}
#endif
