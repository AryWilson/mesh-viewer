#version 400

#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

struct Material{
   float kd;
   float ks;
   float ka;
   vec3 col;
   float alpha;
};

struct Light{
   vec3 pos;
   vec3 col;
};

in vec3 nEye;
in vec3 pEye;

uniform Material material;
uniform Light light;

const int levels = 3;
const float sf = 1.0f/levels;

out vec4 FragColor;


void main()
{
    vec3 s = normalize(light.pos - pEye); // vPos
    float cosine = max(0.0, dot(s, nEye)); // vNormals
    if(cosine < 0.05){
        FragColor = {1.0,0.0,0.0,1.0};
    } else {
        vec3 diffuse = material.kd * floor(cosine * levels) * (scale);
        FragColor = {Light.intensity * (material.ka + diffuse),1.0f};
    }
}

