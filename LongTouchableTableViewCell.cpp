/*
 * =====================================================================================
 *
 *       Filename:  LongTouchableTableViewCell.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/11/11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shuai Yuan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "LongTouchableTableViewCell.h"

USING_NS_CC;

const std::string LongTouchableTableViewCell::SCHEDULE_KEY = "LONG_TOUCHABLE_TABLE_VIEW_CELL";
const float LongTouchableTableViewCell::LONG_TOUCH_INTERVAL = 0.2f;

LongTouchableTableViewCell::LongTouchableTableViewCell():
    TouchableTableViewCell(),
    isTouchHold_(false),
    isLongTouched_(false),
    longTouchedCallback_(nullptr)
{}

LongTouchableTableViewCell::~LongTouchableTableViewCell()
{}

bool LongTouchableTableViewCell::init()
{
    if (!TouchableTableViewCell::init()) {
        return false;
    }
    return true;
}

void LongTouchableTableViewCell::initTouchListener()
{
//    TouchableTableViewCell::initTouchListener();
    auto touchListener = EventListenerTouchOneByOne::create();
    CC_SAFE_RETAIN(touchListener);
    Rect validTouchedRect;
    validTouchedRect.size = touchableNode_->getContentSize();
    touchListener->onTouchBegan = [=] (cocos2d::Touch* touch, cocos2d::Event* event) {
        if (touchableNode_ == nullptr) {
            return false;
        }
        auto touchLocation = touch->getLocation();
        auto localLocation = touchableNode_->convertToNodeSpace(touchLocation);
        if (validTouchedRect.containsPoint(localLocation)) {
            isValidTouched_ = true;
            isTouchHold_ = true;
            isLongTouched_ = false;
            
            Director::getInstance()->getScheduler()->schedule([=](float) {
                if (isTouchHold_) {
                    isLongTouched_ = true;
                    if (longTouchedCallback_ != nullptr) {
                        longTouchedCallback_();
                    }
                }
                Director::getInstance()->getScheduler()->unschedule(SCHEDULE_KEY, this);
            }, this, LONG_TOUCH_INTERVAL, 0, 0.0f, false, SCHEDULE_KEY);

            return true;
        } else {
            isValidTouched_ = false;
            isTouchHold_ = false;
            isLongTouched_ = false;

            return false;
        }
    };
    touchListener->onTouchMoved = [=] (cocos2d::Touch* touch, cocos2d::Event* event) {
//        Director::getInstance()->getScheduler()->unschedule(SCHEDULE_KEY, this);
        isTouchHold_ = false;
        isLongTouched_ = false;

        auto touchLocation = touch->getLocation();
        auto localLocation = touchableNode_->convertToNodeSpace(touchLocation);
        if (validTouchedRect.containsPoint(localLocation)) {
            isValidTouched_ = true;
        } else {
            isValidTouched_ = false;
        }
    };
    touchListener->onTouchEnded = [=] (cocos2d::Touch* touch, cocos2d::Event* event) {
//        Director::getInstance()->getScheduler()->unschedule(SCHEDULE_KEY, this);
        isTouchHold_ = false;

        auto touchLocation = touch->getLocation();
        auto localLocation = touchableNode_->convertToNodeSpace(touchLocation);
        if (validTouchedRect.containsPoint(localLocation)) {
            isValidTouched_ = true;
        } else {
            isValidTouched_ = false;
        }
    };
//    touchListener->onTouchEnded = touchListener->onTouchMoved;
    touchListener->onTouchCancelled = touchListener->onTouchEnded;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
