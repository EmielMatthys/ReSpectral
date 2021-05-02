//
// Created by emiel on 2/05/21.
//

#ifndef RESPECTRAL_VTABLEHOOK_H
#define RESPECTRAL_VTABLEHOOK_H

#include <cstdint>
#include <unistd.h>
#include <sys/mman.h>

int vtablehook_pagesize = sysconf(_SC_PAGE_SIZE);
int vtablehook_pagemask = ~(vtablehook_pagesize-1);

int vtablehook_unprotect(void* region) {
    mprotect((void*) ((intptr_t)region & vtablehook_pagemask), vtablehook_pagesize, PROT_READ|PROT_WRITE|PROT_EXEC);
    return PROT_READ|PROT_EXEC;
}

void vtablehook_protect(void* region, int protection) {
    mprotect((void*) ((intptr_t)region & vtablehook_pagemask), vtablehook_pagesize, protection);
}

/*
* instance: pointer to an instance of a class
* hook: function to overwrite with
* offset: 0 = method 1, 1 = method 2 etc...
* return: original function
*/

void* vtablehook_hook(void* instance, void* hook, int offset) {
    intptr_t vtable = *((intptr_t*)instance);
    intptr_t entry = vtable + sizeof(intptr_t) * offset;
    intptr_t original = *((intptr_t*) entry);

    int original_protection = vtablehook_unprotect((void*)entry);
    *((intptr_t*)entry) = (intptr_t)hook;
    vtablehook_protect((void*)entry, original_protection);

    return (void*)original;
}

#endif //RESPECTRAL_VTABLEHOOK_H
