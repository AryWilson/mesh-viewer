//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "plymesh.h"

using namespace std;
using namespace glm;

namespace agl {

   PLYMesh::PLYMesh(const std::string& filename) {
      load(filename);
   }

   PLYMesh::PLYMesh() {
   }

   void PLYMesh::init() {
      assert(_positions.size() != 0);
      initBuffers(&_faces, &_positions, &_normals);
   }

   PLYMesh::~PLYMesh() {
   }

   bool PLYMesh::load(const std::string& filename) {
      if (_positions.size() != 0) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }
      fstream file;
      file.open(filename, ios::in);
      if(!file.is_open()){
         cerr << "could not open file" << endl;
         file.close();
         return false;
      }
      string line;
      getline(file,line);
      if(!line.compare("ply")){
         cerr << "mesh file not ply" << endl;
         file.close();
         return false;
      }
      int nvertices;
      int nfaces;
      regex re_v("element vertex ([0-9]+)");
      regex re_f("element face ([0-9]+)");
      regex end_h("end_header");
      regex re_vn("(-?[0-9]+\\.?[0-9]*) (-?[0-9]+\\.?[0-9]*) (-?[0-9]+\\.?[0-9]*) (-?[0-9]+\\.?[0-9]*) (-?[0-9]+\\.?[0-9]*) (-?[0-9]+\\.?[0-9]*)");
      regex re_fn("3 (-?[0-9]+) (-?[0-9]+) (-?[0-9]+)");
      smatch matches;
      
      while(getline(file,line)){
         if(regex_search(line, matches, re_v)) {
            nvertices = stoi(matches[0]);
         }
         if(regex_search(line, matches, re_f)) {
            nfaces = stoi(matches[0]);

         }
         if(regex_search(line, end_h)) {
            break;
         }
      }   
      init();
      //&_faces, &_positions, &_normals      
      for(int i = 0; i<nvertices;){

         if(!getline(file,line)){
            cerr << "too few lines" << endl;
            file.close();
            return false;
         }
         
         if(regex_search(line, matches, re_vn)) {
            i++;
            _positions.push_back(stof(matches[0]));
            _positions.push_back(stof(matches[1]));
            _positions.push_back(stof(matches[2]));
            _normals.push_back(stof(matches[3]));
            _normals.push_back(stof(matches[4]));
            _normals.push_back(stof(matches[5]));
         }
      }
      for(int i = 0; i<nfaces;){
         if(!getline(file,line)){
            cerr << "too few lines" << endl;
            file.close();
            return false;
         }
         if(regex_search(line, matches, re_fn)) {
            i++;
            _faces.push_back(stoi(matches[0]));
            _faces.push_back(stoi(matches[1]));
            _faces.push_back(stoi(matches[2]));
         }

      }
      file.close();

      // todo: your code here
      return false;
   }

   glm::vec3 PLYMesh::minBounds() const {
      GLfloat x,y,z;
      for(int i = 0; i<_positions.size(); i=i+3){
         x = std::min(x,_positions[i+0]);
         y = std::min(y,_positions[i+1]);
         z = std::min(z,_positions[i+2]);
      }
      return glm::vec3(x,y,z);
   }

   glm::vec3 PLYMesh::maxBounds() const {
      GLfloat x,y,z;
      for(int i = 0; i<_positions.size(); i=i+3){
         x = std::max(x,_positions[i+0]);
         y = std::max(y,_positions[i+1]);
         z = std::max(z,_positions[i+2]);
      }
      return glm::vec3(x,y,z);
   }

   int PLYMesh::numVertices() const {
      return _positions.size()/3;
   }

   int PLYMesh::numTriangles() const {
      return _faces.size()/3;
   }

   const std::vector<GLfloat>& PLYMesh::positions() const {
      return _positions;
   }

   const std::vector<GLfloat>& PLYMesh::normals() const {
      return _normals;
   }

   const std::vector<GLuint>& PLYMesh::indices() const {
      return _faces;
   }
}
