#pragma region step 3
#include "PauseState.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "State.hpp"
PauseState::PauseState(StateStack* stack, Context* context)
	:State(stack, context)
{
	CreateScene();
}

void PauseState::draw()
{
	((GameState*)((*mStack->GetStateStack())[0].get()))->mPauseSceneGraph->draw();
}

bool PauseState::update(const GameTimer& gt)
{
	((GameState*)((*mStack->GetStateStack())[0].get()))->mPauseSceneGraph->update(gt);
	return false;
}

bool PauseState::handleEvent(WPARAM btnState)
{
	if (btnState == 'Q')
	{
		requestStackPop();
	}
	else if (btnState == VK_BACK)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	return false;
}

void PauseState::CreateScene()
{

}
#pragma endregion
