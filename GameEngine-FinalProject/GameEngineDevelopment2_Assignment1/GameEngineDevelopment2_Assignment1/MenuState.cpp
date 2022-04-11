#include "MenuState.hpp"
#include "Game.hpp"

MenuState::MenuState(StateStack* stack, Context* context)
	: State(stack, context)
	, mOptionIndex(0)
	, mBackgroundSprite(nullptr)
	, mPlay(nullptr)
	, mQuit(nullptr)
	/*, mArrow(nullptr)*/
{
	CreateScene();
}

void MenuState::draw()
{
	mSceneGraph->draw();
}

bool MenuState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	//float x = mOptions[mOptionIndex]->getWorldPosition().x - 0.9;
	//float y = mOptions[mOptionIndex]->getWorldPosition().y;
	//float z = mOptions[mOptionIndex]->getWorldPosition().z;

	//mArrow->setPosition(x, y, z);

	return true;
	
}

bool MenuState::handleEvent(WPARAM btnState)
{
	if (btnState == VK_RETURN)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == Exit)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}
	else if (btnState == VK_UP)
	{
		// Decrement and wrap-around
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}
	else if (btnState == VK_DOWN)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}
	else
	{
		return false;
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;
}

void MenuState::CreateScene()
{
	getContext()->game->BuildMaterials();
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this, "Desert"));
	backgroundSprite->setPosition(0, 0, 0);
	backgroundSprite->setScale(12, 1, 10);
	backgroundSprite->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));



	std::unique_ptr<SpriteNode> QuitSprite(new SpriteNode(this, "Raptor"));
	mQuit = QuitSprite.get();
	mQuit->setPosition(0 ,1, 1);
	mQuit->setScale(1, 1, 1);
	mQuit->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(QuitSprite));
	mOptions.push_back(mQuit);

	std::unique_ptr<SpriteNode> PlaySprite(new SpriteNode(this, "Eagle"));
	mPlay = PlaySprite.get();
	mPlay->setPosition(0, 1, -1);
	mPlay->setScale(1 ,1, 1);
	mPlay->setVelocity(0, 0, 0);
    mSceneGraph->attachChild(std::move(PlaySprite));
    mOptions.push_back(mPlay);


	mSceneGraph->build();
	getContext()->game->ClearFrameResources();
	getContext()->game->BuildFrameResources(mAllRitems.size());

	
	


	//TODO: Add arrow sprite



}
