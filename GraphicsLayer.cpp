#include <assert.h>

#include "GraphicsLayer.h"
#include "GameError.h"

// This is the static member variable that points to the one
// (and only one) graphics layer allowed in each application.   
GraphicsLayer* GraphicsLayer::m_pGraphicsLayer = NULL;

GraphicsLayer::GraphicsLayer( HWND hWnd ) {

	if( m_pGraphicsLayer )
	{
//		throw GameError( "GraphicsLayer object already instantiated\n");
	}
	else
	{
		m_pGraphicsLayer = this;

		m_hWnd = hWnd;
		lpDD = NULL;
		lpFrontBuffer = NULL;
		lpBackBuffer =NULL;
	}

} // The end of Constructor

// This method release all the DirectX COM object
void GraphicsLayer::destroyAll() {

    SafeRelease( lpBackBuffer );
	SafeRelease( lpFrontBuffer );
    SafeRelease( lpDD );

	m_pGraphicsLayer = NULL;

} // The end of Method DestroyAll

GraphicsLayer::~GraphicsLayer() {

	destroyAll();

} // The end of Method Destructor

// This method flip the content of the back buffer to the surface
void GraphicsLayer::flip() {

	HRESULT rval;

	rval = lpFrontBuffer->Flip( NULL, 0 );
	//rval = lpFrontBuffer->BltFast(0, 0, lpBackBuffer, NULL, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT );
	//rval = lpFrontBuffer->Blt( NULL, lpBackBuffer, NULL, DDBLT_WAIT , NULL);
	if ( rval != DD_OK )
		throw GameError("Error in BltFast function ");
	

} // The end of Method Flip

void GraphicsLayer::initFullScreen( 
	GUID* pGuid, int width, int height, int bpp ) {

	//DDCAPS				ddcaps;
    HRESULT				ddrval;
    DDSURFACEDESC2		ddsd;
    DDSCAPS2			ddscaps;
	LPDIRECTDRAW		pDD;
	DWORD dwTransType;
  
    
	ShowCursor(FALSE);

	// Create DirectDraw
	ddrval = DirectDrawCreate( NULL, &pDD, NULL );
    if( ddrval != DD_OK )
       throw GameError("Error in DirectDrawCreate function ");

    // Fetch DirectDraw7 interface
    ddrval = pDD->QueryInterface(IID_IDirectDraw7, (LPVOID*)&lpDD);
    if (ddrval != DD_OK)
        throw GameError("Error in QueryInterface function ");

	SafeRelease(pDD);

	// Set CooperativeLevel
    //ddrval = lpDD->SetCooperativeLevel(m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	ddrval = lpDD->SetCooperativeLevel(m_hWnd, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWMODEX);
    if( ddrval != DD_OK )
      throw GameError("Error in SetCooperativeLevel function ");

    // Set the Display Mode
    ddrval = lpDD->SetDisplayMode( width, height, 16, 0, 0 );
    if( ddrval != DD_OK )
      throw GameError("Error in SetDisplayMode function ");

     // Create surfaces
	dwTransType = DDBLTFAST_SRCCOLORKEY;
    memset( &ddsd, 0, sizeof( ddsd ) );
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
                          DDSCAPS_FLIP |
                          DDSCAPS_COMPLEX;
							
    ddsd.dwBackBufferCount = 1;
    ddrval = lpDD->CreateSurface(&ddsd, &lpFrontBuffer, NULL );
    if( ddrval != DD_OK )
      throw GameError("Error in CreateSurface function ");


    // get a pointer to the back buffer
    ZeroMemory(&ddscaps, sizeof(ddscaps));

//	ddscaps.dwSize = sizeof( ddscaps );
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = lpFrontBuffer->GetAttachedSurface(
                &ddscaps,
                &lpBackBuffer);
    if( ddrval != DD_OK )
		throw GameError("Error in GetAttachedSurface function ");

	
	if(FAILED(lpDD->CreateClipper(0,&pClipper,NULL)))
	{
//		TRACE("CreateClipper() failed. \n");
		throw GameError("Error in CreateClipper function ");
	}

/*	RECT ClipRect;//(0,0,640,480);	

	ClipRect.left = 0;
	ClipRect.top = 0;
	ClipRect.right = 640;
	ClipRect.bottom = 480;

	RGNDATA RgnData;	//this structure will be used in SetClipList()
	RgnData.rdh.dwSize=sizeof(RgnData.rdh);
	RgnData.rdh.iType=RDH_RECTANGLES;
	RgnData.rdh.nCount=1;
	RgnData.rdh.nRgnSize=sizeof(ClipRect);
	RgnData.rdh.rcBound=ClipRect;
	//move data from ClipRect , the length of ClipRect is 16
	memmove(&RgnData.Buffer[0],&ClipRect,16); 

	if(FAILED(pClipper->SetClipList(&RgnData,0)))
	{
//		TRACE("SetClipLiat() failed. \n");
		throw GameError("Error in SetClipLiat  ");
	}

	if(FAILED(lpBackBuffer->SetClipper(pClipper)))
	{
//		TRACE("SetClipLiat() failed. \n");
		throw GameError("Error in SetClipLiat  ");
	}
      
/*
	// Create and set the palette for the art bitmap
    lpArtPalette = DDLoadPalette( lpDD, MAKEINTRESOURCE(IDB_Leader1));
    if( NULL == lpArtPalette )
        throw GameError("Error in Create Palette");

    // set the palette before loading the art
    lpFrontBuffer->SetPalette(lpArtPalette );
*/

} // The end of Method initD3DFullScreen

