#include "Manager.h"
#include "Element.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"


using namespace ci;
using std::list;


Manager::Manager()
{

}

void Manager::addElement( Element e)
{
	elements.push_back( e );
}

void Manager::render()
{
	for( list<Element>::iterator it = elements.begin(); it != elements.end(); ++it ) {
		it->render();
	}
}

void Manager::exists()
{
	if (elements.size() < 1) 
	{
			addElement( Element( ci::Vec2f( -7.2f, -2.74f ), ci::Vec2f( 7.2f, -2.74f ), ci::Vec2f( 7.2f, 2.74f ), ci::Vec2f( -7.2f, 2.74f ) ) );
	}
}

void Manager::trigger()
{
	
	
	for( list<Element>::iterator it = elements.begin(); it != elements.end(); ) {
		if ( Rand::randFloat() < 0.1)
		{
			if( it->calcArea() > 3.5f )
			{
				newcorners = it->split();
				splits.push_back( Element( newcorners[0], newcorners[1], newcorners[2], newcorners[3] ) );
				++it;
			}else{
				if ( Rand::randFloat() < 0.2)
				{
					it = elements.erase( it );
				}else{
					++it;
				}
			}
		}else{
			++it;
		}

	}
	
	for( list<Element>::iterator it = splits.begin(); it != splits.end(); )
	{
		elements.push_back( *it );
		++it;
		
	}	
	for( list<Element>::iterator it = splits.begin(); it != splits.end(); )
	{
		it = elements.erase( it );
		
	}
}