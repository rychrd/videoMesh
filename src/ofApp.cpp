#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofDisableArbTex();

    player.load(ofToDataPath("video/test.mp4"));
    player.play();
    
    tex.allocate(400,400, GL_RGB);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    mesh = ofPlanePrimitive(400, 400, 2, 2).getMesh();
    
    centre = ofVec3f(ofGetWidth()/2,
                ofGetHeight()/2,
                0);
    mesh.setVertex(3, glm::vec3(300,200,0));
    
    ofLog() << "mode: " << mesh.getMode();
    
    mouseEnt = false;
    
    for(int i=0; i<mesh.getNumVertices(); i++)
    {
        //mesh.addTexCoord(mesh.getVertex(i));
        ofLog() << "vertex: " << mesh.getVertex(i);
        ofLog() << "tex coord: " << mesh.getTexCoord(i);
        ofLog() << "index: " << mesh.getIndex(i);


    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    player.update();
    mousePos.set(ofGetMouseX(), ofGetMouseY());
    transPos.set(mousePos.x - centre.x, mousePos.y - centre.y);
    
    if(mouseClick)
    {
        for(auto &vInd : mesh.getIndices())
        {
            ofVec2f vert = mesh.getVertex(vInd);
            ofPoint diff = vert - transPos;
            diff.x = abs(diff.x);
            diff.y = abs(diff.y);
            
            if(diff.x < 10 && diff.y < 10)
            {
                mesh.setVertex(vInd, transPos);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(mouseEnt)
       {
           ofBackground(ofColor::red);
       }
       else
       {
           ofBackground(ofColor::black);
       }

    if(player.isFrameNew())
    {
        ofPushMatrix();
        
        tex = player.getTexture();
        ofTranslate(centre);
        
        tex.bind();
        mesh.draw();
        tex.unbind();
        
        ofPushStyle();
        ofNoFill();
        
        for(size_t i=0; i<mesh.getNumIndices(); i++)
        {
            ofPoint v = mesh.getVertex(i);
            ofDrawCircle(v, 10);
            ofDrawBitmapString(ofToString(v),v.x, v.y);
        }
        
        ofPopMatrix();
        ofPopStyle();
    }
   
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    ofDrawBitmapString("mousePos: " + ofToString(mousePos), 10, 20);
    ofDrawBitmapString("trans mousePos: " + ofToString(transPos), 10, 30);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    mouseClick = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    mouseClick = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

        ofLog() << "mouse entered at " << x << ":" << y;

    if(x>400)
    {
        mouseEnt = true;
    }
    else
    {
        mouseEnt = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
