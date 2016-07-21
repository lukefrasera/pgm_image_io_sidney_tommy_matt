#include <iostream>
#include <fstream>
#include <stdint.h>

struct PgmImage {
  unsigned char *data;
  int width, height;
  int max_val;
};

bool InitPGMImage(PgmImage &image);

bool AllocatePGMImage(PgmImage &image, int max_val, int w, int h);

bool ReadPGMImageHeader(std::string &type, int &w, int &h, int &max_val, std::ifstream &fin);

bool ReadPGMImage(PgmImage &image, std::string filename);

bool WritePGMImage(PgmImage image, std::string filename);

bool DeletePGMImage(PgmImage &image);

int main(int argc, char** argv) {
  // Read and Write PGM IMage
  PgmImage image;
  InitPGMImage(image);
  if (argc < 3) {
    std::cout << "ERROR: Not enough Parameters\n"
                 "Usage: ./[executable] <input_image> <output_iamge>"
              << std::endl;
    return -1;
  }
  std::string filename = argv[1];
  std::string output_filename = argv[2];
  // Read image data into image
  ReadPGMImage(image, filename);
  // Write image out to new file
  WritePGMImage(image, output_filename);

  DeletePGMImage(image);
  return 0;
}

bool InitPGMImage(PgmImage &image) {
  image.data    = NULL;
  image.width   = 0;
  image.height  = 0;
  image.max_val = 0;
  return true;
}

bool AllocatePGMImage(PgmImage &image, int max_val, int w, int h) {
  // Check if image is already allocated
  if (DeletePGMImage(image)) {
    std::cout << "WARNING: Image already allocated, overwriting data!" << std::endl;
  }
  // Check if new image can be allocated based on max_val. We are not
  // going to be dealing with a max_val larger than 255 because that woulr mean
  // storing the data in something larger than a byte!!!.
  if (max_val > 255) {
    std::cout << "ERROR: Can't work with image values this large" << std::endl;
    return false;
  }
  // Allocate new image with passed parameters. This is where the allocation
  // occurs.
  image.data = new unsigned char[w * h];
  image.width = w;
  image.height = h;
  image.max_val = max_val;
  return true;
}

bool DeletePGMImage(PgmImage &image) {
  if (!image.data) {
    return false;
  }
  delete [] image.data;
  image.data = NULL;
  image.width   = 0;
  image.height  = 0;
  image.max_val = 0;
  return true;
}

bool ReadPGMImageHeader(std::string &type, int &w, int &h, int &max_val, std::ifstream &fin) {
  return true;
}

bool ReadPGMImage(PgmImage &image, std::string filename) {
  // Open File to read
  std::ifstream fin(filename.c_str(), std::ifstream::binary);
  std::string image_type;
  int width, height, max_val;
  
  // Read Image header
  ReadPGMImageHeader(image_type, width, height, max_val, fin);

  // Read Image data


  return true;
}

bool WritePGMImage(PgmImage image, std::string filename) {
  return true;
}
