//--------------------------------------------------
// Author: Ary Wilson
// Date: 2/18/23
// Description: Loads PLY files in ASCII format
//--------------------------------------------------
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"


using namespace std;
using namespace glm;
using namespace agl;

struct Material{
   float ka;
   float kd;
   float ks;
   vec3 col;
   float alpha;
};

struct Light{
   vec3 pos;
   vec3 col;
};

class MeshViewer : public Window {
public:

   MeshViewer() : Window() {
      eyePos = vec3(7, 0, 0);
      lookPos = vec3(0, 0, 0);
      upDir = vec3(0, 1, 0);
      models = GetFilenamesInDir("../models", "ply");
      currentModel = 0;
      shaders = {"normals","phong-vertex","phong-pixel", "toon", "thermal"};
      currentShader = 0;
      mesh = PLYMesh("../models/cube.ply");

      radius = 10;
      azimuth = 0;
      elevation = 0;
      lRadius= 1;
      lElevation = 0;
      lAzimuth = 0;
      material = {0.2f,0.8f,0.5f,vec3(0.4f,0.4f,0.8f),10.0f};
      light = {upDir,vec3(1.0f,1.0f,1.0f)};
      colors = {vec3(0.4f,0.4f,0.8f),vec3(0.8f,0.05f,0.1f),vec3(0.9f,0.4f,0.1f),vec3(0.3f,0.7,0.3f),vec3(0.1f,0.1f,0.9f),vec3(.8,0,.8)};
      colIndx = 0;

   }

   void setup() {
      for(string s : shaders){
         renderer.loadShader(s, "../shaders/"+s+".vs", "../shaders/"+s+".fs");
      }
      // renderer.loadShader(shaders[0], "../shaders/normals.vs", "../shaders/normals.fs");
      // renderer.loadShader(shaders[1], "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
      // renderer.loadShader(shaders[2], "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
      // renderer.loadShader(shaders[3], "../shaders/toon.vs", "../shaders/toon.fs");
      // renderer.loadShader(shaders[4], "../shaders/blue.vs", "../shaders/blue.fs");
      // rendere.loadTexture("bricks","textures/bricks.png",0);

      // in vertex shader
      // vec3 c - color * texture(diffuseTexture,uv,1.0);
      // ouput from vertext shader texture vec2 coord


   }

   void mouseMotion(int x, int y, int dx, int dy) {
      if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
         azimuth -= dx*(0.02f);
         azimuth = fmod(azimuth,2*M_PI);

         elevation += dy*(0.02f);
         // elevation += M_PI_2;
         // elevation = fmod(elevation,M_PI);
         // elevation -= M_PI_2;

         if(elevation>=M_PI_2){elevation = M_PI_2 - 0.01f;}
         if(elevation<=-1*M_PI_2){elevation = -1*M_PI_2 + 0.01f;}

         //update angle?
         // x = radius * sin(azimuth) * cos(elevation)
         // y = radius * sin(elevation)
         // z = radius * cos(azimuth) * cos(elevation)
      } 
   }

   void mouseDown(int button, int mods) {
   }

   void mouseUp(int button, int mods) {
   }

   void scroll(float dx, float dy) {
      radius+=dy;
      if(radius<=0){
         radius = 1;
      }
   }

   void keyUp(int key, int mods) {

      if (key == 78 || key == 110){
         currentModel= (currentModel+1) % (models.size());
         mesh.clear();
         mesh = PLYMesh("../models/"+models[currentModel]);
         // cout << models[currentModel]<< endl;
         // cout<< mesh.minBounds()<<endl;
         // cout<< mesh.maxBounds()<<endl;

      } else if (key == 80 || key == 112){
         currentModel= (currentModel-1) % (models.size());
         mesh.clear();
         mesh = PLYMesh("../models/"+models[currentModel]);
         // cout << models[currentModel]<< endl;

      }  else if (key == 83 || key == 115){
         currentShader = ((currentShader + 1) % shaders.size());
      } else if (key == 77 || key == 109){
         material.col = colors[(++colIndx) % (colors.size())];

      }else if (key == GLFW_KEY_RIGHT){
         lAzimuth += 0.5f;
      } else if (key == GLFW_KEY_LEFT){
         lAzimuth -= 0.5f;
      } else if (key == GLFW_KEY_UP) {
         lElevation += 0.5f;
      }else if (key == GLFW_KEY_DOWN) {
         lElevation -= 0.5f;
      } 

      // mesh.load("../models/"+models[currentModel]);


   }

   void update(){

      float x = radius * sin(azimuth) * cos(elevation);
      float y = radius * sin(elevation);
      float z = radius * cos(azimuth) * cos(elevation);
      eyePos = vec3(x,y,z);

      x = radius * sin(lAzimuth) * cos(lElevation);
      y = radius * sin(lElevation);
      z = radius * cos(lAzimuth) * cos(lElevation);
      light.pos = vec3(x,y,z);
   }

