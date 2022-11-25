#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

//10:02
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

std::vector<ColliderComponent*> Game::colliders;


auto& Player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game()
{}
Game :: ~Game()
{}

void Game :: init(const char* title, int xpos, int ypos, int width, int heigh, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!.." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, heigh,flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	
	map = new Map();

	tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("Dirt");
	tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("Grass");

	Player.addComponent<TransformComponent>(2);
	Player.addComponent<SpriteComponent>("Assets/Player.png");
	Player.addComponent<KeyboardController>();
	Player.addComponent<ColliderComponent>("Player");
	
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("Assets/Dirt.png");
	wall.addComponent<ColliderComponent>("wall");

	

}

void Game  :: handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}

}

void Game :: update()
{ 
	manager.refresh();
	manager.update();
	for (auto cc : colliders)
	{
		Collision::AABB(Player.getComponent<ColliderComponent>(), *cc);
		
	}
	
}
void Game::render()
{
	SDL_RenderClear(renderer);
	// aici adaugam lucruri de randat
	//map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleaned" << std::endl;
}