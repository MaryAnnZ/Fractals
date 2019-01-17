#include "MeshImporter.h"

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>		
#include "../Util/UuidHelper.h"

#include <fstream>



std::string is_file_exist(const std::string& name)
{
	std::ifstream file(name);
	if (!file)            // If the file was not found, then file is 0, i.e. !file=1 or true.
		return "does not exist";    // The file was not found.
	else                 // If the file was found, then file is non-0.
		return "exists";     // The file was found.
}



MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}

MeshImporter* MeshImporter::getInstance(){
	static MeshImporter instance;
	return &instance;
}

void MeshImporter::loadMesh(const MeshLoadInfo::LoadInfo* loadInfo)
{
	const aiScene* aScene = aiImportFileEx(loadInfo->meshPath.c_str(),
		aiProcessPreset_TargetRealtime_Quality |
		aiProcess_JoinIdenticalVertices |
		aiProcess_FindInstances |
		aiProcess_ValidateDataStructure |
		aiProcess_OptimizeMeshes |
		aiProcess_Triangulate,
		NULL);

	if (!aScene)
	{
		std::cerr << "Failed to import" << loadInfo->meshPath << " file exists = " << is_file_exist(loadInfo->meshPath) << std::endl;
	}
	else if (aScene->HasMeshes())
	{
		std::cerr << "has Meshes " << aScene->HasMeshes() << std::endl;
		assets.insert(std::pair<const std::string*, const aiScene*>(&(loadInfo->meshPath), aScene));
	}
}

MeshNode* MeshImporter::getMesh(const MeshLoadInfo::LoadInfo* loadInfo)
{
	if (assets.count(&(loadInfo->meshPath)) == 0)
	{
		loadMesh(loadInfo);
	}
	const aiScene* scene = assets.find(&(loadInfo->meshPath))->second;
	return new MeshNode(generateUuid(), scene->mMeshes[0], loadInfo);
}

