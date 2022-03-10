#include "byteGetter.hpp"

class TestObject {
    public:
        TestObject();
        ~TestObject();
        int setPrice(float);
        int setHeight(int);
    private:
        int height;
        float price;
        ByteGetter byteGetter;
};