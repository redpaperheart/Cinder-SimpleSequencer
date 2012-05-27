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
    void trace(string msg);
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
        int count = 0;
        //SimpleSequencer s;
        s.addStep( count++, boost::bind( &MyAnimation::animateIn, &myAnim), &myAnim.signal_onAnimateIn );
        
        s.addStep( count, boost::bind( &MyAnimation::animateOut, &myAnim), &myAnim.signal_onAnimateOut );
        s.addASynchStep( count++, boost::bind( &SimpleSequencerBasicsApp::trace, this, "trace step called with animateOut of myAnim."));
        
        s.addStep( count++, boost::bind( &MyAnimation::start, &myAnim), &myAnim.signal_onComplete );

        s.addASynchStep( 50, boost::bind( &SimpleSequencerBasicsApp::trace, this, "step 50: asynch step called."));
        s.addASynchStep( 49, boost::bind( &SimpleSequencerBasicsApp::trace, this, "step 49: asynch step called."));
        
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

void SimpleSequencerBasicsApp::trace(string msg){
    console() << msg << endl;
}

void SimpleSequencerBasicsApp::update(){}
void SimpleSequencerBasicsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    myAnim.draw();
}


CINDER_APP_BASIC( SimpleSequencerBasicsApp, RendererGl )
