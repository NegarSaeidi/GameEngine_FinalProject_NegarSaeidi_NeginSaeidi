#include "GameState.hpp"
#include "Game.hpp"
GameState::GameState(StateStack* stack, Context* context)
	:State(stack, context)
	, mWorld(this)
	, mPauseSceneGraph(new SceneNode(this))
{
	CreateScene();
}

void GameState::draw()
{
	mWorld.draw();
}



bool GameState::update(const GameTimer& gt)
{
	ProcessInput();
	mWorld.update(gt);
	return true;
}

bool GameState::handleEvent(WPARAM btnState)
{
#pragma region step 1
	if (btnState == 'P')
	{
		requestStackPush(States::Pause);
	}
#pragma endregion
	return true;
}
void GameState::ProcessInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();
	getContext()->player->handleEvent(commands);
	getContext()->player->handleRealtimeInput(commands);
}
void GameState::CreateScene()
{
	getContext()->game->BuildMaterials();
	mWorld.buildScene();
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this, "Desert"));
	backgroundSprite->setPosition(0, 0.5, 0);
	backgroundSprite->setScale(4, 2.0, 2);
	backgroundSprite->setVelocity(0, 0, 0);
	mPauseSceneGraph->attachChild(std::move(backgroundSprite));
	mPauseSceneGraph->build();



	getContext()->game->ClearFrameResources();
	getContext()->game->BuildFrameResources(mAllRitems.size());
}
