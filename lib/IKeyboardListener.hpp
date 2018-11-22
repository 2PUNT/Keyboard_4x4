#ifndef IKEYBOARDLISTENER_HPP
#define IKEYBOARDLISTENER_HPP

class IKeyboardListener{
public:
	///@fn virtual void IKeyboardListener::KeyboardKeyPressed(char Key)=0
    ///@param ButtonID A key from the keyboard.
	virtual void KeyboardKeyPressed(char Key) = 0;
};

#endif