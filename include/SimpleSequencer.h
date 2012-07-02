/**
 * SimpleSequencer.h
 * Created by Daniel Scheibel, Red Paper Heart Inc. 2012
 *
 *
 * SimpleSequencer is inspired by Big Spaceship's AS3 class SimpleSequencer 
 * https://github.com/bigspaceship/as3/blob/master/com/bigspaceship/utils/SimpleSequencer.as
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
    SimpleSequencerItem(float s, std::function<void ()> sFn){
        step = s;
        startFn = sFn;
        signal = NULL;
    }
};

class SimpleSequencer {
public:
    SimpleSequencer();
    ~SimpleSequencer();
    
    virtual void addStep(float step, std::function<void ()> startFn , boost::signals2::signal<void ()> *signal);
    virtual void addStep(SimpleSequencerItem);
    virtual void addASynchStep(float step, std::function<void ()> startFn);
    
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