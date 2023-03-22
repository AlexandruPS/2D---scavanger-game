#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "TransformComponent.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>

//10:02
Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,1600,900 };



bool Game::isRunning = false; 
bool arr[3] = { 0,0,0 };
bool ok = 0, okquiz[3] = {0,0,0}; 
bool okq = 0;
auto& Player(manager.addEntity());
bool answer;
int startq = 0, Books = 0, intrebari[5] = {0}, corect = 0;



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
		std::cout << "You started the game! Find the info panel for further instructions. " << std::endl;

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
	
	map = new Map("Assets/terrain_ss3.png",3,32);
	
	//char path[200];
	//strcpy_s(path, sizeof("Assets/p16x16.map"), "Assets/p16x16.map");
	map->LoadMap("Assets/map.map", 25, 20);
	//strcpy_s(path, sizeof("Assets/p16x16.map"), "Assets/p16x16.map")

	Player.addComponent<TransformComponent>(2);
	Player.addComponent<SpriteComponent>("Assets/finalAnimation.png", true);
	//Player.addComponent<SpriteComponent>("Assets/playerAnimation2.png", true);
	Player.addComponent<KeyboardController>();
	Player.addComponent<ColliderComponent>("Player");
	Player.addGroup(groupPlayers);


}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& Colliders(manager.getGroup(Game::groupColliders));

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
	SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = Player.getComponent<TransformComponent>().position;
	Vector2D Qpos;
	manager.refresh();
	manager.update();

	for (auto& c : Colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			Player.getComponent<TransformComponent>().position = playerPos;
			Qpos = playerPos;
		}

		int x = rand() % 6;

		if (Qpos.x >= 1570 && Qpos.x <= 1726 && Qpos.y >= 706 && Qpos.y <= 862 && okq == 0)
		{
			std::cout << "To get to the final quiz, you need to collect the three hidden books on the map!" << std::endl;
			ok = 1;
			okq = 1;
		}

		if (Qpos.x >= 1570 && Qpos.x <= 1681 && Qpos.y >= 1282 && Qpos.y <= 1372 && arr[0] == 0 && ok == 1) // BOOK 1
		{
			system("cls");
			Books++;
			std::cout << "INFORMATION :	The main traits of a project: The unique result, time limit, goal oriented." << std::endl;
			std::cout << "INFORMATION :	The document on which you should elaborate further project planning should be Project Charter. " << Books << "/3 FOUND !!" << std::endl;
			arr[0] = 1;
		}
		else
			if (Qpos.x >= 1570 && Qpos.x <= 1681 && Qpos.y >= 1282 && Qpos.y <= 1372 && arr[0] == 0 && okquiz[0] == 0)
			{
				std::cout << "You need to go to the quiz zone first !!" << std::endl;
				okquiz[0] = 1;
			}

		if (Qpos.x >= 2050 && Qpos.x <= 2206 && Qpos.y >= 1090 && Qpos.y <= 1246 && arr[1] == 0 && ok == 1) // BOOK 2
		{
			system("cls");
			Books++;
			std::cout << "INFORMATION :	A project scope should include the following : Project charter, organizational process assets, requirements documentation" << std::endl;
			std::cout << "INFORMATION :	Selecting the best method for creating the project from different ways of executing and performing the deliverable is called Alternative Identification. " << Books << "/3 FOUND !!" << std::endl;
			arr[1] = 1;
		}
		else
			if (Qpos.x >= 2050 && Qpos.x <= 2206 && Qpos.y >= 1090 && Qpos.y <= 1246 && arr[1] == 0 && okquiz[1] == 0)
			{
				std::cout << "You need to go to the quiz zone first !!" << std::endl;
				okquiz[1] = 1;
			}
		if (Qpos.x >= 1954 && Qpos.x <= 2110 && Qpos.y >= 322 && Qpos.y <= 478 && arr[2] == 0 && ok == 1) // BOOK 3
		{
			system("cls");
			Books++;
			std::cout << "INFORMATION :	Work Breakdown Structures are, according to current PMI standards, Deliverable-oriented. "<<Books<<"/3 FOUND !!" << std::endl;
			arr[2] = 1;
		}
		else
			if (Qpos.x >= 1954 && Qpos.x <= 2110 && Qpos.y >= 322 && Qpos.y <= 478 && arr[2] == 0 && okquiz[2] == 0)
			{
				std::cout << "You need to go to the quiz zone first !!" << std::endl;
				okquiz[2] = 1;
			}

		if (arr[0] == 1 && arr[1] == 1 && arr[2] == 1 && startq == 0)
		{
			std::cout <<std::endl<< "You can take the quiz!! Go back to the info panel to start the quiz!" << std::endl<<std::endl;
			arr[0] == 0;
			startq = 1;
		}
		char answ1[25],answ2[25],answ3[25];

		if (startq == 1 && Qpos.x >= 1570 && Qpos.x <= 1726 && Qpos.y >= 706 && Qpos.y <= 862)
		{

			int a = rand() % 5;
			int x = (a+1)%5;
			if (x == 0 && intrebari[x] == 0)
			{
				std::cout << " The main traits of a project are:" << std::endl << "			A.Ongoing activity to create product, service or result."
					<< std::endl << "			B.The unique result, time limit, goal - oriented."
					<< std::endl << "			C.A project manager, project team, stakeholders"
					<< std::endl << "			D.Contractand SLA."
					<< std::endl;
				std::cin >> answ1;
				intrebari[x] = 1;
			}

			if (x == 1 && intrebari[x] == 0)
			{
				std::cout << " Based on which document should you elaborate on further project planning?" << std::endl << "			A. Statement of Work"
					<< std::endl << "			B. Stakeholder Register"
					<< std::endl << "			C. Requirements Traceability Matrix"
					<< std::endl << "			D. Project Charter"
					<< std::endl;
				std::cin >> answ1;
				intrebari[x] = 1;
			}

			if (x == 2 && intrebari[x] == 0)
			{
				std::cout << " Which one of the following is not needed to define the project scope?" << std::endl << "			A. Project charter"
					<< std::endl << "			B. Organizational process assets"
					<< std::endl << "			C. Risk management plan"
					<< std::endl << "			D. Requirements documentation"
					<< std::endl;
				std::cin >> answ1;
				intrebari[x] = 1;
			}

			if (x == 3 && intrebari[x] == 0)
			{
				std::cout << " You are working on project scope statement of a software project. You are analyzing the expected deliverables by generating different ways of executing and performing the deliverable. You select the best method for creating that deliverable. Which of the following describes what you are doing?" << std::endl << "			A.Decomposition"
					<< std::endl << "			B.Alternative Identification "
					<< std::endl << "			C.Scope definition"
					<< std::endl << "			D.Stakeholder Analysis"
					<< std::endl;
				std::cin >> answ1;
				intrebari[x] = 1;
			}

			if (x == 4 && intrebari[x] == 0)
			{
				std::cout << " According to current PMI standards, Work Breakdown Structures, are:" << std::endl << "			A.Task-oriented"
					<< std::endl << "			B.Process-oriented "
					<< std::endl << "			C.Deliverable-oriented"
					<< std::endl << "			D.Time-oriented"
					<< std::endl;
				std::cin >> answ1;
				intrebari[x] = 1;
			}

			int y = (a + 2) % 5;
			if (y == 0 && intrebari[y] == 0)
			{
				std::cout << " The main traits of a project are:" << std::endl << "			A.Ongoing activity to create product, service or result."
					<< std::endl << "			B.The unique result, time limit, goal - oriented."
					<< std::endl << "			C.A project manager, project team, stakeholders"
					<< std::endl << "			D.Contractand SLA."
					<< std::endl;
				std::cin >> answ2;
				intrebari[y] = 1;
			}

			if (y == 1 && intrebari[y] == 0)
			{
				std::cout << " Based on which document should you elaborate on further project planning?" << std::endl << "			A. Statement of Work"
					<< std::endl << "			B. Stakeholder Register"
					<< std::endl << "			C. Requirements Traceability Matrix"
					<< std::endl << "			D. Project Charter"
					<< std::endl;
				std::cin >> answ2;
				intrebari[y] = 1;
			}

			if (y == 2 && intrebari[y] == 0)
			{
				std::cout << " Which one of the following is not needed to define the project scope?" << std::endl << "			A. Project charter"
					<< std::endl << "			B. Organizational process assets"
					<< std::endl << "			C. Risk management plan"
					<< std::endl << "			D. Requirements documentation"
					<< std::endl;
				std::cin >> answ2;
				intrebari[y] = 1;
			}

			if (y == 3 && intrebari[y] == 0)
			{
				std::cout << " You are working on project scope statement of a software project. You are analyzing the expected deliverables by generating different ways of executing and performing the deliverable. You select the best method for creating that deliverable. Which of the following describes what you are doing?" << std::endl << "			A.Decomposition"
					<< std::endl << "			B.Alternative Identification "
					<< std::endl << "			C.Scope definition"
					<< std::endl << "			D.Stakeholder Analysis"
					<< std::endl;
				std::cin >> answ2;
				intrebari[y] = 1;
			}

			if (y == 4 && intrebari[y] == 0)
			{
				std::cout << " According to current PMI standards, Work Breakdown Structures, are:" << std::endl << "			A.Task-oriented"
					<< std::endl << "			B.Process-oriented "
					<< std::endl << "			C.Deliverable-oriented"
					<< std::endl << "			D.Time-oriented"
					<< std::endl;
				std::cin >> answ2;
				intrebari[y] = 1;
			}
			int z = (a + 3) % 5;
			if (z == 0 && intrebari[z] == 0)
			{
				std::cout << " The main traits of a project are:" << std::endl << "			A.Ongoing activity to create product, service or result."
					<< std::endl << "			B.The unique result, time limit, goal - oriented."
					<< std::endl << "			C.A project manager, project team, stakeholders"
					<< std::endl << "			D.Contractand SLA."
					<< std::endl;
				std::cin >> answ3;
				intrebari[z] = 1;
			}

			if (z == 1 && intrebari[z] == 0)
			{
				std::cout << " Based on which document should you elaborate on further project planning?" << std::endl << "			A. Statement of Work"
					<< std::endl << "			B. Stakeholder Register"
					<< std::endl << "			C. Requirements Traceability Matrix"
					<< std::endl << "			D. Project Charter"
					<< std::endl;
				std::cin >> answ3;
				intrebari[z] = 1;
			}

			if (z == 2 && intrebari[z] == 0)
			{
				std::cout << " Which one of the following is not needed to define the project scope?" << std::endl << "			A. Project charter"
					<< std::endl << "			B. Organizational process assets"
					<< std::endl << "			C. Risk management plan"
					<< std::endl << "			D. Requirements documentation"
					<< std::endl;
				std::cin >> answ3;
				intrebari[z] = 1;
			}

			if (z == 3 && intrebari[z] == 0)
			{
				std::cout << " You are working on project scope statement of a software project. You are analyzing the expected deliverables by generating different ways of executing and performing the deliverable. You select the best method for creating that deliverable. Which of the following describes what you are doing?" << std::endl << "			A.Decomposition"
					<< std::endl << "			B.Alternative Identification "
					<< std::endl << "			C.Scope definition"
					<< std::endl << "			D.Stakeholder Analysis"
					<< std::endl;
				std::cin >> answ3;
				intrebari[z] = 1;
			}

			if (z == 4 && intrebari[z] == 0)
			{
				std::cout << " According to current PMI standards, Work Breakdown Structures, are:" << std::endl << "			A.Task-oriented"
					<< std::endl << "			B.Process-oriented "
					<< std::endl << "			C.Deliverable-oriented"
					<< std::endl << "			D.Time-oriented"
					<< std::endl;
				std::cin >> answ3;
				intrebari[z] = 1;
			}


			switch (x)
			{
				case 0 :
					if (strcmp(answ1, "B") == NULL || strcmp(answ1, "b") == NULL)
						corect++;
					break;
				case 1:
					if (strcmp(answ1, "D") == NULL || strcmp(answ1, "d") == NULL)
						corect++;
					break;
				case 2:
					if (strcmp(answ1, "C") == NULL || strcmp(answ1, "c") == NULL)
						corect++;
					break;
				case 3:
					if (strcmp(answ1, "B") == NULL || strcmp(answ1, "b") == NULL)
						corect++;
					break;
				case 4:
					if (strcmp(answ1, "C") == NULL || strcmp(answ1, "c") == NULL)
						corect++;
					break;
			}
			switch (y)
			{
			case 0:
				if (strcmp(answ2, "B") == NULL || strcmp(answ2, "b") == NULL)
					corect++;
				break;
			case 1:
				if (strcmp(answ2, "D") == NULL || strcmp(answ2, "d") == NULL)
					corect++;
				break;
			case 2:
				if (strcmp(answ2, "C") == NULL || strcmp(answ2, "c") == NULL)
					corect++;
				break;
			case 3:
				if (strcmp(answ2, "B") == NULL || strcmp(answ2, "b") == NULL)
					corect++;
				break;
			case 4:
				if (strcmp(answ2, "C") == NULL || strcmp(answ2, "c") == NULL)
					corect++;
				break;
		
		
			}
			switch (z)
			{
			case 0:
				if (strcmp(answ3, "B") == NULL || strcmp(answ3, "b") == NULL)
					corect++;
				break;
			case 1:
				if (strcmp(answ3, "D") == NULL || strcmp(answ3, "d") == NULL)
					corect++;
				break;
			case 2:
				if (strcmp(answ3, "C") == NULL || strcmp(answ3, "c") == NULL)
					corect++;
				break;
			case 3:
				if (strcmp(answ3, "B") == NULL || strcmp(answ3, "b") == NULL)
					corect++;
				break;
			case 4:
				if (strcmp(answ3, "C") == NULL || strcmp(answ3, "c") == NULL)
					corect++;
				break;
			}

			if (corect == 3)
			{
				Game::clean();
				system("cls");
				std::cout << std::endl << std::endl <<"Congratulations! You won the game!!!! You can close this window." <<std::endl;
				startq = 2;
				std::cout << "----------------------------------------------------CREDITS------------------------------------------------" << std::endl << std::endl;
				std::cout << "This application was developed by the following students from University POLITEHNICA" << std::endl;
				std::cout << "Bucharest/Automatic Control & Computer Science Faculty within the Erasmus+ Project" << std::endl;
				std::cout << "2020-1-CZ01-KA226-HE-094408" << std::endl;
				std::cout << "-Panait Alexandru-Sorin" << std::endl;
				std::cout << "-Stoica Roland-Viorel" << std::endl;
				std::cout << "-Stoica Andrei-Roberto" << std::endl;
				std::cout << "-Gheorghe Stefania-Aniela" << std::endl;
				std::cout << "-Padurariu Eduard-Dumitru" << std::endl;
				std::cout << "Teacher: M. Caramihai & Daniel Chis" << std::endl;
				std::cout << "Assets used: Textures made in Pyxel edit" << std::endl;
			}
			else
			{
				Game::clean();
				system("cls");
				std::cout << std::endl << std::endl << "That's a shame! You didn't answer correctly to all of the questions. You lose :(  " << std::endl << std::endl << std::endl;
				startq = 2;
				std::cout << "----------------------------------------------------CREDITS------------------------------------------------" << std::endl << std::endl;
				std::cout << "This application was developed by the following students from University POLITEHNICA" << std::endl;
				std::cout << "Bucharest/Automatic Control & Computer Science Faculty within the Erasmus+ Project" << std::endl;
				std::cout << "2020-1-CZ01-KA226-HE-094408" << std::endl;
				std::cout << "-Panait Alexandru-Sorin" << std::endl;
				std::cout << "-Stoica Roland-Viorel" << std::endl;
				std::cout << "-Stoica Andrei-Roberto" << std::endl;
				std::cout << "-Gheorghe Stefania-Aniela" << std::endl;
				std::cout << "-Padurariu Eduard-Dumitru" << std::endl;
				std::cout << "Teacher: M. Caramihai & Daniel Chis" << std::endl;
				std::cout << "Assets used: Textures made in Pyxel edit" << std::endl;
			}
		}

	}

	

	camera.x = Player.getComponent<TransformComponent>().position.x - 400;
	camera.y = Player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}



void Game::render()
{
	SDL_RenderClear(renderer);
	//manager.draw();
	for (auto& t : tiles)
	{
		t->draw();
	}


	for (auto& p : players)
	{
		p->draw();
	}


	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleaned" << std::endl;
}
