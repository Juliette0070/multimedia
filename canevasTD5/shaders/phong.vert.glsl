#version 150 core
// version du langage GLSL utilisée, ici 4.5

in vec3 in_pos;
in vec3 in_normal;

out vec3 lightDir;
out vec3 eyeVec;
out vec3 out_normal;

uniform mat4 v,m,p;

void main(void)
{
    gl_Position = p*v*m * vec4(in_pos, 1.0);

    vec4 vVertex = v*m * vec4(in_pos, 1.0);
    eyeVec = -vVertex.xyz;

    vec4 LightSource_position=vec4(0.0,0.0,10.0,0.0);
    lightDir=vec3(LightSource_position.xyz - vVertex.xyz);

    out_normal = vec3(v*m * vec4(in_normal, 0.0));
}
