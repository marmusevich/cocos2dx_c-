//


#ifndef SPACEGAME_CSPACEGAME_SCENE_H
#define SPACEGAME_CSPACEGAME_SCENE_H

#include "cocos2d.h"

class CGeometryGames : public cocos2d::Scene
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(CGeometryGames);
	static cocos2d::Scene* createScene();
	virtual bool init();
private:

};

#endif // SPACEGAME_CSPACEGAME_SCENE_H


