//
//  GrayScale.hpp
//  GrayScale
//
//  Created by Christopher Sauer on 11/6/19.
//  Copyright © 2019 Christopher Sauer. All rights reserved.
//
#include <stdio.h>
#include "GrayScale.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::string; using std::cin; using std::cout; using std::vector; using std::endl;

Image::Image(string f_name){
    string line;
    vector<long> row; //temp container
    std::ifstream input;
    input.open(f_name);
    if(input.is_open()){
        cout << "open" << endl;
    }
    int step = 0;
    while(getline(input, line))
    {
        if(step == 0){
            if(line[1] == '2'){
                magic_number_ = line;
                step = 1;
                continue;
            }
            else{
                cout << "invalid magic number, must be 'P2' | File: " << "P" << line[1] << endl;
                input.close();
                }
        }
        if(line[0] == '#'){
            string temp;
            test_line = line;
            for (int i = 0; i < line.size(); ++i){
                if(isdigit(line[i])){
                    temp += line[i];
                }
            }
            std::istringstream iss2(temp);
            cout << line << endl;
            iss2 >> max_val_;
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
            iss >> width_ >> height_;
            // column.resize(height);
            cout << "checking W/H" << width_ << height_ << endl;
            step = 3;
            continue;
        }
        if(step == 3){
            long temp;
            std::istringstream iss_temp(line);
            while(iss_temp >> temp){
                row.push_back(temp);
            }
            pixels_.push_back(row);
            row.clear();
        }
    }   
}

void Image::write_image(string f_name) const
{
    std::ofstream myfile;
    myfile.open(f_name);
    myfile << magic_number_ << endl;
    myfile << test_line << endl;
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

Image Image::convolve(vector<vector<long>> mask, long div, long whiten) const {//mask is inputted, and applied to current instance values, and a transformed value is outputted.
       Image new_image;
        auto new_pixels = new_image.pixels_;
       int x_s = 0;//row index (x)
       int y_s = 0;//column index (y)
       for(int x = 0; x < height_ * width_; ++x){
           long sum = 0;//reset sum
           cout << "Pixel from("<< x_s<<","<<y_s<<")"<<  endl;
           for(int x = -1; x < 2; x++){
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
                    sum += 0;
                    }
               }
           }
           if(sum < 0){
           sum = 0;
           }
           //convolve methods if applicable
           sum = sum + whiten;
           sum = sum/div;
           if(sum > max_val_){//per pixel
               sum = max_val_ - 1;
               //could do auto (for each) pixel in .size(), and change the value
           }
           new_pixels[y_s][x_s] = sum;
           x_s += 1; //next pixel
           if(x_s == (width_)){
               x_s = 0;
               y_s += 1;
           }
       }
    return new_image;
    }
Image Image::sharpen() const 
{
    Image image_sharpen; //code for importing mask file
    vector<long>row; vector<vector<long>> mask; string line; long temp;
    std::ifstream mask_file;
    mask_file.open("mask.txt");
        while(getline(mask_file, line)){
            std::istringstream iss_mask(line);
            while(iss_mask >> temp){
                row.push_back(temp);
             }
            mask.push_back(row);
            row.clear();
           }
    long div = 1;
    long whiten = 0;
    image_sharpen.convolve(mask, div, whiten);
    return image_sharpen;
}
Image Image::extract(long) const 
{
     //code for importing mask file
    Image image_sharpen;
    vector<long>row; vector<vector<long>> mask;
    string line; long temp; std::ifstream mask_file;
    mask_file.open("mask_sharpen.txt");
        while(getline(mask_file, line)){
            std::istringstream iss_mask(line);
            while(iss_mask >> temp){
                row.push_back(temp);
               }
            mask.push_back(row);
            row.clear();
           }
    long div = 1;
    long whiten = 0;
    image_sharpen.convolve(mask, div, whiten);
    return image_sharpen;
}
Image Image::blur() const
{
     //code for importing mask file - yes quite teidious
    Image image_blur;//temp
    vector<long>row; vector<vector<long>> mask; long temp;
    std::ifstream mask_file; string line;//temp string for parsing into string
    mask_file.open("mask.txt");
    cout << "blur is working" << endl;
        while(getline(mask_file, line)){
            std::istringstream iss_mask(line);
                while(iss_mask >> temp){
                   row.push_back(temp);
               }
            mask.push_back(row);
            row.clear();
           }
    long div = 9;
    long whiten = 0;
    image_blur.convolve(mask, div, whiten);
    return image_blur;//return blurred 
}
Image Image::edge_detect() const 
{
     //code for importing mask file
    Image image_edge_detect;//temp
    vector<long>row; vector<vector<long>> mask; string line;
    long temp; std::ifstream mask_file;
    mask_file.open("mask_sharpen.txt");//open file 
        while(getline(mask_file, line)){
            std::istringstream iss_mask(line);
                while(iss_mask >> temp){
                   row.push_back(temp);
               }
            mask.push_back(row);
            row.clear();
           }
    long div = 1;
    long whiten = 50;
    image_edge_detect.convolve(mask, div, whiten);
    return image_edge_detect;
}
Image Image::emboss() const 
{
     //code for importing mask file
    Image image_emboss;//temp image
    vector<long>row; vector<vector<long>> mask;
    string line; long temp;
    std::ifstream mask_file;
     mask_file.open("mask_sharpen.txt");
        while(getline(mask_file, line)){
            std::istringstream iss_mask(line);
                while(iss_mask >> temp){
                   row.push_back(temp);
               }
            mask.push_back(row);
            row.clear();
           }
    long div = 1;
    long whiten = 0;
    image_emboss.convolve(mask, div, whiten);
    return image_emboss;
}

