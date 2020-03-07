#include<sstream>
#include<fstream>
#include<vector>
#include<istream>
#include<string>
#include<iostream>
using std::cout; using std::endl; using std::vector;
#include "GrayScale.h"

int main(){
    Image image("test.pgm");//instantiate by giving file name
    image.write_image("test.txt");//writes out to a file and will be named "test"
    auto image_test = image.sharpen();//convolving to sharpen
    image_test.write_image("image_test.txt");
    std::ifstream input;
    input.open("file.txt");

}
