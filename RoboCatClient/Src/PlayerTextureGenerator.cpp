#include <RoboCatClientPCH.h>

std::unique_ptr<PlayerTextureGenerator> PlayerTextureGenerator::sInstance;

PlayerTextureGenerator::PlayerTextureGenerator()
{
	m_humanTextureIDs = {
		"hitman", 
		"hatman",
		"man_blue",
		"man_brown",
		"man_old",
		"robot",
		"soldier",
		"woman"
	};

	m_zombieTextureIDs = {
		"zombie"
	};
}

SFTexturePtr PlayerTextureGenerator::GetPlayerTexure(uint32_t p_id, std::string& p_team)
{

	return SFTextureManager::sInstance->GetTexture(ResolveID(p_id, p_team));
}

std::string PlayerTextureGenerator::ResolveID(uint32_t p_id, std::string& p_team)
{
	if (p_team.compare("human"))
	{
		return m_zombieTextureIDs[0];
	}
	else 
	{

		return m_humanTextureIDs[p_id % m_humanTextureIDs.size()];
	}
}

bool PlayerTextureGenerator::StaticInit()
{
	sInstance.reset(new PlayerTextureGenerator());
	return true;
}
