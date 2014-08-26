/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Converted to c++ / cocos2d-x by Angus C
 */


#ifndef __CCCONTROL_H__
#define __CCCONTROL_H__

#include "CCControlUtils.h"
#include "2d/CCLayer.h"

NS_CC_EXT_BEGIN


class Invocation;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** Number of kinds of control event. */
#define kControlEventTotalNumber 9


/*
 * @class
 * Control is inspired by the UIControl API class from the UIKit library of 
 * CocoaTouch. It provides a base class for control Sprites such as Button 
 * or Slider that convey user intent to the application.
 *
 * The goal of Control is to define an interface and base implementation for 
 * preparing action messages and initially dispatching them to their targets when
 * certain events occur.
 *
 * To use the Control you have to subclass it.
 */
class Control : public Layer
{
public:
    /** Kinds of possible events for the control objects. */
    enum class EventType
    {
        TOUCH_DOWN           = 1 << 0,    // A touch-down event in the control.
        DRAG_INSIDE          = 1 << 1,    // An event where a finger is dragged inside the bounds of the control.
        DRAG_OUTSIDE         = 1 << 2,    // An event where a finger is dragged just outside the bounds of the control.
        DRAG_ENTER           = 1 << 3,    // An event where a finger is dragged into the bounds of the control.
        DRAG_EXIT            = 1 << 4,    // An event where a finger is dragged from within a control to outside its bounds.
        TOUCH_UP_INSIDE      = 1 << 5,    // A touch-up event in the control where the finger is inside the bounds of the control.
        TOUCH_UP_OUTSIDE     = 1 << 6,    // A touch-up event in the control where the finger is outside the bounds of the control.
        TOUCH_CANCEL         = 1 << 7,    // A system event canceling the current touches for the control.
        VALUE_CHANGED        = 1 << 8      // A touch dragging or otherwise manipulating a control, causing it to emit a series of different values.
    };
    
    typedef void (Ref::*Handler)(Ref*, EventType);
    
    /** The possible state for a control.  */
    enum class State
    {
