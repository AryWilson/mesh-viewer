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



const int levels = 3;

vec3 thermal[levels+1] = vec3[](vec3(0.0,0.0,0.4),vec3(0.5,0.0,0.5),vec3(0.9,0.0,0.0),vec3(1.0,1.0,0.0));
// vec3 pyche[levels+1] = vec3[](vec3(0.0,0.0,0.5),vec3(1.0,1.0,1.0),vec3(0.6,0.0,0.6),vec3(1.0,1.0,1.0));
// vec3 inverse[levels+1] = vec3[](vec3(1.0,1.0,1.0),vec3(0.1,0.8,0.1),vec3(0.1,0.2,0.8),vec3(0.3,0.0,0.3));
// vec3 blue[levels+1] = vec3[](vec3(0.0,0.0,0.5),vec3(0.0,0.8,0.8),vec3(0.0,1.0,0.0),vec3(1.0,1.0,0.0));
// vec3 pal[4][4] = vec3[][](blue,thermal,psyche,inverse);




out vec4 FragColor;

void main()
{

    vec3 s = normalize(light.pos - pEye); // vPos
    float cos = max(0.0, dot(s, nEye)); // vNormals
    // FragColor = vec4(blue[floor(cos*levels)], 1.0);
    float i = cos*levels - floor(cos*levels);
    float j = 1-i;
    
    vec3 a = thermal[ int(floor(cos*levels))];
    vec3 b = thermal[ int(ceil(cos*levels))];

    FragColor = vec4(j*a+i*b, 1.0);


}