#include "hwlib.hpp"
#include "rtos.hpp"

#include "IKeyboardListener.hpp"
#include "Keyboard_4x4.hpp"

class KeyboardListener_CoutDummy: public IKeyboardListener{
public:
	KeyboardListener_CoutDummy(){};
	void KeyboardKeyPressed(char c) override{
		hwlib::cout << "Character pressed: " << c << '\n';
	}
};

int main(void){
	
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms(500);
	
	hwlib::target::pin_oc keypadMatrix_out0 = hwlib::target::pin_oc(hwlib::target::pins::a11); //4
	hwlib::target::pin_oc keypadMatrix_out1 = hwlib::target::pin_oc(hwlib::target::pins::a10); //5
	hwlib::target::pin_oc keypadMatrix_out2 = hwlib::target::pin_oc(hwlib::target::pins::a9); //6
	hwlib::target::pin_oc keypadMatrix_out3 = hwlib::target::pin_oc(hwlib::target::pins::a8); //7
	
	hwlib::port_oc_from_pins keypadMatrix_openCollectorPort = hwlib::port_oc_from_pins(
		keypadMatrix_out0,
		keypadMatrix_out1,
		keypadMatrix_out2,
		keypadMatrix_out3
	);
	
	hwlib::target::pin_in keypadMatrix_in0 = hwlib::target::pin_in(hwlib::target::pins::a7); //3
	hwlib::target::pin_in keypadMatrix_in1 = hwlib::target::pin_in(hwlib::target::pins::a6); //2
	hwlib::target::pin_in keypadMatrix_in2 = hwlib::target::pin_in(hwlib::target::pins::a5); //1
	hwlib::target::pin_in keypadMatrix_in3 = hwlib::target::pin_in(hwlib::target::pins::a4); //0
	
	hwlib::port_in_from_pins keypadMatrix_inputPort = hwlib::port_in_from_pins(
		keypadMatrix_in0,
		keypadMatrix_in1,
		keypadMatrix_in2,
		keypadMatrix_in3
	);
	
	hwlib::matrix_of_switches keypadMatrix = hwlib::matrix_of_switches(keypadMatrix_openCollectorPort, keypadMatrix_inputPort);
	
	hwlib::keypad<16> keypad = hwlib::keypad<16>(keypadMatrix, "D#0*C987B654A321");
	
	Keyboard_4x4 keyboard = Keyboard_4x4<1>(keypad, 0, "TheKeyBoard");
	
	KeyboardListener_CoutDummy keyBoardDummy = KeyboardListener_CoutDummy();
	IKeyboardListener* keyBoardDummyBase = &keyBoardDummy;
	keyboard.setKeyboardListener(keyBoardDummyBase);
	
	rtos::run();
	
	return 0;
}
