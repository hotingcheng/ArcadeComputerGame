#ifndef GAMEERROR_H
#define GAMEERROR_H

#include <string>
using namespace std;

class GameError {

	string m_errorText;

public:

	GameError( const char* errorText ) {

		m_errorText = string( errorText );
	}

	string getText() {

		return m_errorText;
	}
};

//==========--------------------------  

enum eResult
{
	resAllGood		= 0, // function passed with flying colors
	resFalse		= 1, // function worked and returns value 'false'
	resFailed		= -1, // function failed miserably
	resNotImpl		= -2, // function has not been implemented
	resForceDWord = 0x7FFFFFFF
};

inline bool Succeeded( eResult in )
{
	if( in >= 0 )
		return true;
	return false;
}

inline bool Failed( eResult in )
{
	if( in < 0 )
		return true;
	return false;
}

#endif 