# pragma once
#include "cinder/Vector.h"
#import "cinder/Area.h"
#import "cinder/Color.h"
#include <vector>

class Element {
public:
	Element( ci::Vec2f p0, ci::Vec2f p1, ci::Vec2f p2, ci::Vec2f p3  );
	void render();
	void subdivide();
	std::vector<ci::Vec2f> split();
	bool exists();
	float calcArea();
	
	std::vector<ci::Vec2f> corners;
	
	std::vector<ci::Vec2f> newcorners;
	int s;
	
	ci::Vec2f e0;
	ci::Vec2f e1;
	
	float d0;
	float d1;
	
	float height;
	
	ci::Color color;
	
};
