#include "KeyBoadEvent.h"

/**
* @brief “ü—Íó‘Ô‚ğ’²‚×‚é
*/
void KeyBoadEvent::Accepts() {
	//Œ…ã‚ª‚è–h~
	cflag_	= 0;
	sflag_	= 0;
	direct_ = Vector2::Zero;

	//Šeƒrƒbƒg‚É“ü—Íó‘Ô‚ğ“ü‚ê‚é
	cflag_ |= (bool)DXTK->KeyEvent->pressed.A				<< A    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.B				<< B    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.C				<< C    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.D				<< D    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.E				<< E    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.F				<< F    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.G				<< G    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.H				<< H    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.I				<< I    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.J				<< J    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.K				<< K    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.L				<< L    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.M				<< M    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.N				<< N    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.O				<< O    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.P				<< P    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.Q				<< Q    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.R				<< R    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.S				<< S    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.T				<< T    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.U				<< U    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.V				<< V    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.W				<< W    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.X				<< X    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.Y				<< Y    ;
	cflag_ |= (bool)DXTK->KeyEvent->pressed.Z				<< Z    ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Up				<< UP   ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Down			<< DOWN ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Left			<< LEFT ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Right			<< RIGHT;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Tab				<< TAB	;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Space			<< SPACE;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.LeftAlt			<< LALT ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.RightAlt		<< RALT ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.LeftControl		<< LCTRL;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.RightControl	<< RCTRL;
}