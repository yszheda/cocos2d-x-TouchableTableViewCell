/*
 * =====================================================================================
 *
 *       Filename:  TouchableTableViewCell.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/10/27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shuai Yuan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "TouchableTableViewCell.h"

USING_NS_CC;

TouchableTableViewCell::TouchableTableViewCell():
    isValidTouched_(false),
    touchableNode_(nullptr)
{}

TouchableTableViewCell::~TouchableTableViewCell()
{}

bool TouchableTableViewCell::init()
{
    if (!TableViewCell::init()) {
        return false;
    }
    return true;
}

void TouchableTableViewCell::initTouchListener()
{
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
            return true;
        } else {
            isValidTouched_ = false;
            return false;
        }
    };
    touchListener->onTouchMoved = [=] (cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchLocation = touch->getLocation();
        auto localLocation = touchableNode_->convertToNodeSpace(touchLocation);
        if (validTouchedRect.containsPoint(localLocation)) {
            isValidTouched_ = true;
        } else {
            isValidTouched_ = false;
        }
    };
//    touchListener->onTouchEnded = [=] (cocos2d::Touch* touch, cocos2d::Event* event) {};
    touchListener->onTouchEnded = touchListener->onTouchMoved;
    touchListener->onTouchCancelled = touchListener->onTouchEnded;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void TouchableTableViewCell::setTouchableNode(cocos2d::Node* touchableNode)
{
    touchableNode_ = touchableNode;
    initTouchListener();
}

