//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_INJECTOR_H
#define RESPECTRAL_INJECTOR_H

static void *g_clientdll = nullptr;
static void *g_cvar      = nullptr;

class Injector {
public:
    static Injector* instance();

protected:
    Injector();

private:
    static Injector *_instance;

};


#endif //RESPECTRAL_INJECTOR_H
