#include "CGeometryGames.hpp"


#include <cmath>
#include <string>

USING_NS_CC;

static int const LABAL_TAG = 1;

const double PI = std::acos(-1);


const CGeometryGames::tLinePos CGeometryGames::calcLinePos(const float t) const
{
    // -PI .. +PI
    float tt = t - PI;

    static const auto visibleSize = Director::getInstance()->getVisibleSize();
    static const Vec2 screenCentr(visibleSize.width / 2, visibleSize.height / 2);

    // -1...+1
    //float x = tt /PI;
    //float y = std::tan(tt/4 );

    float x = std::sin(tt ) * std::cos(tt);
    float y = std::cos(tt);


    //float x = std::sqrt(std::abs(std::sin(tt - PI / 4))) *std::cos(tt);
    //float y = std::cos(tt) * std::cos(tt*t);
    //float y = std::sqrt(std::abs( std::cos(tt ))) * std::sin(tt - PI / 4);

    Vec2 point1 = Vec2(screenCentr.x * x -5, screenCentr.y * y -5)  + screenCentr;
    //Vec2 point2 = Vec2(screenCentr.x * x, screenCentr.y * y) * 0.20f + screenCentr;;
    //Vec2 point2 = screenCentr;
    Vec2 point2 (screenCentr.x,0);
    //Vec2 point2(screenCentr.x * std::cos(t*2), screenCentr.y * std::sin(t*2));


    return std::make_pair(point1, point2);
}

const cocos2d::Vec2 CGeometryGames::toDecCord(cocos2d::Vec2 polyr) const
{
    static const auto visibleSize = Director::getInstance()->getVisibleSize();
    static const Vec2 screenCentr(visibleSize.width / 2, visibleSize.height / 2);

    return Vec2(polyr.x * screenCentr.x * std::sin(polyr.y), polyr.x * screenCentr.y * std::cos(polyr.y)) + screenCentr;
}


const cocos2d::Vec2 CGeometryGames::calcPolyr(const float fi) const
{
    // -PI .. +PI
    float t = fi - PI;


    return Vec2(std::sin(t), t);
}


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
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 16.0f);
    //label->setPosition(visibleSize.width / 4 * 3, visibleSize.height / 2);
    label->setPosition(10, visibleSize.height / 2);
    addChild(label,0, LABAL_TAG);



    //dn = DrawNode::create();
    //this->addChild(dn);

    //dn->drawLine(Vec2(0, 0), visibleSize, Color4F::GREEN);
    //dn->drawLine(Vec2(visibleSize.width, 0), Vec2(0, visibleSize.height), Color4F::BLUE);

    //dn->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2), FadeOut::create(1.2), NULL)));

    //auto action3 = Sequence::create(
    //    FadeIn::create(2.0f),
    //    FadeOut::create(1.2f),
    //    CallFunc::create( std::bind(&CGeometryGames::callback3, this, dn, 42) ),
    //    /* RemoveSelf */
    //    nullptr);

    //dn->runAction(action3);
    
    //draw->drawCircle(VisibleRect::center() - Vec2(140.0f,0.0f), 50, CC_DEGREES_TO_RADIANS(90), 30, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

    
    //move all node
    //dn->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    //dn->setScale(0.5f);
    
    this->scheduleUpdate();

    return true;
}

void CGeometryGames::update(float dt)
{
    const float actionTime = 0.5f;
    const int FACTOR = 100;

    static float t = 0;
    // 0 .. 2 * PI
    t = static_cast<float>(static_cast<int>((t + dt) * FACTOR) % static_cast<int>(PI * 2 * FACTOR)) / FACTOR;

    //dn->drawLine(pos.first, pos.second, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1.0f));
    //auto action = Sequence::create(
    //    //FadeIn::create(actionTime),
    //    FadeOut::create(actionTime),
    //    RemoveSelf::create(),
    //    nullptr);


    const tLinePos pos = calcLinePos(t);
    
    auto dn = DrawNode::create();

    dn->drawLine(pos.first, pos.second, Color4F::GREEN);
    dn->runAction(Sequence::create(
        FadeOut::create(actionTime),
        RemoveSelf::create(),
        nullptr));
    this->addChild(dn);



    //if (static_cast<int>(t * 100) % 99 == 0)
    {
        //std::string str = " _time = (" + std::to_string(t) + ")";

        //auto label1 = (Label*)getChildByTag(LABAL_TAG);
        //label1->setString(str);


        auto dn1 = DrawNode::create();
        dn1->drawDot(pos.first, 3.0f, Color4F::RED);
        dn1->runAction(Sequence::create(
            FadeOut::create(actionTime * 20),
            RemoveSelf::create(),
            nullptr));
        this->addChild(dn1);
    }


    


    //const Vec2 pc = calcPolyr(t);
    //const Vec2 cord = toDecCord(pc);

    //auto dn = DrawNode::create();
    //dn->drawLine(cord, pos.second, Color4F::GREEN);
    //dn->runAction(Sequence::create(
    //    FadeOut::create(actionTime),
    //    RemoveSelf::create(),
    //    nullptr));
    //this->addChild(dn);

    //auto dn1 = DrawNode::create();
    //dn1->drawDot(toDecCord(pc/2), 3.0f, Color4F::RED);
    //dn1->runAction(Sequence::create(
    //    FadeOut::create(actionTime * 4),
    //    RemoveSelf::create(),
    //    nullptr));
    //this->addChild(dn1);




    //std::string str = " _time = (" + std::to_string(_time) + ") \n"
    //    + " pos = [" + std::to_string(x) + ",\t"+ std::to_string(y) + "]";

    //std::string str = " _time = (" + std::to_string(_time) + ")";

    //auto label1 = (Label*)getChildByTag(LABAL_TAG);
    //label1->setString(str);

}
//
//void CGeometryGames::callback3(Node* sender, long data)
//{
//    //auto s = Director::getInstance()->getWinSize();
//    //auto label = Label::createWithTTF("callback 3 called", "fonts/Marker Felt.ttf", 16.0f);
//    //label->setPosition(s.width / 4 * 3, s.height / 2);
//    //addChild(label);
//
//    //CCLOG("target is: %p, data is: %ld", sender, data);
//}