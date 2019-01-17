#pragma once

#include <iostream>
#include <assimp\Importer.hpp>
#include <unordered_map>

#include "../SceneGraph/MeshNode.h"
#include "MeshLoadInfo.h"

//singleton
class MeshImporter
{
public:
	
	static MeshImporter* getInstance();
	
	MeshNode* getMesh(const MeshLoadInfo::LoadInfo* loadInfo);

	~MeshImporter();

private:
	//singleton
	MeshImporter();
	MeshImporter(MeshImporter const&);
	void operator=(MeshImporter const&);

	void loadMesh(const MeshLoadInfo::LoadInfo* loadInfo);

	std::unordered_map<const std::string*, const aiScene*> assets;

};

