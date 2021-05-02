//
// Created by emiel on 9/03/21.
//

#ifndef RESPECTRAL_MODULEMANAGER_H
#define RESPECTRAL_MODULEMANAGER_H

#include "Module.h"
/**
 * Singleton class allowing access to loaded tf2 modules
 */
class ModuleManager {
public:
    static Module client();
};


#endif //RESPECTRAL_MODULEMANAGER_H
