//
// Created by emiel on 9/03/21.
//

#ifndef RESPECTRAL_MODULE_H
#define RESPECTRAL_MODULE_H

/**
 * Represents a module loaded in TF2
 */
class Module {
private:
    const char  *_filename;
    void        *_handle;

public:
    Module(const char *filename);
    void *getSymbol(const char* symbolName);
    void close();

};


#endif //RESPECTRAL_MODULE_H
