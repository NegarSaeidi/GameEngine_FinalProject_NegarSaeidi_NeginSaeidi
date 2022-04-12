/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// World.cpp
-------------------------------------------------------------------------*/
#define NOMINMAX

#include "World.hpp"
#include "State.hpp"
World::World(State* state)
	: mState(state)
	, mSceneGraph(new SceneNode(state))
	, mPlayerAircraft(nullptr)
	, mSceneLayers()
	, mWorldBounds(-4.7f, 4.7f, -3.5f, 4.f)
	, mSpawnPostion(0.0f, 0.0f)
	, mScrollSpeed(-1.f)
{

}
/**
 * Updates the scene graph, calls the update function of eahc scene node
 *@param const GameTimer& gt
 * @return void
 */
void World::update(const GameTimer& gt)
{
	for (int i = 0; i < 5; i++)
	{

		mBackground[i]->move(0.f, 0, mScrollSpeed * gt.DeltaTime());
	}
	
	mPlayerAircraft->setVelocity(0.0f, 0.0f, 0.0f);
	adaptPlayerPosition();

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);

	//adaptPlayerVelocity();

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph->update(gt);

}

void World::draw()
{
	mSceneGraph->draw();
}
/**
 * builds the game scene, creates scene nodes and adds the m to the scene graph
 *@param void
 * @return void
 */
void World::buildScene()
{
	mSceneGraph->ClearChildren();

	std::unique_ptr<Aircraft> aircraft(new Aircraft(Aircraft::Eagle, mState));
	mPlayerAircraft = aircraft.get();
	mPlayerAircraft->setPosition(0, 0.1, -2.0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	mPlayerAircraft->setVelocity(1, 0.0001, 0);
	mSceneGraph->attachChild(std::move(aircraft));



	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mState));
	auto raptor = enemy1.get();
	raptor->setPosition(0.9, 0.2, -1.0);
	raptor->setScale(1, 1, 1);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mState));
	auto raptor1 = enemy2.get();
	raptor1->setPosition(-0.9, 0.2, -1.0);
	raptor1->setScale(1, 1, 1);

	mPlayerAircraft->attachChild(std::move(enemy2));

	for (int i = 0; i < 5; i++)
	{

		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mState));
		mBackground[i] = backgroundSprite.get();
		mBackground[i]->setPosition(0, 0, i*10);
		mBackground[i]->setScale(15, 1, 10);
		mSceneGraph->attachChild(std::move(backgroundSprite));
	}
	
	mSceneGraph->build();

}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}
World::~World()
{
}
#pragma region step 4

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border

	const float borderDistance = 100.f;

	XMFLOAT3 position = mPlayerAircraft->getWorldPosition();
	position.x = MathHelper::Clamp(position.x, mWorldBounds.x, mWorldBounds.y);
	position.y = MathHelper::Clamp(position.y, -0.9f, 3.0f);
	position.z = MathHelper::Clamp(position.z, mWorldBounds.z, mWorldBounds.w);
	mPlayerAircraft->setPosition(position.x, position.y, position.z);

	

}

void World::adaptPlayerVelocity()
{
	XMFLOAT3 velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f && velocity.z != 0)
		mPlayerAircraft->setVelocity(velocity.x / std::sqrt(2.f), velocity.y / std::sqrt(2.f), velocity.z / std::sqrt(2.f));

	// Add scrolling velocity
//	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}

#pragma endregion

