#include "Terrain.h"

Terrain::Terrain(void) {
	init();
}

Terrain::Terrain( int seed ) : heightMap( seed ), grassMap( seed ) {
	init();
}

void Terrain::init() {
	glPointSize( 5.0f );
	size = 256;
	vertexes = new GLfloat[size*size*3];
	colors = new GLfloat[size*size*3];
	texCoords = new GLfloat[size*size*3];
	faces = new int[size*size];

	for( int i = 0; i < size*size*3; i += 3 ) {
		vertexes[i] = ((i%size) - size/2) * 5;
		vertexes[i+1] = 0;
		vertexes[i+2] = ((i/size) - size/2) * 5;

		texCoords[i] = vertexes[i]/float(size*5) * 300;
		texCoords[i+1] = vertexes[i+2]/float(size*5) * 300;
		texCoords[i+2] = 0;

		if( i%150 == 0 ) {
			Tree t;
			t.getTransform().moveTo( Vector3( vertexes[i], 0, vertexes[i+2] ) );
			t.show();
			trees.push_back( t );
		}
	}

	for( int i = 0; i < size-1; i++ ) {
		for( int j = 0; j < size; j += 2 ) {
			faces[i*size + j] = i*size + j;
			faces[i*size + j + 1] = (i+1)*size + j;
		}
	}
}

void Terrain::loadData() {
	desert = TextureLoader::loadTexture( "Sand.jpg", NULL );
	grass = TextureLoader::loadTexture( "Grass.jpg", NULL );
	grassMap.makeGLTex();
	Shaders::getTerrain().setVariable( "sandTex", 0 );
	Shaders::getTerrain().setVariable( "grassTex", 1 );
	Shaders::getTerrain().setVariable( "grassMap", 3 );
	for( Tree &t : trees ) {
		t.init();
	}
}

Terrain::~Terrain(void) {
	delete[] vertexes;
	delete[] colors;
}

void Terrain::update( Vector3 playerPos ) {
	pDistToTemple = Vector3::distance( playerPos, Vector3( 0, 0, 0 ) );	//distance from the player to the spawn point
	float blendFactor;
	greenChance = Globals::battleFactor * pDistToTemple / 256.0f;	//make sure that greenChance is between 0 and 1
	if( greenChance > 1 ) {
		greenChance = 1;
	} else if( greenChance < 0 ) {
		greenChance = 0;
	}
	GLuint height;
	for( int i = 0; i < size*size*3; i+=3 ) {
		//calculate the height of each vertex.
		blendFactor = pDistToTemple * min( abs( vertexes[i] ), 256 ) * Globals::battleFactor / 65536.0f;
		height = heightMap.getPixelBilinear( float(i%size)/float(size), float(i/size)/float(size) );
		vertexes[i+1] = height * blendFactor / 5;	//blend the heightmap in
	}
	/*Vector3 treePos;
	for( int i = 0; i < trees.size(); i++ ) {
		treePos = trees[i].getTransform().getPosition();
		if( greenChance * 256 > grassMap.getPixelBilinear( treePos.getX()/float(size*5), treePos.getY()/float(size*5) ) ) {
			trees[i].show();
			trees[i].setHeight( sampleHeight( treePos ) );
		} else {
			trees[i].hide();
		}
	}*/
}

void Terrain::render( Vector3 lightDir ) {
	float blendFactor;
	int ter = Shaders::getTerrain().id();
	Shaders::getTerrain().bind();
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, desert );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, grass );
	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, grassMap.getGLID() );
	Shaders::getTerrain().setVariable( "light_normal", lightDir );
	Shaders::getTerrain().setVariable( "grassChance", greenChance );
	size *= 3;
	for( int j = 0; j < (size/3)-3; j++ ) {				//render each loop in the terrain. J is y
		glBegin( GL_TRIANGLE_STRIP );
		for( int i = 0; i < (size/3)-3; i += 3 ) {		//draw a vertex, then the one below it. I is x	
			glMultiTexCoord2fv( GL_TEXTURE0, &texCoords[i + (j*size)] );
			glMultiTexCoord2fv( GL_TEXTURE1, &texCoords[i + (j*size)] );
			glVertex3fv( &vertexes[i + (j*size)] );

			glMultiTexCoord2fv( GL_TEXTURE0, &texCoords[i + size + (j*size)] );
			glMultiTexCoord2fv( GL_TEXTURE1, &texCoords[i + size + (j*size)] );
			glVertex3fv( &vertexes[i + size + (j*size)] );
		}
		glEnd();
	}
	size /= 3;
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	Shaders::getDiffuse().bind();
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, trees[0].getTexture() );
	glBegin( GL_QUADS );
	//for( Tree &t : trees ) {
		//t.render();
	//}
	glEnd();
}

float Terrain::sampleHeight( Vector3 pos ) {
	float u = pos.getX() - 0.5;
	float v = pos.getZ() - 0.5;
	int x = floor( u );
	int y = floor( v );
	float uRatio = u - x;
	float vRatio = v - y;
	float uOpposite = 1 - uRatio;
	float vOpposite = 1 - vRatio;
	return (vertexes[1 + x + y*32] * uOpposite + vertexes[x+3 + y*32 + 1] * uRatio) * vOpposite +
		(vertexes[x + (y+3)*32 + 1] * uOpposite + vertexes[x+3 + (y+3)*32 + 1] * uRatio) * vRatio;
}