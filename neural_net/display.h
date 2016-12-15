#ifndef NEURAL_NET_DISPLAY_H_
#define NEURAL_NET_DISPLAY_H_
#include <string>
#include <vector>
namespace neural {
namespace display {
struct Range {
  int first, last;
};
struct Text {
  std::string text = "";
  int object = -1;
};
extern int logloc, layout;
extern int imageindex;
extern bool testset;
extern int firstpixel, lastpixel, imagesize;
extern int firstterminal, lastterminal;
extern int windowwidth, windowheight;
extern std::vector<std::string> terminaltext;
void InitializeDisplay();
// Global Display
void Display();
// Image display
void DrawImage(int index, bool test, int size = 280);
void SetImage(int index, bool test);
void SetImagePosition(int ix, int iy);
void EraseImage();
// Data display
// Image data
void DrawImageData(int index, bool testset);
// Terminal display
void DisplayTerminal(int size);
void AddTerminalText(std::string text);
void ClearTerminal();
}
}
#endif
