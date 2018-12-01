
#include "../djgraph.h"
#include <stdlib.h>
#include <windows.h>

extern int main( int argc, char ** argv );

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                             LPSTR lpCmdLine, int nCmdShow)
{
#ifndef USESDL
	// Extra initialization needed for Windows
	djgInitWin32( (int)hInstance );
#endif

	hInstance = hInstance;		// shut up the "unused" warning
	hPrevInstance = hPrevInstance;	// shut up
	lpCmdLine = lpCmdLine;		// shut up
	nCmdShow = nCmdShow;		// shut up

	// FIXME: The intel compiler thinks that you cannot do this .. ???
	// Run the standard "main" function
	return main(__argc, __argv);
}


