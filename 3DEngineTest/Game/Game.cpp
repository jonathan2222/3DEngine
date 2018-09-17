#include "Game.h"

#include "S3DE\Utils\Error.h"

Game::Game() : IGame()
{
}

Game::Game(const std::string & title, unsigned int width, unsigned int height) : IGame(title, width, height)
{
}

Game::~Game()
{
}

void Game::OnInitiate()
{
}

void Game::OnFrameUpdate()
{
}
