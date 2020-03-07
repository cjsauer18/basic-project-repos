#include "MultiValueMap.h"
#include<string>
#include <iostream>
#include <algorithm>
#include<vector>
#include<initializer_list>
using std::string; using std::vector; using std::initializer_list;
using std::ostream; using std::cout; using std::cin; using std::endl;

//This project creates a struct called Element. Element resembles a map, however instead of
//one value corresponding to key, the key can have multiple values, in turn requires the use of a vector of strings.
//The class MVM contains a vector of elements. The class has various methods which pertain to inserting, checking, removing,
//finding, and comparing values of elements with regard to it's keys and values.


//constructor
Element::Element(string key, initializer_list<string> values){
    key_ = key;
    for(auto &x: values){
        values_.push_back(x);
    }
}
//comparison of alike elements
bool Element::operator==(const Element&x)const{
    return key_ == x.key_ && values_ == x.values_;
}
//format output of type Element
ostream& operator<<(ostream&out, Element& x){
       string temp;
       for(auto i = x.values_.begin(); i != x.values_.end(); ++ i){
           temp += *i + ",";//add to string to output
           
           }
       out << "| " << x.key_ << " | <" << temp << "> |" << endl;
       return out;
    }
           
//constructor
MVM::MVM(initializer_list<Element>&list){
    for(const auto &item: list){
        data_.push_back(item);
    }
}
//auxiliary method finds the iterator where a match is found through lower bound.
//Returns iterator pointing to location in data_ where a match is found.
//If no match is found, last position is returned
vector<Element>::iterator MVM::find_key(string key){

    auto iterator = std::lower_bound(data_.begin(), data_.end(), key,[](const Element&c, const string& key){
        return c.key_ < key;
    });
    if(iterator->key_ == key){
        return iterator;//returns iterator where key is located from parameter input
    }
    else{
        return data_.end();
    }
        
}
//getter method. Returns vector of strings (keys) that are found to match parameter input
vector<string> MVM::find_value(string val){//return vector
  //returns a (possibly empty) vector<string> which is a list of all keys where val is located
    vector<string> value;
    for(auto iter = data_.begin(); iter != data_.end(); ++ iter){//iterates through vector of data which encapulates another vector of data
        for(int i = 0; i < iter->values_.size(); ++i){//loop through element values_
            if(iter->values_[i] == val){//equal to the vector of value
                value.push_back(iter->key_);//push back key of element that contains val in values_
            }
        }
    }
    return value;//returns vector of keys corresponding to val found in values_
}
//auxiliary that checks for equality in vector
bool MVM::temp(string&value, Element&c){
    for(auto i = c.values_.begin(); i!=c.values_.end(); ++i){
        if (*i == value){
            return true;
        }
    }
    return false;
}
//add element directly
bool MVM::add(Element&c){
    data_.push_back(c);
    return true;
}
//function checks multi value map and adds to existing elements based on key input
//function will create a new element if key and value are new, and not previously in the MVM.
bool MVM::add(string key, string value) {
    bool notFound = false; //indicator of if match is found in MVM
    if(data_.size() == 0){
        data_.push_back(Element(key, {value}));//if no element currently in MVM, add to MVM.
    }
       for(auto iter = data_.begin(); iter != data_.end(); ++ iter){
           auto &val_ = iter->values_;
           auto flag = temp(value, *iter);//if value is in element values_
           if(iter->key_ == key && flag == false){//if key is located, push back values_ in element
            val_.push_back(value);//push back into element value vector
            return true;
           }
            else{
            notFound = true;
            }
           if(iter->key_ == key && flag == true){//if key and val both exist already
               return false;
            }else{
            notFound = true;
            }
    }
    if(notFound == true){//if no match is found, create, and add element to MVM with values.
            auto it = find_key(key);
            data_.insert(it, Element(key, {value}));
            return true;
            }
    return false;//already in map
}
//getter that returns size of multi value map
size_t MVM::size(){
    return data_.size();
}
//removes key from element, which in turn removes the element
//removes element from key input
bool MVM::remove_key(string key){
    auto it = find_key(key);//element iterator where key is located in MVM
    if(it->key_ == key){//if element.key_ is equal to key
        data_.erase(it);//remove element from MVM
        return true;
    }
    return false;//no such key found
}
    
//for every Element in the MVM
//if the value is in the values_ of the Element, value is removed from element
vector<string> MVM::remove_value(string val){
    auto it = find_value(val);//keys found to hold values specified by parameter
    for(auto i = 0; i < data_.size(); i++){//loop through data_
        auto &val_ = data_[i].values_;//attain reference to current element pointer in data_
            for(auto x = 0; x<val_.size(); ++x){
                if(val_[x] == val){//if value in values_ matches parameter.
                    val_.erase(val_.begin() + x);//pointer to value in vector to be erased
                }
            }
        }
    return it;//returns vector of every key that had a corresponding value removed.(all the keys where a value was found and removed)
}
//formats multi value map to outstream
ostream& operator<<(ostream& out, MVM& m){
    string temp;
    int counter = 0;
    for(auto i = m.data_.begin(); i < m.data_.end(); ++i){
        counter++;
        out << counter << ": " << *i;//outputs element, calls element ostream operator
    }
    return out;//returns ostream
}
