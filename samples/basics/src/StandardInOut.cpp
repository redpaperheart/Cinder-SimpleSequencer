/**
 * StandardInOut.cpp
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
#include "StandardInOut.h"

StandardInOut::StandardInOut(){
    //console() << "StandardInOut constructor" << endl;
    mCurState = OUT;
    mDispatchCompleteOnUnchangedState = true;
}

StandardInOut::~StandardInOut(){}

void StandardInOut::setup(){
    //console() << "StandardInOut::setup(){}" << endl;
}

void StandardInOut::setup(const string &id){
    //console() << "StandardInOut::setup(){}" << endl;
    mId = id;
}

void StandardInOut::animateIn(){
    animateIn(false);
}
void StandardInOut::animateIn( bool forceAnim ){
    //console() << "StandardInOut::animateIn(){}" << endl;
    console() << "StandardInOut::animateIn() - mCurState:" << stateToString(mCurState) << ", mDispatchCompleteOnUnchangedState: " << mDispatchCompleteOnUnchangedState  << endl;
    if((mCurState != IN_START && mCurState != IN) || forceAnim ){
        mCurState = IN_START;
        signal_onAnimateInStart();
        _animateIn();
    }else if(mCurState == IN && mDispatchCompleteOnUnchangedState){
        console() << "StandardInOut::animateOut() signal_onAnimateIn DISPATCHED!" << endl;
        signal_onAnimateIn();
    }		
}
void StandardInOut::animateOut(){
    animateOut(false);
}
void StandardInOut::animateOut( bool forceAnim ){
    console() << "StandardInOut::animateOut() - mCurState:" << stateToString(mCurState) << ", mDispatchCompleteOnUnchangedState: " << mDispatchCompleteOnUnchangedState  << endl;
    if(mCurState == IN || forceAnim){
        mCurState = OUT_START;
        signal_onAnimateOutStart();
        _animateOut();
    }else if(mCurState == OUT && mDispatchCompleteOnUnchangedState){
       console() << "StandardInOut::animateOut() signal_onAnimateOut DISPATCHED!" << endl;
       signal_onAnimateOut();
    }
}

void StandardInOut::_animateIn(){
    //console() << "StandardInOut::_animateIn(){}, id: "<< mId << endl;
    _onAnimateIn();
}

void StandardInOut::_animateOut(){
    //console() << "StandardInOut::_animateOut(){}, id: "<< mId << endl;
    _onAnimateOut();
}

void StandardInOut::_onAnimateIn(){
    console() << "StandardInOut::_onAnimateIn(), id: "<< mId  << endl;
    mCurState = IN;
    signal_onAnimateIn();
}

void StandardInOut::_onAnimateOut(){
    console() << "StandardInOut::_onAnimateOut(), id: "<< mId  << endl;
    mCurState = OUT;
    signal_onAnimateOut();
}

void StandardInOut::update(){
    //console() << "StandardInOut::update(){}" << endl;
}
void StandardInOut::draw(){
    //console() << "StandardInOut::draw(){}" << endl;
}
