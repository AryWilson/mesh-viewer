#version 400

out vec3 nEye;
out vec3 pEye;

void main()
{
   nEye = normalize(NormalMatrix * vNormals);
   pEye = (ModelViewMatrix * vec4(vPos,1.0f)).xyz;
   gl_Position = MVP * vec4(vPos, 1.0);
}