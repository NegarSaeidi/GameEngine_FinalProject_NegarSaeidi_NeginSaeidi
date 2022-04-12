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
	mArrow->setPosition(mOptions[mOptionIndex]->getWorldPosition().x - 0.7
		, mOptions[mOptionIndex]->getWorldPosition().y
		, mOptions[mOptionIndex]->getWorldPosition().z + 1.4);
}

void MenuState::draw()
{
	mSceneGraph->draw();
}

bool MenuState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);



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
	mArrow->setPosition(mOptions[mOptionIndex]->getWorldPosition().x - 0.7
		, mOptions[mOptionIndex]->getWorldPosition().y
		, mOptions[mOptionIndex]->getWorldPosition().z + 1.4);
}

void MenuState::CreateScene()
{
	getContext()->game->BuildMaterials();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this, "TitleBackground"));
	backgroundSprite->setPosition(0, 0, 0);
	backgroundSprite->setScale(12, 4, 8.5);
	backgroundSprite->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> PlaySprite(new SpriteNode(this, "MenuPlay"));
	mPlay = PlaySprite.get();
	mPlay->setPosition(0, 1, -0.4);
	mPlay->setScale(4 ,1, 3);
	mPlay->setVelocity(0, 0, 0);
    mSceneGraph->attachChild(std::move(PlaySprite));
    mOptions.push_back(mPlay);

	std::unique_ptr<SpriteNode> QuitSprite(new SpriteNode(this, "MenuQuit"));
	mQuit = QuitSprite.get();
	mQuit->setPosition(0 ,1, -1.3);
	mQuit->setScale(4, 1, 3);
	mQuit->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(QuitSprite));
	mOptions.push_back(mQuit);

	std::unique_ptr<SpriteNode> menuArrowSprite(new SpriteNode(this, "Airplane"));
	mArrow= menuArrowSprite.get();
	mArrow->setPosition(-0.5, 0.1, 0.0);
	mArrow->setScale(0.5f, 1.0f, 0.5f);
	mArrow->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(menuArrowSprite));

	mSceneGraph->build();
	getContext()->game->ClearFrameResources();
	getContext()->game->BuildFrameResources(mAllRitems.size());

	
	


	//TODO: Add arrow sprite



}
