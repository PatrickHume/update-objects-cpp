#include <utility>
#include <map>
#include <string>
#include <stack>
#include <array>
#include <bitset>
#include <iostream>

//Some unique IDs for labels
#define HEIGHT  0
#define PRICE   1

using byte = unsigned char;

struct attribute{
    void* pointer;
    unsigned long length;
};

class ByteGetter {
    public:
        ByteGetter();
        ~ByteGetter();
        int     setParent(void*);
        int     mapValue(int, void*, unsigned long);
        int     set(int);
        int     len(int);
        void*   get(int);
        byte    out();
    private:
        void *objectPointer;
        std::map<int, struct attribute> attributeMap;
        std::map<int, bool> updateMap;
        std::stack<int> updateStack;
};