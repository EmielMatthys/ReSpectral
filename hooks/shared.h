//
// Created by emiel on 18/05/21.
//

#ifndef RESPECTRAL_SHARED_H
#define RESPECTRAL_SHARED_H

#define DECLARE_HOOK(index,ret,name,header) static const int name ## _index = index;\
                                            typedef ret (* name ## _fn) header ; \
                                            name ## _fn original_ ## name ; \
                                            ret name header

#define INSTANTIATE_HOOK(instance, funcname) \
hooks::original_ ## funcname = \
        (hooks::funcname ## _fn) vtablehook_hook(instance, (void*) hooks::funcname, hooks::funcname ## _index)

#endif //RESPECTRAL_SHARED_H
