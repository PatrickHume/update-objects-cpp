#include "testObject.hpp"

int main(){
    // make some objects
    TestObject object1  = TestObject();
    TestObject object2  = TestObject();
    TestObject object3  = TestObject();
    
    // set some values
    object1.setHeight(1);
    object1.setPrice(6.73);

    object2.setHeight(4);
    object2.setPrice(2.3);

    object3.setHeight(22);
    object3.setPrice(0.21);

    // use a byteGetter object to output binary data
    ByteGetter byteGetter = ByteGetter();

    int objLength = byteGetter.objOutLen();
    char data[objLength];

    // here's some variable we can also track
    char c[6] = "hello";
    // we are just using the id of 10 here
    byteGetter.mapValue(10, m(c));
    byteGetter.set(10); // now we track the variable at id 10

    objLength = byteGetter.objOut(data);

    //for(int i = 0; i < objLength; i++)
    //    std::cout << std::bitset<8>(data[i]) << "\n";

    byteGetter.objIn(data, objLength);

    printf("%.3fB\n",(double)objLength);
    printf("%.3fKB\n",(double)objLength*0.001);
    printf("%.3fMB\n",(double)objLength*0.001*0.001);

    /*
    An example data output...

    00000001 .
    00000000 obj id = 1
    00000010 num of args    = 2
    00000001 arg id         = 1
    00000000 .
    00000000 .
    11001000 .
    01000000 arg value      = 6.250000
    00000000 arg id         = 0
    00000011 .
    00000000 .
    00000000 .
    00000000 arg value      = 3
    00000000 .
    00000000 obj id = 0
    00000010 num of args    = 2
    00000001 arg id         = 1
    00000000 .
    00000000 .
    11001000 .
    01000000 arg value      = 6.250000
    00000000 arg id         = 0
    00000011 .
    00000000 .
    00000000 .
    00000000 arg value      = 3
    */

    return 0;
}