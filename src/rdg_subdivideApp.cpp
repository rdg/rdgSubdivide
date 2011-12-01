#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"

#include "Manager.h"
#include "Element.h"

using namespace ci;
using namespace ci::app;
using namespace std;

bool		RUN = false;

class rdg_subdivideApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event );	
	void update();
	void draw();
	
	CameraPersp		mCam;
	Manager mgmt;
};



void rdg_subdivideApp::setup()
{
	setWindowSize( 1440, 568 );
	
	mCam = CameraPersp( getWindowWidth(), getWindowHeight(), 40.0f );
	mCam.setPerspective( 40.0f, getWindowAspectRatio(), 0.1f, 60.0f );
	mCam.lookAt( Vec3f( 0, 12.5f,  0 ), Vec3f( 0, 0, 0 ) );
}

void rdg_subdivideApp::mouseDown( MouseEvent event )
{
	mgmt.exists();
	mgmt.trigger();


}

void rdg_subdivideApp::keyDown( KeyEvent event )
{
	char key = event.getChar();
	
	if( ( key == 'r' ) || ( key == 'R' ) )
		RUN = ! RUN;
	
	if( ( key == 'k' ) || ( key == 'K' ) )
	{
		Vec3f eye = mCam.getEyePoint();
		mCam.setEyePoint( eye + Vec3f( 0, 5, 0 ) );
	}
	
	if( ( key == 'l' ) || ( key == 'L' ) )
	{
		Vec3f eye = mCam.getEyePoint();
		mCam.setEyePoint( eye - Vec3f( 0, 5, 0 ) );
	}
}
	
void rdg_subdivideApp::update()
{
}

void rdg_subdivideApp::draw()
{
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	
	glDepthMask( GL_FALSE );
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ZERO );
 
	gl::setMatrices( mCam );
	
	if( RUN) {
		mgmt.exists();
		mgmt.trigger();
	}
	
	mgmt.render();
}


CINDER_APP_BASIC( rdg_subdivideApp, RendererGl )
