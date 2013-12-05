#include "Mesh.h"

/*!\brief Converts any string into a float, using the first occurance of a float.

\param[in] str A string with a float, with or without anything else.
\param[in,out] lastPos An integer used mostly by the Mesh reader to determine what to read.
	It should grow in size so that less and less of the line is passed to this functions.
\return The first float in str.*/
float strToFloat( std::string &str, int *lastPos )
{
	unsigned int start = -1, end = -1;
	bool isNum = false;
	for( unsigned int i = 0; i < str.length(); i++ )
	{
		isNum = false;
		if( int(str[i]) > 47 && int(str[i]) < 58 && start == -1 )
		{
			isNum = true;
			start = i;
		}
		else if( str[i] == '-' && start == -1 )
			start = i;
		else if( end == -1 && start != -1 )
			if( str[i] == ' ' )
			{
				end = i;
				i = str.length()+50;
			}
	}
	(*lastPos) += end+1;
	return (float)atof( str.substr(start, end).c_str() );
}

void Mesh::dumpFile() {
	std::ofstream file( "Out.OBJ" );
	file<<"#OBJ Debugging fun\n";
	for( Vector3 v : vVerts ) {
		file<<"v " <<v.getX() <<" " <<v.getY() <<" " <<v.getZ() <<"\n";
	}
	for( Vector3 v : vNorms ) {
		file<<"vn " <<v.getX() <<" " <<v.getY() <<" " <<v.getZ() <<"\n";
	}
	for( Vector3 v : vTexCoords ) {
		file<<"vt " <<v.getX() <<" " <<v.getY() <<" " <<v.getZ() <<"\n";
	}
	for( int i = 0; i < vFaces.size(); i++ ) {
		if( i%3 == 0 ) {
			file<<"\nf ";
		}
		file<<vFaces[i] <<"/" <<vFaceTexCoords[i] <<"/" <<vFaceNorms[i] <<" ";
	}
	file.close();
}

Mesh::Mesh() : impOut( "ImporterOutput.txt" )
{
	firstRender = true;
}

bool Mesh::readOBJ( std::string filename ) {
     /*std::string line;
	 vCount = 0;
	 fCount = 0;
     float factor = 0;
     bool writeToVerts = false, writeToNorms = false, writeToFaces = false, writeToTex = false;
     file.open( filename.c_str() );
     if( file.is_open() ) {  
		 float d;
		 int slashPos, begin;
         while( file.good() ) {
			  lastPos = 0;
              getline( file, line );
			  if( line.find( "v" ) == 0 && line.find( "n" ) == std::string::npos && line.find( "t" ) == std::string::npos )
			  {
				  writeToVerts = true;
				  writeToNorms = false;
				  writeToFaces = false;
				  writeToTex = false;
			  } else if( line.find( "vn" ) == 0 ) {
				  writeToTex = false;
				  writeToNorms = true;
				  writeToVerts = false;
				  writeToFaces = false;
			  } else if( line.find( "vt" ) == 0 ) {
				  writeToTex = true;
				  writeToFaces = false;
				  writeToVerts = false;
				  writeToNorms = false;
			  } else if( line.find( "f" ) == 0 ) {
				  writeToFaces = true;
				  writeToVerts = false;
				  writeToNorms = false;
				  writeToTex = false;
			  } else {
				  writeToFaces = false;
				  writeToVerts = false;
				  writeToNorms = false;
				  writeToTex = false;
			  }
			  if( writeToVerts || writeToNorms || writeToTex ) {		
				  Vector3 v;		
				  for( int i = 0; i < (writeToTex ? 2 : 3); i++ ) {
					  d = strToFloat( line.substr(lastPos), &lastPos );
					  if( writeToVerts ) {
						  vCount++;
					  }
					  v[i] = d;
				  }
				  if( writeToVerts ) {
					  vVerts.push_back( v );
				  } else if( writeToNorms ) {
					  vNorms.push_back( v );
				  } else if( writeToTex ) {
					  v[1] = 1-v[1];
					  vTexCoords.push_back( v );
				  }
			  } else if( writeToFaces ) {
				  int num;
				  slashPos = line.find( "/" )-1; 
				  begin = 1;
				  //grab the first vertex in this face
				  vFaces.push_back( atoi(line.substr( begin, slashPos ).c_str())-1 );
				  
				  begin = slashPos+2;
				  slashPos = line.find( "/", begin+1 )-1;
				  //grab the texture coordinate associated with this face
				  std::string subLine = line.substr( begin, slashPos );
				  vFaceTexCoords.push_back( atoi(subLine.c_str())-1 );

				  slashPos ++;
				  begin = line.find( " ", begin+1 );
				  //grab the normal associated with this vertex
				  vFaceNorms.push_back( atoi(line.substr( slashPos, begin ).c_str())-1 );

				  slashPos = line.find( "/", begin )-1;
				  //grab the second vertex in this face
				  vFaces.push_back( atoi(line.substr( begin, slashPos ).c_str())-1 );
				  
				  begin = slashPos+2;
				  slashPos = line.find( "/", begin+1 )-1;
				  //grab the texture coordinate associated with this face
				  vFaceTexCoords.push_back( atoi(line.substr( begin, slashPos ).c_str())-1 );

				  slashPos ++;
				  begin = line.find( " ", begin+1 );
				  //grab the normal associated with this vertex
				  vFaceNorms.push_back( atoi(line.substr( slashPos, begin ).c_str())-1 );

				  slashPos = line.find( "/", begin )-1;
				  //grab the third vertex in this face
				  vFaces.push_back( atoi(line.substr( begin, slashPos ).c_str())-1 );
				  
				  begin = slashPos+2;
				  slashPos = line.find( "/", begin+1 )-1;
				  //grab the texture coordinate associated with this face
				  vFaceTexCoords.push_back( atoi(line.substr( begin, slashPos ).c_str())-1 );

				  slashPos ++;
				  begin = line.find( " ", begin+1 );
				  //grab the normal associated with this vertex
				  vFaceNorms.push_back( atoi(line.substr( slashPos, begin ).c_str())-1 );
				  fCount ++;
			  }
		 }
		 //sortNormals();
		 //sortTextureCoordinates();
		 fVertsSize = vVerts.size();
		 fNormsSize = vNorms.size();
		 fTexCordsSize = vTexCoords.size();
		 iFacesSize = vFaces.size();
		 fVerts = new float[vVerts.size()*3];
		 fNorms = new float[vNorms.size()*3];
		 fTexCoords = new float[vFaces.size()*3];
		 iFaces = new int[iFacesSize];
		 int i;
		 for( i = 0; i < fVertsSize; i++ ) {
			 fVerts[i*3] = vVerts[i].getX();
			 fVerts[i*3+1] = vVerts[i].getY();
			 fVerts[i*3+2] = vVerts[i].getZ();
		 }
		 for( i = 0; i < fTexCordsSize; i++ ) {
			 fTexCoords[i*3] = vTexCoords[i].getX();
			 fTexCoords[i*3+1] = vTexCoords[i].getY();
			 fTexCoords[i*3+2] = vTexCoords[i].getZ();
		 }
		 for( i = 0; i < fNormsSize; i++ ){
			 fNorms[i*3] = vNorms[i].getX();
			 fNorms[i*3+1] = vNorms[i].getY();
			 fNorms[i*3+2] = vNorms[i].getZ();
		 }
		 for( i = 0; i < iFacesSize; i++ ) {
			 iFaces[i] = vFaces[i];
		 }
		 vCount /= 3;
		 file.close();
		 dumpFile();
		 return true;
	}
	impOut<<"ERROR: Could not open specified file\n";
	return false;*/
		scene = aiImportFile( filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs );
	return scene;
}

