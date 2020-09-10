//

#ifndef GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H
#define GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H

#include "cocos2d.h"

//#include <memory>
//#include <vector>
#include <list>

class CGeometryGames : public cocos2d::Scene
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(CGeometryGames);
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void update(float dt);
private:
	/*
	class SHolderPoint
	{
		const cocos2d::DrawNode* dn;
	public:
		SHolderPoint(Vec2);

		
		//todo how can i update and calculate
		void update(float dt);
		bool isDead();
	};
	std::list<SHolderPoint> points;
	
	*/
	

	cocos2d::DrawNode* dn;
	//TODO investigat how can i manage memory with node
	//std::shared_ptr<DrawNode> dn;

};

#endif // GEOMETRYGAMES_CGEOMETRYGAMES_SCENE_H


