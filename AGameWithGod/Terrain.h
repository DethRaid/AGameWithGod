#pragma once
#include "stdafx.h"

#include "Globals.h"
#include "PerlinTexture.h"
#include "Shaders.h"
#include "Tree.h"
#include "Vector3.h"

class Terrain
{
public:
	Terrain(void);
	Terrain( int );
	~Terrain(void);

	void init();
	void loadData();

	void render( Vector3 );
	void update( Vector3 );

	void addToBattleFactor( float f ) {battleFactor += f;};

	float sampleHeight( Vector3 );

private:
	float greenChance;
	float battleFactor;
	int size;
	GLfloat *colors;
	GLfloat *vertexes;
	GLfloat *texCoords;
	int *faces;
	std::vector<Tree> trees;
	PerlinTexture heightMap;	//we'll blend between the heightmap and a flat plane as the player approaches
								//the temple and as a vertex approaches infinity
	PerlinTexture grassMap;
	GLuint grass, desert;
	float pDistToTemple;
};

