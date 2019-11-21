//
// Created by alex on 11/8/19.
//

#pragma once

#include <vector>
#include <string>
#include "Definitions.hpp"
#include "Entity.hpp"
#include "IEntityComponentStorage.hpp"
#include "StopWatch.hpp"
#include <iostream>

namespace ecs {

using namespace std;

using Id = size_t;

class World {
public:
    //explicit World(unique_ptr<IEntityComponentStorage> database);
    World() = default;
    ~World() = default;

    void createEntity();

    void registerComponent(string schema);

    Entity* fetchEntity(const string& name);

    template<typename T>
    T& fetchResource(const string& name)
    {
        return any_cast<T&>(m_resources.at(name));
    }

    template<typename T>
    void writeResource(const string& name, const T data)
    {
        m_resources[name] = data;
    }

    template<typename T>
    void writeResource(const string& name)
    {
        static_assert(is_default_constructible<T>::value, "To write a resource without argument the class need to implement a default constructor.");
        m_resources[name] = T();
    }

    template<typename T, typename... Args>
    void writeResource(const string& name, Args&&... args)
    {
        static_assert(is_constructible<T>::value, "To write a resource it need to be constructible.");
        m_resources[name] = T{forward<Args>(args)...};
    }

    StopWatch m_timer;
private:
    unique_ptr<IEntityComponentStorage> database;
    unordered_map<string, any> m_resources;
    unordered_map<string, any> m_components;
};

}
