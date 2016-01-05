#ifndef _SOUND_H
#define _SOUND_H

#pragma warning( disable : 4786 )

#include <map>
using std::map;


#include "SoundLayer.h"
#include "Wavread.h"
#include "GameType.h"

class cSound  
{
	CWaveSoundRead*     m_pWaveSoundRead;
	LPDIRECTSOUNDBUFFER8	m_pBuffer;
	int					m_bufferSize;

	/**
	 * Multiple sounds that use the same
	 * file shouldn't re-read it, they should
	 * share the CWSR object.  This map
	 * implements rudimentary reference counting.
	 * I would have just changed CWaveSoundRead,
	 * but I wanted to keep it unchanged from the
	 * samples.
	 */
	static std::map< CWaveSoundRead*, int > m_waveMap;

	void Init();

public:
	cSound( char* filename );
	cSound( cSound& in );
	cSound& operator=( const cSound &in );

	virtual ~cSound();

	void Restore();
	void Fill();
	void Play( bool bLoop = false );

	bool IsPlaying();

};

#endif //_SOUND_H
