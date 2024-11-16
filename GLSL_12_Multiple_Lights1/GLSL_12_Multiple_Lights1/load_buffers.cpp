#include "Common.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
extern int SCREEN_WIDTH, SCREEN_HEIGHT;

extern glm::vec3 eye;
//extern glm::vec3 right, target, up;

extern bool hasAlpha;
extern int myCam;
extern int imgwidth, imgheight;

extern float deltaTime;

extern float modelX, modelY, modelZ;
extern float lightX, lightY, lightZ;

extern float eyeX, eyeY, eyeZ;
extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;
//////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<glm::vec3> vectorvertices[90000];
std::vector<glm::vec3> vectoruvs[90000];
std::vector<glm::vec3> vectornormals[90000];
std::vector<glm::vec3> vectorcolors[90000];
std::vector<glm::vec3> tangents[90000];
std::vector<glm::vec3> bitangents[90000];
std::vector<unsigned short> indices[90000], daeindices[90000];
std::vector<glm::vec3> indexed_vertices[90000];
std::vector<glm::vec3> indexed_uvs[90000];
std::vector<glm::vec3> indexed_normals[90000];
std::vector<glm::vec3> indexed_tangents[90000];
std::vector<glm::vec3> indexed_bitangents[90000];
//std::vector<glm::vec3> indexed_colors[90000];
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
std::vector<glm::vec3> vectorverticesLight[90000];
std::vector<glm::vec3> vectoruvsLight[90000];
std::vector<glm::vec3> vectornormalsLight[90000];
std::vector<glm::vec3> vectorcolorsLight[90000];
std::vector<unsigned short> indicesLight[90000], daeindicesLight[90000];
std::vector<glm::vec3> indexed_verticesLight[90000];
std::vector<glm::vec3> indexed_uvsLight[90000];
std::vector<glm::vec3> indexed_normalsLight[90000];
//std::vector<glm::vec3> indexed_colorsLight[90000];
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////

int steps;
//int storeID;
//int playLoop;
int playLoop[90000];
int playCount[90000];

int loadCount[90000];

//float playTime;
//float testTime;
float testTime[90000];

float daeLocX, daeLocY, daeLocZ;
float daeRotEulerX, daeRotEulerY, daeRotEulerZ;
float daeScaleX, daeScaleY, daeScaleZ;

float p1[1000][3000],      p2[1000][3000],      p3[1000][3000],      p4[1000][3000],      p5[1000][3000],     p6[1000][3000];
float pRot1[1000][3000],   pRot2[1000][3000],   pRot3[1000][3000],   pRot4[1000][3000],   pRot5[1000][3000],  pRot6[1000][3000];
float pScale1[1000][3000], pScale2[1000][3000], pScale3[1000][3000], pScale4[1000][3000], pScale5[1000][3000], pScale6[1000][3000];
vec3 pVec3Pos[1000][3000], pVec3Rot[1000][3000], pVec3Scale[1000][3000];

//////////////////////////////////////////////////////////////////////////////////////////////////////
//https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/

