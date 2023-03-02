//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

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
      models = GetFilenamesInDir("../models", "ply");
   }

   void setup() {
      // mesh.load("../models/cube.ply");
      // mesh.load(models[currentModel]);

   }

   void mouseMotion(int x, int y, int dx, int dy) {
      if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
         //update angle?
         // x = Radius * sin(Azimuth) * cos(Elevation)
         // y = Radius * sin(Elevation)
         // z = Radius * cos(Azimuth) * cos(Elevation)
      }
   }

   void mouseDown(int button, int mods) {
   }

   void mouseUp(int button, int mods) {
   }

   void scroll(float dx, float dy) {
      Radius+=dy;
   }

   void keyUp(int key, int mods) {

      if (key == 78 || key == 110){
         currentModel= (currentModel+1)% (models.size());

      } else if (key == 80|| key == 112){
         currentModel= (currentModel-1)% (models.size());
      }
   }

// lookAt() changes the camera position and orientation
// translate() applies a translation transformation
// rotate() applies a rotation transformation
// scale() applies a scale transformation




   void draw() {
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      renderer.rotate(vec3(0,0,0));
      renderer.scale(vec3(1,1,1));
      renderer.translate(vec3(0,0,0));
      // mesh.load(models[currentModel]);
      //renderer.mesh(mesh);
      renderer.cube(); // for debugging!
   }

protected:
   PLYMesh mesh;
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);
   vector<string> models;
   int currentModel;
   float Radius;
   float Azimuth;
   float Elevation;
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

