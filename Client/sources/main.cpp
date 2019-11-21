/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#ifndef VERSION
#define VERSION "NOT DEFINED"
#endif

#include "DrawSystem.hpp"
#include "MainMenuState.hpp"
#include "StateMachine.hpp"
#include "World.hpp"
#include <iostream>
#include <memory>
#include "MovementSystem.hpp"

shared_ptr<ecs::World> initializeWorld()
{
    auto world = make_shared<ecs::World>();
    auto pool = new ecs::ThreadPool<ecs::StateData<string>, ecs::Error>();
    world->writeResource("threadPool", pool);
    world->writeResource("transitionQueue", new deque<ecs::Transition<ecs::StateData<string>>>());
    world->writeResource<DrawSystem>("menuState");
    world->fetchResource<DrawSystem>("menuState");
    return world;
}

unique_ptr<ecs::AbstractState<string>> initializeMainMenu(ecs::World& world)
{
    auto pool = world.fetchResource<ecs::ThreadPool<ecs::StateData<string>, ecs::Error>*>("threadPool");
    auto dispatcher = make_unique<ecs::Dispatcher<ecs::StateData<string>, ecs::Error>>(*pool);
    auto state = make_unique<MainMenuState>(move(dispatcher));
    state->registerSystem<DrawSystem>();
    state->registerSystem<MovementSystem>();
    return state;
}

int main(int argc, char* argv[])
{
    auto world = initializeWorld();
    auto initialState = initializeMainMenu(*world);
    ecs::StateMachine states(move(initialState), world);

    states.run("test");
    return 0;
}
