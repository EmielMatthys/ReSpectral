//
// Created by emiel on 3/05/21.
//

#ifndef RESPECTRAL_HEXDUMP_H
#define RESPECTRAL_HEXDUMP_H

#include <cctype>
#include <iomanip>
#include <ostream>

template <unsigned RowSize, bool ShowAscii>
struct CustomHexdump
{
    CustomHexdump(void* data, unsigned length) :
            mData(static_cast<unsigned char*>(data)), mLength(length) { }
    const unsigned char* mData;
    const unsigned mLength;
};

template <unsigned RowSize, bool ShowAscii>
std::ostream& operator<<(std::ostream& out, const CustomHexdump<RowSize, ShowAscii>& dump)
{
    out.fill('0');
    for (int i = 0; i < dump.mLength; i += RowSize)
    {
        out << "0x" << std::setw(6) << std::hex << i << ": ";
        for (int j = 0; j < RowSize; ++j)
        {
            if (i + j < dump.mLength)
            {
                out << std::hex << std::setw(2) << static_cast<int>(dump.mData[i + j]) << " ";
            }
            else
            {
                out << "   ";
            }
        }

        out << " ";
        if (ShowAscii)
        {
            for (int j = 0; j < RowSize; ++j)
            {
                if (i + j < dump.mLength)
                {
                    if (std::isprint(dump.mData[i + j]))
                    {
                        out << static_cast<char>(dump.mData[i + j]);
                    }
                    else
                    {
                        out << ".";
                    }
                }
            }
        }
        out << std::endl;
    }
    return out;
}

typedef CustomHexdump<16, true> Hexdump;
#endif //RESPECTRAL_HEXDUMP_H
