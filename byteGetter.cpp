#include "byteGetter.hpp"

ByteGetter::ByteGetter()
{
}

ByteGetter::~ByteGetter()
{
}

int ByteGetter::setParent(void* objPointer){
    objectPointer = objPointer;
    return 0;
}

int ByteGetter::mapValue(int id, void* pointer, unsigned long length){
    struct attribute a = {pointer, length};
    attributeMap[id] = a;
    updateMap[id] = 0;
    return 0;
}

void* ByteGetter::get(int id){
    return attributeMap[id].pointer;
}

int ByteGetter::len(int id){
    return attributeMap[id].length;
}

int ByteGetter::set(int id){
    if(updateMap[id])
        return 0;

    updateMap[id] = 1;
    updateStack.push(id);
    return 0;
}

byte ByteGetter::out(){
    int length = 0;
    std::stack<int> dataStack;
    
    while(!updateStack.empty()){
        updateMap[updateStack.top()] = 0;
        length += 2;
        length += len(updateStack.top());
        dataStack.push(updateStack.top());
        updateStack.pop();
    }

    byte data[length];
    int ctr = 0;
    while(!dataStack.empty()){
        data[ctr] = dataStack.top();
        //printf("index: %i;\n",(int)data[ctr]);
        ctr++;
        
        for(int i = 0; i < len(dataStack.top()); i++){
            data[ctr] = (&(*(byte *)(get(dataStack.top()))))[i];

            //data[ctr] = (byte)5;
            //std::cout << std::bitset<8>(data[ctr]) << " ";
            ctr++;
        }

        dataStack.pop();
    }
    
    ctr = 0;
    while(ctr < length){
        //printf("ctr: %i;\n",ctr);
        //printf("length: %i;\n",(int)data[ctr+1]);
        //printf("number: %f;\n",*(float *)(get(data[ctr])));
        for(int i = 0; i < len(data[ctr]); i++){
            //printf("i:%i\n",i);
            //std::cout << std::bitset<8>((byte)data[ctr+1+i]) << "\n";
            //std::cout << std::bitset<8>((&(*(byte *)(get(data[ctr]))))[i]) << "\n";
            //std::cout << "\n";
            (&(*(byte *)(get(data[ctr]))))[i] = (byte)data[ctr+1+i];
        }
        ctr = ctr + 1 + len(data[ctr]);
    }
    return 0;
}