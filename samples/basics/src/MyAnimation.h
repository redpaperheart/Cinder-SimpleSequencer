//
//  MyAnimation.h
//  SimpleSequencerBasics
//
//  Created by Daniel Scheibel on 5/23/11.
//  Copyright (c) 2012 Red Paper Heart. All rights reserved.
//
#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"
#include "StandardInOut.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class MyAnimation : public StandardInOut {
  public:
    MyAnimation();
    ~MyAnimation();
    
    virtual void update();
    virtual void draw();
    
    virtual void start();
    virtual void _onComplete();
    
    Anim<Rectf> mRect;
    
    boost::signals2::signal<void ()> signal_onComplete;
    
  protected:
    virtual void _animateIn();
    virtual void _animateOut();
    
};