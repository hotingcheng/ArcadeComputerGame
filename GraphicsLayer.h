#ifndef GRAPHICSLAYER_H
#define GRAPHICSLAYER_H

#include <string>
using namespace std;

#include <ddraw.h>

//#include <d3d8.h>
//#include <D3dx8tex.h>

#include "GameError.h"
#include "GameType.h"
#include "DxHelper.h"
#include "resource.h"

class GraphicsLayer
{

protected:

	HWND					m_hWnd;			// The handle to the window

	LPDIRECTDRAW7            lpDD;
	LPDIRECTDRAWSURFACE7     lpFrontBuffer;
	LPDIRECTDRAWSURFACE7     lpBackBuffer;
	LPDIRECTDRAWPALETTE      lpArtPalette;

	LPDIRECTDRAWCLIPPER		 pClipper;

	RECT	m_rcScreenRect;					// The dimensions of the screen

	GraphicsLayer( HWND );			// Constructor
	static GraphicsLayer* m_pGraphicsLayer;	// Pointer to the main global gfx object

public:

	void destroyAll();
	~GraphicsLayer();
	
	//  Initialization 
	void initFullScreen( GUID* pGuid, int width, int height, int bpp );

	// Get the DirectDraw and the buffers
	LPDIRECTDRAW7 getDirectDraw() const;
	LPDIRECTDRAWSURFACE7 getFrontBuffer() const;
	LPDIRECTDRAWSURFACE7 getBackBuffer() const;
	
	// Gets the screen width
	int width() const;
	
	// Gets the screen height
	int height() const;
	
	// Presents the back buffer to the primary surface
	void flip();

	// Gets a pointer to the main gfx object
	static GraphicsLayer* getGraphics()
	{
		return m_pGraphicsLayer;
	}

	// Initializes this object
	static void create(
		HWND hWnd, // handle to the window
		short width, short height, // width and height
		GUID* pGuid ); // Device guid
		
	//-----------------------------------------------------------------------------
	// Name: DDLoadPalette()
	// Desc: Create a DirectDraw palette object from a bitmap resource
	//       if the resource does not exist or NULL is passed create a
	//       default 332 palette.
	//-----------------------------------------------------------------------------
	IDirectDrawPalette  *DDLoadPalette(LPDIRECTDRAW7 pdd, LPCSTR szBitmap );



	//-----------------------------------------------------------------------------
	// Name: DDLoadBitmap()
	// Desc: Create a DirectDrawSurface from a bitmap resource with the given size.
	//-----------------------------------------------------------------------------
	LPDIRECTDRAWSURFACE7 DDLoadBitmap(LPDIRECTDRAW7 pdd, LPCSTR szBitmap, int dx, int dy);


	//-----------------------------------------------------------------------------
	// Name: DDReLoadBitmap()
	// Desc: Load a bitmap from a file or resource into a directdraw surface.
	//       normaly used to re-load a surface after a restore.
	//-----------------------------------------------------------------------------
	HRESULT DDReLoadBitmap(LPDIRECTDRAWSURFACE7 pdds, LPCSTR szBitmap );



	//-----------------------------------------------------------------------------
	// Name: DDCopyBitmap()
	// Desc: Draw a bitmap into a DirectDrawSurface. This function is called in DDLoadBitmap
	//-----------------------------------------------------------------------------
	HRESULT DDCopyBitmap(LPDIRECTDRAWSURFACE7 pdds, HBITMAP hbm, int x, int y, int dx, int dy );




	//-----------------------------------------------------------------------------
	// Name: DDColorMatch()
	// Desc: Convert a RGB color to a pysical color.
	//       We do this by leting GDI SetPixel() do the color matching
	//       then we lock the memory and see what it got mapped to.
	//-----------------------------------------------------------------------------
	DWORD DDColorMatch(LPDIRECTDRAWSURFACE7 pdds, COLORREF rgb );

	//-----------------------------------------------------------------------------
	// Name: DDSetColorKey()
	// Desc: Set a color key for a surface, given a RGB.
	//       If you pass CLR_INVALID as the color key, the pixel
	//       in the upper-left corner will be used.
	//-----------------------------------------------------------------------------
	HRESULT DDSetColorKey(LPDIRECTDRAWSURFACE7 pdds, COLORREF rgb );

};

inline GraphicsLayer* Graphics()
{
	return GraphicsLayer::getGraphics();
}

/*
struct PANELVERTEX
{
    FLOAT x, y, z;
    DWORD color;
    FLOAT u, v;
};

#define D3DFVF_PANELVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
  */

#endif