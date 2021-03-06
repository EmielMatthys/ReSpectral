//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_INJECTOR_H
#define RESPECTRAL_INJECTOR_H

typedef void *(*CreateInterfaceFn)(const char *, int *);
static void *g_clientdll = nullptr;


class Injector {
public:
    Injector() = default;
    static void Initialize();

private:
    static bool _initialized;
};


#endif //RESPECTRAL_INJECTOR_H
