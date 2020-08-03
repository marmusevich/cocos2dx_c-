// see : https://www.raywenderlich.com/2728-cocos2d-x-tutorial-for-ios-and-android-space-game
//


#ifndef SPACEGAME_CSPACEGAME_SCENE_H
#define SPACEGAME_CSPACEGAME_SCENE_H

#include "cocos2d.h"


class CSpaceGame : public cocos2d::Scene
{
	CSpaceGame() {}

public:
	// implement the "static create()" method manually
	CREATE_FUNC(CSpaceGame);

	static cocos2d::Scene* createScene();

	virtual bool init();

private:

	void menuCloseCallback(cocos2d::Ref* pSender);
	bool addCloseButton(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
	bool addShip(const cocos2d::Size& visibleSize);
	bool addBackgrund(const cocos2d::Size& visibleSize);

	//------------------------------------------
	cocos2d::SpriteBatchNode* m_batchNode;
	cocos2d::Sprite* m_ship;

	cocos2d::ParallaxNode* m_backgroundNode;
	cocos2d::Sprite* m_spaceDust1;
	cocos2d::Sprite* m_spaceDust2;
	cocos2d::Sprite* m_planetSunrise;
	cocos2d::Sprite* m_galaxy;
	cocos2d::Sprite* m_spatialAnomaly1;
	cocos2d::Sprite* m_spatialAnomaly2;



};

#endif // SPACEGAME_CSPACEGAME_SCENE_H


