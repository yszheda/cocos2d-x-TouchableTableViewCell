/*
 * =====================================================================================
 *
 *       Filename:  LongTouchableTableViewCell.h
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
#ifndef __LONG_TOUCHABLE_TABLE_VIEW_CELL_H__
#define __LONG_TOUCHABLE_TABLE_VIEW_CELL_H__ 

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "TouchableTableViewCell.h"

/*
 * =====================================================================================
 *        Class:  LongTouchableTableViewCell
 *  Description:  
 * =====================================================================================
 */
class LongTouchableTableViewCell : public TouchableTableViewCell
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        CREATE_FUNC(LongTouchableTableViewCell);
        virtual bool init();
        explicit LongTouchableTableViewCell ();                            /* constructor      */
        virtual ~LongTouchableTableViewCell ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        inline bool getIsLongTouched() const { return isLongTouched_; }
        inline const std::function<void(void)>& getLongTouchedCallback() const { return longTouchedCallback_; }

        /* ====================  MUTATORS      ======================================= */
        inline void setIsLongTouched(const bool isLongTouched) { isLongTouched_ = isLongTouched; }
        inline void setLongTouchedCallback(const std::function<void(void)>& longTouchedCallback) { longTouchedCallback_ = longTouchedCallback; }

        /* ====================  OPERATORS     ======================================= */

    protected:
        virtual void initTouchListener() override;
        /* ====================  DATA MEMBERS  ======================================= */
        bool isTouchHold_;      // holding the touch place without moving
        bool isLongTouched_;
        std::function<void(void)> longTouchedCallback_;

    private:
        /* ====================  DATA MEMBERS  ======================================= */
        static const std::string SCHEDULE_KEY;
        static const float LONG_TOUCH_INTERVAL;

}; /* -----  end of class LongTouchableTableViewCell  ----- */

#endif /* __LONG_TOUCHABLE_TABLE_VIEW_CELL_H__ */
