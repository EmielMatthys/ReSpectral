//
// Created by emiel on 2/05/21.
//

#ifndef RESPECTRAL_GETVFUNC_H
#define RESPECTRAL_GETVFUNC_H

//Credits: Casual_Hacker

#include <cstddef>

inline void**& getvtable(void* inst, size_t offset = 0 )
{
    return *reinterpret_cast<void***>( (size_t)inst + offset );
}
inline const void** getvtable( const void* inst, size_t offset = 0 )
{
    return *reinterpret_cast<const void***>( (size_t)inst + offset );
}
template< typename Fn >
inline Fn getvfunc( void* inst, size_t index, size_t offset = 0 )
{
    return reinterpret_cast<Fn>( getvtable( inst, offset )[ index ] );
}
//===================================================================================

#endif //RESPECTRAL_GETVFUNC_H
