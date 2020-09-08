#include "CGeometryGames.h"

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

    return true;
}



