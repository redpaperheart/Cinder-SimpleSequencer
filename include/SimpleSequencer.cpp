
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
        //ds: sort array by stepId:
        //steps.sortOn('stepId', Array.NUMERIC);
        mSemLocks.clear();
        
        vector<SimpleSequencerItem *> step = mSteps.begin()->second;
        if(bDebug)console() << "SimpleSequencer::next(), step: " << mSteps.begin()->first << ", parallel tasks:" << mSteps.begin()->second.size() << endl;
        for( vector<SimpleSequencerItem *>::iterator it = step.begin(); it != step.end(); it++){
            (*it)->connection = (*it)->signal->connect( bind( &SimpleSequencer::onItemComplete, this));
            addSemaphore();
        }
        for( vector<SimpleSequencerItem *>::iterator it = step.begin(); it != step.end(); it++){
            (*it)->startFn();
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
    if(bDebug)console() << "SimpleSequencer::onSequenceComplete(){} " << endl;
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



//void SimpleSequencer::update(){
//    console() << "SimpleSequencer::update(){}" << endl;
//}