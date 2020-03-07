#pragma once

#include<string>
using std::string;
#include<vector>
using std::vector;
#include<initializer_list>
using std::initializer_list;
#include<iostream>
using std::ostream;

struct Element{
public:
  string key_;
  vector<string> values_;
  Element()=default;
    Element(string key, initializer_list<string> values);
    bool operator==(const Element&)const;
  friend ostream& operator<<(ostream&, Element&);
    
};

class MVM{
public:
  vector<Element> data_;
  vector<Element>::iterator find_key(string);
  vector<string> find_value(string);

public:
  MVM()=default;
  MVM(initializer_list<Element>&list);
  size_t size();
    bool temp(string&value, Element&c);//auxiliary
    bool add(Element&c);
  bool add(string key, string value);
  bool remove_key(string);
   // void Erase(string value, Element&c);
  vector<string> remove_value(string);
  friend ostream& operator<<(ostream&, MVM& );
};
