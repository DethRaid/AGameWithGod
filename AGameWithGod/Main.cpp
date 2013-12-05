#include "stdafx.h"
#include "resource.h"

#include "Camera.h"
#include "Input.h"
#include "Light.h"
#include "SplashScreen.h"
#include "Mouse.h"
#include "PerlinTexture.h"
#include "Player.h"
#include "Temple.h"
#include "Terrain.h"

//Function declarations. Declare the function at the top of the code and you can use it anywhere
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
DEVMODE getCurDevice();
BOOL createOpenGLWindow( std::string, int, int, int, bool );
void EnableOpenGL( HWND hWnd, HDC *hDC, HGLRC *hRC );
void DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC );
void makeFullscreen();
void getKeyboardInput();
void onKeyDown( int key );
void onKeyUp( int key );
void onMouseDown( int button );
void init();
void run();
void paint();

//global variables. Do not delete if you value this program.
int width = 640, height = 480;
HGLRC hRC;
HWND hWnd;
HDC hDC;
HINSTANCE hInstance;

//add your variables here
bool inScene = false;
bool updateTerrain = true;
long double rTime, rStart, rEnd, tTime;
float pSpeed;
int xDelta;
GLfloat *lightPosition, *lightDiffuse;
GLuint shadowMapTex;

Light sun( GL_LIGHT0 );
SplashScreen main;
Player player;
Temple temple;
Terrain terrain;
std::ofstream debug( "debug.txt" );

RECT windowRect;

void init()
{	
	Shaders::init();
	main.init();
	temple.init();
	terrain.loadData();
	pSpeed = 1;

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, double(width)/double(height), 0.1, 1500 );
	glViewport( 0, 0, width, height );

	//add your initializations here
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glClearDepth( 1.0f );
	glDepthMask( GL_TRUE );

	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.9 );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	glEnable( GL_LIGHTING );
	glShadeModel( GL_FLAT );

	glEnable( GL_LIGHT0 );
	lightPosition = new GLfloat[4];
	lightPosition[0] = 1;
	lightPosition[1] = 1;
	lightPosition[2] = .333;
	lightPosition[3] = 0;
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );

    glEnable( GL_COLOR_MATERIAL );
	
	glGenTextures( 1, &shadowMapTex );
	glBindTexture( GL_TEXTURE_2D, shadowMapTex );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 512, 512, 0,
				  GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
}

void getKeyboardInput()
{
     if( Input::w ) {
		 player.getTransform().translate( player.getTransform().getForward() * -pSpeed );
	 } else if( Input::s ) {
         player.getTransform().translate( player.getTransform().getForward() * pSpeed );
	 }
	 if( Input::a ) {
         player.getTransform().translate( player.getTransform().getRight() * -pSpeed );
	 } else if( Input::d ) {
         player.getTransform().translate( player.getTransform().getRight() * pSpeed );
	 }
	 if( Input::r ) {
         player.getTransform().translate( Vector3::up * pSpeed );
	 } else if( Input::f ) {
         player.getTransform().translate( Vector3::up * -pSpeed );
	 }
	 if( Input::enter ) {
		 inScene = true;
	 }
}

void run()
{
	Mouse::lastX = Mouse::x;
	Mouse::lastY = Mouse::y;
	Mouse::x = Mouse::nextX;
	Mouse::y = Mouse::nextY;
	getKeyboardInput();
	player.getTransform().rotate( Vector3(0, Mouse::x-Mouse::lastX, 0) );
	terrain.update( player.getTransform().getPosition() );
	//player.setHeight( terrain.sampleHeight( player.getTransform().getPosition() ) + 1.5 );
}

void paint()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	player.loadView();

	//render the scene with ambient lighting
	//glViewport( 0, 0, width, height );
	//add drawing code here
	//terrain.render();
	//temple.render();
	
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );

	terrain.render( Vector3(1, 1, .333) );
	temple.render();
}

