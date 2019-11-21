//
// Created by alex on 11/19/19.
//

#include "MainMenuState.hpp"

void MainMenuState::onStart(ecs::StateData<string>& data)
{
    auto shipTexture = sf::Texture();
    shipTexture.loadFromFile("./assets/r-typesheet24.gif");
    auto shipSprite = sf::Sprite();
    shipSprite.setTexture(shipTexture);
    shipSprite.setPosition(100, 100);

    data.world.writeResource("shipTexture", shipTexture);
    data.world.writeResource("shipSprite", shipSprite);
}

void MainMenuState::onStop(ecs::StateData<string>& data)
{
    cout << "Stopping Main Menu" << endl;
}

void MainMenuState::onPause(ecs::StateData<string>& data)
{
    cout << "Pausing Main Menu" << endl;
}

void MainMenuState::onResume(ecs::StateData<string>& data)
{
    cout << "Resuming Main Menu" << endl;
}

ecs::Transition<string, ecs::Event> MainMenuState::update(ecs::StateData<string>& data)
{
    m_dispatcher->dispatch(make_shared<ecs::StateData<string>>(data));
    return ecs::Transition<string, ecs::Event>();
}

ecs::Transition<string, ecs::Event> MainMenuState::handleEvent(ecs::StateData<string>& data, ecs::Event event)
{
    if (event.isOfType("sfml")) {
        cout << "SFML event found." << endl;
    }
    return ecs::Transition<string, ecs::Event>();
}

ecs::Transition<string, ecs::Event> MainMenuState::fixedUpdate(ecs::StateData<string>& data)
{
    cout << "Fixed update." << endl;
    return ecs::Transition<string, ecs::Event>();
}

void MainMenuState::shadowUpdate(ecs::StateData<string>& data)
{

}

void MainMenuState::shadowFixedUpdate(ecs::StateData<string>& data)
{
    cout << "Shadow fixed update." << endl;
}

MainMenuState::MainMenuState(unique_ptr<ecs::Dispatcher<ecs::StateData<string>, ecs::Error>> dispatcher)
    : AbstractState(move(dispatcher))
{
}
