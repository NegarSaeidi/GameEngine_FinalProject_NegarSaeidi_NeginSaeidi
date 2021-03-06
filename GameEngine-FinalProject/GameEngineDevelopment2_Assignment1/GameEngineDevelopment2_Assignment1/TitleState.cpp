/*
-------------------------------------------------------------------------
//Final Assignment
// author : Negar Saeidi - 101261396  and  NeginSaeidi - 101261395
//TitleState.cpp
//Creates the title screen of the game
*/

#include "TitleState.hpp"
#include "World.hpp"
#include "Game.hpp"
/**
 * Constructor(Initializes the variables of the class
 *@param StateStack* stack, Context* context
 * @return None
 */
TitleState::TitleState(StateStack* stack, Context* context)
	: State(stack, context)

{
	CreateScene();
}
/**
 * Draws the title scene
 *@param None
 * @return void
 */
void TitleState::draw()
{
	mSceneGraph->draw();
}
/**
 * updates the scene accordingly
 *@param const GameTimer& gt
 * @return bool
 */
bool TitleState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);
	

	return true;
}
/**
 * handles any input by player(if any key pressed -> go to menu)
 *@param WPARAM btnState
 * @return bool
 */
bool TitleState::handleEvent(WPARAM btnState)
{
	
		requestStackPop();
		
		requestStackPush(States::Menu);
	
	return true;
}
/**
 *Creates the title screen( background, title)
 *@param None
 * @return void
 */
void TitleState::CreateScene()
{
	getContext()->game->BuildMaterials();
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this, "TitleBackground"));
	backgroundSprite->setPosition(0, 0, 0);
	backgroundSprite->setScale(12, 4, 8.5);
	backgroundSprite->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	
	
	std::unique_ptr<SpriteNode> TitleScreenPrompt(new SpriteNode(this, "TitlePrompt"));
	//mPrompt = TitlePrompt.get();
	TitleScreenPrompt->setPosition(0, 0.1, -0.5);
	TitleScreenPrompt->setScale(4.5, 1.0, 3);
	TitleScreenPrompt->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(TitleScreenPrompt));

	mSceneGraph->build();
	getContext()->game->ClearFrameResources();
	getContext()->game->BuildFrameResources(mAllRitems.size());
}
