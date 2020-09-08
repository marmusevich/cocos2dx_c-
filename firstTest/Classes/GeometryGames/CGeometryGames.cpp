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


    auto dn = DrawNode::create();


    //m_ship = Sprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    //m_ship->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.5f);


    return true;
}



