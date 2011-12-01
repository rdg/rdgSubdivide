#include "Element.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;

Element::Element( Vec2f p0, Vec2f p1, Vec2f p2, Vec2f p3 )
{
	corners.push_back( p0 );
	corners.push_back( p1 );
	corners.push_back( p2 );
	corners.push_back( p3 );
	
	newcorners.push_back( p0 );
	newcorners.push_back( p1 );
	newcorners.push_back( p2 );
	newcorners.push_back( p3 );
	
	height = Rand::randFloat() * 3.0f;
	
	if ( Rand::randFloat() < 0.2 )
	{
		color = ci::ColorA(0.7f, 0.7f, 0.7f, 1.0f);
	}else {
		color = ci::ColorA(0.3f, 0.3f, 0.3f, 1.0f);
	}

}

void Element::render()
{	
	
	/*
	 http://www.songho.ca/opengl/gl_vertexarray.html
	 */
	
	GLubyte indices[] = {0, 1, 2, 3,
		4, 5, 6, 7,
		0, 1, 5, 4,
		2, 3, 7, 6,
		1, 2, 6, 5,
		0, 3, 7, 4};
	
	Vec3f cube[8];
	
	for( int i = 0; i < 4; i++ ) {		
		cube[i] = Vec3f( corners[i].x, 0.0f, corners[i].y );
	}
	for( int i = 0; i < 4; i++ ) {		
		cube[ i + 4 ] = Vec3f( corners[i].x, height, corners[i].y ) ;
	}
	
	glNormal3b(0, 1, 0);
	
	glColor4f( color );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cube);
	
	// draw a cube
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	
	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBegin(GL_LINE_LOOP);
	glColor4f( 0.0f, 0.0f, 0.0f, 0.0f );
	for( int i = 0; i < 4; i++ ) {		
		glVertex3fv( Vec3f( corners[i].x, height, corners[i].y ) );
	}
	glEnd();
}

void Element::subdivide()
{
	s = Rand::randInt(0,3);
	
	e0 = corners[ (s + 1) % 4 ] - corners[s];
	d0 = e0.length();
	
	e1 = corners[ (s + 2) % 4 ] - corners[ (s + 3) % 4 ];
	d1 = e1.length();
	
	corners[ (s + 1) % 4 ] = corners[s] + e0.normalized() * d0 * Rand::randFloat();
	
	corners[ (s + 2) % 4 ] = corners[(s + 2) % 4] - e1.normalized() * d1 * Rand::randFloat();
	corners[ (s + 3) % 4 ] = corners[ ( s + 3 ) % 4 ];
	
	
}

std::vector<ci::Vec2f> Element::split()
{
	s = Rand::randInt(0,3);
	
	e0 = corners[ (s + 1) % 4 ] - corners[s];
	d0 = e0.length();
	
	e1 = corners[ (s + 2) % 4 ] - corners[ (s + 3) % 4 ];
	d1 = e1.length();
	
	std::cout << corners[0] << std::endl;
	
	newcorners[ 1 ] = corners[ (s + 1) % 4 ];
	newcorners[ 2 ] = corners[  (s + 2) % 4 ];
	
	corners[ (s + 1) % 4 ] = corners[s] + e0.normalized() * d0 * Rand::randFloat();
	corners[ (s + 2) % 4 ] = corners[(s + 2) % 4] - e1.normalized() * d1 * Rand::randFloat();
	
	
	newcorners[ 0 ] = corners[ (s + 1) % 4 ];
	newcorners[ 3 ] = corners[ (s + 2) % 4 ];
	
	return newcorners;
}

bool Element::exists()
{
	return 1;
}


float Element::calcArea()
{
	
	/*
	 http://paulbourke.net/geometry/polyarea/
	 */
	
	float area = 0.0;
	for( int i = 0; i < 4; i++ ) {		
		int j = (i + 1 ) % 4;
		area += corners[i].x * corners[j].y;
		area -= corners[i].y * corners[j].x;
	}
	
	area /= 2;
	std::cout << area << std::endl;
	return (area < 0 ? -area : area);
}
