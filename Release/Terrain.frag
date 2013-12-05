uniform vec3 light_normal;
uniform sampler2D sandTex;
uniform sampler2D grassTex;
uniform sampler2D grassMap;
uniform float grassChance;

varying vec3 vertex_normal;
varying vec4 texCord;
varying vec2 grassMapCoord;

void main() {
    vec4 color;
    vec3 lightNormal = light_normal;
    float gMP;

    //some lighting calculations
    lightNormal = normalize( gl_NormalMatrix * lightNormal );
    float diff = max( dot(vertex_normal, lightNormal), 0.5 );

    gMP = texture2D( grassMap, grassMapCoord.st ).r;

    if( grassChance > gMP ) {
        gMP = grassChance - gMP;
        gMP = min( gMP / 0.1, 1.0 );
        color = texture2D( grassTex, texCord.st ) * gMP;
        color = color + vec4( 1.0, 0.85, 0.466, 1.0 ) * (1 - gMP);
    } else {
        color = vec4( 1.0, 0.85, 0.466, 1.0 );
    }
    gl_FragColor = color;
}