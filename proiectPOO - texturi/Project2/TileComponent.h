#pragma once


#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
	public:

		TransformComponent* transform;
		SpriteComponent* sprite;

		SDL_Rect tileRect;
		int tileID;
		char path[20];

		TileComponent() = default;

		TileComponent(int x, int y, int w, int h, int id)
		{
			tileRect.x = x;
			tileRect.y = y;
			tileRect.w = w;
			tileRect.h = h;
			tileID = id;

			switch (tileID)
			{
			case 0:
				strcpy_s(path,sizeof("Assets/Water.png"), "Assets/Water.png");
				break;

			case 1:
				strcpy_s(path, sizeof("Assets/Dirt.png"),"Assets/Dirt.png");
				break;
			case 2:
				strcpy_s(path,sizeof("Assets/Grass.png"), "Assets/Grass.png");
				break;

			default:
				break;
			}

		}

		void init() override
		{
			entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
			transform = &entity->getComponent<TransformComponent>();

			entity->addComponent<SpriteComponent>(path);
			sprite = &entity->getComponent<SpriteComponent>();
		}
};
