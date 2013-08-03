#include "CookieParser.hpp"

int main(){
    char * cData = "key1=value1;key2=value2;key3=value3;key4=value4";
    
    CookieParser p( cData );
    p.Print();
}
