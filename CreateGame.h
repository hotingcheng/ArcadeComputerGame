#ifndef CreateGame_H
#define CreateGame_H


CApplication* createCApplication() {

	PlayerFactory *f = new ConcretePlayerFactory1;	
	return new StarWar(f);

//	return new StreetFighter;

} // The end of Method createCApplication




#endif