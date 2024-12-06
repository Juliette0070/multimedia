#version 150 core
// version du langage GLSL utilisée, ici 4.5

// in indique que la variable est fournie en entrée pour chaque point
// chaque point possède une position 3D
in vec3 in_pos;
in vec3 in_normal;

out vec4 color;
out vec3 lightDir;
out vec3 eyeVec;
out vec3 out_normal;

uniform mat4 v,m,p;

float random (vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}

void main(void)
{
    color = vec4(in_normal, 0.0);
    // color =in_pos;
    // calcul de la position du point une fois toutes les transformations appliquées

    gl_Position = p*v*m * vec4(in_pos, 1.0);
    // gl_Position = p*v*m * (vec4(in_pos, 1.0)+0.1*random(in_pos.xy));

    vec4 vVertex = v*m * vec4(in_pos, 1.0);
    eyeVec = -vVertex.xyz;

    vec4 LightSource_position=vec4(0.0,0.0,10.0,0.0)*m*v;
    lightDir=vec3(LightSource_position.xyz - vVertex.xyz);

    // out_normal = in_normal;
    // out_normal = vec3(v*m * vec4(in_normal, 0.0));
    out_normal = vec3(v*m*vec4(in_normal.x+0.2*random(in_pos.xy),in_normal.y+0.2*random(in_pos.xz),in_normal.z+0.2*random(in_pos.yz), 0.0));
}