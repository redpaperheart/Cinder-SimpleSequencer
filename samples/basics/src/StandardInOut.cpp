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
