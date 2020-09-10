#include "CGeometryGames.hpp"

USING_NS_CC;

Scene* CGeometryGames::createScene()
{
    return CGeometryGames::create();
}

bool CGeometryGames::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    dn = (DrawNode::create());
    this->addChild(dn);


    dn->drawLine(Vec2(0, 0), visibleSize, Color4F::GREEN);
    dn->drawLine(Vec2(visibleSize.width, 0), Vec2(0, visibleSize.height), Color4F::BLUE);

    dn->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2), FadeOut::create(1.2), NULL)));
    
    //draw->drawCircle(VisibleRect::center() - Vec2(140.0f,0.0f), 50, CC_DEGREES_TO_RADIANS(90), 30, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

    
    //move all node
    //dn->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    //dn->setScale(0.5f);


    this->scheduleUpdate();

    return true;
}

void CGeometryGames::update(float dt)
{

}