// lookAt() changes the camera position and orientation
// translate() applies a translation transformation
// rotate() applies a rotation transformation
// scale() applies a scale transformation
// loockAt(vec3(0,0,0),lookPos,upDir);

//load in mesh



   void draw() {
      update();

      renderer.beginShader(shaders[currentShader]); // activates shader with given name
      // renderer.textureI"diffuseTexture","bricks");

      float aspect = ((float)width()) / height();
      // renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      // renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      // renderer.translate(vec3(0,0,0));
      // mesh.load("../models/"+models[currentModel]);
      // renderer.mesh(mesh);
      // renderer.cube(); // for debugging!

      //find bounding box
      vec3 bbMin = mesh.minBounds();
      vec3 bbMax = mesh.maxBounds();
      float bbCentx = (bbMin.x + bbMax.x)/2.0f;
      float bbCenty = (bbMin.y + bbMax.y)/2.0f;
      float bbCentz = (bbMin.z + bbMax.z)/2.0f;
      //translate bounding box to 0,0,0
      // renderer.translate(vec3(-1*bbCentx,-1*bbCenty,-1*bbCentz));
      float bbXlen = abs(bbMax.x - bbMin.x);
      float bbYlen = abs(bbMax.y - bbMin.y);
      float bbZlen = abs(bbMax.z - bbMin.z);
      float d = std::max(bbXlen,std::max(bbYlen,bbZlen));
      //scale bounding box to correct size, unit cube? camera at 0,0,0
      renderer.scale(vec3(1.0f/d, 1.0f/d, 1.0f/d));
      renderer.translate(vec3(-1*bbCentx,-1*bbCenty,-1*bbCentz));

      //translate bonuding box to unit cub coords?
      // renderer.translate(vec3(.5,.5,.5));
      //set camera position
      renderer.lookAt(eyePos,lookPos,upDir);
      //project
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      // renderer.mesh(mesh);

      
      renderer.mesh(mesh);

      
      renderer.setUniform("ViewMatrix", renderer.viewMatrix());
      renderer.setUniform("ProjMatrix", renderer.projectionMatrix());
      renderer.setUniform("eyePos", eyePos);
      renderer.setUniform("material.kd", material.kd);
      renderer.setUniform("material.ks", material.ks);
      renderer.setUniform("material.ka", material.ka);
      renderer.setUniform("material.col", material.col);
      renderer.setUniform("material.alpha", material.alpha);
      renderer.setUniform("light.pos", light.pos);
      renderer.setUniform("light.col", light.col);

      // all primitives draw here will use the current shader
      renderer.endShader();

   }

protected:
   PLYMesh mesh;
   vec3 eyePos;
   vec3 lookPos;
   vec3 upDir;
   vector<string> models;
   int currentModel;
   vector<string> shaders;
   int currentShader;
   float radius;
   float azimuth; // in [0, 360]
   float elevation; // in [-90, 90]
   Material material;
   Light light;
   float lRadius;
   float lElevation;
   float lAzimuth;
   vector<vec3> colors;
   int colIndx;


};

void fnExit(){
   cout << "hi" <<endl;
   // closedir();

}

int main(int argc, char** argv)
{
   atexit (fnExit);
   MeshViewer viewer;
   viewer.run();
   return 0;
}

