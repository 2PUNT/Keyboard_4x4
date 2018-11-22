#ifndef KEYBOARD_4X4_HPP
#define KEYBOARD_4X4_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "IKeyboardListener.hpp"

// Template parameter N is the max amount of listeners
///@class Keyboard_4x4 A class that represents a 4x4 keyboard.
/// This class is a task, and will poll the keyBoard and let the listeners know that a key has been pressed by calling the function KeyboardKeyPressed()
template<int N>
class Keyboard_4x4: public rtos::task<>{
private:
	rtos::clock KeyBoardClock;
	
	hwlib::keypad<16> keyBoard;
	IKeyboardListener* listeners[N];
	int listenersSize;
	char pressedChar;
public:
	///@fn Keyboard_4x4::Keyboard_4x4(hwlib::keypad<16> _keyBoard, const unsigned int priority, const char* name)
    ///@brief The constructor for the Keyboard_4x4 class.
    ///@details This constructor creates a Keyboard_4x4 object.
	///@param _keyBoard A @c keypad object.
	///@param priority The priority of the keyboard.
	///@param name The name of the keyboard.
	Keyboard_4x4(hwlib::keypad<16> _keyBoard, const unsigned int priority, const char* name):
		task(priority, name ), KeyBoardClock(this, 50000, "KeyBoardClock"),
		keyBoard(_keyBoard), listenersSize(0){}
	
	///@fn void Keyboard_4x4::setKeyboardListener(IKeyboardListener* Listener)
    ///@brief Set IKeyboardListener.
    ///@details This method sets the listeners.
    ///@param Listener A listener.
	void setKeyboardListener(IKeyboardListener* Listener){
		if(listenersSize == N){ hwlib::cout << "Maximum listeners reached!\n"; return;}
		listeners[listenersSize] = Listener;
		listenersSize++;
	}
	
	///@fn void Keyboard_4x4::main()
    ///@brief The main of the Button task.
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