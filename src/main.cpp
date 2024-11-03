#include <fstream>
#include <iostream>
#include "map.cpp"
using namespace std;


int main(){
    PersistentMap mp("foo", ":");
    // mp.set("foo", "bar");
    // mp.set("hello", "world");
    // mp.set("foo", "come");
    cout << "foo's value = " << mp.get("foo") << endl;
    return 0;
}
