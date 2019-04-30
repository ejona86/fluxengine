#include "globals.h"
#include "image.h"
#include "sector.h"
#include "sectorset.h"

Sector*& SectorSet::get(int track, int head, int sector)
{
	key_t key(track, head, sector);
	return _data[key];
}

Sector* SectorSet::get(int track, int head, int sector) const
{
        key_t key(track, head, sector);
	auto i = _data.find(key);
	if (i == _data.end())
		return NULL;
	return i->second;
}

void SectorSet::calculateSize(int& numTracks, int& numHeads, int& numSectors,
	int& sectorSize) const
{
	numTracks = numHeads = numSectors = sectorSize = 0;

	for (auto& i : _data)
	{
		auto& sector = i.second;
		if (sector)
		{
			numTracks = std::max(numTracks, sector->logicalTrack+1);
			numHeads = std::max(numHeads, sector->logicalSide+1);
			numSectors = std::max(numSectors, sector->logicalSector+1);
			sectorSize = std::max(sectorSize, (int)sector->data.size());
		}
	}
}


