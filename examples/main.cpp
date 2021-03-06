#include "hwlib.hpp"
#include "rtos.hpp"

#include "IKeyboardListener.hpp"
#include "Keyboard_4x4.hpp"

class KeyboardListener_CoutDummy: public IKeyboardListener{
public:
	KeyboardListener_CoutDummy(){};
	void KeyboardKeyPressed(char Key) override{
		hwlib::cout << Key << '\n';
	}
};

int main(void){
	
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms(500);
	
	namespace target = hwlib::target;
	auto out0 = target::pin_oc( target::pins::a0 );
	auto out1 = target::pin_oc( target::pins::a1 );
	auto out2 = target::pin_oc( target::pins::a2 );
	auto out3 = target::pin_oc( target::pins::a3 );
	
	auto in0  = target::pin_in( target::pins::a4 );
	auto in1  = target::pin_in( target::pins::a5 );
	auto in2  = target::pin_in( target::pins::a6 );
	auto in3  = target::pin_in( target::pins::a7 );
	
	auto out_port = hwlib::port_oc_from_pins( out0, out1, out2, out3 );
	auto in_port  = hwlib::port_in_from_pins( in0,  in1,  in2,  in3  );
	auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
	auto keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );
	
	auto keyboard = Keyboard_4x4<1>(keypad, 0, "TheKeyBoard");
	
	KeyboardListener_CoutDummy keyBoardDummy = KeyboardListener_CoutDummy();
	IKeyboardListener* keyBoardDummyBase = &keyBoardDummy;
	keyboard.setKeyboardListener(keyBoardDummyBase);
	
	rtos::run();
	
	return 0;
}
