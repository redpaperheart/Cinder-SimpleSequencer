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
#include "SimpleSequencer.h"

SimpleSequencer::SimpleSequencer(){
    mId = "id_"+toString( Rand::randFloat() );
    bDebug = true;
}
SimpleSequencer::~SimpleSequencer(){}



void SimpleSequencer::addStep(float step, std::function<void ()> startFn , boost::signals2::signal<void ()> *signal){    
    if(bDebug)console() << "SimpleSequencer::addStep(){}, add to step: "<< step << endl;
    mSteps[step].push_back( new SimpleSequencerItem(step, startFn, signal) );
}

void SimpleSequencer::addStep(SimpleSequencerItem item ){    
    //console() << "SimpleSequencer::addStep(){}, add to step: "<< item.step << endl;
    mSteps[item.step].push_back( &item );
}

void SimpleSequencer::addASynchStep(float step, std::function<void ()> startFn){
    if(bDebug)console() << "SimpleSequencer::addASynchStep(){}, add to step: "<< step << endl;
    mSteps[step].push_back( new SimpleSequencerItem(step, startFn) );
}



void SimpleSequencer::start(){
    if(bDebug)console() << "SimpleSequencer::start(){}, total steps:"<< mSteps.size() << endl;
    //    for ( map<float, vector<SimpleSequencerItem *> >::iterator mIt=mSteps.begin() ; mIt != mSteps.end(); mIt++ ){
    //        for( vector<SimpleSequencerItem *>::iterator vIt = (*mIt).second.begin(); vIt != (*mIt).second.end(); vIt++){
    //            console () << (*vIt)->step << ", ";
    //        }
    //        console () << endl;
    //    }
    next();
}


void SimpleSequencer::next(){
    
    if(mSteps.size() > 0){
        mSemLocks.clear();
        
        vector<SimpleSequencerItem *> step = mSteps.begin()->second;
        if(bDebug)console() << "SimpleSequencer::next(), step: " << mSteps.begin()->first << ", parallel tasks:" << mSteps.begin()->second.size() << endl;
        for( vector<SimpleSequencerItem *>::iterator it = step.begin(); it != step.end(); it++){
            if((*it)->signal != NULL){
                // connect to signals
                (*it)->connection = (*it)->signal->connect( bind( &SimpleSequencer::onItemComplete, this));
            }
            addSemaphore();
        }
        for( vector<SimpleSequencerItem *>::iterator it = step.begin(); it != step.end(); it++){
            (*it)->startFn();
            if((*it)->signal == NULL){
                onItemComplete();
            }
        }
    }else{
        onSequenceComplete();
    }
}

void SimpleSequencer::onItemComplete(){
    if(bDebug)console() << "SimpleSequencer::onItemDone(){}, mId: "<< mId << endl;
    mSemLocks.pop_back();
    checkSemaphores();
}

void SimpleSequencer::onSequenceComplete(){
    if(bDebug)console() << "SimpleSequencer::onSequenceComplete(){}: " << endl;
    signal_onComplete();
}

void SimpleSequencer::addSemaphore(){
    mSemLocks.push_back(true);
}

void SimpleSequencer::checkSemaphores(){
    if(mSemLocks.size() < 1){
        
        //disconnect all signals 
        vector<SimpleSequencerItem *> step = mSteps.begin()->second;
        for( vector<SimpleSequencerItem *>::iterator it = step.begin(); it != step.end(); it++){
            (*it)->connection.disconnect();
        }
        step.clear();
        //erase the step
        mSteps.erase(mSteps.begin());
        
        //check if there are more steps:
        if(mSteps.size() > 0){
            //start next step
            next();
        }else{
            //all animations complete
            onSequenceComplete();
        }
    }
}