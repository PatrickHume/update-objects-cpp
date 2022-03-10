#include "byteGetter.hpp"

std::map<int, ByteGetter*>      ByteGetter::objMap;
std::map<int, bool>             ByteGetter::objUpdateMap;
std::stack<unsigned short int>  ByteGetter::objStack;

unsigned short int ByteGetter::nextObjId = 0;
unsigned short int ByteGetter::objLength = 1;

ByteGetter::ByteGetter()
{
    objId = nextObjId;
    nextObjId++;

    objMap[objId] = this;
    objUpdateMap[objId] = 0;
    length = 1;
}

ByteGetter::~ByteGetter()
{
}

unsigned short int ByteGetter::objOutLen(){
    return objLength;
}

int ByteGetter::objOut(char* outStr){
    printf("outLen: %i\n",objLength);

    unsigned int ctr = 0;

    while(!objStack.empty()){

        unsigned short int _objId = objStack.top();

        outStr[ctr] = ((byte *)&_objId)[0]; ctr++;
        outStr[ctr] = ((byte *)&_objId)[1]; ctr++;

        //printf("--%i--\n",_objId);
        //std::cout << std::bitset<16>(_objId) << "\n";
        //std::cout << std::bitset<8>(((byte *)&_objId)[0]) << "\n";
        //std::cout << std::bitset<8>(((byte *)&_objId)[1]) << "\n";
        //printf("----\n");

        //printf("overall: %i\n",objLength);
        unsigned int jump = objGet(_objId)->outLen();
        //printf("jump: %i\n",jump);
        objGet(_objId)->out(outStr + ctr);
        ctr += jump;

        objStack.pop();
    }
    length = 1;
    printf("==========\n");
    //out(outStr);
    return ctr;
}

int ByteGetter::objIn(char* inStr, int inLen){
    printf("outLen: %i\n",objLength);

    int ctr = 0;
    //std::cout << std::bitset<8>(inStr[ctr]) << " No. objs: " << (int)inStr[ctr] << "\n";
    //for (int objCtr = 0; objCtr < (int)inStr[ctr]; objCtr++){
    while (ctr < inLen){
        unsigned short int _objId = 0;
        std::cout << std::bitset<8>(inStr[ctr]) << "\n";
        ((byte *)&_objId)[0] = inStr[ctr]; ctr++;
        std::cout << std::bitset<8>(inStr[ctr]) << " objId: ";
        ((byte *)&_objId)[1] = inStr[ctr]; ctr++;
        std::cout << _objId << "\n";

        ctr += 1 + objGet(_objId)->in(inStr + ctr);
    }
    return 0;
}

int ByteGetter::setObjId(unsigned short int id){
    objId = id;
    return 0;
}
/*
int ByteGetter::setParent(void* objPointer){
    objectPointer = objPointer;
    return 0;
}
*/
int ByteGetter::mapValue(int id, void* pointer, byte length){
    struct byteAttribute a = {pointer, length};
    attributeMap[id] = a;
    updateMap[id] = 0;
    return 0;
}

ByteGetter* ByteGetter::objGet(int id){
    return objMap[id];
}

void* ByteGetter::get(int id){
    return attributeMap[id].pointer;
}

int ByteGetter::len(unsigned int id){
    return attributeMap[id].length;
}

int ByteGetter::set(unsigned int id){
    if(updateMap[id])
        return 0;

    updateMap[id] = 1;
    updateStack.push(id);
    length += 1 + len(id);
    objLength += 1 + len(id);
    //printf("overall: %i\n",objLength);

    if(objUpdateMap[objId])
        return 0;

    objUpdateMap[objId] = 1;
    objStack.push(objId);
    objLength += 3;
    //printf("overall: %i\n",objLength);

    return 0;
}

int ByteGetter::outLen(){
    return length;
}

int ByteGetter::out(char* outStr){

    //Encoder
    int ctr = 0;
    outStr[ctr] = updateStack.size();
    ctr++;
    while(!updateStack.empty()){
        outStr[ctr] = updateStack.top();
        ctr++;
        for(int i = 0; i < len(updateStack.top()); i++){
            outStr[ctr] = (&(*(byte *)(get(updateStack.top()))))[i];
            ctr++;
        }
        updateStack.pop();
    }
    length = 1;
    return 0;
}

int ByteGetter::in(char* inStr){ 
    /*
    An example data input...

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

    //Decoder
    int ctr = 0;

    std::cout << "--" << std::bitset<8>(inStr[ctr]) << " No. attrs: " << (unsigned int)inStr[ctr] << "\n";
    int numAttr = inStr[ctr];
    for (int j = 0; j < numAttr; j++){
        std::cout << "----" << std::bitset<8>(inStr[ctr+1]) << " attrId: "  << (unsigned int)inStr[ctr+1] << " length (" << len((unsigned int)inStr[ctr+1]) << ")";
        for(int i = 0; i < len((unsigned int)inStr[ctr+1]); i++){
            (&(*(byte *)(get(inStr[ctr+1]))))[i] = (byte)inStr[ctr+2+i];
            std::cout << "\n" << "------" << std::bitset<8>(inStr[ctr+2+i]) << " [" << i << "]";
        }
        printf(" %s (string) ",(char *)get(inStr[ctr+1]));
        std::cout << *(int *)get(inStr[ctr+1]) << " (int) " << *(float *)get(inStr[ctr+1]) << "(float) ...etc" << "\n";
        ctr = ctr + 1 + len((unsigned int)inStr[ctr+1]);
    }
    return ctr;
}