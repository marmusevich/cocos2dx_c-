//

#ifndef GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H
#define GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H

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

#endif // GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H


