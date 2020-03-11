#include <iostream>
#include "MultiValueMap.h"
using namespace std;
//Project description located in class .cpp file. This main serves as a test/display of the class features. 

int main(){
    Element a("key1", {"1","2","3"});
    Element b("key2", {"1","2","3"});
    Element c("key3", {"1","2","3"});
    Element d("key4", {"1","2","3"});
    Element e("key1", {"1","2","3"});
    MVM m;//default constructor
    m.add(a); m.add(b); m.add(c); m.add(d);m.add(e);//add elements to map
    cout << m;//calls ostream MVM operator, as well as ostream Element operator
    
    //add or append element
    m.add("key2", "4");//add by value, not element
    m.add("key3", "4");//adds value 4 to key 3
    m.add("key5", "5");//key 5 not in 'm', adds element with key of 'key5' with value of 5, to m.
    cout << "Add '4' to elements with 'keys' as key2 and key3: " << endl << m;
    
    
    //remove values
    m.add("key1", "3");//3 not added to key 1, as it is already present
    auto removed_keys = m.remove_value("3");//removes every value within elements in MVM that contain the value 3.
    cout << "Remove value '3' from elements: "<< endl << m;
    
    cout << "Keys where a value of '3' was removed: " << endl;
    for(int i = 0; i < removed_keys.size(); ++i){
        cout << removed_keys[i] << endl;//prints every key where a value was removed from the remove_value function value
    }
}
