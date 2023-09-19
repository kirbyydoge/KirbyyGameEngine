#pragma once
#include "GameScene.h"

class Game;

class BaseScene : public GameScene {
public:
	using GameScene::GameScene;
	void setup() override;
};