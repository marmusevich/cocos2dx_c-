#include "CAsteroidsGame.hpp"

USING_NS_CC;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    log("Error while loading: %s\n", filename);
    log("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CSpaceGame.cpp\n");
}

Scene* CAsteroidsGame::createScene()
{
    return CAsteroidsGame::create();
}

bool CAsteroidsGame::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();


    bool ret = true;

    ret = ret && mPlayer.init();
    if (ret)
    {
        //mPlayer.setPosition(visibleSize.height/2, visibleSize.height / 2);

        addChild(&mPlayer);
    }



    return ret;

    //this.

}



//detals
namespace NAsteroids
{
    //CPlayer::CPlayer(const CAsteroidsGame& parent)
    //    : mParent(parent)
    //{

    //}

    bool CPlayer::init()
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        setPosition(visibleSize.height / 2, visibleSize.height / 2);

        //                            
        mShip = Sprite::create("Asteroids/spaceship.png", Rect(40, 0, 40, 40));

        addChild(mShip);
        
        return true;
    }

}
