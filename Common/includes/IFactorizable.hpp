//
// Created by nwmqpa on 12/11/2019
//

#pragma once

#include <any>
#include "Definitions.hpp"

template<typename To, typename From>
Box<To> static_unique_pointer_cast(Box<From>&& old){
    To *ptr = dynamic_cast<To *>(old.get());
    if (ptr == nullptr) {
        return Box<To>(nullptr);
    }
    old.release();
    return Box<To>(ptr);
}

template<typename T>
class IFactorizable {
    public:
        virtual ~IFactorizable() = default;
        virtual Box<IFactorizable> copy() const = 0;
        virtual T getKey() const = 0;

};
