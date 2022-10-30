#include "stdafx.h"
#include "cImprCombManager.h"
#include <Spore\Simulator\cGameTerrainCursor.h>

cImprCombManager::cImprCombManager()
{
}


cImprCombManager::~cImprCombManager()
{
}

// For internal use, do not modify.
int cImprCombManager::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cImprCombManager::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cImprCombManager::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cImprCombManager);
	return nullptr;
}

bool ModelFilter(Graphics::Model* model)
{
	// I don't know if cStar is the type you are looking for

	if (object_cast<Simulator::cCombatant>(model->GetOwner()))
	{
		auto combatant = (object_cast<Simulator::cCombatant>(model->GetOwner()));

		if (combatant->mHealthPoints <= 0)
		{
			return false;
		}

		if (combatant->field_80 != 0 || combatant->field_8 == 1)
		{
			return false;
		}

		if (object_cast<Simulator::cCreatureAnimal>(combatant) == GameNounManager.GetAvatar())
		{
			return false;
		}

		if (object_cast<Simulator::cBuilding>(model->GetOwner()))
		{
				return true;
		}
		else if (object_cast<Simulator::cLocomotiveObject>(model->GetOwner()))
		{
			return true;
		}
	}
	else return false;
}

void cImprCombManager::Update()
{
	if (Simulator::IsScenarioMode() && ScenarioMode.GetMode() == App::cScenarioMode::Mode::PlayMode)
	{
		Vector3 cameraPosition, mouseDir;
		cCreatureAnimalPtr avatar = GameNounManager.GetAvatar();
		App::GetViewer()->GetCameraToMouse(cameraPosition, mouseDir);
		cGameDataPtr object;
		Vector3 intersection;
		
		//auto cursor = Simulator::cGameTerrainCursor::GetTerrainCursor();
		//Vector3 position = cursor->GetPosition();

		GameViewManager.Raycast(cameraPosition, cameraPosition + mouseDir * 1000.0f, ModelFilter, object, intersection,true);

		Simulator::cCombatant* comb;

		if (comb = object_cast<Simulator::cCombatant>(object))
		{
			avatar->mpCombatantTarget = comb;
		}
		else
		{
			if (avatar->mpCombatantTarget != nullptr)
			{
				//Vector3 dist = avatar->mpCombatantTarget->ToSpatialObject()->GetPosition() - avatar->GetPosition();

				//SporeDebugPrint(to_string(dist.Length()).c_str());
				//SporeDebugPrint(to_string(1.5 * max(avatar->mScale, comb->ToSpatialObject()->mScale)).c_str());

				//if (dist.Length() > 1.5 * avatar->GetScale())
					avatar->mpCombatantTarget = nullptr;
			}
		}

	}
}
