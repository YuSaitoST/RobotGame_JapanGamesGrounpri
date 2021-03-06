#include "ESDown.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"
#include "DontDestroyOnLoad.h"

void ESDown::Update(const int myID) {
	DontDestroy->score_.Addition(SCORE::BREAK_ENEMY);

	// まだリスト内に残っていれば削除
	if (EnemyManager::DoesThisIDexist(myID))
		EnemyManager::RemoveEnePosList(myID);
}