#pragma once
#include <iostream>
class MeshLoadInfo{
public:
	enum CollisionType{
		DYNAMIC,	//physics applied
		STATIC,		//doesn't move, e.g. ground
		KINEMATIC	//moves, but isn't affected by physics (no gravity, isn't pushed by other objects). e.g moving platform. 
	};

	enum CollisionShapeType{
		CONVEX,
		SPHERE,
		BOX,
		CAPSULE,
		TRIANGLE, //can only be kinematic
	};

	struct ShaderLoadInfo {
		const std::string vertexShaderPath;
		const std::string fragmentShaderPath;
		const std::string geometryShaderPath;
		ShaderLoadInfo(const std::string& vShaderPath, const std::string& fShaderPath) : fragmentShaderPath(fShaderPath), vertexShaderPath(vShaderPath){}
		ShaderLoadInfo(const std::string& vShaderPath, const std::string& gShaderPath,const std::string& fShaderPath) : fragmentShaderPath(fShaderPath), geometryShaderPath(gShaderPath), vertexShaderPath(vShaderPath){}
	};
	static const ShaderLoadInfo* LIGHTING_SHADER;
	static const ShaderLoadInfo* TEXTURE_SHADER;
	static const ShaderLoadInfo* SIMPLE_LIGHTING_SHADER;


	struct LoadInfo {
		const std::string meshPath;
		const std::string texturePath;
		const ShaderLoadInfo* shaderInfo;
		const CollisionType collisionType;
		const CollisionShapeType collisionShapeType;
		LoadInfo(const std::string& mPath, const std::string& tPath, const ShaderLoadInfo* sInfo, const CollisionType cType, const CollisionShapeType cSType) : meshPath(mPath), texturePath(tPath), shaderInfo(sInfo), collisionType(cType), collisionShapeType(cSType){}
	};
	static const LoadInfo* CYLINDER;
};