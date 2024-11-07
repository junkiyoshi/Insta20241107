#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(239);
	ofEnableDepthTest();

	this->noise_param_1 = ofRandom(1000);
	this->noise_param_2 = ofRandom(1000);

	this->font_size = 40;
	this->font.loadFont("fonts/msgothic.ttc", this->font_size, true, true, true);

}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param_1 += 0.025 * 2;

	if (ofGetFrameNum() % 50 < 20) {

		this->noise_param_2 += ofMap(ofGetFrameNum() % 50, 0, 20, 0.2, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.25);

	ofSetColor(239);
	ofSetLineWidth(3);
	ofNoFill();

	auto tmp_noise_param = this->noise_param_1;

	ofBeginShape();
	for (int x = 0; x <= 330; x += 1) {

		auto y = ofMap(ofNoise(tmp_noise_param), 0, 1, -100, 100);
		ofVertex(x, y);

		tmp_noise_param += 0.025;
	}
	ofEndShape();

	ofDrawLine(glm::vec2(0, -100), glm::vec2(0, 100));
	ofDrawLine(glm::vec2(330, -100), glm::vec2(330, 100));

	auto y = ofMap(ofNoise(this->noise_param_1), 0, 1, -100, 100);
	ofFill();
	ofDrawCircle(0, y, 8);

	ofTranslate(-180, 0);
	ofSetColor(239);
	ofSetLineWidth(1.5);

	int noise_value = ofNoise(this->noise_param_1) * 100;
	this->font.drawString("0." + to_string(noise_value), -50, 20);

	tmp_noise_param = this->noise_param_1;
	for (int x = 0; x <= 10; x += 1) {

		auto deg = ofMap(ofNoise(tmp_noise_param), 0, 1, -180, 180);
		ofDrawCircle(glm::vec2(120 * cos(deg * DEG_TO_RAD), 120 * sin(deg * DEG_TO_RAD)), ofMap(x, 10, 0, 5, 0));
		ofDrawCircle(glm::vec2(120 * cos((deg + 180) * DEG_TO_RAD), 120 * sin((deg + 180) * DEG_TO_RAD)), ofMap(x, 10, 0, 5, 0));

		tmp_noise_param += 0.025;
	}

	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.75);

	ofSetColor(239);
	ofSetLineWidth(3);
	ofNoFill();

	tmp_noise_param = this->noise_param_2;

	ofBeginShape();
	for (int x = 0; x <= 330; x += 1) {

		if (x > 0 && (ofGetFrameNum() + x) % 50 < 20) {

			tmp_noise_param += ofMap((ofGetFrameNum() + x) % 50, 0, 20, 0.2, 0);
		}

		y = ofMap(ofNoise(tmp_noise_param), 0, 1, -100, 100);
		ofVertex(x, y);
	}
	ofEndShape();

	ofDrawLine(glm::vec2(0, -100), glm::vec2(0, 100));
	ofDrawLine(glm::vec2(330, -100), glm::vec2(330, 100));

	y = ofMap(ofNoise(this->noise_param_2), 0, 1, -100, 100);
	ofFill();
	ofDrawCircle(0, y, 8);

	ofTranslate(-180, 0);
	ofSetColor(239);
	ofSetLineWidth(1.5);

	noise_value = ofNoise(this->noise_param_2) * 100;
	this->font.drawString("0." + to_string(noise_value), -50, 20);

	tmp_noise_param = this->noise_param_2;
	for (int x = 0; x <= 10; x += 1) {
	
		tmp_noise_param += 0.025;

		auto deg = ofMap(ofNoise(tmp_noise_param), 0, 1, -180, 180);
		ofDrawCircle(glm::vec2(120 * cos(deg * DEG_TO_RAD), 120 * sin(deg * DEG_TO_RAD)), ofMap(x, 10, 0, 5, 0));
		ofDrawCircle(glm::vec2(120 * cos((deg + 180) * DEG_TO_RAD), 120 * sin((deg + 180) * DEG_TO_RAD)), ofMap(x, 10, 0, 5, 0));
	}

	ofPopMatrix();

	/*
	int start = 1;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}