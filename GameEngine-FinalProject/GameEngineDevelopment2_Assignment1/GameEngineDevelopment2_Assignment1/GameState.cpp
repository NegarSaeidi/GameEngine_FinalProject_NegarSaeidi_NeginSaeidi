/*
-------------------------------------------------------------------------
//Final Assignment
// author : Negar Saeidi - 101261396  and  NeginSaeidi - 101261395
//GameState.cpp
//Creates the Game world
*/
#include "GameState.hpp"
#include "Game.hpp"
/**
 * Constructor(Initializes the variables of the class
 *@param StateStack* stack, Context* context
 * @return None
 */
GameState::GameState(StateStack* stack, Context* context)
	:State(stack, context)
	, mWorld(this)
	, mPauseSceneGraph(new SceneNode(this))
{
	CreateScene();
}
/**
 * Draws the world
 *@param None
 * @return void
 */
void GameState::draw()
{
	mWorld.draw();
}

/**
 * Calls processInput function to handle any input by player and updates the world accordingly
 *@param const GameTimer& gt
 * @return bool
 */

bool GameState::update(const GameTimer& gt)
{
	ProcessInput();
	mWorld.update(gt);
	return true;
}
/**
 * handles any input by player(if P pressed -> pause the game_
 *@param WPARAM btnState
 * @return bool
 */

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
/**
 *  handle any input by player 
 *@param None
 * @return void
 */
void GameState::ProcessInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();
	getContext()->player->handleEvent(commands);
	getContext()->player->handleRealtimeInput(commands);
}
/**
 *Creates the pause panel
 *@param None
 * @return void
 */
void GameState::CreateScene()
{
	getContext()->game->BuildMaterials();
	mWorld.buildScene();
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this, "PausePrompt"));
	backgroundSprite->setPosition(0, 0.5, 0);
	backgroundSprite->setScale(8, 2.0, 6);
	backgroundSprite->setVelocity(0, 0, 0);
	mPauseSceneGraph->attachChild(std::move(backgroundSprite));

	
	mPauseSceneGraph->build();



	getContext()->game->ClearFrameResources();
	getContext()->game->BuildFrameResources(mAllRitems.size());
}