/*
struct Hermite {
int greater, smaller;

int storeID;
float myXInput[1000][ARRAYCOUNT];
float myXOutput[1000][ARRAYCOUNT];
float myXInTangent[1000][ARRAYCOUNT];
float myXOutTangent[1000][ARRAYCOUNT];

float testTime;
float testP;
float p1;
float p2;

//TANGENT 1
vec2 tangentOut1;
vec2 tangentIn1;
//TANGENT 2
vec2 tangentOut2;
vec2 tangentIn2;
};

typedef struct Hermite Struct;

Struct HermiteValues(int a, int b)
{
Struct s;
if (a > b) {
s.greater = a;
s.smaller = b;
}
else {
s.greater = b;
s.smaller = a;
}

return s;
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////
quat gOrientation2[90000];
//////////////////////////////////////////////////////////////////////////////////////////////////////
//int *meshnormals;
//int *meshtexturemaps;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;//colorIndices
//std::vector<glm::vec3> temp_vertices, temp_indicesvertices;
//std::vector<glm::vec2> temp_uvs;
//std::vector<glm::vec3> temp_normals;
//////////////////////////////////////////////////////////////////////////////////////////////////////
extern drawObjects dObj;
//////////////////////////////////////////////////////////////////////////////////////////////////////
extern float rotMat;
extern glm::mat4 mat4Rot;

float tempTime;

//////////////////////////////////////////////////////////////////////////////////////////////////////

//int meshCount;
//int limitOne;

//////////////////////////////////////////////////////////////////////////////////////////////////////

int loopTest[90000];
int savedDoubleArray[1000][3000];

//X TANGENT
vec2 tangentOutX[1000][3000];//(myXOutTangent[i*2+0], myXOutTangent[i*2+1]);
vec2 tangentInX[1000][3000];//(myXInTangent[i*2+0], myXInTangent[i*2+1]);
vec2 tangentOutXRot[1000][3000];
vec2 tangentInXRot[1000][3000];
vec2 tangentOutXScale[1000][3000];
vec2 tangentInXScale[1000][3000];
//Y TANGENT
vec2 tangentOutY[1000][3000];//(myYOutTangent[i*2+0], myYOutTangent[i*2+1]);
vec2 tangentInY[1000][3000];//(myYInTangent[i*2+0], myYInTangent[i*2+1]);
vec2 tangentOutYRot[1000][3000];
vec2 tangentInYRot[1000][3000];
vec2 tangentOutYScale[1000][3000];
vec2 tangentInYScale[1000][3000];
//Z TANGENT
vec2 tangentOutZ[1000][3000];//(myZOutTangent[i*2+0], myZOutTangent[i*2+1]);
vec2 tangentInZ[1000][3000];//(myZInTangent[i*2+0], myZInTangent[i*2+1]);
vec2 tangentOutZRot[1000][3000];
vec2 tangentInZRot[1000][3000];
vec2 tangentOutZScale[1000][3000];
vec2 tangentInZScale[1000][3000];

//////////////////////////////////////////////////////////////////////////////////////////////////////

char pointLight[255] = "pointLight";
char dirLight[255] = "dirLight";
char spotLight[255] = "spotLight";
//
char matDirection[255] = ".direction";
char matPosition[255] = ".position";
//
char matAmbient[255] = ".ambient";
char matDiffuse[255] = ".diffuse";
char matSpecular[255] = ".specular";
//
char matConstant[255] = ".constant";
char matLinear[255] = ".linear";
char matQuadratic[255] = ".quadratic";
//
char matCutOff[255] = ".cutOff";
char matOuterCutOff[255] = ".outerCutOff";

//////////////////////////////////////////////////////////////////////////////////////////////////////

extern bool meshuv, meshcolor;


//https://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
mat4 rotationMatrix(vec3 axis, float angle)
{
	axis = normalize(axis);
	float s = sin(angle);
	float c = cos(angle);
	float oc = 1.0f - c;

	return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
		oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
		oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
		0.0,                                0.0,                                0.0,                                1.0);
}

//int rotSwap;
int trsSwapArray[90000];

//int initalVBO;
//int vboCount[90000];

int vboColorCount;
int vboColorArray[90000];

int vboOrderCount;
int vboOrderArray[90000];

//int vboNumber;

float testX, testY, testZ;

//int testNum;//TEST

void drawVBO(int vboID, GLint myShader, char*modelfile, char*texturefile, int vboTRS)
{
	//printf("vboID: %d\n", vboID);
	glEnable(GL_DEPTH_TEST);//Enable depth test
	glDepthFunc(GL_LESS);//Accept fragment if it closer to the camera than the former one
	//
	glEnable(GL_CULL_FACE);//Cull triangles which normal is not towards the camera
	glCullFace(GL_BACK);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_FRONT_AND_BACK);
	//

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);
	//
	glClearDepth(1.0f);//glClearDepth(1.0f); //Set background depth to farthest
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	//glUseProgram(programID);//BASIC SHADER
	glUseProgram(myShader);
	//materialShaderID
	//lightShaderID
	dObj.meshCount = 0;
	dObj.initalVBO = vboID;
	//printf("testTexture: %d\n", texturefile);
	if(dObj.loadOnce[vboID] == 0)
	{
		//vectorvertices[vboID].clear(), vectoruvs[vboID].clear(), vectornormals[vboID].clear();
		//indices[vboID].clear();
		//indexed_vertices[vboID].clear(), indexed_uvs[vboID].clear(), indexed_normals[vboID].clear();

		//loadOBJ(modelfile, vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID]);
		//indexVBO(vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID], indices[vboID], indexed_vertices[vboID], indexed_uvs[vboID], indexed_normals[vboID]);

		//dObj.meshVBO = 1;//TEST 1 TO START THE LOOP
		//for(int i = 0; i < dObj.testMeshCount; i++)
		//for(int i = 0; i <= dObj.meshCount; i++)
		//for(int i = 0; i < dObj.meshVBO; i++)
		dObj.meshVBO = 0;//RESET
		dObj.meshIncrementCount = 0;
		dObj.matrixCount = 0;
		dObj.matrixIncrement = 0;
		//dObj.matrixLock = 0;
		dObj.noMesh = 0;
		//
		dObj.camSkip = 0;
		dObj.lightSkip = 0;
		dObj.matrixCamCount = 0;
		dObj.matrixLightCount = 0;
		//
		//for(int i = 0; i <= dObj.meshVBO; i++)//FALLBACK
		//for(int i = 0; i <= dObj.meshVBO + dObj.matrixCount; i++)
		for(int i = 0; i <= dObj.meshVBO + dObj.matrixCount - dObj.noMesh; i++)
		{
			printf("i: %d meshVBO: %d vboID: %d total: %d VOC: %d noMesh: %d\n", i, dObj.meshVBO, vboID, dObj.meshVBO + dObj.matrixCount, vboOrderCount, dObj.noMesh);
			_getch();
			dObj.currentMesh = 0;
			dObj.meshIndicesIncrement = 0;
			dObj.meshIncrement = 0;
			//dObj.meshLock = 0;
			//dObj.meshVBOi = 0;
			dObj.meshVBOi = i;
			//MATERIALS
			dObj.currentDAEvbo = vboID+i;
			//MATRIX
			//dObj.matrixCount = 0;
			dObj.matrixAll = 0;
			dObj.matrixSkip = 0;
			dObj.matrixLock = 0;
			//
			dObj.camCounter = 0;
			dObj.lightCounter = 0;
			//
			dObj.matrixSkip = dObj.matrixAll - dObj.matrixCount;
			printf("matrixCount1: %d matrixAll: %d matrixSkip: %d\n", dObj.matrixCount, dObj.matrixAll, dObj.matrixSkip);
			loadmyDAE(modelfile, vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i], daeindices[vboID+i]);
			dObj.matrixSkip = dObj.matrixAll - dObj.matrixCount;
			printf("matrixCount2: %d matrixAll: %d matrixSkip: %d\n", dObj.matrixCount, dObj.matrixAll, dObj.matrixSkip);

			if(dObj.indicescount != 1)//if(dObj.indicescount != 0)
			{
				computeTangentBasis(
					vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i],//input
					tangents[vboID+i], bitangents[vboID+i]);//output

				indexVBO_TBN(vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i], tangents[vboID+i], bitangents[vboID+i],
					indices[vboID+i], indexed_vertices[vboID+i], indexed_uvs[vboID+i], indexed_normals[vboID+i], indexed_tangents[vboID+i], indexed_bitangents[vboID+i]);



				//indexVBO(vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i],
				//indices[vboID+i], indexed_vertices[vboID+i], indexed_uvs[vboID+i], indexed_normals[vboID+i]);

				//loadmyDAE(modelfile, vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID], daeindices[vboID]);
				//indexVBO(vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID],
				//indices[vboID], indexed_vertices[vboID], indexed_uvs[vboID], indexed_normals[vboID]);

				printf("vboID: %d xInput: %d xOutput: %d xInTangent: %d xOutTangent: %d\n", vboID+i, dObj.xInputCount, dObj.xOutputCount, dObj.xInTangentCount, dObj.xOutTangentCount);
				//for(int x1 = 0; x1 <= xInputCount;      x1++)printf("xInput: %f\n",      storedXInput[x1]);
				//for(int x2 = 0; x2 <= xOutputCount;     x2++)printf("xOutput: %f\n",     storedXOutput[x2]);
				//for(int x3 = 0; x3 <= xInTangentCount;  x3++)printf("xInTangent: %f\n",  storedXInTangent[x3]);
				//for(int x4 = 0; x4 <= xOutTangentCount; x4++)printf("xOutTangent: %f\n", storedXOutTangent[x4]);

				if(meshcolor == 1)
				{
					vboColorArray[vboColorCount] = vboID;//vboColorArray[vboColorCount] = vboID+i;
					printf("vboColorArray: %d\n", vboColorArray[vboColorCount]);
					//printf("COLOR FOUND: %d\n", vboColorCount);
					vboColorCount++;
					meshcolor = 0;
				}
				meshuv = 0;

				//FALLBACK
				vboOrderArray[vboOrderCount] = vboID;//vboOrderArray[vboOrderCount+i] = vboID+i;
				printf("vboOrderCount: %d vboOrderArray: %d\n", vboOrderCount, vboOrderArray[vboOrderCount]);

				if(dObj.matrixCount > 1)
				{
					dObj.matrixCountArray[vboID] = dObj.matrixCount;
					printf("matrixCountArray1: %d matrixCount: %d matrixIncrement: %d\n", dObj.matrixCountArray[vboID], dObj.matrixCount, dObj.matrixIncrement);//_getch();
					if(dObj.matrixIncrement == dObj.matrixCount)
					{
						dObj.noMesh = 1;
						printf("noMesh\n");
						//_getch();
					}
				}

				//TEST
				//vboOrderArray[vboOrderCount] = vboID+i+dObj.matrixCount;//vboOrderArray[vboOrderCount+i] = vboID+i;
				//printf("vboOrderCount: %d vboOrderArray: %d\n", vboOrderCount, vboOrderArray[vboOrderCount]);
				//vboOrderCount++;
			}
			else
			{
				for(int ii = 0; ii < dObj.matrixCount; ii++)
				{
					/*
					//printf("TEST1ID: %d loadedID++ : %d vboNum: %d\n", vboID, dObj.VBOloadedID, dObj.vboNumber);_getch();
					//dObj.notDrawArray[dObj.vboNumber] = dObj.VBOloadedID;
					//printf("notDraw: %d num: %d\n", dObj.notDrawArray[dObj.vboNumber], dObj.vboNumber);//_getch();
					*/

					//AVOID USING dObj.vboNumber
					//dObj.notDrawArray[dObj.vboNumber] = dObj.VBOloadedID + dObj.matrixCount + ii;
					//printf("notDraw1: %d num: %d loop: %d\n", dObj.notDrawArray[dObj.vboNumber], dObj.vboNumber, ii);//_getch();
					dObj.notDrawArray[vboID+i] = 1;

					if(dObj.matrixCount > 1)
					{
						dObj.matrixCountArray[vboID] = dObj.matrixCount;
						printf("matrixCountArray1: %d matrixCount: %d matrixIncrement: %d\n", dObj.matrixCountArray[vboID], dObj.matrixCount, dObj.matrixIncrement);//_getch();
						dObj.loadOnce[vboID+i] = 1;//dObj.loadOnce[vboID] = 1;
						printf("vboNumTEST: %d loadOnce: %d\n", dObj.vboNumber, vboID+i);//_getch();
						if(dObj.matrixIncrement == dObj.matrixCount)
						{
							dObj.noMesh = 1;
							printf("noMesh\n");
							//_getch();
						}
					}
				}
				//dObj.vboNumber++;
				//printf("dObjID: %d\n", dObj.VBOloadedID);
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			printf("xCount1: %d\n", dObj.xInputCount);
			if(dObj.xInputCount != 0)
			{
				printf("xCount2: %d\n", dObj.xInputCount);
				int x1 = 0, x2 = 0, x3 = 0, x4 = 0;
				for(;x1 <= dObj.xInputCount; x1++)//TIME
				{
					//printf("xInput: %f\n", storedXInput[x1]);
					dObj.myXInput[x1] = dObj.storedXInput[x1];
					//printf("xInput: %f\n", dObj.myXInput[x1]);
					dObj.myXRotEulerInput[x1] = dObj.storedXRotEulerInput[x1];
					//printf("xRotInput: %f\n", dObj.myXRotEulerInput[x1]);
					dObj.myXScaleInput[x1] = dObj.storedXScaleInput[x1];
					//printf("xScaleInput: %f\n", dObj.myXScaleInput[x1]);

					dObj.myXInterpolation[x1] = dObj.storedXInterpolation[x1];
					//printf("xInterpolation: %d\n", dObj.myXInterpolation[x1]);
					dObj.myXRotEulerInterpolation[x1] = dObj.storedXRotEulerInterpolation[x1];
					//printf("xRotEulerInterpolation: %d\n", dObj.myXRotEulerInterpolation[x1]);
					dObj.myXScaleInterpolation[x1] = dObj.storedXScaleInterpolation[x1];
					//printf("xScaleInterpolation: %d\n", dObj.myXScaleInterpolation[x1]);

					//LESS THAN 2 POINTS
					if(dObj.xInputCount <= 1)
					{
						//printf("2PTESTXINPUTCOUNT: %d\n", dObj.xInputCount);
						//dObj.xInputCountControlPointID[vboID] = 1;
						dObj.xInputCountControlPointID[vboOrderCount] = 1;
						//printf("2PTESTXINPUTCOUNT: %d vboID: %d\n", dObj.xInputCountControlPointID[vboID], vboID);
					}
					//MORE THAN 3 POINTS
					if(dObj.xInputCount >= 2)
					{
						//printf("3PTESTXINPUTCOUNT: %d\n", dObj.xInputCount);
						//dObj.xInputCountControlPointID[vboID] = 2;
						dObj.xInputCountControlPointID[vboOrderCount] = 2;
						//printf("3PTESTXINPUTCOUNT: %d vboID: %d\n", dObj.xInputCountControlPointID[vboID], vboID);
					}

					//SCALE
					dObj.xScaleInputFoundArray[vboID] = 1;
					//printf("xScaleInputFoundArray: %d\n", dObj.xScaleInputFoundArray[vboID]);
				}


				//dObj.myXInterpolation[x1] = dObj.storedXInterpolation[x1];
				//printf("xInterpolation: %d\n", dObj.myXInterpolation[x1]);

				//dObj.xInputCount;
				//printf("xIcount: %d dObj.vboNumber: %d\n", dObj.xInputCount, dObj.vboNumber);
				for(int aaa = 0; aaa < dObj.xInputCount; aaa++)
				{
					savedDoubleArray[dObj.vboNumber][aaa] = dObj.myXInterpolation[aaa];
					//printf("savedDoubleArray: %d\n", savedDoubleArray[dObj.vboNumber][aaa]);
				}
				for(;x2 <= dObj.xOutputCount; x2++)//POS
				{
					//printf("xOutput: %f\n", storedXOutput[x2]);
					dObj.myXOutput[x2] = dObj.storedXOutput[x2];
					//printf("xOutput: %f\n", dObj.myXOutput[x2]);

					dObj.myXRotEulerOutput[x2] = dObj.storedXRotEulerOutput[x2];
					//printf("xRotEulerOutput: %f\n", dObj.myXRotEulerOutput[x2]);
					dObj.myXScaleOutput[x2] = dObj.storedXScaleOutput[x2];
					//printf("xScaleOutput: %f\n", dObj.myXScaleOutput[x2]);
				}
				for(;x3 <= dObj.xInTangentCount; x3++)
				{
					//printf("xInTangent: %f\n", storedXInTangent[x3]);
					dObj.myXInTangent[x3] = dObj.storedXInTangent[x3];
					//printf("xInTangent: %f\n", myXInTangent[x3]);

					dObj.myXRotEulerInTangent[x3] = dObj.storedXRotEulerInTangent[x3];
					//printf("xRotEulerInTangent: %f\n", dObj.myXRotEulerInTangent[x3]);
					dObj.myXScaleInTangent[x3] = dObj.storedXScaleInTangent[x3];
					//printf("xScaleInTangent: %f\n", dObj.myXScaleInTangent[x3]);
				}
				for(;x4 <= dObj.xOutTangentCount; x4++)
				{
					//printf("xOutTangent: %f\n", storedXOutTangent[x4]);
					dObj.myXOutTangent[x4] = dObj.storedXOutTangent[x4];
					//printf("xOutTangent: %f\n", dObj.myXOutTangent[x4]);

					dObj.myXRotEulerOutTangent[x4] = dObj.storedXRotEulerOutTangent[x4];
					//printf("xRotEulerOutTangent: %f\n", dObj.myXRotEulerOutTangent[x4]);
					dObj.myXScaleOutTangent[x4] = dObj.storedXScaleOutTangent[x4];
					//printf("xScaleOutTangent: %f\n", dObj.myXScaleOutTangent[x4]);
				}
				if(x1 != 0 && x2 != 0 && x3 != 0 && x4 != 0)
				{
					//printf("TESTX\n");
					//steps++;
				}

				int y1 = 0, y2 = 0, y3 = 0, y4 = 0;
				for(;y1 <= dObj.yInputCount; y1++)//TIME
				{
					//printf("yInput: %f\n", storedYInput[y1]);
					dObj.myYInput[y1] = dObj.storedYInput[y1];
					//printf("yInput: %f\n", myYInput[storeID][y1]);

					dObj.myYRotEulerInput[y1] = dObj.storedYRotEulerInput[y1];
					//printf("yRotInput: %f\n", dObj.myYRotEulerInput[y1]);
					dObj.myYScaleInput[y1] = dObj.storedYScaleInput[y1];
					//printf("yScaleInput: %f\n", dObj.myYScaleInput[y1]);

					dObj.myYInterpolation[y1] = dObj.storedYInterpolation[y1];
					//printf("yInterpolation: %d\n", dObj.myYInterpolation[y1]);
					dObj.myYRotEulerInterpolation[y1] = dObj.storedYRotEulerInterpolation[y1];
					//printf("yRotEulerInterpolation: %d\n", dObj.myYRotEulerInterpolation[y1]);
					dObj.myYScaleInterpolation[y1] = dObj.storedYScaleInterpolation[y1];
					//printf("yScaleInterpolation: %d\n", dObj.myYScaleInterpolation[y1]);
				}
				for(;y2 <= dObj.yOutputCount; y2++)//POS
				{
					//printf("yOutput: %f\n", storedYOutput[y2]);
					dObj.myYOutput[y2] = dObj.storedYOutput[y2];
					//printf("yOutput: %f\n", dObj.myYOutput[y2]);

					dObj.myYRotEulerOutput[y2] = dObj.storedYRotEulerOutput[y2];
					//printf("yRotEulerOutput: %f\n", dObj.myYRotEulerOutput[y2]);
					dObj.myYScaleOutput[y2] = dObj.storedYScaleOutput[y2];
					//printf("yScaleOutput: %f\n", dObj.myYScaleOutput[y2]);
				}
				for(;y3 <= dObj.yInTangentCount; y3++)
				{
					//printf("yInTangent: %f\n", storedYInTangent[y3]);
					dObj.myYInTangent[y3] = dObj.storedYInTangent[y3];
					//printf("yInTangent: %f\n", myYInTangent[y3]);

					dObj.myYRotEulerInTangent[y3] = dObj.storedYRotEulerInTangent[y3];
					//printf("yRotEulerInTangent: %f\n", dObj.myYRotEulerInTangent[y3]);
					dObj.myYScaleInTangent[y3] = dObj.storedYScaleInTangent[y3];
					//printf("yScaleInTangent: %f\n", dObj.myYScaleInTangent[y3]);
				}
				for(;y4 <= dObj.yOutTangentCount; y4++)
				{
					//printf("yOutTangent: %f\n", storedYOutTangent[y4]);
					dObj.myYOutTangent[y4] = dObj.storedYOutTangent[y4];
					//printf("yOutTangent: %f\n", dObj.myYOutTangent[y4]);

					dObj.myYRotEulerOutTangent[y4] = dObj.storedYRotEulerOutTangent[y4];
					//printf("yRotEulerOutTangent: %f\n", dObj.myYRotEulerOutTangent[y4]);
					dObj.myYScaleOutTangent[y4] = dObj.storedYScaleOutTangent[y4];
					//printf("yScaleOutTangent: %f\n", dObj.myYScaleOutTangent[y4]);
				}
				if(y1 != 0 && y2 != 0 && y3 != 0 && y4 != 0)
				{
					//printf("TESTY\n");
					//steps++;
				}

				int z1 = 0, z2 = 0, z3 = 0, z4 = 0;
				for(;z1 <= dObj.zInputCount; z1++)//TIME
				{
					//printf("zInput: %f\n", storedZInput[z1]);
					dObj.myZInput[z1] = dObj.storedZInput[z1];
					//printf("zInput: %f\n", myZInput[storeID][z1]);

					dObj.myZRotEulerInput[z1] = dObj.storedZRotEulerInput[z1];
					//printf("zRotInput: %f\n", dObj.myZRotEulerInput[z1]);
					dObj.myZScaleInput[z1] = dObj.storedZScaleInput[z1];
					//printf("zScaleInput: %f\n", dObj.myZScaleInput[z1]);

					dObj.myZInterpolation[z1] = dObj.storedZInterpolation[z1];
					//printf("zInterpolation: %d\n", dObj.myZInterpolation[z1]);
					dObj.myZRotEulerInterpolation[z1] = dObj.storedZRotEulerInterpolation[z1];
					//printf("zRotEulerInterpolation: %d\n", dObj.myZRotEulerInterpolation[z1]);
					dObj.myZScaleInterpolation[z1] = dObj.storedZScaleInterpolation[z1];
					//printf("zScaleInterpolation: %d\n", dObj.myZScaleInterpolation[z1]);
				}
				for(;z2 <= dObj.zOutputCount; z2++)//POS
				{
					//printf("zOutput: %f\n", storedZOutput[z2]);
					dObj.myZOutput[z2] = dObj.storedZOutput[z2];
					//printf("zOutput: %f\n", dObj.myZOutput[z2]);
					//steps++;
					dObj.myZRotEulerOutput[z2] = dObj.storedZRotEulerOutput[z2];
					//printf("zRotEulerOutput: %f\n", dObj.myZRotEulerOutput[z2]);
					dObj.myZScaleOutput[z2] = dObj.storedZScaleOutput[z2];
					//printf("zScaleOutput: %f\n", dObj.myZScaleOutput[z2]);
				}
				for(;z3 <= dObj.zInTangentCount; z3++)
				{
					//printf("zInTangent: %f\n", storedZInTangent[z3]);
					dObj.myZInTangent[z3] = dObj.storedZInTangent[z3];
					//printf("zInTangent: %f\n", myZInTangent[z3]);

					dObj.myZRotEulerInTangent[z3] = dObj.storedZRotEulerInTangent[z3];
					//printf("zRotEulerInTangent: %f\n", dObj.myZRotEulerInTangent[z3]);
					dObj.myZScaleInTangent[z3] = dObj.storedZScaleInTangent[z3];
					//printf("zScaleInTangent: %f\n", dObj.myZScaleInTangent[z3]);
				}
				for(;z4 <= dObj.zOutTangentCount; z4++)
				{
					//printf("zOutTangent: %f\n", storedZOutTangent[z4]);
					dObj.myZOutTangent[z4] = dObj.storedZOutTangent[z4];
					//printf("zOutTangent: %f\n", dObj.myZOutTangent[z4]);

					dObj.myZRotEulerOutTangent[z4] = dObj.storedZRotEulerOutTangent[z4];
					//printf("zRotEulerOutTangent: %f\n", dObj.myZRotEulerOutTangent[z4]);
					dObj.myZScaleOutTangent[z4] = dObj.storedZScaleOutTangent[z4];
					//printf("zScaleOutTangent: %f\n", dObj.myZScaleOutTangent[z4]);
				}

				if(x1 != 0 && x2 != 0 && x3 != 0 && x4 != 0 &&
					y1 != 0 && y2 != 0 && y3 != 0 && y4 != 0 &&
					z1 != 0 && z2 != 0 && z3 != 0 && z4 != 0)
					//if(z1 != 0 && z2 != 0 && z3 != 0 && z4 != 0)
				{
					//printf("TESTXYZ\n");
					if(steps == 0)
					{
						steps++;
					}
					//printf("Step: %d Control point: %d\n", steps, dObj.xInputCountControlPointID[vboOrderCount]);
				}
				//if(steps < dObj.xInputCountControlPointID[vboID])

				//playCount[vboID] = dObj.xInputCount;
				playCount[vboOrderCount] = dObj.xInputCount;
				//playCount[vboID] = dObj.xInputCount - 2;

				//HERMITE CURVE INTERPOLATION (STEPS)
				//https://cubic.org/docs/hermite.htm
				//https://discussions.unity.com/t/how-to-interprete-keyframe-intangent-and-outtangent-values/70249
				//for(int t=0; t < steps; t++)
				for(int ii = 0; ii <= dObj.xInputCount; ii++)
				{
					/*
					if(playCount[i] < i)
					{
					playCount[i] = i;
					printf("playCount: %d\n", playCount[i]);
					}
					*/

					for(int t = 0; t < steps; t += 1)
					{
						//printf("xIC: %d STEPS: %d vboOcount: %d\n", i, t, vboOrderCount);
						//float s = (float)t / (float)steps;    // scale s to go from 0 to 1
						//float s = (float)t / (float)1.0f;    // scale s to go from 0 to 1
						float s = (float)t / 1.0f;    // scale s to go from 0 to 1
						//float h1 =  2s^3 - 3s^2 + 1;          // calculate basis function 1
						float h1 = 2* pow(s, 3) - 3* pow(s, 2) + 1;          // calculate basis function 1
						//float h2 = -2s^3 + 3s^2;              // calculate basis function 2
						float h2 = -2* pow(s, 3) + 3* pow(s, 2);              // calculate basis function 2
						//float h3 =   s^3 - 2*s^2 + s;         // calculate basis function 3
						float h3 = pow(s, 3) - 2* pow(s, 2) + s;         // calculate basis function 3
						//float h4 =   s^3 -  s^2;              // calculate basis function 4
						float h4 = pow(s, 3) - pow(s, 2);              // calculate basis function 4

						//playCount[vboID] = dObj.xInputCount - 2;
						//playCount[vboID] = dObj.xInputCount;

						if(ii == 0)
						{
							//printf("FIRSTLOOP: %d\n", i);
							//X POINTS
							p1[vboOrderCount][ii] = dObj.myXOutput[ii*2+0];
							p2[vboOrderCount][ii] = dObj.myXOutput[ii*2+1];
							pRot1[vboOrderCount][ii] = dObj.myXRotEulerOutput[ii*2+0];
							pRot2[vboOrderCount][ii] = dObj.myXRotEulerOutput[ii*2+1];
							pScale1[vboOrderCount][ii] = dObj.myXScaleOutput[ii*2+0];
							pScale2[vboOrderCount][ii] = dObj.myXScaleOutput[ii*2+1];
							//Y POINTS
							p3[vboOrderCount][ii] = dObj.myYOutput[ii*2+0];
							p4[vboOrderCount][ii] = dObj.myYOutput[ii*2+1];
							pRot3[vboOrderCount][ii] = dObj.myYRotEulerOutput[ii*2+0];
							pRot4[vboOrderCount][ii] = dObj.myYRotEulerOutput[ii*2+1];
							pScale3[vboOrderCount][ii] = dObj.myYScaleOutput[ii*2+0];
							pScale4[vboOrderCount][ii] = dObj.myYScaleOutput[ii*2+1];
							//Z POINTS
							p5[vboOrderCount][ii] = dObj.myZOutput[ii*2+0];
							p6[vboOrderCount][ii] = dObj.myZOutput[ii*2+1];
							pRot5[vboOrderCount][ii] = dObj.myZRotEulerOutput[ii*2+0];
							pRot6[vboOrderCount][ii] = dObj.myZRotEulerOutput[ii*2+1];
							pScale5[vboOrderCount][ii] = dObj.myZScaleOutput[ii*2+0];
							pScale6[vboOrderCount][ii] = dObj.myZScaleOutput[ii*2+1];
							//vec2 p1(0.0f,0.0f);//vec2 p2(8.0f,0.0f);
							//X TANGENT
							tangentOutX[vboOrderCount][ii] = vec2(dObj.myXOutTangent[ii*2+0], dObj.myXOutTangent[ii*2+1]);
							tangentInX[vboOrderCount][ii] = vec2(dObj.myXInTangent[ii*2+0], dObj.myXInTangent[ii*2+1]);
							tangentOutXRot[vboOrderCount][ii] = vec2(dObj.myXRotEulerOutTangent[ii*2+0], dObj.myXRotEulerOutTangent[ii*2+1]);
							tangentInXRot[vboOrderCount][ii] = vec2(dObj.myXRotEulerInTangent[ii*2+0], dObj.myXRotEulerInTangent[ii*2+1]);
							tangentOutXScale[vboOrderCount][ii] = vec2(dObj.myXScaleOutTangent[ii*2+0], dObj.myXScaleOutTangent[ii*2+1]);
							tangentInXScale[vboOrderCount][ii] = vec2(dObj.myXScaleInTangent[ii*2+0], dObj.myXScaleInTangent[ii*2+1]);
							//Y TANGENT
							tangentOutY[vboOrderCount][ii] = vec2(dObj.myYOutTangent[ii*2+0], dObj.myYOutTangent[ii*2+1]);
							tangentInY[vboOrderCount][ii] = vec2(dObj.myYInTangent[ii*2+0], dObj.myYInTangent[ii*2+1]);
							tangentOutYRot[vboOrderCount][ii] = vec2(dObj.myYRotEulerOutTangent[ii*2+0], dObj.myYRotEulerOutTangent[ii*2+1]);
							tangentInYRot[vboOrderCount][ii] = vec2(dObj.myYRotEulerInTangent[ii*2+0], dObj.myYRotEulerInTangent[ii*2+1]);
							tangentOutYScale[vboOrderCount][ii] = vec2(dObj.myYScaleOutTangent[ii*2+0], dObj.myYScaleOutTangent[ii*2+1]);
							tangentInYScale[vboOrderCount][ii] = vec2(dObj.myYScaleInTangent[ii*2+0], dObj.myYScaleInTangent[ii*2+1]);
							//Z TANGENT
							tangentOutZ[vboOrderCount][ii] = vec2(dObj.myZOutTangent[ii*2+0], dObj.myZOutTangent[ii*2+1]);
							tangentInZ[vboOrderCount][ii] = vec2(dObj.myZInTangent[ii*2+0], dObj.myZInTangent[ii*2+1]);
							tangentOutZRot[vboOrderCount][ii] = vec2(dObj.myZRotEulerOutTangent[ii*2+0], dObj.myZRotEulerOutTangent[ii*2+1]);
							tangentInZRot[vboOrderCount][ii] = vec2(dObj.myZRotEulerInTangent[ii*2+0], dObj.myZRotEulerInTangent[ii*2+1]);
							tangentOutZScale[vboOrderCount][ii] = vec2(dObj.myZScaleOutTangent[ii*2+0], dObj.myZScaleOutTangent[ii*2+1]);
							tangentInZScale[vboOrderCount][ii] = vec2(dObj.myZScaleInTangent[ii*2+0], dObj.myZScaleInTangent[ii*2+1]);
							//printf("TEST1: %d TEST2: %d\n", vboOrderArray[vboOrderCount], vboOrderCount);
						}
						else if(ii == dObj.xInputCount)//LAST ONE
						{
							//printf("LASTLOOP: %d\n", i);
							//X POINTS
							p1[vboOrderCount][ii] = dObj.myXOutput[ii+0];//p1[i] = myXOutput[i*2-1];
							p2[vboOrderCount][ii] = dObj.myXOutput[ii+0];//p2[i] = myXOutput[i*2+0];
							pRot1[vboOrderCount][ii] = dObj.myXRotEulerOutput[ii+0];
							pRot2[vboOrderCount][ii] = dObj.myXRotEulerOutput[ii+0];
							pScale1[vboOrderCount][ii] = dObj.myXScaleOutput[ii+0];
							pScale2[vboOrderCount][ii] = dObj.myXScaleOutput[ii+0];
							//Y POINTS
							p3[vboOrderCount][ii] = dObj.myYOutput[ii+0];//p3[i] = myYOutput[i*2-1];
							p4[vboOrderCount][ii] = dObj.myYOutput[ii+0];//p4[i] = myYOutput[i*2+0];
							pRot3[vboOrderCount][ii] = dObj.myYRotEulerOutput[ii+0];
							pRot4[vboOrderCount][ii] = dObj.myYRotEulerOutput[ii+0];
							pScale3[vboOrderCount][ii] = dObj.myYScaleOutput[ii+0];
							pScale4[vboOrderCount][ii] = dObj.myYScaleOutput[ii+0];
							//Z POINTS
							p5[vboOrderCount][ii] = dObj.myZOutput[ii+0];//p5[i] = myZOutput[i*2-1];
							p6[vboOrderCount][ii] = dObj.myZOutput[ii+0];//p6[i] = myZOutput[i*2+0];
							pRot5[vboOrderCount][ii] = dObj.myZRotEulerOutput[ii+0];
							pRot6[vboOrderCount][ii] = dObj.myZRotEulerOutput[ii+0];
							pScale5[vboOrderCount][ii] = dObj.myZScaleOutput[ii+0];
							pScale6[vboOrderCount][ii] = dObj.myZScaleOutput[ii+0];
							//X TANGENT
							tangentOutX[vboOrderCount][ii] = vec2(dObj.myXOutTangent[ii*2-1], dObj.myXOutTangent[ii*2+0]);
							tangentInX[vboOrderCount][ii] = vec2(dObj.myXInTangent[ii*2-1], dObj.myXInTangent[ii*2+0]);
							tangentOutXRot[vboOrderCount][ii] = vec2(dObj.myXRotEulerOutTangent[ii*2-1], dObj.myXRotEulerOutTangent[ii*2+0]);
							tangentInXRot[vboOrderCount][ii] = vec2(dObj.myXRotEulerInTangent[ii*2-1], dObj.myXRotEulerInTangent[ii*2+0]);
							tangentOutXScale[vboOrderCount][ii] = vec2(dObj.myXScaleOutTangent[ii*2-1], dObj.myXScaleOutTangent[ii*2+0]);
							tangentInXScale[vboOrderCount][ii] = vec2(dObj.myXScaleInTangent[ii*2-1], dObj.myXScaleInTangent[ii*2+0]);
							//Y TANGENT
							tangentOutY[vboOrderCount][ii] = vec2(dObj.myYOutTangent[ii*2-1], dObj.myYOutTangent[ii*2+0]);
							tangentInY[vboOrderCount][ii] = vec2(dObj.myYInTangent[ii*2-1], dObj.myYInTangent[ii*2+0]);
							tangentOutYRot[vboOrderCount][ii] = vec2(dObj.myYRotEulerOutTangent[ii*2-1], dObj.myYRotEulerOutTangent[ii*2+0]);
							tangentInYRot[vboOrderCount][ii] = vec2(dObj.myYRotEulerInTangent[ii*2-1], dObj.myYRotEulerInTangent[ii*2+0]);
							tangentOutYScale[vboOrderCount][ii] = vec2(dObj.myYScaleOutTangent[ii*2-1], dObj.myYScaleOutTangent[ii*2+0]);
							tangentInYScale[vboOrderCount][ii] = vec2(dObj.myYScaleInTangent[ii*2-1], dObj.myYScaleInTangent[ii*2+0]);
							//Z TANGENT
							tangentOutZ[vboOrderCount][ii] = vec2(dObj.myZOutTangent[ii*2-1], dObj.myZOutTangent[ii*2+0]);
							tangentInZ[vboOrderCount][ii] = vec2(dObj.myZInTangent[ii*2-1], dObj.myZInTangent[ii*2+0]);
							tangentOutZRot[vboOrderCount][ii] = vec2(dObj.myZRotEulerOutTangent[ii*2-1], dObj.myZRotEulerOutTangent[ii*2+0]);
							tangentInZRot[vboOrderCount][ii] = vec2(dObj.myZRotEulerInTangent[ii*2-1], dObj.myZRotEulerInTangent[ii*2+0]);
							tangentOutZScale[vboOrderCount][ii] = vec2(dObj.myZScaleOutTangent[ii*2-1], dObj.myZScaleOutTangent[ii*2+0]);
							tangentInZScale[vboOrderCount][ii] = vec2(dObj.myZScaleInTangent[ii*2-1], dObj.myZScaleInTangent[ii*2+0]);
						}
						else
						{
							//X POINTS
							p1[vboOrderCount][ii] = dObj.myXOutput[ii+0];//p1[i] = myXOutput[i*2-1];
							p2[vboOrderCount][ii] = dObj.myXOutput[ii+1];//p2[i] = myXOutput[i*2+0];
							pRot1[vboOrderCount][ii] = dObj.myXRotEulerOutput[ii+0];
							pRot2[vboOrderCount][ii] = dObj.myXRotEulerOutput[ii+1];
							pScale1[vboOrderCount][ii] = dObj.myXScaleOutput[ii+0];
							pScale2[vboOrderCount][ii] = dObj.myXScaleOutput[ii+1];
							//Y POINTS
							p3[vboOrderCount][ii] = dObj.myYOutput[ii+0];//p3[i] = myYOutput[i*2-1];
							p4[vboOrderCount][ii] = dObj.myYOutput[ii+1];//p4[i] = myYOutput[i*2+0];
							pRot3[vboOrderCount][ii] = dObj.myYRotEulerOutput[ii+0];
							pRot4[vboOrderCount][ii] = dObj.myYRotEulerOutput[ii+1];
							pScale3[vboOrderCount][ii] = dObj.myYScaleOutput[ii+0];
							pScale4[vboOrderCount][ii] = dObj.myYScaleOutput[ii+1];
							//Z POINTS
							p5[vboOrderCount][ii] = dObj.myZOutput[ii+0];//p5[i] = myZOutput[i*2-1];
							p6[vboOrderCount][ii] = dObj.myZOutput[ii+1];//p6[i] = myZOutput[i*2+0];
							pRot5[vboOrderCount][ii] = dObj.myZRotEulerOutput[ii+0];
							pRot6[vboOrderCount][ii] = dObj.myZRotEulerOutput[ii+1];
							pScale5[vboOrderCount][ii] = dObj.myZScaleOutput[ii+0];
							pScale6[vboOrderCount][ii] = dObj.myZScaleOutput[ii+1];
							//X TANGENT
							tangentOutX[vboOrderCount][ii] = vec2(dObj.myXOutTangent[ii*2-1], dObj.myXOutTangent[ii*2+0]);
							tangentInX[vboOrderCount][ii] = vec2(dObj.myXInTangent[ii*2-1], dObj.myXInTangent[ii*2+0]);
							tangentOutXRot[vboOrderCount][ii] = vec2(dObj.myXRotEulerOutTangent[ii*2-1], dObj.myXRotEulerOutTangent[ii*2+0]);
							tangentInXRot[vboOrderCount][ii] = vec2(dObj.myXRotEulerInTangent[ii*2-1], dObj.myXRotEulerInTangent[ii*2+0]);
							tangentOutXScale[vboOrderCount][ii] = vec2(dObj.myXScaleOutTangent[ii*2-1], dObj.myXScaleOutTangent[ii*2+0]);
							tangentInXScale[vboOrderCount][ii] = vec2(dObj.myXScaleInTangent[ii*2-1], dObj.myXScaleInTangent[ii*2+0]);
							//Y TANGENT
							tangentOutY[vboOrderCount][ii] = vec2(dObj.myYOutTangent[ii*2-1], dObj.myYOutTangent[ii*2+0]);
							tangentInY[vboOrderCount][ii] = vec2(dObj.myYInTangent[ii*2-1], dObj.myYInTangent[ii*2+0]);
							tangentOutYRot[vboOrderCount][ii] = vec2(dObj.myYRotEulerOutTangent[ii*2-1], dObj.myYRotEulerOutTangent[ii*2+0]);
							tangentInYRot[vboOrderCount][ii] = vec2(dObj.myYRotEulerInTangent[ii*2-1], dObj.myYRotEulerInTangent[ii*2+0]);
							tangentOutYScale[vboOrderCount][ii] = vec2(dObj.myYScaleOutTangent[ii*2-1], dObj.myYScaleOutTangent[ii*2+0]);
							tangentInYScale[vboOrderCount][ii] = vec2(dObj.myYScaleInTangent[ii*2-1], dObj.myYScaleInTangent[ii*2+0]);
							//Z TANGENT
							tangentOutZ[vboOrderCount][ii] = vec2(dObj.myZOutTangent[ii*2-1], dObj.myZOutTangent[ii*2+0]);
							tangentInZ[vboOrderCount][ii] = vec2(dObj.myZInTangent[ii*2-1], dObj.myZInTangent[ii*2+0]);
							tangentOutZRot[vboOrderCount][ii] = vec2(dObj.myZRotEulerOutTangent[ii*2-1], dObj.myZRotEulerOutTangent[ii*2+0]);
							tangentInZRot[vboOrderCount][ii] = vec2(dObj.myZRotEulerInTangent[ii*2-1], dObj.myZRotEulerInTangent[ii*2+0]);
							tangentOutZScale[vboOrderCount][ii] = vec2(dObj.myZScaleOutTangent[ii*2-1], dObj.myZScaleOutTangent[ii*2+0]);
							tangentInZScale[vboOrderCount][ii] = vec2(dObj.myZScaleInTangent[ii*2-1], dObj.myZScaleInTangent[ii*2+0]);
						}

						vec2 pX, pY, pZ,
							pRotX, pRotY, pRotZ,
							pScaleX, pScaleY, pScaleZ;

						/////////////////////////////////////////////////////////////////////////////

						pX = vec2(h1*p1[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*p2[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutX[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInX[vboOrderCount][ii]);
						pVec3Pos[vboOrderCount][ii].x = pX.x;//p1[i] = pX.x;

						pY = vec2(h1*p3[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*p4[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutY[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInY[vboOrderCount][ii]);
						pVec3Pos[vboOrderCount][ii].y = pY.x;//p3[i] = pY.x;

						pZ = vec2(h1*p5[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*p6[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutZ[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInZ[vboOrderCount][ii]);
						pVec3Pos[vboOrderCount][ii].z = pZ.x;//p5[i] = pZ.x;
						//printf("pVec3 i: %d X: %f Y: %f Z: %f\n", i, pVec3Pos[i].x, pVec3Pos[i].y, pVec3Pos[i].z);

						/////////////////////////////////////////////////////////////////////////////

						pRotX = vec2(h1*pRot1[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*pRot2[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutXRot[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInXRot[vboOrderCount][ii]);
						pVec3Rot[vboOrderCount][ii].x = pRotX.x;//pRot1[i] = pRotX.x;

						pRotY = vec2(h1*pRot3[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*pRot4[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutYRot[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInYRot[vboOrderCount][ii]);
						pVec3Rot[vboOrderCount][ii].y = pRotY.x;//pRot3[i] = pRotY.x;

						pRotZ = vec2(h1*pRot5[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*pRot6[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutZRot[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInZRot[vboOrderCount][ii]);
						pVec3Rot[vboOrderCount][ii].z = pRotZ.x;//pRot5[i] = pRotZ.x;

						/////////////////////////////////////////////////////////////////////////////

						pScaleX = vec2(h1*pScale1[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*pScale2[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutXScale[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInXScale[vboOrderCount][ii]);
						pVec3Scale[vboOrderCount][ii].x = pScaleX.x;//pScale1[i] = pScaleX.x;

						pScaleY = vec2(h1*pScale3[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*pScale4[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutYScale[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInYScale[vboOrderCount][ii]);
						pVec3Scale[vboOrderCount][ii].y = pScaleY.x;//pScale3[i] = pScaleY.x;

						pScaleZ = vec2(h1*pScale5[vboOrderCount][ii]) +                    // multiply and sum all funtions
							vec2(h2*pScale6[vboOrderCount][ii]) +                    // together to build the interpolated
							vec2(h3*tangentOutZScale[vboOrderCount][ii]) +                    // point along the curve.
							vec2(h4*tangentInZScale[vboOrderCount][ii]);
						pVec3Scale[vboOrderCount][ii].z = pScaleZ.x;//pScale5[i] = pScaleZ.x;
						//printf("pScale: %f\n", pScale1[i]);

						/////////////////////////////////////////////////////////////////////////////
						//lineto (p)                            // draw to calculated point on the curve
						//printf("t: %f X: %f Y: %f\n", t, p.x, p.y);
						//printf("t: %d storeID: %d X: %f Y: %f Z: %f\n", t, steps, pX.x, pY.x, pZ.x);
						//printf("t: %d storeID: %d X: %f Y: %f Z: %f\n", t, steps, pRotX.x, pRotY.x, pRotZ.x);
						//printf("t: %d storeID: %d X: %f Y: %f Z: %f\n", t, steps, pScaleX.x, pScaleY.x, pScaleZ.x);
						/////////////////////////////////////////////////////////////////////////////
						//printf("xIC: %d STEPS: %d vCount: %d X: %f Y: %f Z: %f\n", i, t, vboOrderCount, pVec3Pos[i].x, pVec3Pos[i].y, pVec3Pos[i].z);
						//printf("vC: %d loop: %d X: %f Y: %f Z: %f\n", vboOrderCount, loop, pVec3Rot[vboOrderCount][loop].x, pVec3Rot[vboOrderCount][loop].y, pVec3Rot[vboOrderCount][loop].z);
						trsSwapArray[vboOrderCount] = ii;
						//printf("vboOcount: %d i: %d trsSwap: %d\n", vboOrderCount, i, trsSwapArray[vboOrderCount]);
					}
				}
			}
			else
			{
				printf("noAnimation: %d\n", dObj.vboNumber);
				dObj.noAnimation[dObj.vboNumber] = dObj.vboNumber;
			}
			//printf("vboCount: %d\n", dObj.vboCount[vboID+i]);
			/*
			if(i == 0 || i <= dObj.matrixCount - 1)
			{
			vboOrderCount++;
			printf("vboOrderCount: %d\n", vboOrderCount);
			}
			*/

			dObj.loadOnce[vboID+i] = 1;//dObj.loadOnce[vboID] = 1;
			printf("loadOnce: %d - %d\n", dObj.loadOnce[vboID+i], vboID+i);

			vboOrderCount++;
		}
		//for(int i = 0; i < dObj.testMeshCount; i++)
		//for(int i = 0; i <= dObj.meshCount; i++)
		for(int i = 0; i < dObj.meshCount; i++)
		{
			if(dObj.indicescount != 1)//if(dObj.indicescount != 0)
			{
				printf("MESHCOUNT: %d i: %d\n", dObj.meshCount, i);
				//printf("MESHCOUNT: %d i: %d\n", dObj.testMeshCount, i);
				//loadmyDAE(modelfile, vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i], daeindices[vboID+i]);
				//indexVBO(vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i],
				//indices[vboID+i], indexed_vertices[vboID+i], indexed_uvs[vboID+i], indexed_normals[vboID+i]);
				if(texturefile != 0)
				{
					//Load the texture
					//Texture[vboID] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
					//Texture[0] = loadPngImage(DAEtexture, imgwidth, imgheight, hasAlpha, &textureImage);
					//Texture[vboID*3+0] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
					dObj.Texture[(vboID+i)*4+0] = loadPngImage("container2.png",          imgwidth, imgheight, hasAlpha, &textureImage);
					dObj.Texture[(vboID+i)*4+1] = loadPngImage("container2_normal.png", imgwidth, imgheight, hasAlpha, &textureImage);
					dObj.Texture[(vboID+i)*4+2] = loadPngImage("container2_specular.png", imgwidth, imgheight, hasAlpha, &textureImage);
					dObj.Texture[(vboID+i)*4+3] = loadPngImage("matrix.png",              imgwidth, imgheight, hasAlpha, &textureImage);
					printf("vboCHECK: %d, i: %d RESULT: %d\n", vboID, i, (vboID+i)*4+0);//printf("vboCHECK: %d, i: %d RESULT: %d\n", vboID, i, (vboID+i)*3+0);
					//Texture[vboID] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
					//delete textureImage;//REFRESH GENTEXTURES
					printf("TEST_TEXTURE: %d\n", dObj.Texture[(vboID+i)*4+3]);
					if(dObj.Texture[(vboID+i)*4+3] != 0)
					{
						dObj.materialVBOStoredUV[vboID+i] = 1;
					}
				}

				/*
				else if(texturefile == 0 && dObj.materialVBOnumber[vboID+i] == 1)//UV
				{
				//USE THE MATERIAL PARSED FROM FILE HERE
				//printf("TEST: %d\n", dObj.materialVBOnumber[dObj.currentDAEvbo]);
				printf("0TEXTURE: %d vboID: %d\n", dObj.materialVBOnumber[vboID+i], vboID+i);
				//SAVE ARRAY FOR LOOPING
				dObj.materialVBOStoredUV[vboID+i] = 1;
				}
				else if(texturefile == 0 && dObj.materialVBOnumber[vboID+i] == 0)//COLOR
				{
				printf("FOUNDCOLOR: %d vboID: %d\n", dObj.materialVBOnumber[vboID+i], vboID+i);
				//SAVE ARRAY FOR LOOPING
				dObj.materialVBOStoredColor[vboID+i] = 1;
				}
				*/

				//loadBMP_custom("test.bmp");
				//LoadBMP("test.bmp");
				//loadDDS("uvmap.DDS");
				//Get a handle for our "myTextureSampler" uniform
				//diffuseID[0] = glGetUniformLocation(programID, "myTexture");
				//diffuseID[vboID] = glGetUniformLocation(programID, "myTexture");
				dObj.diffuseID[vboID+i] = glGetUniformLocation(myShader, "material.diffuse");//DIFFUSE(TEXTURE) MAP
				dObj.normalID[vboID+i] = glGetUniformLocation(myShader, "material.normal");//NORMAL MAP
				dObj.specularID[vboID+i] = glGetUniformLocation(myShader, "material.specular");//SPECULAR MAP
				dObj.emissionID[vboID+i] = glGetUniformLocation(myShader, "material.emission");//EMISSION MAP


				glGenVertexArrays(1, &dObj.VertexArrayID[vboID+i]);
				glGenBuffers(1, &dObj.vertexbuffer[vboID+i]);
				glGenBuffers(1, &dObj.uvbuffer[vboID+i]);
				glGenBuffers(1, &dObj.normalbuffer[vboID+i]);
				glGenBuffers(1, &dObj.colorbuffer[vboID+i]);

				glGenBuffers(1, &dObj.tangentbuffer[vboID+i]);
				glGenBuffers(1, &dObj.bitangentbuffer[vboID+i]);

				glGenBuffers(1, &dObj.elementbuffer[vboID+i]);


				glBindVertexArray(dObj.VertexArrayID[vboID+i]);
				//printf("vboArrayID: %d\n", vboID+i);
				//VERTEXBUFFER
				glBindBuffer(GL_ARRAY_BUFFER, dObj.vertexbuffer[vboID+i]);
				//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, indexed_vertices[vboID+i].size() * sizeof(glm::vec3), &indexed_vertices[vboID+i][0], GL_STATIC_DRAW);
				//UVBUFFER
				glBindBuffer(GL_ARRAY_BUFFER, dObj.uvbuffer[vboID+i]);
				//glBufferData(GL_ARRAY_BUFFER, vectoruvs[vboLoop].size() * sizeof(glm::vec2), &vectoruvs[vboLoop][0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboID+i].size() * sizeof(glm::vec3), &indexed_uvs[vboID+i][0], GL_STATIC_DRAW);
				//COLORBUFFER
				glBindBuffer(GL_ARRAY_BUFFER, dObj.colorbuffer[vboID+i]);
				glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboID+i].size() * sizeof(glm::vec3), &indexed_uvs[vboID+i][0], GL_STATIC_DRAW);
				//NORMALBUFFER
				glBindBuffer(GL_ARRAY_BUFFER, dObj.normalbuffer[vboID+i]);
				//glBufferData(GL_ARRAY_BUFFER, vectornormals[vboLoop].size() * sizeof(glm::vec3), &vectornormals[vboLoop][0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, indexed_normals[vboID+i].size() * sizeof(glm::vec3), &indexed_normals[vboID+i][0], GL_STATIC_DRAW);

				//TANGENT
				glBindBuffer(GL_ARRAY_BUFFER, dObj.tangentbuffer[vboID+i]);
				glBufferData(GL_ARRAY_BUFFER, indexed_tangents[vboID+i].size() * sizeof(glm::vec3), &indexed_tangents[vboID+i][0], GL_STATIC_DRAW);
				//BITANGENT
				glBindBuffer(GL_ARRAY_BUFFER, dObj.bitangentbuffer[vboID+i]);
				glBufferData(GL_ARRAY_BUFFER, indexed_bitangents[vboID+i].size() * sizeof(glm::vec3), &indexed_bitangents[vboID+i][0], GL_STATIC_DRAW);

				//INDICEBUFFERS
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.elementbuffer[vboID+i]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[vboID+i].size() * sizeof(unsigned short), &indices[vboID+i][0], GL_STATIC_DRAW);
				printf("INDSIZE: %d\n", indices[vboID+i].size() * sizeof(unsigned short));
			}

			//dObj.loadOnce[vboID+i] = 1;//dObj.loadOnce[vboID] = 1;
			dObj.vboCount[vboID+i] = dObj.meshCount;//dObj.vboCount[vboID] = dObj.meshCount;
			//printf("vboCount: %d\n", dObj.vboCount[vboID]);
			//printf("vboCount: %d\n", dObj.vboCount[vboID+i]);

			//printf("vboOrderCount1: %d\n", vboOrderCount);
			//vboOrderCount++;
			//printf("vboOrderCount2: %d\n", vboOrderCount);

			//TEST
			dObj.meshLoad[vboID+i] = dObj.testMeshCount;//dObj.meshLoad[vboID] = dObj.testMeshCount;

		}

		/*
		dObj.vboCount[vboID] = dObj.meshCount;
		printf("vboCount: %d\n", dObj.vboCount[vboID]);
		//printf("vboOrderCount: %d\n", vboOrderCount);
		vboOrderCount++;
		//TEST
		dObj.meshLoad[vboID] = dObj.testMeshCount;
		*/

		//printf("vboID: %d vboOrderCount: %d matrixCount: %d mTransform: %d\n", vboID, vboOrderCount, dObj.matrixCount, dObj.meshTransform);
		//if(dObj.matrixCount < dObj.meshTransform)vboOrderCount += dObj.matrixCount;
		if(dObj.matrixCount < dObj.meshTransform)
		{
			//vboOrderCount += dObj.matrixCount;
			printf("vboID: %d vboOrderCount: %d matrixCount: %d mTransform: %d\n", vboID, vboOrderCount, dObj.matrixCount, dObj.meshTransform);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//printf("tNum: %d\n", dObj.testMeshCount);

	/*
	if(vboID == 1013)
	{
	testNum = 2;//dObj.testMeshCount;
	//testNum = dObj.testMeshCount;
	}
	else
	{
	testNum = 0;
	}
	*/

	//printf("meshLoad: %d\n", dObj.meshLoad[vboID]);

	//LOCROTSCALE ANIMATION
	//dObj.testMeshCount
	//rotSwap = 0;

	//for(int ii = 0; ii < dObj.vboCount[dObj.initalVBO] + dObj.matrixCountArray[vboID]; ii++)//TEST
	//printf("vN: %d VoC %d\n", dObj.vboNumber, vboOrderCount);
	if(dObj.vboNumber >= vboOrderCount)//FALLBACK
		//if(dObj.vboNumber + dObj.matrixCountArray[vboID] > vboOrderCount + dObj.vboCount[dObj.initalVBO])//TEST
	{
		//printf("vboCompare: %d - %d\n", dObj.vboNumber, vboOrderCount);
		//printf("vboCompare: %d - %d\n", dObj.vboNumber + dObj.matrixCountArray[vboID], vboOrderCount);//TEST
		//printf("vboCompare: %d - %d\n", dObj.vboNumber, vboOrderCount + dObj.vboCount[dObj.initalVBO]);//TEST
		dObj.vboNumber = 0;
		//printf("vboNumber 0\n");
		//printf("vboNumber 0: %d - %d\n", dObj.vboNumber, vboOrderCount);
	}

	//dObj.notDrawArray[dObj.vboNumber] = dObj.VBOloadedID;
	/*
	if(dObj.notDrawArray[dObj.vboNumber] != vboID)
	{
	dObj.VBOloadedID++;
	printf("TEST4ID: %d loadedID++ : %d\n", vboID, dObj.VBOloadedID);//_getch();
	}
	*/
	/*
	for(int i = 0; i < dObj.matrixCount; i++)
	{
	//if(dObj.notDrawArray[dObj.vboNumber] == vboID)
	if(dObj.notDrawArray[dObj.vboNumber] == vboID + i)
	{
	//dObj.VBOloadedID++;
	//printf("TEST4ID: %d loadedID++ : %d\n", vboID, dObj.VBOloadedID);//_getch();
	//printf("initialVBO: %d\n", dObj.initalVBO);
	}
	}
	*/

	/*
	if(dObj.loadOnce[vboID] == 1)
	//if(vboID == dObj.initalVBO + dObj.matrixCount)
	{
	//printf("END loadOnce: %d!\n", vboID);//_getch();
	//for(int i = 0; i < dObj.matrixCountArray[i]; i++)
	//for(int i = 0; i < dObj.matrixCountArray[vboID] - 1; i++)
	for(int i = 0; i < dObj.matrixCountArray[vboID]; i++)
	{
	dObj.cameraLightFound = 0;
	dObj.matrixCount = 0;

	//MOVE UP ID
	dObj.VBOloadedID++;
	printf("END countA: %d countB: %d\n", vboID, dObj.VBOloadedID);
	//printf("matrixCountArray2: %d\n", dObj.matrixCountArray[vboID]);_getch();
	}
	}
	*/
	//printf("TEST: %d\n", vboID);_getch();
	//printf("TEST5ID: %d loadedID++ : %d\n", vboID, dObj.VBOloadedID);//_getch();
	if(dObj.notDrawArray[dObj.vboNumber] != vboID)
	{
		//printf("notDrawArray: %d vboNumber: %d\n", dObj.notDrawArray[dObj.vboNumber], dObj.vboNumber);_getch();
		//for(int ii = 0; ii < dObj.meshCount; ii++)
		//for(int ii = 0; ii < dObj.testMeshCount; ii++)
		//for(int ii = 0; ii < dObj.vboCount[dObj.initalVBO]; ii++)//FALLBACK
		for(int ii = 0; ii < dObj.vboCount[dObj.initalVBO] + dObj.matrixCountArray[vboID]; ii++)//TEST
			//for(int ii = 0; ii < dObj.vboCount[dObj.initalVBO+ii]; ii++)
				//for(int ii = 0; ii < dObj.meshLoad[vboID]; ii++)
		{
			//printf("II loop: %d\n", ii);
			//printf("ii: %d vboCount: %d initialVBO: %d VBOloadedID: %d vboID: %d\n", ii, dObj.vboCount[dObj.initalVBO+ii], dObj.initalVBO, dObj.VBOloadedID, vboID);
			//printf("v: %d\n", dObj.vboNumber);

			dObj.TranslationMatrix = glm::mat4(
				dObj.storedmatrixtransform[dObj.vboNumber][0], dObj.storedmatrixtransform[dObj.vboNumber][4], dObj.storedmatrixtransform[dObj.vboNumber][8], dObj.storedmatrixtransform[dObj.vboNumber][12],
				dObj.storedmatrixtransform[dObj.vboNumber][1], dObj.storedmatrixtransform[dObj.vboNumber][5], dObj.storedmatrixtransform[dObj.vboNumber][9], dObj.storedmatrixtransform[dObj.vboNumber][13],
				dObj.storedmatrixtransform[dObj.vboNumber][2], dObj.storedmatrixtransform[dObj.vboNumber][6], dObj.storedmatrixtransform[dObj.vboNumber][10], dObj.storedmatrixtransform[dObj.vboNumber][14],
				dObj.storedmatrixtransform[dObj.vboNumber][3], dObj.storedmatrixtransform[dObj.vboNumber][7], dObj.storedmatrixtransform[dObj.vboNumber][11], dObj.storedmatrixtransform[dObj.vboNumber][15]);
			
			if(dObj.drawDisable[vboID+ii] == 0)
			{
				if(vboTRS > 0)//SET THE SPHERE TO THE VBONUMBER(TRANSLATION) OF LIGHTS
				{
					//printf("vboTRS\n");_getch();
					//dObj.loadLightPointArray[dObj.loadLightPoint]
					dObj.storedVboNumber = dObj.vboNumber;//RESTORE BACK TO VBONUMBER WHEN DONE
					if(vboTRS-1 < dObj.loadLightPoint)
					{
						//printf("AAA: %d\n", dObj.loadLightPoint);
						dObj.vboNumber = dObj.loadLightPointArray[vboTRS-1];
						//printf("1vboNumber: %d vboTRS: %d n: %d\n", dObj.vboNumber, dObj.loadLightPointArray[vboTRS-1], vboTRS-1);//_getch();
					}
					else if(vboTRS-1 < dObj.loadLightDirectional + dObj.loadLightPoint)
					{
						dObj.vboNumber = dObj.loadLightDirectionalArray[vboTRS - 1 - dObj.loadLightPoint];
						//printf("2vboNumber: %d vboTRS: %d n: %d\n", dObj.vboNumber, dObj.loadLightDirectionalArray[vboTRS-1-dObj.loadLightPoint], vboTRS-1);//_getch();
					}

					else if(vboTRS-1 < dObj.loadLightSpot + dObj.loadLightDirectional + dObj.loadLightPoint)
					{
						dObj.vboNumber = dObj.loadLightSpotArray[vboTRS - 1 - dObj.loadLightDirectional - dObj.loadLightPoint];
						//printf("3vboNumber: %d vboTRS: %d n: %d\n", dObj.vboNumber, dObj.loadLightSpotArray[vboTRS-1-dObj.loadLightDirectional-dObj.loadLightPoint], vboTRS-1);//_getch();
					}
					//printf("TOTAL: %d\n", dObj.loadLightPoint + dObj.loadLightDirectional + dObj.loadLightSpot);
				}

				/*
				for(int i = 0; i < vboColorCount; i++)
				{
				//printf("I: %d vboID: %d vboCount: %d vboArray\n", i, vboID, vboColorCount, vboColorArray[i]);
				if(vboColorArray[i] == vboID)
				{
				//glUseProgram(dObj.programShapesShaderID);
				//printf("COLOR SHADER %d vboColorCount: %d vboID: %d\n", i, vboColorCount, vboID);
				//rotSwap = 1;
				}
				}
				*/
				//printf("playLoop: %d\n", playLoop);
				//for(int i = dObj.vboNumber; i <= vboOrderCount; i++)


				//CHECK
				//dObj.matrixCountArray[vboID]
				//if(vboID + ii < vboID + dObj.matrixCountArray[vboID])
				//printf("TEST: %d - %d\n", vboID + ii, vboID + dObj.matrixCountArray[vboID]);_getch();
				//if(vboID == dObj.initalVBO || vboID + ii <= vboID + dObj.matrixCountArray[vboID] - 1)

				//if(dObj.initalVBO - dObj.vboCount[dObj.initalVBO+ii] < dObj.initalVBO)
				//printf("TEST: %d - %d\n", dObj.initalVBO - dObj.vboCount[dObj.initalVBO+ii], dObj.initalVBO);


				//if(dObj.vboNumber < vboOrderCount)
				//if(dObj.initalVBO - dObj.vboCount[dObj.initalVBO+ii] < dObj.initalVBO)
				//if(dObj.vboNumber < vboOrderCount && dObj.initalVBO - dObj.vboCount[dObj.initalVBO+ii] < dObj.initalVBO)//FALLBACK
				if(dObj.vboNumber < vboOrderCount)//TEST
				{
					//printf("v: %d\n", dObj.vboNumber);
					//printf("TEST: %d vboID: %d\n", dObj.vboNumber, vboID);_getch();//TEMP TEST
					//printf("START1 ");
					//printf("iLoop: %d vboOrderCount: %d\n", dObj.vboNumber, vboOrderCount);
					if(vboOrderArray[dObj.vboNumber] == vboID || vboTRS > 0)
					{
						//printf("v1: %d\n", dObj.vboNumber);
						//printf("2 ");
						//printf("vboID: %d i: %d testTime: %f vboOrderCount: %d\n", vboID, i, testTime[i], vboOrderCount);
						//printf("vboID: %d i: %d testTime: %f vboOrderCount: %d\n", vboID, ii, testTime[ii], vboOrderCount);
						//printf("trsSwapArray: %d dObj.vboNumber: %d\n", trsSwapArray[dObj.vboNumber], dObj.vboNumber);
						//printf("testTime: %f\n", testTime[vboNumber]);
						//(testTime[dObj.vboNumber] <= 1.0f && trsSwapArray[dObj.vboNumber] >= 0)
						if(testTime[dObj.vboNumber] < 1.0f && trsSwapArray[dObj.vboNumber] > 0 || vboTRS > 0)
						{
							//printf("v: %d\n", dObj.vboNumber);
							//if(dObj.myXInterpolation[playLoop[dObj.vboNumber]] == 2)//0 AS CUBIC, 1 AS LINEAR, 2 AS STEP (CONSTANT)

							if(vboTRS > 0)
							{
								//printf("v2: %d\n", dObj.vboNumber);
							}


							if(savedDoubleArray[dObj.vboNumber][playLoop[dObj.vboNumber]] == 2)//0 AS CUBIC, 1 AS LINEAR, 2 AS STEP (CONSTANT)
							{
								if(testTime[dObj.vboNumber] < 1.0f)
								{
									//LOC
									daeLocX = ((1.0f - 0) * p1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * p2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeLocY = ((1.0f - 0) * p3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * p4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeLocZ = ((1.0f - 0) * p5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * p6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									//printf("t: %f daeLocX: %f\n", testTime, daeLocX);
									//ROT
									daeRotEulerX = ((1.0f - 0) * pRot1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * pRot2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeRotEulerY = ((1.0f - 0) * pRot3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * pRot4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeRotEulerZ = ((1.0f - 0) * pRot5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * pRot6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									//printf("daeRot X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);
									//SCALE
									daeScaleX = ((1.0f - 0) * pScale1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * pScale2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeScaleY = ((1.0f - 0) * pScale3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * pScale4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeScaleZ = ((1.0f - 0) * pScale5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (0 * pScale6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									//printf("1t: %f daeScale X: %f Y: %f Z: %f\n", testTime, daeScaleX, daeScaleY, daeScaleZ);
								}
								else
								{
									//LOC
									daeLocX = ((1.0f - testTime[dObj.vboNumber]) * p1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * p2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeLocY = ((1.0f - testTime[dObj.vboNumber]) * p3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * p4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeLocZ = ((1.0f - testTime[dObj.vboNumber]) * p5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * p6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									//printf("t: %f daeLocX: %f\n", testTime, daeLocX);
									//ROT
									daeRotEulerX = ((1.0f - testTime[dObj.vboNumber]) * pRot1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pRot2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeRotEulerY = ((1.0f - testTime[dObj.vboNumber]) * pRot3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pRot4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeRotEulerZ = ((1.0f - testTime[dObj.vboNumber]) * pRot5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pRot6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									//printf("daeRot X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);
									//SCALE
									daeScaleX = ((1.0f - testTime[dObj.vboNumber]) * pScale1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pScale2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeScaleY = ((1.0f - testTime[dObj.vboNumber]) * pScale3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pScale4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									daeScaleZ = ((1.0f - testTime[dObj.vboNumber]) * pScale5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pScale6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
									//printf("2t: %f daeScale X: %f Y: %f Z: %f\n", testTime, daeScaleX, daeScaleY, daeScaleZ);
								}
								//printf("playLoop: %d testTime: %f\n", playLoop, testTime);
								//printf("DAE STEP CONSTANT\n");

								dObj.TranslationMatrix = glm::mat4(1.0f);
								dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

								dObj.RotationMatrixArray[dObj.vboNumber] = glm::mat4(1.0f);
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

								dObj.ScalingMatrix = glm::mat4(1.0f);
								dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
								//printf("STEP\n");
							}
							//else if(dObj.myXInterpolation[playLoop[dObj.vboNumber]] == 1)//LINEAR
							else if(savedDoubleArray[dObj.vboNumber][playLoop[dObj.vboNumber]] == 1)//LINEAR
							{
								//printf("1\n");
								//LOC
								daeLocX = ((1.0f - testTime[dObj.vboNumber]) * p1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * p2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								daeLocY = ((1.0f - testTime[dObj.vboNumber]) * p3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * p4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								daeLocZ = ((1.0f - testTime[dObj.vboNumber]) * p5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * p6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								//printf("t: %f daeLocX: %f\n", testTime, daeLocX);
								//ROT
								daeRotEulerX = ((1.0f - testTime[dObj.vboNumber]) * pRot1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pRot2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								daeRotEulerY = ((1.0f - testTime[dObj.vboNumber]) * pRot3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pRot4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								daeRotEulerZ = ((1.0f - testTime[dObj.vboNumber]) * pRot5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pRot6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								//printf("daeRot X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);
								//SCALE
								daeScaleX = ((1.0f - testTime[dObj.vboNumber]) * pScale1[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pScale2[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								daeScaleY = ((1.0f - testTime[dObj.vboNumber]) * pScale3[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pScale4[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								daeScaleZ = ((1.0f - testTime[dObj.vboNumber]) * pScale5[dObj.vboNumber][playLoop[dObj.vboNumber]] + (testTime[dObj.vboNumber] * pScale6[dObj.vboNumber][playLoop[dObj.vboNumber]]));
								//printf("t: %f daeScale X: %f Y: %f Z: %f\n", testTime, daeScaleX, daeScaleY, daeScaleZ);


								dObj.TranslationMatrix = glm::mat4(1.0f);
								dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

								dObj.RotationMatrixArray[dObj.vboNumber] = glm::mat4(1.0f);
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

								dObj.ScalingMatrix = glm::mat4(1.0f);
								dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
								//printf("DAE LINEAR\n");
							}
							//if(dObj.myXInterpolation[playLoop[dObj.vboNumber]] == 0)//CUBIC SPLINE
							if(savedDoubleArray[dObj.vboNumber][playLoop[dObj.vboNumber]] == 0)//CUBIC SPLINE
							{
								//printf("testVBO1: %d\n", dObj.vboNumber);
								//printf("0\n");
								vec3 previousTangent, nextTangent;
								previousTangent = deltaTime * vec3(tangentOutX[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentOutY[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentOutZ[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
								nextTangent = deltaTime * vec3(tangentInX[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentInY[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentInZ[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
								//printf("Tangent PREV X: %f Y: %f\n", previousTangent.x, previousTangent.y);
								//printf("Tangent NEXT X: %f Y: %f\n", nextTangent.x, nextTangent.y);

								vec3 tempVec3Pos, tempVec3Rot, tempVec3Scale;
								tempVec3Pos = vec3(p1[dObj.vboNumber][playLoop[dObj.vboNumber]], p3[dObj.vboNumber][playLoop[dObj.vboNumber]], p5[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
									((1.0f + 2.0f * testTime[dObj.vboNumber]) * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
									previousTangent * (testTime[dObj.vboNumber] * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
									vec3(p2[dObj.vboNumber][playLoop[dObj.vboNumber]], p4[dObj.vboNumber][playLoop[dObj.vboNumber]], p6[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
									((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (3.0f - 2.0f * testTime[dObj.vboNumber])) +
									nextTangent * ((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (testTime[dObj.vboNumber] - 1.0f));

								daeLocX = tempVec3Pos.x;
								daeLocY = tempVec3Pos.y;
								daeLocZ = tempVec3Pos.z;
								//printf("v3Pos X: %f Y: %f Z: %f\n", tempVec3Pos.x, tempVec3Pos.y, tempVec3Pos.z);
								//daeLocX = pVec3Pos[i][loopTest[i]].x;
								//daeLocY = pVec3Pos[i][loopTest[i]].y;
								//daeLocZ = pVec3Pos[i][loopTest[i]].z;
								
								//ROT
								previousTangent = deltaTime * vec3(tangentOutXRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentOutYRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentOutZRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
								nextTangent = deltaTime * vec3(tangentInXRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentInYRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentInZRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x);

								tempVec3Rot = vec3(pRot1[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot3[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot5[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
									((1.0f + 2.0f * testTime[dObj.vboNumber]) * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
									previousTangent * (testTime[dObj.vboNumber] * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
									vec3(pRot2[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot4[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot6[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
									((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (3.0f - 2.0f * testTime[dObj.vboNumber])) +
									nextTangent * ((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (testTime[dObj.vboNumber] - 1.0f));


								daeRotEulerX = tempVec3Rot.x;
								daeRotEulerY = tempVec3Rot.y;
								daeRotEulerZ = tempVec3Rot.z;
								//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX[dObj.vboNumber], daeRotEulerY[dObj.vboNumber], daeRotEulerZ[dObj.vboNumber], dObj.vboNumber);
								//daeRotEulerX = pVec3Rot[dObj.vboNumber][loopTest[dObj.vboNumber]].x;
								//daeRotEulerY = pVec3Rot[dObj.vboNumber][loopTest[dObj.vboNumber]].y;
								//daeRotEulerZ = pVec3Rot[dObj.vboNumber][loopTest[dObj.vboNumber]].z;
								//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, i);

								//SCALE
								previousTangent = deltaTime * vec3(tangentOutXScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentOutYScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentOutZScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
								nextTangent = deltaTime * vec3(tangentInXScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentInYScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
									tangentInZScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x);

								tempVec3Scale = vec3(pScale1[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale3[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale5[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
									((1.0f + 2.0f * testTime[dObj.vboNumber]) * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
									previousTangent * (testTime[dObj.vboNumber] * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
									vec3(pScale2[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale4[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale6[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
									((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (3.0f - 2.0f * testTime[dObj.vboNumber])) +
									nextTangent * ((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (testTime[dObj.vboNumber] - 1.0f));

								daeScaleX = tempVec3Scale.x;
								daeScaleY = tempVec3Scale.y;
								daeScaleZ = tempVec3Scale.z;
								//printf("playLoop: %d daeScale X: %f Y: %f Z: %f\n", playLoop[i], daeScaleX, daeScaleY, daeScaleZ);

								dObj.TranslationMatrix = glm::mat4(1.0f);
								dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));


								if(dObj.vboNumber == 5)
								{
									//printf("1X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][0], dObj.TranslationMatrix[0][4], dObj.TranslationMatrix[0][8], dObj.TranslationMatrix[0][12]);
									//printf("2X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][1], dObj.TranslationMatrix[0][5], dObj.TranslationMatrix[0][9], dObj.TranslationMatrix[0][13]);
									//printf("3X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][2], dObj.TranslationMatrix[0][6], dObj.TranslationMatrix[0][10], dObj.TranslationMatrix[0][14]);
									//printf("4X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][3], dObj.TranslationMatrix[0][7], dObj.TranslationMatrix[0][11], dObj.TranslationMatrix[0][15]);
								}


								dObj.RotationMatrixArray[dObj.vboNumber] = glm::mat4(1.0f);
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

								dObj.ScalingMatrix = glm::mat4(1.0f);
								dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
							}
							else
							{
								//
							}
						}
						else
						{
							//printf("testVBO2: %d\n", dObj.vboNumber);

							vec3 previousTangent, nextTangent;
							previousTangent = deltaTime * vec3(tangentOutX[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentOutY[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentOutZ[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
							nextTangent = deltaTime * vec3(tangentInX[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentInY[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentInZ[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
							//printf("Tangent PREV X: %f Y: %f\n", previousTangent.x, previousTangent.y);
							//printf("Tangent NEXT X: %f Y: %f\n", nextTangent.x, nextTangent.y);

							vec3 tempVec3Pos, tempVec3Rot, tempVec3Scale;
							tempVec3Pos = vec3(p1[dObj.vboNumber][playLoop[dObj.vboNumber]], p3[dObj.vboNumber][playLoop[dObj.vboNumber]], p5[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
								((1.0f + 2.0f * testTime[dObj.vboNumber]) * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
								previousTangent * (testTime[dObj.vboNumber] * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
								vec3(p2[dObj.vboNumber][playLoop[dObj.vboNumber]], p4[dObj.vboNumber][playLoop[dObj.vboNumber]], p6[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
								((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (3.0f - 2.0f * testTime[dObj.vboNumber])) +
								nextTangent * ((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (testTime[dObj.vboNumber] - 1.0f));

							daeLocX = tempVec3Pos.x;
							daeLocY = tempVec3Pos.y;
							daeLocZ = tempVec3Pos.z;
							//printf("v3Pos X: %f Y: %f Z: %f\n", tempVec3Pos.x, tempVec3Pos.y, tempVec3Pos.z);
							//daeLocX = pVec3Pos[i][loopTest[i]].x;
							//daeLocY = pVec3Pos[i][loopTest[i]].y;
							//daeLocZ = pVec3Pos[i][loopTest[i]].z;

							//ROT
							previousTangent = deltaTime * vec3(tangentOutXRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentOutYRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentOutZRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
							nextTangent = deltaTime * vec3(tangentInXRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentInYRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentInZRot[dObj.vboNumber][playLoop[dObj.vboNumber]].x);

							tempVec3Rot = vec3(pRot1[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot3[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot5[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
								((1.0f + 2.0f * testTime[dObj.vboNumber]) * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
								previousTangent * (testTime[dObj.vboNumber] * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
								vec3(pRot2[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot4[dObj.vboNumber][playLoop[dObj.vboNumber]], pRot6[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
								((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (3.0f - 2.0f * testTime[dObj.vboNumber])) +
								nextTangent * ((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (testTime[dObj.vboNumber] - 1.0f));

							daeRotEulerX = tempVec3Rot.x;
							daeRotEulerY = tempVec3Rot.y;
							daeRotEulerZ = tempVec3Rot.z;
							//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, vboNumber);
							//daeRotEulerX = pVec3Rot[dObj.vboNumber][loopTest[dObj.vboNumber]].x;
							//daeRotEulerY = pVec3Rot[dObj.vboNumber][loopTest[dObj.vboNumber]].y;
							//daeRotEulerZ = pVec3Rot[dObj.vboNumber][loopTest[dObj.vboNumber]].z;
							//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, i);

							//SCALE
							previousTangent = deltaTime * vec3(tangentOutXScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentOutYScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentOutZScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x);
							nextTangent = deltaTime * vec3(tangentInXScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentInYScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x, 
								tangentInZScale[dObj.vboNumber][playLoop[dObj.vboNumber]].x);

							tempVec3Scale = vec3(pScale1[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale3[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale5[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
								((1.0f + 2.0f * testTime[dObj.vboNumber]) * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
								previousTangent * (testTime[dObj.vboNumber] * ((1.0f - testTime[dObj.vboNumber]) * (1.0f - testTime[dObj.vboNumber]))) +
								vec3(pScale2[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale4[dObj.vboNumber][playLoop[dObj.vboNumber]], pScale6[dObj.vboNumber][playLoop[dObj.vboNumber]]) * 
								((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (3.0f - 2.0f * testTime[dObj.vboNumber])) +
								nextTangent * ((testTime[dObj.vboNumber] * testTime[dObj.vboNumber]) * (testTime[dObj.vboNumber] - 1.0f));

							daeScaleX = tempVec3Scale.x;
							daeScaleY = tempVec3Scale.y;
							daeScaleZ = tempVec3Scale.z;

							dObj.TranslationMatrix = glm::mat4(1.0f);
							dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

							dObj.RotationMatrixArray[dObj.vboNumber] = glm::mat4(1.0f);
							dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
							dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
							dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(dObj.RotationMatrixArray[dObj.vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

							dObj.ScalingMatrix = glm::mat4(1.0f);
							dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))


							testTime[dObj.vboNumber] = 0.0f;
							if(playLoop[dObj.vboNumber] > playCount[dObj.vboNumber] - 1)//if(playLoop[i] > playCount[vboID] - 1)
							{
								playLoop[dObj.vboNumber] = 0;
							}
							else
							{
								playLoop[dObj.vboNumber] += 1;
							}
						}
						if(trsSwapArray[dObj.vboNumber] == 0)
						{
							//printf("v: %d\n", dObj.vboNumber);

							daeLocX = 0.0f;
							daeLocY = 0.0f;
							daeLocZ = 0.0f;
							daeRotEulerX = 0.0f;
							daeRotEulerY = 0.0f;
							daeRotEulerZ = 0.0f;
							daeScaleX = 1.0f;
							daeScaleY = 1.0f;
							daeScaleZ = 1.0f;

							//dObj.TranslationMatrix = glm::mat4(1.0f);
							//dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(modelX, modelY, modelZ)));

							/*
							if(vboTRS == 1)//ORBIT
							{
								//LIGHT SOURCE
								glm::vec3 lightPos(lightX * sin(glfwGetTime() * 0.5f), lightY, lightZ * cos(glfwGetTime() * 0.5f));//OUTSIDE_ORBIT
								dObj.TranslationMatrix = glm::mat4(1.0f);
								dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, lightPos);
								//dObj.TranslationMatrix = glm::scale(dObj.TranslationMatrix, glm::vec3(0.2f));//0.2f
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::mat4(1.0f);
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
								dObj.ScalingMatrix = scale(mat4(), vec3(0.2f, 0.2f, 0.2f));//scalingX, scalingY, scalingZ));
							}
							*/
							//else
							//{
								//printf("testVBO2: %d\n", dObj.vboNumber);
								if(dObj.vboNumber == dObj.noAnimation[dObj.vboNumber])
								{
									//printf("testVBO: %d\n", dObj.vboNumber);

									dObj.TranslationMatrix = glm::mat4(1.0f);
									dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, vec3(0.0f, 0.0f, 0.0f));


									//dObj.TranslationMatrix = glm::mat4(
									//dObj.storedmatrixtransform[dObj.vboNumber][0], dObj.storedmatrixtransform[dObj.vboNumber][4], dObj.storedmatrixtransform[dObj.vboNumber][8], dObj.storedmatrixtransform[dObj.vboNumber][12],
									//dObj.storedmatrixtransform[dObj.vboNumber][1], dObj.storedmatrixtransform[dObj.vboNumber][5], dObj.storedmatrixtransform[dObj.vboNumber][9], dObj.storedmatrixtransform[dObj.vboNumber][13],
									//dObj.storedmatrixtransform[dObj.vboNumber][2], dObj.storedmatrixtransform[dObj.vboNumber][6], dObj.storedmatrixtransform[dObj.vboNumber][10], dObj.storedmatrixtransform[dObj.vboNumber][14],
									//dObj.storedmatrixtransform[dObj.vboNumber][3], dObj.storedmatrixtransform[dObj.vboNumber][7], dObj.storedmatrixtransform[dObj.vboNumber][11], dObj.storedmatrixtransform[dObj.vboNumber][15]);
									//printf("1aX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][0], dObj.storedmatrixtransform[dObj.vboNumber][4], dObj.storedmatrixtransform[dObj.vboNumber][8], dObj.storedmatrixtransform[dObj.vboNumber][12]);
									//printf("2aX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][1], dObj.storedmatrixtransform[dObj.vboNumber][5], dObj.storedmatrixtransform[dObj.vboNumber][9], dObj.storedmatrixtransform[dObj.vboNumber][13]);
									//printf("3aX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][2], dObj.storedmatrixtransform[dObj.vboNumber][6], dObj.storedmatrixtransform[dObj.vboNumber][10], dObj.storedmatrixtransform[dObj.vboNumber][14]);
									//printf("4aX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][3], dObj.storedmatrixtransform[dObj.vboNumber][7], dObj.storedmatrixtransform[dObj.vboNumber][11], dObj.storedmatrixtransform[dObj.vboNumber][15]);
								}
								else
								{
									dObj.TranslationMatrix = glm::mat4(1.0f);
									dObj.TranslationMatrix = glm::mat4(
										dObj.storedmatrixtransform[dObj.vboNumber][0], dObj.storedmatrixtransform[dObj.vboNumber][4], dObj.storedmatrixtransform[dObj.vboNumber][8], dObj.storedmatrixtransform[dObj.vboNumber][12],
										dObj.storedmatrixtransform[dObj.vboNumber][1], dObj.storedmatrixtransform[dObj.vboNumber][5], dObj.storedmatrixtransform[dObj.vboNumber][9], dObj.storedmatrixtransform[dObj.vboNumber][13],
										dObj.storedmatrixtransform[dObj.vboNumber][2], dObj.storedmatrixtransform[dObj.vboNumber][6], dObj.storedmatrixtransform[dObj.vboNumber][10], dObj.storedmatrixtransform[dObj.vboNumber][14],
										dObj.storedmatrixtransform[dObj.vboNumber][3], dObj.storedmatrixtransform[dObj.vboNumber][7], dObj.storedmatrixtransform[dObj.vboNumber][11], dObj.storedmatrixtransform[dObj.vboNumber][15]);

									//printf("1bX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][0], dObj.storedmatrixtransform[dObj.vboNumber][4], dObj.storedmatrixtransform[dObj.vboNumber][8], dObj.storedmatrixtransform[dObj.vboNumber][12]);
									//printf("2bX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][1], dObj.storedmatrixtransform[dObj.vboNumber][5], dObj.storedmatrixtransform[dObj.vboNumber][9], dObj.storedmatrixtransform[dObj.vboNumber][13]);
									//printf("3bX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][2], dObj.storedmatrixtransform[dObj.vboNumber][6], dObj.storedmatrixtransform[dObj.vboNumber][10], dObj.storedmatrixtransform[dObj.vboNumber][14]);
									//printf("4bX: %f Y: %f Z: %f W: %f\n", dObj.storedmatrixtransform[dObj.vboNumber][3], dObj.storedmatrixtransform[dObj.vboNumber][7], dObj.storedmatrixtransform[dObj.vboNumber][11], dObj.storedmatrixtransform[dObj.vboNumber][15]);
									//_getch();
								}


								//DIRECTIONAL LIGHT
								//glm::mat4 model = glm::mat4(1.0f);
								//model = glm::translate(model, cubePositions[i]);
								float angle = 20.0f * ii;
								dObj.TranslationMatrix = glm::rotate(dObj.TranslationMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
								//lightingShader.setMat4("model", model);

								dObj.RotationMatrixArray[dObj.vboNumber] = glm::mat4(1.0f);
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
								dObj.RotationMatrixArray[dObj.vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

								dObj.ScalingMatrix = glm::mat4(1.0f);
								dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
								//printf("trsSwapArray: %d\n", trsSwapArray[dObj.vboNumber]);
								//printf("VBONUMBER: %d\n", dObj.vboNumber);
							}
						//}
						//printf("daeRot X: %f Y: %f Z: %f i: %d playLoop: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, i, playLoop[i]);
						testTime[dObj.vboNumber] += 0.1f;
					}
					else
					{
						//
					}
				}
				else
				{
					//if(dObj.vboNumber >= vboOrderCount)dObj.vboNumber = 0;
				}

				//printf("123\n");

				//dObj.myXInterpolation[playLoop[dObj.vboNumber]]
				//printf("vboNum: %d playLtest: %d\n", dObj.vboNumber, playLoop[dObj.vboNumber]);

				//dObj.vboNumber++;
				//printf("vboNumber: %d\n", dObj.vboNumber);

				//dObj.TranslationMatrix = glm::mat4(1.0f);
				//dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

				//printf("tMatrix1 X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][0], dObj.TranslationMatrix[0][1], dObj.TranslationMatrix[0][2], dObj.TranslationMatrix[0][3]);
				//printf("tMatrix2 X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][4], dObj.TranslationMatrix[0][5], dObj.TranslationMatrix[0][6], dObj.TranslationMatrix[0][7]);
				//printf("tMatrix3 X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][8], dObj.TranslationMatrix[0][9], dObj.TranslationMatrix[0][10], dObj.TranslationMatrix[0][11]);
				//printf("tMatrix4 X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][12], dObj.TranslationMatrix[0][13], dObj.TranslationMatrix[0][14], dObj.TranslationMatrix[0][15]);

				//EULER
				//dObj.RotationMatrix = eulerAngleYXZ(rotY, rotX, rotZ);
				//dObj.RotationMatrix = eulerAngleYXZ(daeRotEulerX, daeRotEulerY, daeRotEulerZ);
				//https://stackoverflow.com/questions/63955651/how-to-rotate-an-object-around-world-axis-and-not-local-axis-in-opengl
				//dObj.RotationMatrix = glm::rotate(dObj.RotationMatrix, -90 * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

				//YZX
				//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
				//dObj.RotationMatrix = glm::rotate(dObj.RotationMatrix, daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				//dObj.RotationMatrix = glm::rotate(dObj.RotationMatrix, daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
				//dObj.RotationMatrix = glm::rotate(dObj.RotationMatrix, daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
				//printf("DAE X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);

				/*
				if(rotSwap == 0)
				{
				dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
				dObj.ModelMatrix = dObj.TranslationMatrix * dObj.RotationMatrix * dObj.ScalingMatrix;
				//printf("rotSwap0\n");
				}
				else if(rotSwap == 1)
				{
				//dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(modelX, modelY, modelZ)));
				dObj.ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
				dObj.ModelMatrix = dObj.TranslationMatrix * dObj.shapesRotationMatrix * dObj.ScalingMatrix;
				//printf("rotSwap1\n");
				}
				*/

				//QUAT
				//vec3 desiredDir = glm::vec3(daeRotEulerX, daeRotEulerY, daeRotEulerZ);
				//vec3 desiredDir = glm::vec3(daeRotEulerY, daeRotEulerZ, daeRotEulerX);
				//vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
				//vec3 desiredDir = glm::vec3(testX, testY, testZ);
				//vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y

				//EULER TO QUATERNION
				//quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
				//gOrientation2[vboID+ii] = RotateTowards(gOrientation2[vboID+ii], targetOrientation, 1.0f*deltaTime);//And interpolate
				//dObj.RotationMatrix = mat4_cast(targetOrientation);
				//dObj.RotationMatrix = mat4_cast(gOrientation2[vboID+ii]);

				//view = LookAt(eye, eye + target, up);
				if(myCam == 0)
				{
					dObj.view = LookAt(eye, eye + dObj.target, dObj.up);
					//printf("myCam: %d\n", myCam);
				}
				else if(myCam == 1)
				{
					dObj.view = dObj.viewCamera1;
					//printf("myCam: %d\n", myCam);
				}

				dObj.projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
				glUniformMatrix4fv(dObj.uniformProjectionVBO, 1, GL_FALSE, glm::value_ptr(dObj.projection));
				glUniformMatrix4fv(dObj.uniformViewVBO, 1, GL_FALSE, glm::value_ptr(dObj.view));

				dObj.ModelMatrix = dObj.TranslationMatrix * dObj.RotationMatrixArray[dObj.vboNumber] * dObj.ScalingMatrix;
				glUniformMatrix4fv(dObj.uniformModelVBO, 1, GL_FALSE, glm::value_ptr(dObj.ModelMatrix));
				dObj.MVP = dObj.projection * dObj.view * dObj.ModelMatrix;
				glUniformMatrix4fv(dObj.MatrixIDVBO, 1, GL_FALSE, &dObj.MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//glm::mat4 ModelViewMatrix = dObj.view * dObj.ModelMatrix;
				//glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
				//glUniformMatrix3fv(dObj.ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//glUniform3f(glGetUniformLocation(myShader, "lightColor"), 1.0f, 1.0f, 1.0f);
				//glUniform3f(glGetUniformLocation(myShader, "lightColor"), 0.5f, 0.5f, 0.5f);
				//glUniform3f(glGetUniformLocation(myShader, "objectColor"), 1.0f, 0.5f, 0.31f);
				//glUniform4f(glGetUniformLocation(myShader, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4

				//glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
				//glm::vec3 lightPos = glm::vec3(4,4,4);
				//glm::vec3 lightPos = glm::vec3(1.0f,1.0f,1.0f);
				//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
				//LightID[vboID] = glGetUniformLocation(myShader, "LightPosition_worldspace");
				glUniform3f(glGetUniformLocation(myShader, "LightPosition_worldspace"), eye.x, eye.y, eye.z);

				//printf("STOP2: %d\n", dObj.vboNumber);_getch();
				glUniform1i(glGetUniformLocation(myShader, "numDirLights"), dObj.loadLightDirectional);//dObj.loadLightDirectional
				glUniform1i(glGetUniformLocation(myShader, "numPointLights"), dObj.loadLightPoint);//dObj.loadLightPoint
				glUniform1i(glGetUniformLocation(myShader, "numSpotLights"), dObj.loadLightSpot);//dObj.loadLightSpot

				//TEST
				if(dObj.switchColor == 1)
				{
					glUniform1i(glGetUniformLocation(myShader, "shiftColor"), 1);
				}

				//LIGHT SOURCE
				//glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX * (float)sin(glfwGetTime()) - modelX, lightY - modelY, lightZ * (float)cos(glfwGetTime()) - modelZ);//OUTSIDE_ORBIT
				glUniform3f(glGetUniformLocation(myShader, "lightPos"), eye.x, eye.y, eye.z);//modelX, modelY, modelZ);
				//glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX, lightY, lightZ);
				//glUniform3f(glGetUniformLocation(myShader, "lightPos"), 0.0f, 0.0f, 0.0f);
				//glUniform3f(glGetUniformLocation(myShader, "lightPos"), 1.2f, 1.0f, 2.0f);
				//glUniform3f(glGetUniformLocation(myShader, "lightPos"), 0.0f - modelX, 0.0f - modelY, 5.0f - modelZ);
				//glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX - modelX, lightY - modelY, lightZ - modelZ);
				//glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX * sin(glfwGetTime()), lightY, lightZ * cos(glfwGetTime()));

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//CAMERA POSITION
				//vec3 tempEye = eye + target;
				//glUniform3f(glGetUniformLocation(myShader, "viewPos"), lightX, lightY, lightZ);
				//glUniform3f(glGetUniformLocation(myShader, "viewPos"), 0.0f, 0.0f, 0.0f);
				//glUniform3f(glGetUniformLocation(myShader, "viewPos"), eyeX, eyeY, eyeZ);
				glUniform3f(glGetUniformLocation(myShader, "viewPos"), eye.x, eye.y, eye.z);
				//printf("EYE X: %f Y: %f Z: %f\n", eye.x, eye.y, eye.z);

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								
				for(int i = 0; i < dObj.loadLightPoint; i++)
				{
					if(dObj.vboNumber == dObj.loadLightPointArray[i])
					{
						char tempPointLightPosition[255], tempPointLightAmbient[255], tempPointLightDiffuse[255], tempPointLightSpecular[255], tempPointLightConstant[255], tempPointLightLinear[255], tempPointLightQuadratic[255], tempArray[255];
						//PREFIX
						strcpy(tempPointLightPosition, pointLight);strcpy(tempPointLightAmbient, pointLight);strcpy(tempPointLightDiffuse, pointLight);strcpy(tempPointLightSpecular, pointLight);strcpy(tempPointLightConstant, pointLight);strcpy(tempPointLightLinear, pointLight);strcpy(tempPointLightQuadratic, pointLight);
						//ARRAY NUMBER
						strcpy(tempArray, "[");
						char snum[100];
						snprintf(snum, 100, "%d", i);
						strncat(tempArray, snum, 100);
						strncat(tempArray, "]", 1);
						//APPEND ARRAY
						strncat(tempPointLightPosition, tempArray, strlen(tempArray));
						strncat(tempPointLightAmbient, tempArray, strlen(tempArray));
						strncat(tempPointLightDiffuse, tempArray, strlen(tempArray));
						strncat(tempPointLightSpecular, tempArray, strlen(tempArray));
						strncat(tempPointLightConstant, tempArray, strlen(tempArray));
						strncat(tempPointLightLinear, tempArray, strlen(tempArray));
						strncat(tempPointLightQuadratic, tempArray, strlen(tempArray));
						//APPEND SUFFIX
						strncat(tempPointLightPosition, matPosition, strlen(matPosition));
						strncat(tempPointLightAmbient, matAmbient, strlen(matAmbient));
						strncat(tempPointLightDiffuse, matDiffuse, strlen(matDiffuse));
						strncat(tempPointLightSpecular, matSpecular, strlen(matSpecular));
						strncat(tempPointLightConstant, matConstant, strlen(matConstant));
						strncat(tempPointLightLinear, matLinear, strlen(matLinear));
						strncat(tempPointLightQuadratic, matQuadratic, strlen(matQuadratic));
						//POINT LIGHT
						glUniform3f(glGetUniformLocation(myShader, tempPointLightPosition), dObj.TranslationMatrix[0][12], dObj.TranslationMatrix[0][13], dObj.TranslationMatrix[0][14]);//glUniform3f(glGetUniformLocation(myShader, "pointLight.position"), 5.0f, 5.0f, 0.0f);//modelX, modelY, modelZ);
						glUniform3f(glGetUniformLocation(myShader, tempPointLightAmbient), 0.4f, 0.4f, 0.4f);//glUniform3f(glGetUniformLocation(myShader, "pointLight.ambient"), 0.5f, 0.5f, 0.5f);//1.0f, 1.0f, 1.0f);
						glUniform3f(glGetUniformLocation(myShader, tempPointLightDiffuse), 0.6f, 0.6f, 0.6f);//glUniform3f(glGetUniformLocation(myShader, "pointLight.diffuse"), 0.6f, 0.6f, 0.6f);//1.0f, 1.0f, 1.0f);
						glUniform3f(glGetUniformLocation(myShader, tempPointLightSpecular), 0.7f, 0.7f, 0.7f);//glUniform3f(glGetUniformLocation(myShader, "pointLight.specular"), 0.7f, 0.7f, 0.7f);//1.0f, 1.0f, 1.0f);
						glUniform1f(glGetUniformLocation(myShader, tempPointLightConstant), 1.0f);//glUniform1f(glGetUniformLocation(myShader, "pointLight.constant"), 1.0f);
						glUniform1f(glGetUniformLocation(myShader, tempPointLightLinear), 0.09f);//glUniform1f(glGetUniformLocation(myShader, "pointLight.linear"), 0.09f);
						glUniform1f(glGetUniformLocation(myShader, tempPointLightQuadratic), 0.032f);//glUniform1f(glGetUniformLocation(myShader, "pointLight.quadratic"), 0.032f);
						//printf("A: %s point: %d\n", tempPointLightPosition, dObj.loadLightPoint);
						//printf("B: %s point: %d\n", tempPointLightAmbient, dObj.loadLightPoint);
						//printf("C: %s point: %d\n", tempPointLightDiffuse, dObj.loadLightPoint);
						//printf("D: %s point: %d\n", tempPointLightSpecular, dObj.loadLightPoint);
					}
				}

				for(int i = 0; i < dObj.loadLightDirectional; i++)
				{
					//printf("lLight: %d\n", i);
					//dObj.loadLightArray[dObj.loadLight] = vboOrderCount;
					if(dObj.vboNumber == dObj.loadLightDirectionalArray[i])//if(dObj.vboNumber == 0)
					{
						//if(dObj.vboNumber == 5)//IF FOUND LIGHTING USE ARRAY
						//{
							//glm::vec4 tempVec4 = dObj.TranslationMatrix * vec4(1.0f);
							//printf("v3 X: %f Y: %f Z: %f\n", tempVec4.x, tempVec4.y, tempVec4.z);
							//printf("LLA: %d\n", dObj.loadLightArray[i]);_getch();
							//printf("1X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][0], dObj.TranslationMatrix[0][4], dObj.TranslationMatrix[0][8], dObj.TranslationMatrix[0][12]);
							//printf("2X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][1], dObj.TranslationMatrix[0][5], dObj.TranslationMatrix[0][9], dObj.TranslationMatrix[0][13]);
							//printf("3X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][2], dObj.TranslationMatrix[0][6], dObj.TranslationMatrix[0][10], dObj.TranslationMatrix[0][14]);
							//printf("4X: %f Y: %f Z: %f W: %f\n", dObj.TranslationMatrix[0][3], dObj.TranslationMatrix[0][7], dObj.TranslationMatrix[0][11], dObj.TranslationMatrix[0][15]);


							//DIRECTIONAL LIGHT
							//char dirLight[255];strcpy(dirLight, "dirLight.direction");
							//glUniform3f(glGetUniformLocation(myShader, dirLight), modelX, modelY, modelZ);
							char tempDirLightDirection[255], tempDirLightAmbient[255], tempDirLightDiffuse[255], tempDirLightSpecular[255], tempArray[255];
							strcpy(tempDirLightDirection, dirLight);strcpy(tempDirLightAmbient, dirLight);strcpy(tempDirLightDiffuse, dirLight);strcpy(tempDirLightSpecular, dirLight);
							//
							strcpy(tempArray, "[");//strncat(tempArray, "[", 1);
							//
							int num = 123;
							char snum[100];
							//itoa(num, snum, 100);
							//snprintf(snum, 100, "%d", num);
							//printf("%s\n", snum);
							//
							snprintf(snum, 100, "%d", i);
							//printf("%s\n", snum);
							//
							strncat(tempArray, snum, 100);
							//
							strncat(tempArray, "]", 1);
							//
							//APPEND ARRAYS
							strncat(tempDirLightDirection, tempArray, strlen(tempArray));
							strncat(tempDirLightAmbient, tempArray, strlen(tempArray));
							strncat(tempDirLightDiffuse, tempArray, strlen(tempArray));
							strncat(tempDirLightSpecular, tempArray, strlen(tempArray));
							//APPEND dirLight
							strncat(tempDirLightDirection, matDirection, strlen(matDirection));
							strncat(tempDirLightAmbient, matAmbient, strlen(matAmbient));
							strncat(tempDirLightDiffuse, matDiffuse, strlen(matDiffuse));
							strncat(tempDirLightSpecular, matSpecular, strlen(matSpecular));
							//
							glUniform3f(glGetUniformLocation(myShader, tempDirLightDirection), dObj.TranslationMatrix[0][12], dObj.TranslationMatrix[0][13], dObj.TranslationMatrix[0][14]);
							//glUniform3f(glGetUniformLocation(myShader, "dirLight[0].direction"), dObj.TranslationMatrix[0][12], dObj.TranslationMatrix[0][13], dObj.TranslationMatrix[0][14]);
							//
							//glUniform3f(glGetUniformLocation(myShader, tempDirLightDirection), modelX, modelY, modelZ);//dObj.target.x, dObj.target.y, dObj.target.z);//eye.x, eye.y, eye.z);
							//glUniform3f(glGetUniformLocation(myShader, "dirLight.direction"), modelX, modelY, modelZ);//dObj.target.x, dObj.target.y, dObj.target.z);//eye.x, eye.y, eye.z);
							//glUniform3f(glGetUniformLocation(myShader, "dirLight.direction"), dObj.TranslationMatrix[0][12], dObj.TranslationMatrix[0][13], dObj.TranslationMatrix[0][14]);
							//
							//glUniform3f(glGetUniformLocation(myShader, "dirLight[0].ambient"), 0.1f, 0.1f, 0.1f);//0.05f, 0.05f, 0.05f);
							glUniform3f(glGetUniformLocation(myShader, tempDirLightAmbient), 0.1f, 0.1f, 0.1f);//0.05f, 0.05f, 0.05f);
							//glUniform3f(glGetUniformLocation(myShader, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);//0.05f, 0.05f, 0.05f);
							//
							//glUniform3f(glGetUniformLocation(myShader, "dirLight[0].diffuse"), 0.6f, 0.6f, 0.6f);
							glUniform3f(glGetUniformLocation(myShader, tempDirLightDiffuse), 0.6f, 0.6f, 0.6f);
							//glUniform3f(glGetUniformLocation(myShader, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
							//
							//glUniform3f(glGetUniformLocation(myShader, "dirLight[0].specular"), 0.7f, 0.7f, 0.7f);
							glUniform3f(glGetUniformLocation(myShader, tempDirLightSpecular), 0.7f, 0.7f, 0.7f);
							//glUniform3f(glGetUniformLocation(myShader, "dirLight.specular"), 0.7f, 0.7f, 0.7f);
							//
							//printf("A: %s\n", tempDirLightDirection);
							//printf("B: %s\n", tempDirLightAmbient);
							//printf("C: %s\n", tempDirLightDiffuse);
							//printf("D: %s\n", tempDirLightSpecular);
						//}
					}
				}
								
				for(int i = 0; i <= dObj.loadLightSpot; i++)//for(int i = 0; i < dObj.loadLightSpot; i++)
				{
					char tempSpotLightPosition[255], tempSpotLightDirection[255], tempSpotLightAmbient[255], tempSpotLightDiffuse[255], tempSpotLightSpecular[255], tempSpotLightConstant[255], tempSpotLightLinear[255], tempSpotLightQuadratic[255], tempSpotLightCutOff[255], tempSpotLightOuterCutOff[255], tempArray[255];
					//PREFIX
					strcpy(tempSpotLightPosition, spotLight);strcpy(tempSpotLightDirection, spotLight);strcpy(tempSpotLightAmbient, spotLight);strcpy(tempSpotLightDiffuse, spotLight);strcpy(tempSpotLightSpecular, spotLight);strcpy(tempSpotLightConstant, spotLight);strcpy(tempSpotLightLinear, spotLight);strcpy(tempSpotLightQuadratic, spotLight);strcpy(tempSpotLightCutOff, spotLight);strcpy(tempSpotLightOuterCutOff, spotLight);
					//ARRAY NUMBER
					strcpy(tempArray, "[");
					char snum[100];
					snprintf(snum, 100, "%d", i);
					strncat(tempArray, snum, 100);
					strncat(tempArray, "]", 1);


					if(dObj.vboNumber == dObj.loadLightSpotArray[i])
					{
						//APPEND ARRAY
						strncat(tempSpotLightPosition, tempArray, strlen(tempArray));
						strncat(tempSpotLightDirection, tempArray, strlen(tempArray));
						//
						strncat(tempSpotLightAmbient, tempArray, strlen(tempArray));
						strncat(tempSpotLightDiffuse, tempArray, strlen(tempArray));
						strncat(tempSpotLightSpecular, tempArray, strlen(tempArray));
						strncat(tempSpotLightConstant, tempArray, strlen(tempArray));
						strncat(tempSpotLightLinear, tempArray, strlen(tempArray));
						strncat(tempSpotLightQuadratic, tempArray, strlen(tempArray));
						//
						strncat(tempSpotLightCutOff, tempArray, strlen(tempArray));
						strncat(tempSpotLightOuterCutOff, tempArray, strlen(tempArray));
						//APPEND SUFFIX
						strncat(tempSpotLightPosition, matPosition, strlen(matPosition));
						strncat(tempSpotLightDirection, matDirection, strlen(matDirection));
						//
						strncat(tempSpotLightAmbient, matAmbient, strlen(matAmbient));
						strncat(tempSpotLightDiffuse, matDiffuse, strlen(matDiffuse));
						strncat(tempSpotLightSpecular, matSpecular, strlen(matSpecular));
						strncat(tempSpotLightConstant, matConstant, strlen(matConstant));
						strncat(tempSpotLightLinear, matLinear, strlen(matLinear));
						strncat(tempSpotLightQuadratic, matQuadratic, strlen(matQuadratic));
						//
						strncat(tempSpotLightCutOff, matCutOff, strlen(matCutOff));
						strncat(tempSpotLightOuterCutOff, matOuterCutOff, strlen(matOuterCutOff));
						
						//SPOT LIGHT
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightPosition), dObj.TranslationMatrix[0][12], dObj.TranslationMatrix[0][13], dObj.TranslationMatrix[0][14]);
						//glUniform3f(glGetUniformLocation(myShader, tempSpotLightDirection), dObj.target.x, dObj.target.y, dObj.target.z);
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightDirection), -5.0f, 0.0f, 0.0f);
						//
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightAmbient), 0.4f, 0.4f, 0.4f);
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightDiffuse), 0.6f, 0.6f, 0.6f);
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightSpecular), 0.7f, 0.7f, 0.7f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightConstant), 1.0f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightLinear), 0.09f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightQuadratic), 0.032f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightCutOff), glm::cos(glm::radians(12.5f)));
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightOuterCutOff), glm::cos(glm::radians(15.0f)));
					}
					if(i == dObj.loadLightSpot)//else if(i == dObj.loadLightSpot)
					{
						/*
						char tempSpotLightPosition[255], tempSpotLightDirection[255], tempSpotLightAmbient[255], tempSpotLightDiffuse[255], tempSpotLightSpecular[255], tempSpotLightConstant[255], tempSpotLightLinear[255], tempSpotLightQuadratic[255], tempSpotLightCutOff[255], tempSpotLightOuterCutOff[255], tempArray[255];
						//PREFIX
						strcpy(tempSpotLightPosition, spotLight);strcpy(tempSpotLightDirection, spotLight);strcpy(tempSpotLightAmbient, spotLight);strcpy(tempSpotLightDiffuse, spotLight);strcpy(tempSpotLightSpecular, spotLight);strcpy(tempSpotLightConstant, spotLight);strcpy(tempSpotLightLinear, spotLight);strcpy(tempSpotLightQuadratic, spotLight);strcpy(tempSpotLightCutOff, spotLight);strcpy(tempSpotLightOuterCutOff, spotLight);
						//ARRAY NUMBER
						strcpy(tempArray, "[");
						char snum[100];
						snprintf(snum, 100, "%d", i);
						strncat(tempArray, snum, 100);
						strncat(tempArray, "]", 1);

						//APPEND ARRAY
						strncat(tempSpotLightPosition, tempArray, strlen(tempArray));
						strncat(tempSpotLightDirection, tempArray, strlen(tempArray));
						//
						strncat(tempSpotLightAmbient, tempArray, strlen(tempArray));
						strncat(tempSpotLightDiffuse, tempArray, strlen(tempArray));
						strncat(tempSpotLightSpecular, tempArray, strlen(tempArray));
						strncat(tempSpotLightConstant, tempArray, strlen(tempArray));
						strncat(tempSpotLightLinear, tempArray, strlen(tempArray));
						strncat(tempSpotLightQuadratic, tempArray, strlen(tempArray));
						//
						strncat(tempSpotLightCutOff, tempArray, strlen(tempArray));
						strncat(tempSpotLightOuterCutOff, tempArray, strlen(tempArray));
						//APPEND SUFFIX
						strncat(tempSpotLightPosition, matPosition, strlen(matPosition));
						strncat(tempSpotLightDirection, matDirection, strlen(matDirection));
						//
						strncat(tempSpotLightAmbient, matAmbient, strlen(matAmbient));
						strncat(tempSpotLightDiffuse, matDiffuse, strlen(matDiffuse));
						strncat(tempSpotLightSpecular, matSpecular, strlen(matSpecular));
						strncat(tempSpotLightConstant, matConstant, strlen(matConstant));
						strncat(tempSpotLightLinear, matLinear, strlen(matLinear));
						strncat(tempSpotLightQuadratic, matQuadratic, strlen(matQuadratic));
						//
						strncat(tempSpotLightCutOff, matCutOff, strlen(matCutOff));
						strncat(tempSpotLightOuterCutOff, matOuterCutOff, strlen(matOuterCutOff));
						*/

						//SPOT LIGHT
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightPosition), eye.x, eye.y, eye.z);//modelX, modelY, modelZ);
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightDirection), dObj.target.x, dObj.target.y, dObj.target.z);
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightAmbient), 0.1f, 0.1f, 0.1f);
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightDiffuse), 1.0f, 1.0f, 1.0f);
						glUniform3f(glGetUniformLocation(myShader, tempSpotLightSpecular), 1.0f, 1.0f, 1.0f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightConstant), 1.0f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightLinear), 0.09f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightQuadratic), 0.032f);
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightCutOff), glm::cos(glm::radians(12.5f)));
						glUniform1f(glGetUniformLocation(myShader, tempSpotLightOuterCutOff), glm::cos(glm::radians(15.0f)));
						
						/*
						//SPOT LIGHT
						glUniform3f(glGetUniformLocation(myShader, "spotLight[1].position"), eye.x, eye.y, eye.z);//modelX, modelY, modelZ);
						glUniform3f(glGetUniformLocation(myShader, "spotLight[1].direction"), dObj.target.x, dObj.target.y, dObj.target.z);
						glUniform3f(glGetUniformLocation(myShader, "spotLight[1].ambient"), 0.1f, 0.1f, 0.1f);
						glUniform3f(glGetUniformLocation(myShader, "spotLight[1].diffuse"), 1.0f, 1.0f, 1.0f);
						glUniform3f(glGetUniformLocation(myShader, "spotLight[1].specular"), 1.0f, 1.0f, 1.0f);
						glUniform1f(glGetUniformLocation(myShader, "spotLight[1].constant"), 1.0f);
						glUniform1f(glGetUniformLocation(myShader, "spotLight[1].linear"), 0.09f);
						glUniform1f(glGetUniformLocation(myShader, "spotLight[1].quadratic"), 0.032f);
						glUniform1f(glGetUniformLocation(myShader, "spotLight[1].cutOff"), glm::cos(glm::radians(12.5f)));
						glUniform1f(glGetUniformLocation(myShader, "spotLight[1].outerCutOff"), glm::cos(glm::radians(15.0f)));
						*/
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//MATERIAL
				glUniform3f(glGetUniformLocation(myShader, "material.ambient"), 1.0f, 1.0f, 1.0f);
				glUniform3f(glGetUniformLocation(myShader, "material.diffuse"), 1.0f, 1.0f, 1.0f);
				glUniform3f(glGetUniformLocation(myShader, "material.specular"), 1.0f, 1.0f, 1.0f);
				glUniform1f(glGetUniformLocation(myShader, "material.shininess"), 32.0f);

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//dObj.diffuseID[vboID+ii]  = glGetUniformLocation(myShader, "DiffuseTextureSampler");
				//dObj.specularID[vboID+ii]  = glGetUniformLocation(myShader, "SpecularTextureSampler");
				dObj.normalID[vboID+ii]  = glGetUniformLocation(myShader, "NormalTextureSampler");

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				tempTime = (float)glfwGetTime();
				glUniform1f(glGetUniformLocation(myShader, "time"), tempTime);
				//TEST FOR EMISSION
				if(dObj.materialVBOStoredUV[vboID+ii] == 1)glUniform1i(glGetUniformLocation(myShader, "shaderEmission"), 1);
				else
				{
					glUniform1i(glGetUniformLocation(myShader, "shaderEmission"), 0);
				}
				//if(dObj.materialVBOStoredColor[vboID+ii] == 1)glUniform1i(glGetUniformLocation(myShader, "shaderFlow"), 2);
								
				//dObj.notDrawArray[vboID+ii] = 1;
				if(dObj.notDrawArray[vboID+ii] == 0)
				{
					//printf("test vboNum: %d vboOrderCount: %d\n", dObj.vboNumber, vboOrderCount);

					glActiveTexture(GL_TEXTURE0);//Bind our texture in Texture Unit 0
					glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*4+0]);//dTexture
					glUniform1i(dObj.diffuseID[vboID+ii], 0);//Set "myTextureSampler" sampler to use Texture Unit 0

					glActiveTexture(GL_TEXTURE1);//Bind our texture in Texture Unit 1
					glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*4+1]);//nTexture
					glUniform1i(dObj.normalID[vboID+ii], 1);//Set "myTextureSampler" sampler to use Texture Unit 1

					glActiveTexture(GL_TEXTURE2);//Bind our texture in Texture Unit 2
					glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*4+2]);//sTexture
					glUniform1i(dObj.specularID[vboID+ii], 2);//Set "myTextureSampler" sampler to use Texture Unit 2

					glActiveTexture(GL_TEXTURE3);//Bind our texture in Texture Unit 3
					glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*4+3]);//eTexture
					glUniform1i(dObj.emissionID[vboID+ii], 3);//Set "myTextureSampler" sampler to use Texture Unit 3

					//1st attribute buffer : vertices
					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, dObj.vertexbuffer[vboID+ii]);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
					//2nd attribute buffer : UVs
					glEnableVertexAttribArray(1);
					glBindBuffer(GL_ARRAY_BUFFER, dObj.uvbuffer[vboID+ii]);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
					//3rd attribute buffer : normals
					glEnableVertexAttribArray(2);
					glBindBuffer(GL_ARRAY_BUFFER, dObj.normalbuffer[vboID+ii]);
					glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
					//4th attribute buffer : color
					glEnableVertexAttribArray(3);
					glBindBuffer(GL_ARRAY_BUFFER, dObj.colorbuffer[vboID+ii]);
					glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
					//4th attribute buffer : tangents
					glEnableVertexAttribArray(4);
					glBindBuffer(GL_ARRAY_BUFFER, dObj.tangentbuffer[vboID+ii]);
					glVertexAttribPointer(
						4,                                // attribute
						3,                                // size
						GL_FLOAT,                         // type
						GL_FALSE,                         // normalized?
						0,                                // stride
						(void*)0                          // array buffer offset
						);
					// 5th attribute buffer : bitangents
					glEnableVertexAttribArray(5);
					glBindBuffer(GL_ARRAY_BUFFER, dObj.bitangentbuffer[vboID+ii]);
					glVertexAttribPointer(
						5,                                // attribute
						3,                                // size
						GL_FLOAT,                         // type
						GL_FALSE,                         // normalized?
						0,                                // stride
						(void*)0                          // array buffer offset
						);

					//Index buffer
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.elementbuffer[vboID+ii]);
					glDrawElements(GL_TRIANGLES, indices[vboID+ii].size(), GL_UNSIGNED_SHORT, (void*)0);
					glDisableVertexAttribArray(0);
					glDisableVertexAttribArray(1);
					glDisableVertexAttribArray(2);
					glDisableVertexAttribArray(3);
					glDisableVertexAttribArray(4);
					glDisableVertexAttribArray(5);
				}
				if(vboTRS > 0)
				{
					dObj.vboNumber = dObj.storedVboNumber;
				}
				dObj.vboNumber++;
				//printf("vboNumber: %d X: %f Y: %f Z: %f\n", dObj.vboNumber, daeRotEulerX[dObj.vboNumber], daeRotEulerY[dObj.vboNumber], daeRotEulerZ[dObj.vboNumber]);
				//printf("vboNumber: %d\n", dObj.vboNumber);
			}
			//printf("VBOloadedID1: %d\n", dObj.VBOloadedID);
			dObj.VBOloadedID++;
			//printf("VBOloadedID2: %d loadedID++ : %d vboNum: %d\n", vboID, dObj.VBOloadedID, dObj.vboNumber);//_getch();
		}
		//dObj.VBOloadedID++;
		//printf("TEST3ID: %d loadedID++ : %d\n", vboID, dObj.VBOloadedID);_getch();
	}
	//printf("END\n");
}

void deleteVBO(GLuint vboID)
{
	/*
	//glDeleteVertexArrays(1, &VertexArrayID[vboID]);
	//glDeleteBuffers(1, &vertexbuffer[vboID]);
	//glDeleteBuffers(1, &uvbuffer[vboID]);
	//glDeleteBuffers(1, &normalbuffer[vboID]);
	//glDeleteBuffers(1, &elementbuffer[vboID]);


	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(0), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(0), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(0), 0, GL_STATIC_DRAW);


	glBindTexture(GL_TEXTURE_2D, Texture[vboID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
	//allocate memory on the graphics card for the texture. It's fine if texture_data doesn't have any data in it, the texture will just appear black until you update it.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 0, GL_RGB, GL_UNSIGNED_BYTE, &Texture[vboID]);

	//glDeleteTextures(1, &Texture[vboID]);



	glDeleteVertexArrays(1, &VertexArrayID[vboID]);
	glDeleteBuffers(1, &vertexbuffer[vboID]);
	glDeleteBuffers(1, &uvbuffer[vboID]);
	glDeleteBuffers(1, &normalbuffer[vboID]);
	glDeleteBuffers(1, &elementbuffer[vboID]);


	glBindTexture(GL_TEXTURE_2D, Texture[vboID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//allocate memory on the graphics card for the texture. It's fine if
	//texture_data doesn't have any data in it, the texture will just appear black until you update it.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB,
	GL_UNSIGNED_BYTE, &Texture[vboID]);

	glDeleteTextures(1, &Texture[vboID]);



	glDeleteVertexArrays(vboID, &VertexArrayID[vboID]);
	glDeleteBuffers(vboID, &vertexbuffer[vboID]);
	glDeleteBuffers(vboID, &uvbuffer[vboID]);
	glDeleteBuffers(vboID, &normalbuffer[vboID]);
	glDeleteBuffers(vboID, &elementbuffer[vboID]);
	glDeleteTextures(vboID, &Texture[vboID]);


	//vectorvertices[0].clear(), vectoruvs[0].clear(), vectornormals[0].clear(), indices[0].clear(), indexed_vertices[0].clear(), indexed_uvs[0].clear(), indexed_normals[0].clear();
	//vectorvertices[1].clear(), vectoruvs[1].clear(), vectornormals[1].clear(), indices[1].clear(), indexed_vertices[1].clear(), indexed_uvs[1].clear(), indexed_normals[1].clear();
	//vectorvertices[vboID].clear(), vectoruvs[vboID].clear(), vectornormals[vboID].clear(), indices[vboID].clear(), indexed_vertices[vboID].clear(), indexed_uvs[vboID].clear(), indexed_normals[vboID].clear();
	*/
}

void deleteVBOall()
{
	glDeleteVertexArrays(1, dObj.VertexArrayID);
	glDeleteBuffers(1, dObj.vertexbuffer);
	glDeleteBuffers(1, dObj.uvbuffer);
	glDeleteBuffers(1, dObj.normalbuffer);
	glDeleteBuffers(1, dObj.elementbuffer);
	glDeleteTextures(1, dObj.Texture);
	glDeleteProgram(dObj.programID);
}
