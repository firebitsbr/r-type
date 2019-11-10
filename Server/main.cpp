/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>
#include <ostream>
#include <GameServer.hpp>

#ifndef VERSION
    #define VERSION "NOT DEFINED"
#endif

int main(void) {
    std::cout << "Welcome to server V" << VERSION << "." << std::endl;
    auto server = GameServer(8080, "0.0.0.0");

    return server.run();
}
