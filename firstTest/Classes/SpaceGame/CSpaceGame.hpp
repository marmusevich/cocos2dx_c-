// see : https://www.raywenderlich.com/2728-cocos2d-x-tutorial-for-ios-and-android-space-game
//


#ifndef SPACEGAME_CSPACEGAME_SCENE_H
#define SPACEGAME_CSPACEGAME_SCENE_H

#include "cocos2d.h"


class CSpaceGame : public cocos2d::Scene
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(CSpaceGame);

	static cocos2d::Scene* createScene();

	virtual bool init();



	class ParallaxNodeExtras : public cocos2d::ParallaxNode
	{
	public:
		// Need to provide a constructor
		ParallaxNodeExtras();

		// just to avoid ugly later cast and also for safety
		static ParallaxNodeExtras* create();

		// Facility method (it’s expected to have it soon in COCOS2DX)
		void incrementOffset(cocos2d::Point offset, cocos2d::Node* node);
	};

private:

	void menuCloseCallback(cocos2d::Ref* pSender);
	bool addCloseButton(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
	bool addShip(const cocos2d::Size& visibleSize);
	bool addBackgrund(const cocos2d::Size& visibleSize);
	bool addAsteroid(const cocos2d::Size& visibleSize);
	bool addLaser(const cocos2d::Size& visibleSize);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	virtual void update(float dt);

	float getTimeTick();
	float randomValueBetween(float low, float high);
	void setInvisible(Node* node);

	void onFire();

	typedef enum {
		KENDREASONWIN,
		KENDREASONLOSE
	} EndReason;

	void endScene(EndReason endReason);
	void restartTapped(Ref* pSender);


	//------------------------------------------
	cocos2d::SpriteBatchNode* m_batchNode;
	cocos2d::Sprite* m_ship;

	ParallaxNodeExtras* m_backgroundNode;
	cocos2d::Sprite* m_spaceDust1;
	cocos2d::Sprite* m_spaceDust2;
	cocos2d::Sprite* m_planetSunrise;
	cocos2d::Sprite* m_galaxy;
	cocos2d::Sprite* m_spatialAnomaly1;
	cocos2d::Sprite* m_spatialAnomaly2;

	float m_shipPointsPerSecY = 0.0f;

	cocos2d::Vector<cocos2d::Sprite*>* m_asteroids;
	int m_nextAsteroid = 0;
	float m_nextAsteroidSpawn = 0.0f;

	cocos2d::Vector<cocos2d::Sprite*>* m_shipLasers;
	int m_nextShipLaser = 0;
	int m_lives = 0;

	double m_gameOverTime;
	bool m_gameOver = false;

};

#endif // SPACEGAME_CSPACEGAME_SCENE_H