/*
void renderShadow() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glColorMask( 0, 0, 0, 0 );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( -256, 256, -256, 256, 0.1, 1500 );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	gluLookAt( 256, 256, 256, 0, 0, 0, 0, 0, 1 );

	glViewport( 0, 0, 512, 512 );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_FRONT );

	terrain.render();
	temple.render();
	
	glBindTexture( GL_TEXTURE_2D, shadowMapTex );
	glCopyTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 0, 0, 512, 512 );

	glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glColorMask( ~0, ~0, ~0, ~0 );
	glDisable( GL_CULL_FACE );
}

void translateLightDepths() {
	//static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
		//						0.0f, 0.5f, 0.0f, 0.0f,
			//					0.0f, 0.0f, 0.5f, 0.0f,
				//				0.5f, 0.5f, 0.5f, 1.0f);

	//MATRIX4X4 textureMatrix = biasMatrix * lightProjectionMatrix * lightViewMatrix;
	
	//Bind & enable shadow map texture
	glBindTexture( GL_TEXTURE_2D, shadowMapTex);
	glEnable( GL_TEXTURE_2D );

	//Set up texture coordinate generation.
	glEnable( GL_TEXTURE_GEN_S );
	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	//glTexGenfv( GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0) );
	
	glEnable( GL_TEXTURE_GEN_T );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	//glTexGenfv( GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1) );
	
	glEnable( GL_TEXTURE_GEN_R );
	glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	//glTexGenfv( GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2) );
	
	glEnable( GL_TEXTURE_GEN_Q );
	glTexGeni( GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	//glTexGenfv( GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3) );

	//Enable shadow comparison
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE );

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL );

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY );

	//Set alpha test to discard false comparisons
	glAlphaFunc( GL_GEQUAL, 0.99f );
	glEnable( GL_ALPHA_TEST );
}
*/

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow )
{
    WNDCLASS wc;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW ); 
    wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "A Game With God";
    RegisterClass( &wc );
	makeFullscreen();
    hWnd = CreateWindow( "A Game With God", "A Game With God",
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      -8, -32, width+16, height+40,
      NULL, NULL, hInstance, NULL );
    EnableOpenGL( hWnd, &hDC, &hRC );
	init();
	GetWindowRect( hWnd, &windowRect );
	ShowCursor( false );
    while( !bQuit )
    {
		rEnd = rStart;
		rStart = double(clock());
		rTime = (rStart-rEnd)/1000.0;
		tTime += rTime;
		if( rEnd < 0.01 ) {
			tTime = 0;
		}
		//SetCursorPos( width/2, height/2 );
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
            if( msg.message == WM_QUIT )
                bQuit = TRUE;
            else
            {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
            }
        else
        {
			debug<<"\nRender time: " <<1000*rTime <<"ms\n";
			debug<<"Framerate: " <<(1.0/rTime) <<"fps\n";
			run();
			if( !inScene ) {
				main.render( tTime );
			} else {
				paint();
			}
			SwapBuffers( hDC );
            Sleep( 1 );
        }
    }
    DisableOpenGL( hWnd, hDC, hRC );
    DestroyWindow( hWnd );
    return msg.wParam;
}

