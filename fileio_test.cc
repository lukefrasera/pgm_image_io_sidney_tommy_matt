#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <stdint.h>

struct PgmImage {
  std::string type;
  std::string comment;
  int width, height, max_val;
  unsigned char *data;
  // char data_1[];
  // std::string data_str;
};

bool InitPGMImage(PgmImage &image);

bool AllocatePGMImage(PgmImage &image, int max_val, int w, int h);

bool ReadPGMImageHeader(PgmImage &image, std::string image_type, int &w, int &h, int &max_val, std::ifstream &fin);

bool ReadPGMImage(PgmImage &image, std::string filename, std::string output_filename);

bool WritePGMImage(PgmImage image, std::string output_filename);

bool DeletePGMImage(PgmImage &image);

int main(int argc, char** argv) {
  // Read and Write PGM IMage
  PgmImage image;
  InitPGMImage(image);
  if (argc < 3) {
    std::cout << "ERROR: Not enough Parameters\n"
                 "Usage: ./[executable] <input_image> <output_image>"
              << std::endl;
    return -1;
  }
  std::string filename = argv[1];
  std::string output_filename = argv[2];

  AllocatePGMImage(image, image.max_val, image.width, image.height);
  // Read image data into image
  ReadPGMImage(image, filename, output_filename);
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

bool ReadPGMImageHeader(PgmImage &image, std::string type, int &w, int &h, int &max_val, std::ifstream &image_in) {
   // Read Image header

  // Read Image Type
  getline(image_in, image.type,'\n');
  std::cout << image.type << std::endl;

  // Read Comment
  getline(image_in, image.comment,'\n');
  std::cout << image.comment << std::endl;

  // Read Width and Height
  image_in >> image.width;
  std::cout << image.width << " ";
  image_in.get();

  image_in >> image.height;
  image_in.get();
  std::cout << image.height << std::endl;

  // Read Max Value

  image_in >> image.max_val;
  image_in.get();
  std::cout << image.max_val << std::endl;

  return true;
}

bool ReadPGMImage(PgmImage &image, std::string filename, std::string output_filename) {
  // Open File to read
  std::ifstream image_in(filename.c_str(), std::ifstream::binary);

  if (image_in.is_open()) {
    std::cout << "Image is opening" << std::endl;
  } else {
    std::cout << "Image isn't opening" << std::endl;
  }

  // Read Header 

  ReadPGMImageHeader(image, image.type, image.width, image.height, image.max_val, image_in);

  // Read Data

  image_in.read(image.data, image.width*image.height);
  std::cout << "IMAGE DATA: " << image.data;

  // getline(image_in, image.data_str,'\n');
  // std::cout << "IMAGE DATA STR: " << image.data_str;
  // image_in >> image.data_1;
  // image_in.get();

  // getline(image_in, image.data_1,'\n');
  // std::cout << image.data_str << std::endl;

  // image_in.read(image.data_1, image.width*image.height);
  // std::cout << image.data_1 << std::endl;

  // image_in.read(data_1, image.width*image.height);
  // std::cout << data_1 << std::endl;

  image_in.close();
  std::cout << "Image is closing" << std::endl;

  return 0;
}

bool WritePGMImage(PgmImage image, std::string output_filename) {

  // Writing PGM Image

  std::ofstream image_out;
  image_out.open(output_filename.c_str());

  image_out << image.type << std::endl;
  image_out << image.comment << std::endl;
  image_out << image.width <<" ";
  image_out << image.height << std::endl;
  image_out << image.max_val <<std::endl;
  image_out << image.data;

  image_out.close();
  return true;
}