void Mesh::sortNormals()
{
	//loop through all the vertexes. Create a new vector<Vector3>. Load it with normals, one per vertex
	std::vector<Vector3> newNormals;
	for( int i : vFaceNorms )
		newNormals.push_back( vNorms[i] );
	vNorms = newNormals;
}

void Mesh::sortTextureCoordinates()
{
	//loop through all the vertexes. Create a new vector<Vector3>. Load it with texture coordinates, one per vertex
	std::vector<Vector3> newCoords;
	for( int i : vFaceTexCoords )
		newCoords.push_back( vTexCoords[i] );
	vTexCoords = newCoords;
}

void Mesh::render()
{
	renderNode( scene, scene->mRootNode );
}

//Mostly from http://assimp.svn.sourceforge.net/viewvc/assimp/trunk/samples/SimpleOpenGL/Sample_SimpleOpenGL.c?revision=1332&view=markup
void Mesh::renderNode( const aiScene *sc, const aiNode *nd ) {
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;
	
	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);
	
	// draw all meshes assigned to this node
	for( ; n < nd->mNumMeshes; ++n ) {
		const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
	
		if( mesh->mNormals == NULL ) {
			glDisable( GL_LIGHTING );
		} else {
			glEnable( GL_LIGHTING );
		}
	
		for( t = 0; t < mesh->mNumFaces; ++t ) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;
	
			switch( face->mNumIndices ) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}
	
			glBegin( face_mode );
	
			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if( mesh->mTextureCoords[0] != NULL ) {
					glTexCoord2fv( &mesh->mTextureCoords[0][index].x );
				}
				if( mesh->mColors[0] != NULL ) {
					glColor4fv( (GLfloat*)&mesh->mColors[0][index] );
				}
				if( mesh->mNormals != NULL ) {
					glNormal3fv( &mesh->mNormals[index].x );
				}
				glVertex3fv( &mesh->mVertices[index].x );
			}
			glEnd();
		}
	}
	
	// draw all children
	for( n = 0; n < nd->mNumChildren; ++n ) {
		renderNode( sc, nd->mChildren[n] );
	}
	glPopMatrix();
}

Vector3 &Mesh::getVert( int i, Vector3 *out )
{
	out = new Vector3( fVerts[i*3], fVerts[i*3 +1], fVerts[i*3 +2] );
	return *out;
}

Vector3 &Mesh::getNormal( int i, Vector3 *out )
{
	out = new Vector3( fNorms[i*3], fNorms[i*3 +1], fNorms[i*3 +2] );
	return *out;
}

Mesh::~Mesh()
{
	delete[] fVerts;
	delete[] fNorms;
	delete[] iFaces;
}

void Mesh::clear()
{
	delete[] fVerts;
	delete[] fNorms;
	delete[] iFaces;
	vFaces.clear();
	vVerts.clear();
	vNorms.clear();
	vFaceNorms.clear();
}