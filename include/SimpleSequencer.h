//
//  SimpleSequencer.h
//  ThreeDoors
//
//  Created by Daniel Scheibel on 12/06/11.
//  Copyright (c) 2011 Red Paper Heart. All rights reserved.
//
#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Utilities.h"

// boost error hack: http://forum.libcinder.org/topic/notificationcenter-in-cinder
#define BOOST_INTEL_STDCXX0X
#include <boost/signals2.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;


struct SimpleSequencerItem{
    float step;
    std::function<void ()> startFn;
    boost::signals2::signal<void ()> *signal;
    boost::signals2::connection connection;
    SimpleSequencerItem(float s, std::function<void ()> sFn, boost::signals2::signal<void ()> *sig){
        step = s;
        startFn = sFn;
        signal = sig;
    }
};

class SimpleSequencer {
  public:
    SimpleSequencer();
    ~SimpleSequencer();
    
    virtual void addStep(float step, std::function<void ()> startFn , boost::signals2::signal<void ()> *signal);
    //virtual void addStep(float step, std::function<void ()> startFn , std::function<void ()> signalFn);
    virtual void addStep(SimpleSequencerItem);
    
    //virtual void update();
    virtual void start();
    
    boost::signals2::signal<void ()> signal_onComplete;
    
  protected:
    virtual void next();
    virtual void onItemComplete();
    virtual void onSequenceComplete();
    
    virtual void addSemaphore();
    virtual void checkSemaphores();
    
    
    string mId;
    map<float, vector<SimpleSequencerItem *> > mSteps;
    vector<bool> mSemLocks;
    
    bool bDebug;
};