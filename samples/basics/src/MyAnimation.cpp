#include "MyAnimation.h"

MyAnimation::MyAnimation(){
    mRect = Rectf(0,0,0,0);
}

MyAnimation::~MyAnimation(){}


void MyAnimation::start(){
    timeline().apply( &mRect, Rectf(0,0,getWindowWidth(), getWindowHeight()), 1.0f, EaseOutCubic() );
    timeline().appendTo( &mRect, Rectf(getWindowWidth(), getWindowHeight(),getWindowWidth(), getWindowHeight()), 1.0f, EaseOutCubic() ).finishFn( bind( &MyAnimation::_onComplete, this ) );
}

void MyAnimation::_onComplete(){
    signal_onComplete();
}


void MyAnimation::_animateIn(){
    mRect = Rectf(0,0,0,0);
    timeline().apply( &mRect, Rectf(0,0,getWindowWidth(), getWindowHeight()), 1.0f, EaseOutCubic() ).finishFn( bind( &MyAnimation::_onAnimateIn, this ) );
    //_onAnimateIn();
}

void MyAnimation::_animateOut(){
    timeline().apply( &mRect, Rectf(0,0,0,0), 1.0f, EaseOutCubic() ).finishFn( bind( &MyAnimation::_onAnimateOut, this ) );
    //_onAnimateOut();
}

void MyAnimation::update(){
    
}
void MyAnimation::draw(){
    gl::color(0.5f, 0.5f, 0.5f);
    gl::drawSolidRect(mRect);
}
