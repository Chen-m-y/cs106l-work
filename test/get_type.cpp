#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>

using namespace std ;

template <typename T>
T get_type(){
    while(true){
        cout << "Enter a " << typeid(T).name() << ":";
        string line;
        // istringstream iss(line);在 line 被填充之前就执行了。此时 line 是空字符串，导致后续 iss >> r 必然失败。
        T r;
        char extra;
        if(!getline(cin, line)){
            throw domain_error("Unable to get line from cin.");
        }
        istringstream iss(line);
        if(iss >> r && !(iss >> extra)){
            return r;
        }
        cout << "Invalid format!" << endl;
    }
}

int main(){
    int a = get_type<int>();
    cout << a << endl;
}