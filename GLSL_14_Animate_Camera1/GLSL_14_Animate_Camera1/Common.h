#ifndef COMMON_H
#define COMMON_H

#define _CRT_SECURE_NO_WARNINGS
#define NDEBUG
#define GLEW_STATIC
#define FREEGLUT_STATIC
//#define LIBXML_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0

#define ARRAYCOUNT 90000

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
	std::vector<glm::vec3> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<unsigned short> & out_indices
);

void indexVBO(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec3> & in_uvs,
	std::vector<glm::vec3> & in_normals,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec3> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

void indexVBO_slow(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec3> & in_uvs,
	std::vector<glm::vec3> & in_normals,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec3> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

void indexVBO_TBN(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec3> & in_uvs,
	std::vector<glm::vec3> & in_normals,
	std::vector<glm::vec3> & in_tangents,
	std::vector<glm::vec3> & in_bitangents,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec3> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<glm::vec3> & out_tangents,
	std::vector<glm::vec3> & out_bitangents
);

void computeTangentBasis(
	// inputs
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec3> & uvs,//std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals,
	// outputs
	std::vector<glm::vec3> & tangents,
	std::vector<glm::vec3> & bitangents
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
void drawVBO(int vboID, int myShader, char*modelfile, char*texturefile, int vboTRS);
//void drawVBO_light(int vboID, GLint myShader, char*modelfile);//OLD

void deleteVBO(GLuint vboID);
void deleteVBOall();
////////////////////////////////////////////////////////////////////////////////////////////////////

void hermiteCurve();

////////////////////////////////////////////////////////////////////////////////////////////////////

class drawObjects {
public:
	//VBO
	int VBOloadedID;

	int loadOnce[90000];
	//int drawObj[90000];
	int drawDisable[90000];
	//int objDelete[90000];
	int notDrawArray[90000];


	int vboNumber;
	int currentDAEvbo;//TEST
	int initalVBO;
	int vboCount[90000];


	bool matrixUse;
	bool matrixLock;
	int matrixCamCount;
	int matrixLightCount;
	int matrixIncrement;
	int matrixCountArray[90000];


	int noUVorColor;
	int switchColor;
	

	//LOAD MULTIPLE
	int limitOne;
	int meshCount;
	int currentMesh;//TEST
	int meshLock;//TEST
	int meshIncrement;//TEST
	int meshIncrementCount;//TEST
	int meshIndicesIncrement;//TEST
	//
	int camCounter;
	int camSkip;
	int lightCounter;
	int lightSkip;
	//
	int loadCamera;
	int loadCameraArray[90000];
	//int loadLight;
	//int loadLightArray[90000];
	int loadLightDirectional;
	int loadLightDirectionalArray[90000];
	int loadLightPoint;
	int loadLightPointArray[90000];
	int loadLightSpot;
	int loadLightSpotArray[90000];
	int storedVboNumber;
	//
	int noMesh;
	int meshVBO;//TEST
	int meshVBOi;//TEST
	int meshTransform;//TEST
	//int meshVBOarray;//TEST
	int meshLoad[90000];//TEST
	int testMeshCount;//TEST
	int meshUp;
	int noAnimation[90000];

	//MATERIAL
	bool materialVBOnumber[90000];//TEST
	bool materialVBOStoredUV[90000];//TEST
	bool materialVBOStoredColor[90000];//TEST

	//CAMERA
	float radius;//const
	
	glm::vec3 target, right, up;
	
	float cam1X;// = sin(currentTime) * radius;
	float cam1Y;
	float cam1Z;// = cos(currentTime) * radius;
	glm::vec3 cameraPos1;// = glm::vec3(cam1X, cam1Y, cam1Z);
	glm::vec3 objectPos1;// = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up1;// = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::mat4 viewCamera1;// = glm::lookAt(cameraPos1, objectPos1, up1);


	//GLM
	glm::mat4 projection,
	view, viewCamera1,
	ModelMatrix, MVP, RotationMatrix, RotationMatrixArray[90000], TranslationMatrix, TranslationMatrixArray[90000], ScalingMatrix,
	mat4Rot;
	//LIGHT
	//projectionLight, viewLight, ModelMatrixLight, MVPLight, RotationMatrixLight, TranslationMatrixLight, ScalingMatrixLight;
	
	GLuint programID, materialShaderID,
		uniformModel, uniformView, uniformProjection, uniformRotation,
		MatrixID, MatrixIDVBO, uniformModelVBO, uniformViewVBO, uniformProjectionVBO,
		//ModelView3x3MatrixID,
		//LIGHT
		lightShaderID, MatrixIDLight, uniformModelLight, uniformViewLight, uniformProjectionLight;

	GLuint diffuseID[90000], specularID[90000], normalID[90000], emissionID[90000], Texture[90000], //LightID[90000],
	VertexArrayID[90000], vertexbuffer[90000], colorbuffer[90000], uvbuffer[90000], normalbuffer[90000], tangentbuffer[90000], bitangentbuffer[90000], elementbuffer[90000];
	//LIGHT
	//VertexArrayIDLight[90000], vertexbufferLight[90000], uvbufferLight[90000], normalbufferLight[90000], elementbufferLight[90000];

	//FONT
	GLuint fontText, programFontID, fontMatrixID, fontUniformModel, fontUniformView, fontUniformProjection, fontVertexArrayID[90000],
	fontVertexBuffer[1000][10000], fontElementBuffer[1000][10000];

	glm::mat4 fontProjection, fontView, fontModelMatrix, fontMVP, fontRotationMatrix, fontTranslationMatrix, fontScalingMatrix;

	//SHAPES
	GLuint programShapesShaderID, shapesMatrixID, shapesUniformModel, shapesUniformView, shapesUniformProjection,
	shapeVertexArrayID[90000], shapesVertexBuffer[90000], shapesColorBuffer[90000], shapesUVBuffer[90000], shapesNormalBuffer[90000], shapesElementBuffer[90000];
	
	glm::mat4 shapesProjection, shapesModelMatrix, shapesMVP, shapesRotationMatrix, shapesTranslationMatrix, shapesScalingMatrix;
	
	//XML
	int initialCount;
	int meshSkip;
	int newVecArray;
	
	int matrixCount, matrixAll, matrixSkip;
	int cameraLightFound;

	int vertindices[ARRAYCOUNT];
	int normindices[ARRAYCOUNT];
	int uvindices[ARRAYCOUNT];

	//MESH
	/*
	float meshvertices[ARRAYCOUNT];
	float meshnormals[ARRAYCOUNT];
	float meshuvmaps[ARRAYCOUNT];
	float meshcolors[ARRAYCOUNT];
	*/
	
	int intarray[ARRAYCOUNT];
	float floatarray[ARRAYCOUNT];
	
	//TEMP
	float storedvertices[ARRAYCOUNT];
	float storednormals[ARRAYCOUNT];
	float storeduvmaps[ARRAYCOUNT];
	float storedcolors[ARRAYCOUNT];
	//float storedmatrixtransform[ARRAYCOUNT];
	float storedmatrixtransform[9000][10000];

	//SPOTLIGHT ARRAY
	float storedSpotLightArray[ARRAYCOUNT];

	//INTERPOLATION
	int storedXInterpolation[ARRAYCOUNT], storedXRotEulerInterpolation[ARRAYCOUNT], storedXScaleInterpolation[ARRAYCOUNT],
		storedYInterpolation[ARRAYCOUNT], storedYRotEulerInterpolation[ARRAYCOUNT], storedYScaleInterpolation[ARRAYCOUNT],
		storedZInterpolation[ARRAYCOUNT], storedZRotEulerInterpolation[ARRAYCOUNT], storedZScaleInterpolation[ARRAYCOUNT],
		myXInterpolation[ARRAYCOUNT], myXRotEulerInterpolation[ARRAYCOUNT], myXScaleInterpolation[ARRAYCOUNT],
		myYInterpolation[ARRAYCOUNT], myYRotEulerInterpolation[ARRAYCOUNT], myYScaleInterpolation[ARRAYCOUNT],
		myZInterpolation[ARRAYCOUNT], myZRotEulerInterpolation[ARRAYCOUNT], myZScaleInterpolation[ARRAYCOUNT],
		
		xInputCountControlPointID[90000];
	
	//LOCROTSCALE TEMP X
	float storedXInput[ARRAYCOUNT], storedXOutput[ARRAYCOUNT],  storedXInTangent[ARRAYCOUNT], storedXOutTangent[ARRAYCOUNT];
	float storedXRotEulerInput[ARRAYCOUNT], storedXRotEulerOutput[ARRAYCOUNT], storedXRotEulerInTangent[ARRAYCOUNT], storedXRotEulerOutTangent[ARRAYCOUNT];
	float storedXScaleInput[ARRAYCOUNT], storedXScaleOutput[ARRAYCOUNT],  storedXScaleInTangent[ARRAYCOUNT], storedXScaleOutTangent[ARRAYCOUNT];
	//LOCROTSCALE TEMP Y
	float storedYInput[ARRAYCOUNT], storedYOutput[ARRAYCOUNT], storedYInTangent[ARRAYCOUNT], storedYOutTangent[ARRAYCOUNT];
	float storedYRotEulerInput[ARRAYCOUNT], storedYRotEulerOutput[ARRAYCOUNT], storedYRotEulerInTangent[ARRAYCOUNT], storedYRotEulerOutTangent[ARRAYCOUNT];
	float storedYScaleInput[ARRAYCOUNT], storedYScaleOutput[ARRAYCOUNT], storedYScaleInTangent[ARRAYCOUNT], storedYScaleOutTangent[ARRAYCOUNT];
	//LOCROTSCALE TEMP Z
	float storedZInput[ARRAYCOUNT], storedZOutput[ARRAYCOUNT], storedZInTangent[ARRAYCOUNT], storedZOutTangent[ARRAYCOUNT];
	float storedZRotEulerInput[ARRAYCOUNT], storedZRotEulerOutput[ARRAYCOUNT], storedZRotEulerInTangent[ARRAYCOUNT], storedZRotEulerOutTangent[ARRAYCOUNT];
	float storedZScaleInput[ARRAYCOUNT], storedZScaleOutput[ARRAYCOUNT], storedZScaleInTangent[ARRAYCOUNT], storedZScaleOutTangent[ARRAYCOUNT];

	//LOCROTSCALE X
	float myXInput[ARRAYCOUNT], myXOutput[ARRAYCOUNT],myXInTangent[ARRAYCOUNT], myXOutTangent[ARRAYCOUNT];
	float myXRotEulerInput[ARRAYCOUNT], myXRotEulerOutput[ARRAYCOUNT], myXRotEulerInTangent[ARRAYCOUNT], myXRotEulerOutTangent[ARRAYCOUNT];
	float myXScaleInput[ARRAYCOUNT], myXScaleOutput[ARRAYCOUNT], myXScaleInTangent[ARRAYCOUNT], myXScaleOutTangent[ARRAYCOUNT];
	//LOCROTSCALE Y
	float myYInput[ARRAYCOUNT], myYOutput[ARRAYCOUNT], myYInTangent[ARRAYCOUNT], myYOutTangent[ARRAYCOUNT];
	float myYRotEulerInput[ARRAYCOUNT], myYRotEulerOutput[ARRAYCOUNT], myYRotEulerInTangent[ARRAYCOUNT], myYRotEulerOutTangent[ARRAYCOUNT];
	float myYScaleInput[ARRAYCOUNT], myYScaleOutput[ARRAYCOUNT], myYScaleInTangent[ARRAYCOUNT], myYScaleOutTangent[ARRAYCOUNT];
	//LOCROTSCALE Z
	float myZInput[ARRAYCOUNT], myZOutput[ARRAYCOUNT], myZInTangent[ARRAYCOUNT], myZOutTangent[ARRAYCOUNT];
	float myZRotEulerInput[ARRAYCOUNT], myZRotEulerOutput[ARRAYCOUNT], myZRotEulerInTangent[ARRAYCOUNT], myZRotEulerOutTangent[ARRAYCOUNT];
	float myZScaleInput[ARRAYCOUNT], myZScaleOutput[ARRAYCOUNT], myZScaleInTangent[ARRAYCOUNT], myZScaleOutTangent[ARRAYCOUNT];
	
	bool verticesfound, normalsfound, uvmapfound, colorsfound, indicesfound, matrixtransformfound,
	//LOC
	xInputFound, xOutputFound, xInterpolationFound, xInTangentFound, xOutTangentFound,
	yInputFound, yOutputFound, yInterpolationFound, yInTangentFound, yOutTangentFound,
	zInputFound, zOutputFound, zInterpolationFound, zInTangentFound, zOutTangentFound,
	//ROT
	xRotEulerInputFound, xRotEulerOutputFound, xRotEulerInterpolationFound, xRotEulerInTangentFound, xRotEulerOutTangentFound,
	yRotEulerInputFound, yRotEulerOutputFound, yRotEulerInterpolationFound, yRotEulerInTangentFound, yRotEulerOutTangentFound,
	zRotEulerInputFound, zRotEulerOutputFound, zRotEulerInterpolationFound, zRotEulerInTangentFound, zRotEulerOutTangentFound,
	//SCALE
	xScaleInputFound, xScaleOutputFound, xScaleInterpolationFound, xScaleInTangentFound, xScaleOutTangentFound,
	yScaleInputFound, yScaleOutputFound, yScaleInterpolationFound, yScaleInTangentFound, yScaleOutTangentFound,
	zScaleInputFound, zScaleOutputFound, zScaleInterpolationFound, zScaleInTangentFound, zScaleOutTangentFound,

	xScaleInputFoundArray[90000];

	int verticescount, normalscount, uvmapscount, colorscount, indicescount, matrixtransformcount,
	//LOC
	xInputCount, xOutputCount, xInterpolationCount, xInTangentCount, xOutTangentCount,
	yInputCount, yOutputCount, yInterpolationCount, yInTangentCount, yOutTangentCount,
	zInputCount, zOutputCount, zInterpolationCount, zInTangentCount, zOutTangentCount,
	//ROT
	xRotEulerInputCount, xRotEulerOutputCount, xRotEulerInterpolationCount, xRotEulerInTangentCount, xRotEulerOutTangentCount,
	yRotEulerInputCount, yRotEulerOutputCount, yRotEulerInterpolationCount, yRotEulerInTangentCount, yRotEulerOutTangentCount,
	zRotEulerInputCount, zRotEulerOutputCount, zRotEulerInterpolationCount, zRotEulerInTangentCount, zRotEulerOutTangentCount,
	//SCALE
	xScaleInputCount, xScaleOutputCount, xScaleInterpolationCount, xScaleInTangentCount, xScaleOutTangentCount,
	yScaleInputCount, yScaleOutputCount, yScaleInterpolationCount, yScaleInTangentCount, yScaleOutTangentCount,
	zScaleInputCount, zScaleOutputCount, zScaleInterpolationCount, zScaleInTangentCount, zScaleOutTangentCount;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif