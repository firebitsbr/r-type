//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_ISERIALIZE_HPP
#define CPP_RTYPE_2019_ISERIALIZE_HPP

#include <vector>
#include "Definitions.hpp"
using namespace std;

class ISerialize {
public:
    virtual ~ISerialize() = default;
    virtual void *serialize(size_t &size) const = 0;
};

class IDeserialize {
public:
    virtual ~IDeserialize() = default;
    IDeserialize(void *data, size_t size) {};
};

#endif //CPP_RTYPE_2019_ISERIALIZE_HPP
