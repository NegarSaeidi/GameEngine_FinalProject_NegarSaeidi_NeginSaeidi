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