LPDIRECTDRAW7 GraphicsLayer::getDirectDraw() const {

	return lpDD;

} // The end of Method getDirectDraw

LPDIRECTDRAWSURFACE7 GraphicsLayer::getFrontBuffer() const {

	return lpFrontBuffer;

} // The end of Method getFrontBuffer

LPDIRECTDRAWSURFACE7 GraphicsLayer::getBackBuffer() const {

	return lpBackBuffer;

} // The end of Method getBackBuffer

// Gets the screen width
int GraphicsLayer::width() const { return m_rcScreenRect.right; }

// Gets the screen height
int GraphicsLayer::height() const { return m_rcScreenRect.bottom; }

void GraphicsLayer::create(
	HWND hWnd,
	short width, short height,
	GUID* pGuid )
{
	new GraphicsLayer( hWnd ); // construct the object.

	// Init Direct3D and the device for fullscreen operation
	Graphics()->initFullScreen( pGuid, width, height, 16 );

} // The end of Method Create

LPDIRECTDRAWSURFACE7 GraphicsLayer::DDLoadBitmap(LPDIRECTDRAW7 pdd, LPCSTR szBitmap, int dx, int dy)
{
    HBITMAP                 hbm;
    BITMAP                  bm;
    sAutoZero<DDSURFACEDESC2>          ddsd;
    IDirectDrawSurface7    *pdds;

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx,
                              dy, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy,
                                  LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
        return NULL;
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    //
    // Create a DirectDrawSurface for this bitmap
    //
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;
    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
        return NULL;
    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    DeleteObject(hbm);
    return pdds;
}

HRESULT GraphicsLayer::DDReLoadBitmap(LPDIRECTDRAWSURFACE7 pdds, LPCSTR szBitmap) {

    HBITMAP                 hbm;
    HRESULT                 hr;

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0,
                              0, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0,
                                  LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
    {
        OutputDebugString("handle is null\n");
        return E_FAIL;
    }
    hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    if (hr != DD_OK)
    {
        OutputDebugString("ddcopybitmap failed\n");
    }
    DeleteObject(hbm);
    return hr;

} // The end of Method DDReLoadBitmap

HRESULT GraphicsLayer::DDCopyBitmap(LPDIRECTDRAWSURFACE7 pdds, HBITMAP hbm, int x, int y,
             int dx, int dy)
{
    HDC                     hdcImage;
    HDC                     hdc;
    BITMAP                  bm;
    DDSURFACEDESC2          ddsd;
    HRESULT                 hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;
    //
    // Make sure this surface is restored.
    //
    pdds->Restore();
    //
    // Select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
        OutputDebugString("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    dx = dx == 0 ? bm.bmWidth : dx;     // Use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;
    //
    // Get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y,
                   dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }
    DeleteDC(hdcImage);
    return hr;

} // The end of Method DDCopyBitmap

