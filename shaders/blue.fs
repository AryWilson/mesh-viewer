#version 400

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

const int levels = 5;
const float sf = 1.0f/levels;
vector<vec3> blue = {vec3(1,1,1),vec3(1,1,0),vec3(0,1,0),vec3(0,0.8,0.8),vec3(0,0,0.5), vec3(0,0,0)};


out vec4 FragColor;

void main()
{
    vec3 s = normalize(light.pos - pEye); // vPos
    float cos = max(0.0, dot(s, nEye)); // vNormals
    // FragColor = vec4(blue[floor(cos*levels)], 1.0);

    int i = fmod(cos,1);
    int j = 1-i;
    
    vec3 a = blue[floor(cos*levels)];
    vec3 b = blue[ceil(cos*levels)];1.1

    FragColor = vec4(j*a+i*b, 1.0);


}