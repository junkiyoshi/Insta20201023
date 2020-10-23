#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(300);
	ofRotateZ(ofGetFrameNum() * 0.25);

	float deg_span = 0.1;
	float noise_span = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0.001, 0.025);
	for (float radius = 50; radius <= 200; radius += 50) {

		ofMesh face, frame;
		frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
		for (float deg = 0; deg < 360; deg += deg_span) {

			int index = face.getNumVertices() - 2;

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(location * noise_span, ofGetFrameNum() * 0.0001));
			float z = noise_value < 0.45 ? 1 : ofMap(noise_value, 0.45, 1.0, 0, 80);

			face.addVertex(glm::vec3(location, -z));
			face.addVertex(glm::vec3(location, z));

			frame.addVertex(glm::vec3(location, -z));
			frame.addVertex(glm::vec3(location, z));

			if (index > -1) {

				face.addIndex(index); face.addIndex(index + 1); face.addIndex(index + 3);
				face.addIndex(index); face.addIndex(index + 2); face.addIndex(index + 3);

				frame.addIndex(index); frame.addIndex(index + 2);
				frame.addIndex(index + 1); frame.addIndex(index + 3);
			}
		}

		ofSetColor(39);
		face.draw();

		ofSetColor(239);
		frame.drawWireframe();
	}


	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}