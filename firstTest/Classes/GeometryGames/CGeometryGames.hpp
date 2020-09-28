//

#ifndef GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H
#define GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H

#include "cocos2d.h"

#include<utility>

class CGeometryGames : public cocos2d::Scene
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(CGeometryGames);
	static cocos2d::Scene* createScene();

private:
	virtual bool init();
	virtual void update(float dt);

	
	typedef std::pair<cocos2d::Vec2, cocos2d::Vec2> tLinePos;
	const tLinePos calcLinePos(const float t) const;



	// convert cord from polyar to decard
	const cocos2d::Vec2 toDecCord(cocos2d::Vec2 polyr) const;

	const cocos2d::Vec2  calcPolyr(const float fi) const;



	//void callback3(Node* sender, long data);
	cocos2d::DrawNode* dn;
};

#endif // GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H


