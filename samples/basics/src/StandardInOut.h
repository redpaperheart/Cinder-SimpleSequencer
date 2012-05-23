//
//  StandardInOut.h
//  ThreeDoors
//
//  Created by Daniel Scheibel on 12/06/11.
//  Copyright (c) 2011 Red Paper Heart. All rights reserved.
//
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