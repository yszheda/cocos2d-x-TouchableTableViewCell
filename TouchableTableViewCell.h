/*
 * =====================================================================================
 *
 *       Filename:  TouchableTableViewCell.h
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
#ifndef __TOUCHABLE_TABLE_VIEW_CELL_H__
#define __TOUCHABLE_TABLE_VIEW_CELL_H__ 

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

/*
 * =====================================================================================
 *        Class:  TouchableTableViewCell
 *  Description:  
 * =====================================================================================
 */
class TouchableTableViewCell : public cocos2d::extension::TableViewCell
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        CREATE_FUNC(TouchableTableViewCell);
        virtual bool init();
        explicit TouchableTableViewCell();
        virtual ~TouchableTableViewCell ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        inline bool getIsValidTouched() const { return isValidTouched_; }

        /* ====================  MUTATORS      ======================================= */
        inline void setIsValidTouched(const bool isValidTouched) { isValidTouched_ = isValidTouched; }

        /* ====================  OPERATORS     ======================================= */

    protected:
        virtual void setTouchableNode(cocos2d::Node* touchableNode);
        virtual void initTouchListener();
        /* ====================  DATA MEMBERS  ======================================= */
        bool isValidTouched_;
        cocos2d::Node* touchableNode_;

    private:
        /* ====================  DATA MEMBERS  ======================================= */

}; /* -----  end of class TouchableTableViewCell  ----- */

#endif /* __TOUCHABLE_TABLE_VIEW_CELL_H__ */
