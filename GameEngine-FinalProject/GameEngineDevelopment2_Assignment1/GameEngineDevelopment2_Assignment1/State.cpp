#include "State.hpp"
#include "StateStack.hpp"


State::Context::Context( Player* player, Game* game)
	: player(player),
	game(game)
{
}

State::State(StateStack* stack, Context* context)
	: mStack(stack)
	, mContext(context)
	, mSceneGraph(new SceneNode(this))
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context* State::getContext() const
{
	return mContext;
}
