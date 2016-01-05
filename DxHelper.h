#ifndef DXHELPER_H
#define DXHELPER_H

#include <memory.h>

// This template class zero the Windows and DirectX structures
template <class T>
struct sAutoZero : public T {

	sAutoZero() {

		memset( this, 0, sizeof(T) );
		dwSize = sizeof(T);
	}
};


// This template class release the COM object of DirectX 8
// If they are valid, release them and then invalid tem
template <class T>
inline void SafeRelease( T& iface ) {

	if( iface ) {

		iface->Release();
		iface = NULL;
	}
}

template <class T>
inline void SafeDelete( T& iface ) {

	if( iface ) {

		delete iface;
		iface = NULL;
	}
}

#endif 