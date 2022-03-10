#include "testObject.hpp"

TestObject::TestObject()
{
    // This allows us to record the height and price
    byteGetter.mapValue(HEIGHT, m(height));
    byteGetter.mapValue(PRICE,  m(price));
    
    height = 0;
    price = 0;

    // This means we will record the height and price until they are sent
    byteGetter.set(HEIGHT);
    byteGetter.set(PRICE);
}

TestObject::~TestObject()
{
}

int TestObject::setPrice(float p){
    price = p;
    return 0;
}

int TestObject::setHeight(int h){
    height = h;
    return 0;
}