#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}
// only saving boids weight for assignment 3. can implement rest if needed with same pattern one per line;
void DataManager::save()
{
	std::ofstream saveFile;

	saveFile.open(SAVE_FILE);

	saveFile << gpGame->getValue(AlignWeight) << std::endl
		<< gpGame->getValue(CohesionWeight) << std::endl
		<< gpGame->getValue(SeperateWeight);
	
	saveFile.close();

}

void DataManager::load()
{
	// align, cohesion, seperation;
	int a, c, s;

	std::ifstream saveFile;

	saveFile.open(SAVE_FILE);

	if (saveFile.is_open())
	{
		saveFile >> a >> c >> s;
	}

	saveFile.close();

	gpGame->setValue(AlignWeight,a);
	gpGame->setValue(CohesionWeight,c);
	gpGame->setValue(SeperateWeight,s);

}
