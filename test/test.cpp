
#include <cstring>
#include <iostream>
#include <memory>
#include "smalloc.h"
int main(){
    for(auto i=0;i<10;i++){
    auto* ptr = smalloc::smalloc(i);
    smalloc::sfree(ptr);

    }
    return 1;
}