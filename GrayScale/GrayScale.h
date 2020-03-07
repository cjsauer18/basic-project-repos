#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<istream>
#include<string>
using std::vector; using std::string; using std::endl; using std::cout;

struct Image{
public: 
  vector<vector<long>> pixels_;
  string magic_number_;
  long height_ = 0;
  long width_ = 0;
  long max_val_ = 0;
  Image convolve(vector<vector<long>> mask, long div=1, long whiten=0) const;
  
public:
  Image()=default;
  Image (string f_name);
  void write_image(string f_name) const;
  vector<vector<long>>mask(string filename) const;
  Image sharpen() const;
  Image edge_detect() const;
  Image blur() const;
  Image emboss() const;
  Image extract(long) const;
};
