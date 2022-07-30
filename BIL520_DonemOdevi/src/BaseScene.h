#pragma once
#include "GameScene.h"

class BaseScene : public GameScene {
public:
	using GameScene::GameScene;
	void setup() override;
};