IDirectDrawPalette* GraphicsLayer::DDLoadPalette(LPDIRECTDRAW7 pdd, LPCSTR szBitmap) {

    IDirectDrawPalette     *ddpal;
    int                     i;
    int                     n;
    int                     fh;
    HRSRC                   h;
    LPBITMAPINFOHEADER      lpbi;
    PALETTEENTRY            ape[256];
    RGBQUAD                *prgb;

    //
    // Build a 332 palette as the default.
    //
    for (i = 0; i < 256; i++)
    {
        ape[i].peRed = (BYTE) (((i >> 5) & 0x07) * 255 / 7);
        ape[i].peGreen = (BYTE) (((i >> 2) & 0x07) * 255 / 7);
        ape[i].peBlue = (BYTE) (((i >> 0) & 0x03) * 255 / 3);
        ape[i].peFlags = (BYTE) 0;
    }
    //
    // Get a pointer to the bitmap resource.
    //
    if (szBitmap && (h = FindResource(NULL, szBitmap, RT_BITMAP)))
    {
        lpbi = (LPBITMAPINFOHEADER) LockResource(LoadResource(NULL, h));
        if (!lpbi)
            OutputDebugString("lock resource failed\n");
        prgb = (RGBQUAD *) ((BYTE *) lpbi + lpbi->biSize);
        if (lpbi == NULL || lpbi->biSize < sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (lpbi->biBitCount > 8)
            n = 0;
        else if (lpbi->biClrUsed == 0)
            n = 1 << lpbi->biBitCount;
        else
            n = lpbi->biClrUsed;
        //
        //  A DIB color table has its colors stored BGR not RGB
        //  so flip them around.
        //
        for (i = 0; i < n; i++)
        {
            ape[i].peRed = prgb[i].rgbRed;
            ape[i].peGreen = prgb[i].rgbGreen;
            ape[i].peBlue = prgb[i].rgbBlue;
            ape[i].peFlags = 0;
        }
    }
    else if (szBitmap && (fh = _lopen(szBitmap, OF_READ)) != -1)
    {
        BITMAPFILEHEADER        bf;
        BITMAPINFOHEADER        bi;

        _lread(fh, &bf, sizeof(bf));
        _lread(fh, &bi, sizeof(bi));
        _lread(fh, ape, sizeof(ape));
        _lclose(fh);
        if (bi.biSize != sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (bi.biBitCount > 8)
            n = 0;
        else if (bi.biClrUsed == 0)
            n = 1 << bi.biBitCount;
        else
            n = bi.biClrUsed;
        //
        //  A DIB color table has its colors stored BGR not RGB
        //  so flip them around.
        //
        for (i = 0; i < n; i++)
        {
            BYTE        r = ape[i].peRed;

            ape[i].peRed = ape[i].peBlue;
            ape[i].peBlue = r;
        }
    }
    pdd->CreatePalette(DDPCAPS_8BIT, ape, &ddpal, NULL);
    return ddpal;

} // The end of Method DDLoadPalette

DWORD GraphicsLayer::DDColorMatch(LPDIRECTDRAWSURFACE7 pdds, COLORREF rgb) {

    COLORREF                rgbT;
    HDC                     hdc;
    DWORD                   dw = CLR_INVALID;
    DDSURFACEDESC2          ddsd;
    HRESULT                 hres;

    //
    //  Use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
        SetPixel(hdc, 0, 0, rgb);       // Set our value
        pdds->ReleaseDC(hdc);
    }
    //
    // Now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;
    if (hres == DD_OK)
    {
        dw = *(DWORD *) ddsd.lpSurface;                 // Get DWORD
        if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32)
            dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;  // Mask it to bpp
        pdds->Unlock(NULL);
    }
    //
    //  Now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }
    return dw;

} // The end of Method DDColorMatch

HRESULT GraphicsLayer::DDSetColorKey(LPDIRECTDRAWSURFACE7 pdds, COLORREF rgb) {

    DDCOLORKEY              ddck;

    ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);

} // The end of Method DDSetColorKey


