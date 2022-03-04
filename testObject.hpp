#include "byteGetter.hpp"

class TestObject {
    public:
        TestObject();
        ~TestObject();
    private:
        int height;
        float price;

        ByteGetter byteGetter;
};