#version 150 core

out vec4 frag_color;
in vec3 lightDir;
in vec3 eyeVec;
in vec3 out_normal;

void main( void )
{
    vec3 L = normalize(lightDir);
    vec3 N = normalize(out_normal);

    float intensity = max(dot(L,N),0.0);
    vec4 final_color = vec4(0.1,0.1,0.1, 1.0);
    final_color += vec4(0.7*intensity,0.5*intensity,0.5*intensity, 1.0);

    vec3 E = normalize(eyeVec);
    vec3 R = reflect(-L, N);
    float specular = pow(max(dot(R, E), 0.0),10);
    final_color += vec4(0.8,0.0,0.0,1.0)*specular;
    frag_color = final_color;
}
