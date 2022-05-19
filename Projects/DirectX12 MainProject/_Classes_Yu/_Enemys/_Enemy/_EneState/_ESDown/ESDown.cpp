#include "ESDown.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "DontDestroyOnLoad.h"

void ESDown::Update(const int myID) {
	DontDestroy->score_.Addition(SCORE::BREAK_ENEMY);

	// ‚Ü‚¾ƒŠƒXƒg“à‚Éc‚Á‚Ä‚¢‚ê‚Îíœ
	if (EnemyManager::DoesThisIDexist(myID))
		EnemyManager::RemoveEnePosList(myID);
}