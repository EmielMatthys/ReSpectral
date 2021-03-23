//
// Created by emiel on 9/03/21.
//

#ifndef RESPECTRAL_MODULE_H
#define RESPECTRAL_MODULE_H

#include <map>
#include <unordered_map>
#include <memory>

typedef void *(*CreateInterfaceFn)(const char *, int *);

class InterfaceReg;

/**
 * Represents a module loaded in TF2
 */
class Module {
private:
    const char  *_filename;
    void        *_handle;

    static std::map<const char *, std::shared_ptr<Module>> _cache;

    Module(const char *filename);

public:

    static std::shared_ptr<Module> grab(const char* filename);

    void *getSymbol(const char* symbolName) const;
    void close();
    void *getHandle() const {return _handle;}

    InterfaceReg *getInterfaces() const;

    CreateInterfaceFn CreateInterface;

};


class InterfaceReg {
public:
    char *_name;
    InterfaceReg *_next;
    void *_createFn();
};


#endif //RESPECTRAL_MODULE_H
