#include <iostream>
#include <fstream>
#include <stdint.h>

// Global Constant Definitions
const char NEW_LINE = '\n';
const char COMMENT_SYMBOL = '#';
const char SPACE = ' ';
const int SEARCH_BLOCK = 100; // the block size that the program should
                              // search to find the delim char in .ignore
                              // function
struct PgmImage {
  char type[3];
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
  // going to be dealing with a max_val larger than 255 because that would mean
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
  //Initialize Variables
  std::string comment;

  if (fin.is_open()) {
    std::cout << "Image is opening" << std::endl;
  } else {
    std::cout << "Image isn't opening" << std::endl;
  }

  if (fin.peek() == COMMENT_SYMBOL)
  {
    fin.ignore(SEARCH_BLOCK,NEW_LINE);
  }

  // Read Image Type
  fin >> type;
  std::cout << type << std::endl;
  fin.ignore(SEARCH_BLOCK,NEW_LINE);

  if (fin.peek() == COMMENT_SYMBOL)
  {
    fin.ignore(SEARCH_BLOCK,NEW_LINE);
  }

  // Read Width and Height
  fin >> w;
  fin.ignore(1, SPACE);
  std::cout << w << " ";
  
  fin >> h;
  fin.ignore(SEARCH_BLOCK, NEW_LINE);
  std::cout << h << std::endl;

  if (fin.peek() == COMMENT_SYMBOL)
  {
    fin.ignore(SEARCH_BLOCK,NEW_LINE);
  }

  // Read Max Value
  fin >> max_val;
  std::cout << max_val << std::endl;

  return 0;
}

bool ReadPGMImage(PgmImage &image, std::string filename) {
  // Open File to read
  std::ifstream fin(filename.c_str(), std::ifstream::binary);
  std::string image_type;
  int width, height, max_val;
  
  // Read Image header
  ReadPGMImageHeader(image_type, width, height, max_val, fin);

  // Allocate PGM Image 
  AllocatePGMImage(image, max_val, width, height);

  // Read Image data
  fin.read((char*)image.data, image.width*image.height);

  // Inputs values from the string to the char array
  for(int i = 0; i < 3 ; i++){
    image.type[i] = image_type[i];
  }

  fin.close();
  std::cout << "Image is closing" << std::endl;

  return true;
}

bool WritePGMImage(PgmImage image, std::string filename) {

  // Writing PGM Image

  std::ofstream fout;
  fout.open(filename.c_str());

  fout << image.type << std::endl;
  // fout << "# Comment goes here" << std::endl;
  fout << image.width <<" ";
  fout << image.height << std::endl;
  fout << image.max_val << std::endl;
  fout.write((char*)image.data, image.width*image.height);

  fout.close();
  return true;

}