#ifndef KEYBOARD_4X4_HPP
#define KEYBOARD_4X4_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "IKeyboardListener.hpp"

// Template parameter N is the max amount of listeners
template<int N>
class Keyboard_4x4: public rtos::task<>{
private:
	rtos::clock KeyBoardClock;
	
	hwlib::keypad<16> keyBoard;
	IKeyboardListener* listeners[N];
	int listenersSize;
	char pressedChar;
public:
	Keyboard_4x4(hwlib::keypad<16> _keyBoard, const unsigned int priority, const char* name):
		task(priority, name ), KeyBoardClock(this, 50000, "KeyBoardClock"),
		keyBoard(_keyBoard), listenersSize(0){}
	
	void setKeyboardListener(IKeyboardListener* Listener){
		if(listenersSize == N){ hwlib::cout << "Maximum listeners reached!\n"; return;}
		listeners[listenersSize] = Listener;
		listenersSize++;
	}
	
	void main(){
		while(true){
			wait(KeyBoardClock);
			if(keyBoard.char_available()){
				pressedChar = keyBoard.getc();
				for(int i=0; i<listenersSize; i++){
					listeners[i] -> KeyboardKeyPressed(pressedChar);
				}
			}
		}
	}
	
};

#endif