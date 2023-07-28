#ifndef COMMON_H
#define COMMON_H

#define _CRT_SECURE_NO_WARNINGS
#define NDEBUG
#define GLEW_STATIC
#define FREEGLUT_STATIC
//#define LIBXML_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0

#pragma comment(lib,"libxml2-static.lib")
#pragma comment(lib,"libz-static.lib")
#pragma comment(lib,"libiconv-static.lib")
#pragma comment(lib, "WS2_32.lib")

//#pragma comment(lib,"libxml2.lib")
//#pragma comment(lib, "libiconv.lib")
//#pragma comment(lib,"WS2_32.lib")
//#pragma comment(lib, "zlib.lib")

#pragma comment(lib, "freetype.lib")
#include <ft2build.h>
#include FT_FREETYPE_H


#pragma comment(lib, "libpng16.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "libglew32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "freeglut_static.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "libfbxsdk-mt.lib")
#include <fbxsdk.h>
#include <stdio.h>
//#include <stdlib.h>
#include <glew.h>
#include <freeglut.h>
#include <glfw3.h>
// Include GLM
#include <glm\glm.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
//LOAD XML
#include <libxml/HTMLparser.h>
//#include <libxml/xmlreader.h>
//#include <libxml/parser.h>
//#include <libxml/tree.h>
//#include <libxml/encoding.h>
//#include <libxml/xmlwriter.h>

#include <Windows.h>
#include <conio.h>

#include <map>

#include <png.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>
using namespace glm;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//LOAD SHADERS
void loadShaders(GLuint&prog_hdlr, const char*vsfile, const char*fsfile);
void setShaders(GLuint &prog_hdlr, GLuint vert_hdlr, GLuint frag_hdlr);
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//CAMERA
glm::mat4 LookAt(const glm::vec3& Eye, const glm::vec3& Center, const glm::vec3& Up);
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//QUATERNIONS
quat RotationBetweenVectors(vec3 start, vec3 dest);
quat qLookAt(vec3 direction, vec3 desiredUp);
quat RotateTowards(quat q1, quat q2, float maxAngle);
//TEXTURES
extern GLubyte*textureImage;
extern int LoadBMP(char*p_filename);
extern int loadPngImage(char*name, int&outWidth, int&outHeight, bool&outHasAlpha, GLubyte**outData);
GLuint loadBMP_custom(const char * imagepath);
GLuint loadDDS(const char * imagepath);
////////////////////////////////////////////////////////////////////////////////////////////////////

//LOADXML
void traverse_dom_trees(xmlNode*a_node);

////////////////////////////////////////////////////////////////////////////////////////////////////
//OBJECTS!
bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs, 
	std::vector<glm::vec3> & out_normals
);

/*
bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
);
*/

bool loadmyFBX(
	const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

void loadmyDAE(
	const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<unsigned short> & out_indices
);

void indexVBO(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

void indexVBO_slow(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

void indexVBO_TBN(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,
	std::vector<glm::vec3> & in_tangents,
	std::vector<glm::vec3> & in_bitangents,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<glm::vec3> & out_tangents,
	std::vector<glm::vec3> & out_bitangents
);

////////////////////////////////////////////////////////////////////////////////////////////////////
void keyPress();
////////////////////////////////////////////////////////////////////////////////////////////////////
//2D HUD
//void init2dhud(int vboID, char*fName, float x, float y, float width, float height);//OLD
void draw2dhud(int vboID, char*fName, float x, float y, float width, float height);

//2D FONT
void init2dfont();
//void draw2dfont(int vboID, float x, float y, float xwidth, float yheight);
void draw2dfont(int vboID, std::string text, float tempX, float tempY, float xwidth, float yheight);

////////////////////////////////////////////////////////////////////////////////////////////////////

//Shapes
void drawPoints(int vboID, vec3 point, vec4 color);//void drawPoints(int vboID);
void drawLine(int vboID, vec4 startColor4f, vec4 endColor4f, vec3 point1, vec3 point2);
void drawLineStrip(int vboID);
void drawLineLoop(int vboID);
void drawTriangle(int vboID);
void drawTriangleStrip(int vboID, int facing);
void drawTriangleFan(int vboID, int facing);

////////////////////////////////////////////////////////////////////////////////////////////////////
//VBO
//void initVBO(char*modelfile, char*texturefile, int vboLoop);//OLD
//void drawVBO(int vboID);//OLD
//void drawVBO(int vboID, char*modelfile, char*texturefile);
void drawVBO(int vboID, int myShader, char*modelfile, char*texturefile);
void drawVBO_light(int vboID, GLint myShader, char*modelfile);

void deleteVBO(GLuint vboID);
void deleteVBOall();
////////////////////////////////////////////////////////////////////////////////////////////////////

class drawObjects {
public:
	int VBOloadedID;

	int loadOnce[90000];
	//int drawObj[90000];
	int drawDisable[90000];
	//int objDelete[90000];
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
