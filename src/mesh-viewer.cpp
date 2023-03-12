//--------------------------------------------------
// Author:
// Date:
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

class MeshViewer : public Window {
public:
   MeshViewer() : Window() {
      eyePos = vec3(7, 0, 0);
      lookPos = vec3(0, 0, 0);
      upDir = vec3(0, 1, 0);
      models = GetFilenamesInDir("../models", "ply");
      currentModel = 0;
      mesh = PLYMesh("../models/cube.ply");

      // mesh = PLYMesh("../models/shark.ply");
      radius = 10;
      azimuth = 0;
      elevation = 0;
   }

   void setup() {
      // mesh = PLYMesh("../models/shark.ply");
      // mesh = PLYMesh("../models/"+models[currentModel]);

      // mesh.load("../models/cube.ply");
      // mesh.load("../models/shark.ply");

      // mesh.load("../models/"+models[currentModel]);

   }

   void mouseMotion(int x, int y, int dx, int dy) {
      if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
         azimuth += dx*(0.05f);
         azimuth = fmod(azimuth,2*M_PI);

         elevation += dy*(0.05f);
         elevation += M_PI_2;
         elevation = fmod(elevation,M_PI);
         elevation -= M_PI_2;

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
         currentModel= (currentModel+1)% (models.size());
         mesh.clear();
         mesh = PLYMesh("../models/"+models[currentModel]);
         cout << models[currentModel]<< endl;
         cout<< mesh.minBounds()<<endl;
         cout<< mesh.maxBounds()<<endl;

      } else if (key == 80|| key == 112){
         currentModel= (currentModel-1)% (models.size());
         mesh.clear();
         mesh = PLYMesh("../models/"+models[currentModel]);
         cout << models[currentModel]<< endl;

      } else if (GLFW_KEY_UP){
         scroll(1,1);
      }
      else if (GLFW_KEY_DOWN){
         scroll(-1,-1);
      }
      // mesh.load("../models/"+models[currentModel]);


   }

   void update(){
      float x = radius * sin(azimuth) * cos(elevation);
      float y = radius * sin(elevation);
      float z = radius * cos(azimuth) * cos(elevation);
      eyePos = vec3(x,y,z);

   }

// lookAt() changes the camera position and orientation
// translate() applies a translation transformation
// rotate() applies a rotation transformation
// scale() applies a scale transformation
// loockAt(vec3(0,0,0),lookPos,upDir);

//load in mesh



   void draw() {
      update();
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
      renderer.translate(vec3(-1*bbCentx,-1*bbCenty,-1*bbCentz));
      float bbXlen = abs(bbMax.x - bbMin.x);
      float bbYlen = abs(bbMax.y - bbMin.y);
      float bbZlen = abs(bbMax.z - bbMin.z);
      //scale bounding box to correct size, unit cube? camera at 0,0,0
      renderer.scale(vec3(1.0f/bbXlen, 1.0f/bbYlen, 1.0f/bbZlen));
      //translate bonuding box to unit cub coords?
      // renderer.translate(vec3(.5,.5,.5));
      //set camera position
      renderer.lookAt(eyePos,lookPos,upDir);
      //project
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      renderer.mesh(mesh);
      



   }

protected:
   PLYMesh mesh;
   vec3 eyePos;
   vec3 lookPos;
   vec3 upDir;
   vector<string> models;
   int currentModel;
   float radius;
   float azimuth; // in [0, 360]
   float elevation; // in [-90, 90]
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

