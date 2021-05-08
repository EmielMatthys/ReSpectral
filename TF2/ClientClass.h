//
// Created by emiel on 8/05/21.
//

#ifndef RESPECTRAL_CLIENTCLASS_H
#define RESPECTRAL_CLIENTCLASS_H

class ClientClass
{
private:
    char _chPadding[8];
public:
    char* chName;
    RecvTable* Table;
    ClientClass* pNextClass;
    int iClassID;
};

#endif //RESPECTRAL_CLIENTCLASS_H
