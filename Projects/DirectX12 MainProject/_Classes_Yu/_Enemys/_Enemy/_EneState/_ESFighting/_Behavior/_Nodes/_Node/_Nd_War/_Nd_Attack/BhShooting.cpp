#include "BhShooting.h"
#include "_Classes_Yu/_Enemys/EnemyManager.h"

using namespace DirectX::SimpleMath;

Action BhShooting::Behavior(const int myID) {
	Enemy* enemy				= EnemyManager::Access(myID);
	const float distance		= PlayerInfo.GetDistance(enemy->myPosition());
	const bool certainDistance	= (ENParams.RANGE_OF_MELEEATTACK < distance) && (distance <= ENParams.RANGE_OF_SHOOTING);
	const bool TooClose			= distance <= ENParams.UNAPPROACHABLE_DISTANCE;
	
	// Œü‚¢‚Ä‚¢‚é•ûŒü‚ÉƒvƒŒƒCƒ„[‚ª‚¢‚é‚©’²‚×‚é
	const float angle = AngleOf2Vector(PlayerInfo.GetDirection(enemy->myPosition()), Vector3(1.0f, 0.0f, 0.0f));
	const float angleAbs = std::abs(angle - enemy->GetRotateY());
	const bool direction = (angleAbs <= XM_PI * 0.6f);

	if (TooClose)
		return Action::FAILIRE;
	else if (certainDistance && direction)
		return enemy->Shooting();
	else
		enemy->ResetAttackState();

	return Action::FAILIRE;
}

float BhShooting::AngleOf2Vector(Vector3 a, Vector3 b){
	const float lenght_a = a.Length();
	const float lenght_b = b.Length();
	const float cosSita = a.Dot(b) / (lenght_a * lenght_b);
	return acos(cosSita);
}