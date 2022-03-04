#include "testObject.hpp"

#define m(x) &x, sizeof(x)

TestObject::TestObject()
{
    byteGetter.setParent(this); // this allows us to transport data
    byteGetter.mapValue( HEIGHT, m(height));
    byteGetter.mapValue( PRICE,  m(price));
    
    height = 3;
    price = 6.25;

    //printf("%i\n",*(int *)(byteGetter.get(HEIGHT)));
    //printf("%f\n",*(float *)(byteGetter.get(PRICE)));

    //*(char *)(byteGetter.get(PRICE)) = (char)4.5;
    //printf("%f\n",*(float *)(byteGetter.get(PRICE)));

    //byteGetter.set(HEIGHT);

    byteGetter.set(HEIGHT);
    byteGetter.set(PRICE);
    byteGetter.out();

    printf("done: %d\n",height);
    printf("done: %f\n",price);
}

TestObject::~TestObject()
{
}