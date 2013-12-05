#include "TextureLoader.h"

std::vector<Texture> TextureLoader::loadedTextures;

GLuint TextureLoader::loadTexture( std::string texName, GLubyte *data ) {
	if( loadedTextures.size() > 0 ) {
		for( Texture &t : loadedTextures ) {
			if( t.sName == texName ) {
				return t.glName;
			}
		}
	}
	GLuint *texture = new GLuint[1];
	FILE *file = fopen( texName.c_str(), "rb" );	//open filename as a read-only binary file
	int x, y, comp;	//actual x-dimension, y-dimension, and number of byter per pixel in the actual file
	data = stbi_load_from_file( file, &x, &y, &comp, 0 );
	fclose( file );

	glEnable( GL_TEXTURE_2D );

	glGenTextures( 1, texture );

	glBindTexture( GL_TEXTURE_2D, texture[0] );
	if( glIsTexture( texture[0] ) ) {
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

		if( comp == 3 ) {
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, x, y, GL_RGB, GL_UNSIGNED_BYTE, data );
		} else if( comp == 4 ) {
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, x, y, GL_RGBA, GL_UNSIGNED_BYTE, data );
		}

		const GLubyte *err = glewGetErrorString( glGetError() );

		std::ofstream out( "TextureLoaderOutput.txt", std::ios::app );
		out<<"\nError: " <<err <<"\nComp: " <<comp;

		Texture t;
		t.glName = texture[0];
		t.sName = texName;
		loadedTextures.push_back( t );

		return texture[0];
	}

	//delete file;
	return -1;
}
