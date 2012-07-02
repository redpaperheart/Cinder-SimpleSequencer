/**
 * StandardInOut.h
 * Created by Daniel Scheibel, Red Paper Heart Inc. 2012
 *
 *
 * StandardInOut is inspired by Big Spaceship's AS3 class StandardInOut 
 * https://github.com/bigspaceship/as3/blob/master/com/bigspaceship/display/StandardInOut.as
 * 
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
 **/
#pragma once

#include "cinder/app/AppBasic.h"

// boost error hack: http://forum.libcinder.org/topic/notificationcenter-in-cinder
#define BOOST_INTEL_STDCXX0X
#include <boost/signals2.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;

class StandardInOut {
  public:
    StandardInOut();
    ~StandardInOut();
    
    enum AnimationState
    {
        IN_START,
        IN,
        OUT_START,
        OUT
    };
    
    static string stateToString(const AnimationState &state){
        map<AnimationState, string> stateToString;
        stateToString[IN_START]     = "IN_START";
        stateToString[IN]           = "IN";
        stateToString[OUT_START]    = "OUT_START";
        stateToString[OUT]          = "OUT";
        return stateToString[state];
    }
    
    virtual void setup();
    virtual void setup(const string &id);
    virtual void update();
    virtual void draw();
    
    virtual void animateIn();
    virtual void animateOut();
    virtual void animateIn(bool forceAnim);
    virtual void animateOut(bool forceAnim);

    virtual AnimationState getCurState()const{return mCurState;};
    
    virtual void setId(string id){mId = id;};
    virtual string getId()const{return mId;};
    
    boost::signals2::signal<void ()> signal_onAnimateInStart;
    boost::signals2::signal<void ()> signal_onAnimateIn;
    boost::signals2::signal<void ()> signal_onAnimateOutStart;
    boost::signals2::signal<void ()> signal_onAnimateOut;
    
  protected:
    //override these ones, and don't forget to call _onAnimateIn()/_onAnimateOut() at the end.
    virtual void _animateIn();
    virtual void _animateOut();
    
    virtual void _onAnimateIn();
    virtual void _onAnimateOut();
    
    string mId;
    AnimationState mCurState;

    bool mDispatchCompleteOnUnchangedState;
    
};