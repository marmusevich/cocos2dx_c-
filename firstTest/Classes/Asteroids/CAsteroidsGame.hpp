
#ifndef ASTEROIDS_CGAME_SCENE_H
#define ASTEROIDS_CGAME_SCENE_H

#include "cocos2d.h"

class CAsteroidsGame;

/*detals*/
namespace NAsteroids
{
	class CPlayer : public cocos2d::Node
	{
	public:
		//explicit CPlayer(const CAsteroidsGame& parent);
		bool init();

	private:
		cocos2d::Sprite* mShip;
	};
}
//-----------------------------------------------------------------------------------------------------------------------------------------

class CAsteroidsGame : public cocos2d::Scene
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(CAsteroidsGame);
	static cocos2d::Scene* createScene();

	virtual bool init();

private:
	NAsteroids::CPlayer mPlayer;
};

#endif // ASTEROIDS_CGAME_SCENE_H


