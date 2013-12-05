#pragma once

#include "stdafx.h"
#include "Vector3.h"

class Mesh
{
public:
    Mesh();
	~Mesh();

	void						clear();

	void						dumpFile();
    bool						readOBJ( std::string );
	void						sortNormals();
	void						sortTextureCoordinates();
    void						render();
	void						renderNode( const aiScene*, const aiNode* );

	Vector3&					getVert( int i, Vector3* );		//the caller must allocate some memory so the memory 
	Vector3&					getNormal( int i, Vector3* );	//won't soon go out of scope
	int							numVerts() {return vCount;};
	int							numFaces() {return fCount;};

private:
    std::vector<Vector3>		vVerts;
	std::vector<Vector3>		vNorms;
	std::vector<int>			vFaceNorms;
	std::vector<int>			vFaces;
	std::vector<int>			vFaceTexCoords;
	std::vector<Vector3>		vTexCoords;
	char						*shaderPath;
	float						*fVerts, *fNorms, *fTexCoords;
	int							*iFaces;
	int							vCount, fCount;
	 
	int							lastPos, fVertsSize, fNormsSize, iFacesSize, iFaceNormsSize, fTexCordsSize;
	int							shader;

	bool						firstRender;
		
	std::ifstream				file;
	std::ofstream				impOut;

	const aiScene				*scene;
};