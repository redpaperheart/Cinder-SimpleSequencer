#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "MyAnimation.h"
#include "SimpleSequencer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SimpleSequencerBasicsApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    void onAnimComplete_handler();
    
    MyAnimation myAnim;
    SimpleSequencer s;
    
    bool bIsAnimating;
};

void SimpleSequencerBasicsApp::setup(){
    bIsAnimating = false;
    
    myAnim.setup();
    
    s.signal_onComplete.connect( bind(&SimpleSequencerBasicsApp::onAnimComplete_handler, this));
}

void SimpleSequencerBasicsApp::mouseDown( MouseEvent event )
{
    if(!bIsAnimating){
        
        console() << "Initialising and starting a sequence of tasks:" << endl;
        bIsAnimating = true;
        //SimpleSequencer s;
        s.addStep( 1.0f, boost::bind( &MyAnimation::animateIn, &myAnim), &myAnim.signal_onAnimateIn );
        
        s.addStep( 5.0f, boost::bind( &MyAnimation::start, &myAnim), &myAnim.signal_onComplete );
        
        s.addStep( 3.0f, boost::bind( &MyAnimation::animateOut, &myAnim), &myAnim.signal_onAnimateOut );
        s.start();
        
    }else{
        console() << "current tasks still running. return;" << endl;
    }
    
}
void SimpleSequencerBasicsApp::onAnimComplete_handler()
{
    bIsAnimating = false;
    console() << "All tasks tcomplete ..ready for some more interaction." << endl;
}

void SimpleSequencerBasicsApp::update()
{
    
}

void SimpleSequencerBasicsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    myAnim.draw();
}


CINDER_APP_BASIC( SimpleSequencerBasicsApp, RendererGl )
