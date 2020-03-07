#include <stdio.h>
#include "GrayScale.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::string; using std::cin; using std::cout; using std::vector; using std::endl;

//This project consists of designing a class 'Image' which opens a PGM (portable gray map) file.
//The class parses in data from a file, assigning variables to it's unique magic number, as well as assigning height and
//width values based on file properties.
//Various methods consist of calling the convolve method, which applies a mask over every pixel value, changing each value
//Based on the purpose of the method. Each method calls convolve to manipulate the pixels in the image.
//Class contains a method that writes out a file to a name given by user.

Image::Image(string f_name){
    string line;
    vector<long> row; //temp container
    std::ifstream input;
    input.open(f_name);
    if(input.is_open()){//open file
        cout << "open" << endl;//file is open
    }
    int step = 0;
    while(getline(input, line))//parsing in file
    {
        if(step == 0){
            if(line[1] == '2'){
                magic_number_ = line;//PGM attribute
                step = 1;
                continue;
            }
            else{
                cout << "invalid magic number, must be 'P2' | File: " << "P" << line[1] << endl;//checks file must be of proper PGM format
                input.close();
                }
        }
        if(line[0] == '#'){
            string temp;
            for (int i = 0; i < line.size(); ++i){
                if(isdigit(line[i])){
                    temp += line[i];
                }
            }
            std::istringstream iss2(temp);
            iss2 >> max_val_;//max val number
            step = 2;
            continue;
        }
        if(step == 1){
            std::istringstream iss2(line);
            iss2 >> max_val_;
            step = 2;
            continue;
        }
        if(step == 2){
            std::istringstream iss(line);
            cout << line << endl;
            iss >> width_ >> height_;//extract height and width parameters
            step = 3;
            continue;
        }
        if(step == 3){//passed first few lines, reaching pixels
            long temp;
            std::istringstream iss_temp(line);
            while(iss_temp >> temp){//input pixels to stringstream
                row.push_back(temp);//insert into row
            }
            pixels_.push_back(row);//insert row into pixels_
            row.clear();//reset row
        }
    }
}
//retreives file from given filename (passed by methods) to extract masking from particular file.
vector<vector<long>>Image::mask(string file) const {
vector<long>row; vector<vector<long>> mask;
    string line; long temp;
    std::ifstream mask_file;
     mask_file.open(file);//extract emboss mask
        while(getline(mask_file, line)){//parse string
            std::istringstream iss_mask(line);
                while(iss_mask >> temp){//parse number
                   row.push_back(temp);
               }
            mask.push_back(row);//push back to mask vector
            row.clear();//clear row
         }
    return mask;//return extracted image.
}
//Function writes image to file
//Iterates through each pixel
void Image::write_image(string f_name) const
{
    std::ofstream myfile;
    myfile.open(f_name);
    myfile << magic_number_ << endl;
    myfile << width_ << ' ' << height_ << endl;
    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            myfile << pixels_[i][j] << ' ';
        }
        myfile << endl;
    }
        myfile.close();
}
//Convolve method
//Transforms image in pixels_ by applying the mask (passed by parameter).
//Mask iterates over each pixel, and does the proper calculations of each pixel in the 9x9 mask and changes the pixel values
//returns new image
Image Image::convolve(vector<vector<long>> mask, long div, long whiten) const {//mask is inputted, and applied to current instance values, and a transformed value is outputted.
       Image new_image;
       auto new_pixels = new_image.pixels_;
       int x_s = 0;//row index (x)
       int y_s = 0;//column index (y)
       for(int x = 0; x < height_ * width_; ++x){//body of pixels
           long sum = 0;//reset sum
           cout << "Pixel from("<< x_s<<","<<y_s<<")"<<  endl;
           for(int x = -1; x < 2; x++){//scan 9x9 area surrounding mask focal point
               for(int i = -1; i < 2; i++){
                   try{
                      pixels_[y_s-x].at(x_s+i);//if returns error, go to catch
                      pixels_.at(y_s-x);//if returns error, go to catch. (Error mitigation)
                      
                      long matrix = pixels_[y_s-x][x_s+i];
                      long matrix_mask = mask[1-x][1+i];
                       sum += matrix * matrix_mask;
                       cout << "(i val) "<<pixels_[y_s-x][x_s+i]<< endl; //check!
                       cout << sum << endl;
                }
                catch(...) {//catches indexing(thread error) which value would be zero
                    sum += 0;//if near border (passed by any real index in pixel vector)
                    }
               }
           }
           if(sum < 0){
           sum = 0;
           }
           //convolve methods if applicable
           sum = sum + whiten;//result of asking mutation. Values whiten and div are passed in by
           //other member functions that call for specific properties to be changed according to desired effect.
           sum = sum/div;
           if(sum > max_val_){//per pixel
               sum = max_val_ - 1;
               //could do auto (for each) pixel in .size(), and change the value
           }
           new_pixels[y_s][x_s] = sum;//calculated value is now the pixel value
           x_s += 1; //next pixel
           if(x_s == (width_)){
               x_s = 0;
               y_s += 1;
           }
       }
    return new_image;//returns new image
    }
//Sharpen method. Calls convole passing in values that pertain to sharpening the pixels in the image.
//Returns sharpened image.
Image Image::sharpen() const
{
    Image image_sharpen; //code for importing mask file
    string filename = "sharpen.txt";//standard file mask call
    auto tempMask = mask(filename);//retrieve mask from file
    long div = 1;
    long whiten = 0;
    image_sharpen.convolve(tempMask, div, whiten);
    return image_sharpen;
}
//Blur method. Opens blur mask document and calls convolve to change image.
//returns blurred image
Image Image::blur() const
{
    Image image_blur;//temp
    string filename = "blur.txt";//standard file mask call
    auto tempMask = mask(filename);//retrieve mask from file
    long div = 9;//preset condition for blur masking
    long whiten = 0;
    image_blur.convolve(tempMask, div, whiten);//call convolve
    return image_blur;//return blurred image
}
//Method detects edges in the file, and raises value of edges by setting "whiten" to 50, to pass into convolve.
//Returns image with highlighted edges
Image Image::edge_detect() const
{
     //code for importing mask file
    Image image_edge_detect;//temp
    string filename = "edge_detect.txt";//standard file mask call
    auto tempMask = mask(filename);//retrieve mask from file
    long div = 1;
    long whiten = 50;
    image_edge_detect.convolve(tempMask, div, whiten);//call convolve
    return image_edge_detect;
}
//Emboss method. Opens emboss mask document and calls convolve to change image.
//Returns embossed image
Image Image::emboss() const
{
    Image image_emboss;//temp image
    string filename = "emboss.txt";//standard file mask call
    auto tempMask = mask(filename);//retrieve mask from file
    long div = 1;
    long whiten = 0;
    image_emboss.convolve(tempMask, div, whiten);//call convolve
    return image_emboss;
}