void onKeyDown( int key ) {
	switch( key ) {
	case 'A':
		Input::a = true;
		break;
	case 'B':
		Input::b = true;
		break;
	case 'C':
		Input::c = true;
		break;
	case 'D':
		Input::d = true;
		break;
	case 'E':
		Input::e = true;
		break;
	case 'F':
		Input::f = true;
		break;
	case 'G':
		Input::g = true;
		break;
	case 'H':
		Input::h = true;
		break;
	case 'I':
		Input::i = true;
		break;
	case 'J':
		Input::j = true;
		break;
	case 'K':
		Input::k = true;
		break;
	case 'L':
		Input::l = true;
		break;
	case 'M':
		Input::m = true;
		break;
	case 'N':
		Input::n = true;
		break;
	case 'O':
		Input::o = true;
		break;
	case 'P':
		Input::p = true;
		break;
	case 'Q':
		Input::q = true;
		break;
	case 'R':
		Input::r = true;
		break;
	case 'S':
		Input::s = true;
		break;
	case 'T':
		Input::t = true;
		break;
	case 'U':
		Input::u = true;
		break;
	case 'V':
		Input::v = true;
		break;
	case 'W':
		Input::w = true;
		break;
	case 'X':
		Input::x = true;
		break;
	case 'Y':
		Input::y = true;
		break;
	case 'Z':
		Input::z = true;
		break;
	case VK_RETURN:
		Input::enter = true;
		break;
	}
}

void onKeyUp( int key ) {
	switch( key ) {
	case 'A':
		Input::a = false;
		break;
	case 'B':
		Input::b = false;
		break;
	case 'C':
		Input::c = false;
		break;
	case 'D':
		Input::d = false;
		break;
	case 'E':
		Input::e = false;
		break;
	case 'F':
		Input::f = false;
		break;
	case 'G':
		Input::g = false;
		break;
	case 'H':
		Input::h = false;
		break;
	case 'I':
		Input::i = false;
		break;
	case 'J':
		Input::j = false;
		break;
	case 'K':
		Input::k = false;
		break;
	case 'L':
		Input::l = false;
		break;
	case 'M':
		Input::m = false;
		break;
	case 'N':
		Input::n = false;
		break;
	case 'O':
		Input::o = false;
		break;
	case 'P':
		Input::p = false;
		break;
	case 'Q':
		Input::q = false;
		break;
	case 'R':
		Input::r = false;
		break;
	case 'S':
		Input::s = false;
		break;
	case 'T':
		Input::t = false;
		break;
	case 'U':
		Input::u = false;
		break;
	case 'V':
		Input::v = false;
		break;
	case 'W':
		Input::w = false;
		break;
	case 'X':
		Input::x = false;
		break;
	case 'Y':
		Input::y = false;
		break;
	case 'Z':
		Input::z = false;
		break;
	case VK_RETURN:
		Input::enter = false;
		break;
	}
}

void onMouseDown( int button ) {
	if( button == 0 ) {
		player.fire();
	}
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch (message)
    {
		case WM_CREATE:
			return 0;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{}
			return 0;

		case WM_CLOSE:
			PostQuitMessage (0);
			return 0;
		case WM_DESTROY:
			return 0;

		case WM_KEYDOWN:
			if( wParam ==  VK_ESCAPE ) {
					PostQuitMessage(0);
					return 0;
			} else {
				onKeyDown( wParam );
				return 0;
			}
			return 0;
		case WM_KEYUP:
			onKeyUp( wParam );
			return 0;

		case WM_MOUSEMOVE:
			Mouse::nextX = GET_X_LPARAM( lParam );
			Mouse::nextY = GET_Y_LPARAM( lParam );
			return 0;

		case WM_LBUTTONDOWN:
			onMouseDown( 0 );

		default:
			return DefWindowProc (hWnd, message, wParam, lParam);
	}
}

DEVMODE getCurDeviceMode() {
	DEVMODE deviceMode;
	int maxWidth = -1;
	EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &deviceMode );
	return deviceMode;
}

void makeFullscreen() {
	DEVMODE dmScreenSettings = getCurDeviceMode();
	width = dmScreenSettings.dmPelsWidth;
	height = dmScreenSettings.dmPelsHeight;
	ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN );
	ShowCursor( false );
}

void EnableOpenGL( HWND hWnd, HDC *hDC, HGLRC *hRC )
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    *hDC = GetDC( hWnd );
    ZeroMemory( &pfd, sizeof(pfd) );
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( *hDC, &pfd );
    SetPixelFormat( *hDC, iFormat, &pfd );
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
	glewInit();
}

void DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}