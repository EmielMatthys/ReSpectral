//
// Created by emiel on 22/07/21.
//

#ifndef RESPECTRAL_CLIENTCLASS_H
#define RESPECTRAL_CLIENTCLASS_H

#include <dt_recv.h>

class ClientClass
{
private:
    char _chPadding[8];
public:
    char* chName;
    RecvTable* m_pRecvTable;
    ClientClass* m_pNext;
    int iClassID;
};

#endif //RESPECTRAL_CLIENTCLASS_H
