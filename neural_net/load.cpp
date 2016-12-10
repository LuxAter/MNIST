#include "load.h"
#include "neural_core.h"
#include <fstream>
#include <iostream>
#include <vector>

void neural::load::LoadImages() {
  LoadImageSet(false);
  LoadImageLabels(false);
  LoadImageSet(true);
  LoadImageLabels(true);
}

void neural::load::LoadImageSet(bool testset) {
  std::string filename = "NULL";
  if (testset == false) {
    filename = "dataset/trainingimageset";
  } else if (testset == true) {
    filename = "dataset/testingimageset";
  }
  std::ifstream file(filename.c_str(), std::fstream::binary);
  if (file.is_open()) {
    int magic_number = 0, number_of_images = 0, n_rows = 0, n_cols = 0;
    file.read((char *)&magic_number, sizeof(magic_number));
    magic_number = ReverseInt(magic_number);
    file.read((char *)&number_of_images, sizeof(number_of_images));
    number_of_images = ReverseInt(number_of_images);
    file.read((char *)&n_rows, sizeof(n_rows));
    n_rows = ReverseInt(n_rows);
    file.read((char *)&n_cols, sizeof(n_cols));
    n_cols = ReverseInt(n_cols);
    for (int i = 0; i < number_of_images; i++) {
      Image newimage;
      newimage.index = i;
      for (int j = 0; j < n_rows; j++) {
        for (int k = 0; k < n_cols; k++) {
          unsigned char temp = 0;
          file.read((char *)&temp, sizeof(temp));
          newimage.pixels.push_back((double)temp);
        }
      }
      if (testset == false) {
        trainingset.push_back(newimage);
      } else if (testset == true) {
        testingset.push_back(newimage);
      }
    }
  }
}

void neural::load::LoadImageLabels(bool testset) {
  std::string filename = "NULL";
  if (testset == false) {
    filename = "dataset/traininglabelset";
  } else if (testset == true) {
    filename = "dataset/testinglabelset";
  }
  std::ifstream file(filename.c_str(), std::fstream::binary);
  if (file.is_open()) {
    int magic_number = 0, number_of_images = 0;
    file.read((char *)&magic_number, sizeof(magic_number));
    magic_number = ReverseInt(magic_number);
    file.read((char *)&number_of_images, sizeof(number_of_images));
    number_of_images = ReverseInt(number_of_images);
    for (int i = 0; i < number_of_images; i++) {
      unsigned char temp = 0;
      file.read((char *)&temp, sizeof(temp));
      if (testset == false) {
        trainingset[i].label = (int)temp;
      } else if (testset == true) {
        testingset[i].label = (int)temp;
      }
    }
  }
}

int neural::load::ReverseInt(int i) {
  unsigned char ch1, ch2, ch3, ch4;
  ch1 = i & 255;
  ch2 = (i >> 8) & 255;
  ch3 = (i >> 16) & 255;
  ch4 = (i >> 24) & 255;
  return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}
