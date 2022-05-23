#include "KeyBoadState.h"

/**
* @brief “ü—Íó‘Ô‚ð’²‚×‚é
*/
void KeyBoadState::Accepts() {
	//Œ…ã‚ª‚è–hŽ~
	cflag_	= 0;
	sflag_  = 0;
	direct_ = Vector2::Zero;

	//Šeƒrƒbƒg‚É“ü—Íó‘Ô‚ð“ü‚ê‚é
	cflag_ |= (bool)DXTK->KeyState->A					<< A    ;
	cflag_ |= (bool)DXTK->KeyState->B					<< B    ;
	cflag_ |= (bool)DXTK->KeyState->C					<< C    ;
	cflag_ |= (bool)DXTK->KeyState->D					<< D    ;
	cflag_ |= (bool)DXTK->KeyState->E					<< E    ;
	cflag_ |= (bool)DXTK->KeyState->F					<< F    ;
	cflag_ |= (bool)DXTK->KeyState->G					<< G    ;
	cflag_ |= (bool)DXTK->KeyState->H					<< H    ;
	cflag_ |= (bool)DXTK->KeyState->I					<< I    ;
	cflag_ |= (bool)DXTK->KeyState->J					<< J    ;
	cflag_ |= (bool)DXTK->KeyState->K					<< K    ;
	cflag_ |= (bool)DXTK->KeyState->L					<< L    ;
	cflag_ |= (bool)DXTK->KeyState->M					<< M    ;
	cflag_ |= (bool)DXTK->KeyState->N					<< N    ;
	cflag_ |= (bool)DXTK->KeyState->O					<< O    ;
	cflag_ |= (bool)DXTK->KeyState->P					<< P    ;
	cflag_ |= (bool)DXTK->KeyState->Q					<< Q    ;
	cflag_ |= (bool)DXTK->KeyState->R					<< R    ;
	cflag_ |= (bool)DXTK->KeyState->S					<< S    ;
	cflag_ |= (bool)DXTK->KeyState->T					<< T    ;
	cflag_ |= (bool)DXTK->KeyState->U					<< U    ;
	cflag_ |= (bool)DXTK->KeyState->V					<< V    ;
	cflag_ |= (bool)DXTK->KeyState->W					<< W    ;
	cflag_ |= (bool)DXTK->KeyState->X					<< X    ;
	cflag_ |= (bool)DXTK->KeyState->Y					<< Y    ;
	cflag_ |= (bool)DXTK->KeyState->Z					<< Z    ;
	sflag_ |= (bool)DXTK->KeyState->Up					<< UP   ;
	sflag_ |= (bool)DXTK->KeyState->Down				<< DOWN ;
	sflag_ |= (bool)DXTK->KeyState->Left				<< LEFT ;
	sflag_ |= (bool)DXTK->KeyState->Right				<< RIGHT;
	sflag_ |= (bool)DXTK->KeyState->Tab					<< TAB	;
	sflag_ |= (bool)DXTK->KeyState->Space				<< SPACE;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Up			<< UP	;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Down		<< DOWN ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Left		<< LEFT ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Right		<< RIGHT;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Tab			<< TAB  ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.Space		<< SPACE;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.LeftAlt		<< LALT ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.RightAlt	<< RALT ;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.LeftControl << LCTRL;
	sflag_ |= (bool)DXTK->KeyEvent->pressed.RightControl<< RCTRL;
}