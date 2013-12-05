varying vec3 vertex_normal;
varying vec3 halfVector;	//What is a half vector? It's the angle halfway between the vector from the light
      				//to the camera and from the viewer straight forward. It is useful for specular
   				//lighting
varying vec4 texCord;
varying vec4 diffuse;
varying vec4 ambient;
varying vec2 grassMapCoord;
float heightFac;

void main() {         
    //lighting calculations. They just are.
    vertex_normal = normalize(gl_NormalMatrix * gl_Normal);   
    /*halfVector = gl_LightSource[0].halfVector.xyz;
    diffuse = vec4( 1.0, 1.0, 1.0, 1.0 ) * gl_LightSource[0].diffuse;
    ambient = vec4( 1.0, 1.0, 1.0, 1.0 ) * gl_LightSource[0].ambient;
    ambient += gl_LightModel.ambient * vec4( 1.0, 1.0, 1.0, 1.0 );*/

    texCord = gl_MultiTexCoord0;
    vec4 vertPos = gl_Vertex;

    gl_Position = gl_ModelViewProjectionMatrix * vertPos;

    grassMapCoord.x = vertPos.x / (256.0 * 5.0);
    grassMapCoord.y = vertPos.z / (256.0 * 5.0);
}
