#include "TitleState.hpp"
#include "World.hpp"
#include "Game.hpp"

TitleState::TitleState(StateStack* stack, Context* context)
	: State(stack, context)

{
	CreateScene();
}

void TitleState::draw()
{
	mSceneGraph->draw();
}

bool TitleState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);
	

	return true;
}

bool TitleState::handleEvent(WPARAM btnState)
{
	
		requestStackPop();
		
		requestStackPush(States::Menu);
	
	return true;
}

void TitleState::CreateScene()
{
	getContext()->game->BuildMaterials();
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this, "Desert"));
	backgroundSprite->setPosition(0, 0, 0);
	backgroundSprite->setScale(12, 4, 10);
	backgroundSprite->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	
	
	

	mSceneGraph->build();
	getContext()->game->ClearFrameResources();
	getContext()->game->BuildFrameResources(mAllRitems.size());
}
