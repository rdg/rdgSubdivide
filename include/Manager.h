#pragma once
#include "Element.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/gl/Texture.h"
#include <list>

class Manager {
public:
	Manager();  
	void addElement( Element e );
	void trigger();
	void render();
	void exists();
	std::list<Element>	elements;
	std::list<Element>	splits;
	std::vector<ci::Vec2f> newcorners;
};