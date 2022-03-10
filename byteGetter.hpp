#include <utility>
#include <map>
#include <string>
#include <stack>
#include <array>
#include <vector>
#include <bitset>
#include <iostream>

using byte = unsigned char;

#define m(x) &x, sizeof(x)

//Some unique IDs for labels
#define HEIGHT  0
#define PRICE   1

struct byteAttribute{
    void* pointer;
    byte length;
};

class ByteGetter {
    public:
        ByteGetter();
        ~ByteGetter();
        int                 setObjId(unsigned short int);
        unsigned short int  objOutLen();
        int                 objOut(char*);
        int                 objIn(char*, int);
        int                 objSet(int);
        ByteGetter*         objGet(int);

        //int     setParent(void*);
        int     mapValue(int, void*, byte);
        int     set(unsigned int);
        int     len(unsigned int);
        int     outLen();
        void*   get(int);
        int     out(char *);
        int     in(char *);
    private:
        static std::map<int, ByteGetter*>       objMap;
        static std::map<int, bool>              objUpdateMap;
        static std::stack<unsigned short int>   objStack;
        static unsigned short int               objLength;
        static unsigned short int               nextObjId;
        unsigned short int                      objId;

        byte                                length;
        void*                               objectPointer;
        std::map<int, struct byteAttribute> attributeMap;
        std::map<int, bool>                 updateMap;
        std::stack<unsigned int>            updateStack;
};