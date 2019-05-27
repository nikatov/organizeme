#include <memory>
#include <cassert>

#include "package/package.h"


bool testHeader(Header &h){
    uint8_t *encodedHeader = encodeHeader(std::make_shared<Header>(h));
    std::shared_ptr<Header> decoded = decodeHeader(encodedHeader);
    
    delete[] encodedHeader;
    
    return (h.idUser == decoded->idUser && h.numOfOperations == decoded->numOfOperations &&
            h.opType == decoded->opType && h.password == decoded->password);
}

int main(){
    Header h = {1, "qwerty", 1, ADD_TASK};
    Header h1 = {0, "qwerty", 1, ADD_TASK};
    Header h2 = {1, "", 1, ADD_TASK};
    Header h3 = {1, "qwerty", 0, ADD_TASK};
    assert(testHeader(h));
    assert(testHeader(h1));
    assert(testHeader(h2));
    assert(testHeader(h3));
}