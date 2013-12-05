#include "Shaders.h"

Shader Shaders::diffuse;
Shader Shaders::terrain;
Shader Shaders::emit;

void Shaders::init() {
	diffuse.init( "Diffuse.vert", "Diffuse.frag" );
	terrain.init( "Terrain.vert", "Terrain.frag" );
	emit.init( "Emit.vert", "Emit.frag" );
}