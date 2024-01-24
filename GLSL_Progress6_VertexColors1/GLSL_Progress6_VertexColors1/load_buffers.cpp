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
std::vector<unsigned short> indices[90000], daeindices[90000];
std::vector<glm::vec3> indexed_vertices[90000];
std::vector<glm::vec3> indexed_uvs[90000];
std::vector<glm::vec3> indexed_normals[90000];
//std::vector<glm::vec3> indexed_colors[90000];
//////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<glm::vec3> vectorverticesLight[90000];
std::vector<glm::vec3> vectoruvsLight[90000];
std::vector<glm::vec3> vectornormalsLight[90000];
std::vector<glm::vec3> vectorcolorsLight[90000];
std::vector<unsigned short> indicesLight[90000], daeindicesLight[90000];
std::vector<glm::vec3> indexed_verticesLight[90000];
std::vector<glm::vec3> indexed_uvsLight[90000];
std::vector<glm::vec3> indexed_normalsLight[90000];
//std::vector<glm::vec3> indexed_colorsLight[90000];
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

int initalVBO;
int vboCount[90000];

int vboColorCount;
int vboColorArray[90000];

int vboOrderCount;
int vboOrderArray[90000];

int vboNumber;

float testX, testY, testZ;

void drawVBO(int vboID, GLint myShader, char*modelfile, char*texturefile)
{
	glCullFace(GL_BACK);
	//glUseProgram(programID);//BASIC SHADER
	glUseProgram(myShader);
	//materialShaderID
	//lightShaderID
	dObj.meshCount = 0;

	initalVBO = vboID;

	if(dObj.loadOnce[vboID] == 0)
	{
		//vectorvertices[vboID].clear(), vectoruvs[vboID].clear(), vectornormals[vboID].clear();
		//indices[vboID].clear();
		//indexed_vertices[vboID].clear(), indexed_uvs[vboID].clear(), indexed_normals[vboID].clear();

		//loadOBJ(modelfile, vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID]);
		//indexVBO(vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID], indices[vboID], indexed_vertices[vboID], indexed_uvs[vboID], indexed_normals[vboID]);

		loadmyDAE(modelfile, vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID], daeindices[vboID]);
		indexVBO(vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID],
			indices[vboID], indexed_vertices[vboID], indexed_uvs[vboID], indexed_normals[vboID]);

		//loadmyDAE(modelfile, vectorvertices[vboID+1], vectoruvs[vboID+1], vectornormals[vboID+1], daeindices[vboID+1]);
		//indexVBO(vectorvertices[vboID+1], vectoruvs[vboID+1], vectornormals[vboID+1],
		//indices[vboID+1], indexed_vertices[vboID+1], indexed_uvs[vboID+1], indexed_normals[vboID+1]);

		printf("vboID: %d xInput: %d xOutput: %d xInTangent: %d xOutTangent: %d\n", vboID, dObj.xInputCount, dObj.xOutputCount, dObj.xInTangentCount, dObj.xOutTangentCount);
		//for(int x1 = 0; x1 <= xInputCount;      x1++)printf("xInput: %f\n",      storedXInput[x1]);
		//for(int x2 = 0; x2 <= xOutputCount;     x2++)printf("xOutput: %f\n",     storedXOutput[x2]);
		//for(int x3 = 0; x3 <= xInTangentCount;  x3++)printf("xInTangent: %f\n",  storedXInTangent[x3]);
		//for(int x4 = 0; x4 <= xOutTangentCount; x4++)printf("xOutTangent: %f\n", storedXOutTangent[x4]);

		if(meshcolor == 1)
		{
			vboColorArray[vboColorCount] = vboID;
			printf("vboColorArray: %d\n", vboColorArray[vboColorCount]);
			//printf("COLOR FOUND: %d\n", vboColorCount);
			vboColorCount++;
			meshcolor = 0;
		}
		meshuv = 0;

		vboOrderArray[vboOrderCount] = vboID;
		printf("vboOrderCount: %d vboOrderArray: %d\n", vboOrderCount, vboOrderArray[vboOrderCount]);
		//vboOrderCount++;


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
		//printf("xIcount: %d vboNumber: %d\n", dObj.xInputCount, vboNumber);
		for(int aaa = 0; aaa < dObj.xInputCount; aaa++)
		{
			savedDoubleArray[vboNumber][aaa] = dObj.myXInterpolation[aaa];
			//printf("savedDoubleArray: %d\n", savedDoubleArray[vboNumber][aaa]);
		}
		//_getch();

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
		for(int i = 0; i <= dObj.xInputCount; i++)
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

				if(i == 0)
				{
					//printf("FIRSTLOOP: %d\n", i);
					//X POINTS
					p1[vboOrderCount][i] = dObj.myXOutput[i*2+0];
					p2[vboOrderCount][i] = dObj.myXOutput[i*2+1];
					pRot1[vboOrderCount][i] = dObj.myXRotEulerOutput[i*2+0];
					pRot2[vboOrderCount][i] = dObj.myXRotEulerOutput[i*2+1];
					pScale1[vboOrderCount][i] = dObj.myXScaleOutput[i*2+0];
					pScale2[vboOrderCount][i] = dObj.myXScaleOutput[i*2+1];
					//Y POINTS
					p3[vboOrderCount][i] = dObj.myYOutput[i*2+0];
					p4[vboOrderCount][i] = dObj.myYOutput[i*2+1];
					pRot3[vboOrderCount][i] = dObj.myYRotEulerOutput[i*2+0];
					pRot4[vboOrderCount][i] = dObj.myYRotEulerOutput[i*2+1];
					pScale3[vboOrderCount][i] = dObj.myYScaleOutput[i*2+0];
					pScale4[vboOrderCount][i] = dObj.myYScaleOutput[i*2+1];
					//Z POINTS
					p5[vboOrderCount][i] = dObj.myZOutput[i*2+0];
					p6[vboOrderCount][i] = dObj.myZOutput[i*2+1];
					pRot5[vboOrderCount][i] = dObj.myZRotEulerOutput[i*2+0];
					pRot6[vboOrderCount][i] = dObj.myZRotEulerOutput[i*2+1];
					pScale5[vboOrderCount][i] = dObj.myZScaleOutput[i*2+0];
					pScale6[vboOrderCount][i] = dObj.myZScaleOutput[i*2+1];
					//vec2 p1(0.0f,0.0f);//vec2 p2(8.0f,0.0f);
					//X TANGENT
					tangentOutX[vboOrderCount][i] = vec2(dObj.myXOutTangent[i*2+0], dObj.myXOutTangent[i*2+1]);
					tangentInX[vboOrderCount][i] = vec2(dObj.myXInTangent[i*2+0], dObj.myXInTangent[i*2+1]);
					tangentOutXRot[vboOrderCount][i] = vec2(dObj.myXRotEulerOutTangent[i*2+0], dObj.myXRotEulerOutTangent[i*2+1]);
					tangentInXRot[vboOrderCount][i] = vec2(dObj.myXRotEulerInTangent[i*2+0], dObj.myXRotEulerInTangent[i*2+1]);
					tangentOutXScale[vboOrderCount][i] = vec2(dObj.myXScaleOutTangent[i*2+0], dObj.myXScaleOutTangent[i*2+1]);
					tangentInXScale[vboOrderCount][i] = vec2(dObj.myXScaleInTangent[i*2+0], dObj.myXScaleInTangent[i*2+1]);
					//Y TANGENT
					tangentOutY[vboOrderCount][i] = vec2(dObj.myYOutTangent[i*2+0], dObj.myYOutTangent[i*2+1]);
					tangentInY[vboOrderCount][i] = vec2(dObj.myYInTangent[i*2+0], dObj.myYInTangent[i*2+1]);
					tangentOutYRot[vboOrderCount][i] = vec2(dObj.myYRotEulerOutTangent[i*2+0], dObj.myYRotEulerOutTangent[i*2+1]);
					tangentInYRot[vboOrderCount][i] = vec2(dObj.myYRotEulerInTangent[i*2+0], dObj.myYRotEulerInTangent[i*2+1]);
					tangentOutYScale[vboOrderCount][i] = vec2(dObj.myYScaleOutTangent[i*2+0], dObj.myYScaleOutTangent[i*2+1]);
					tangentInYScale[vboOrderCount][i] = vec2(dObj.myYScaleInTangent[i*2+0], dObj.myYScaleInTangent[i*2+1]);
					//Z TANGENT
					tangentOutZ[vboOrderCount][i] = vec2(dObj.myZOutTangent[i*2+0], dObj.myZOutTangent[i*2+1]);
					tangentInZ[vboOrderCount][i] = vec2(dObj.myZInTangent[i*2+0], dObj.myZInTangent[i*2+1]);
					tangentOutZRot[vboOrderCount][i] = vec2(dObj.myZRotEulerOutTangent[i*2+0], dObj.myZRotEulerOutTangent[i*2+1]);
					tangentInZRot[vboOrderCount][i] = vec2(dObj.myZRotEulerInTangent[i*2+0], dObj.myZRotEulerInTangent[i*2+1]);
					tangentOutZScale[vboOrderCount][i] = vec2(dObj.myZScaleOutTangent[i*2+0], dObj.myZScaleOutTangent[i*2+1]);
					tangentInZScale[vboOrderCount][i] = vec2(dObj.myZScaleInTangent[i*2+0], dObj.myZScaleInTangent[i*2+1]);
					//printf("TEST1: %d TEST2: %d\n", vboOrderArray[vboOrderCount], vboOrderCount);
				}
				else if(i == dObj.xInputCount)//LAST ONE
				{
					//printf("LASTLOOP: %d\n", i);
					//X POINTS
					p1[vboOrderCount][i] = dObj.myXOutput[i+0];//p1[i] = myXOutput[i*2-1];
					p2[vboOrderCount][i] = dObj.myXOutput[i+0];//p2[i] = myXOutput[i*2+0];
					pRot1[vboOrderCount][i] = dObj.myXRotEulerOutput[i+0];
					pRot2[vboOrderCount][i] = dObj.myXRotEulerOutput[i+0];
					pScale1[vboOrderCount][i] = dObj.myXScaleOutput[i+0];
					pScale2[vboOrderCount][i] = dObj.myXScaleOutput[i+0];
					//Y POINTS
					p3[vboOrderCount][i] = dObj.myYOutput[i+0];//p3[i] = myYOutput[i*2-1];
					p4[vboOrderCount][i] = dObj.myYOutput[i+0];//p4[i] = myYOutput[i*2+0];
					pRot3[vboOrderCount][i] = dObj.myYRotEulerOutput[i+0];
					pRot4[vboOrderCount][i] = dObj.myYRotEulerOutput[i+0];
					pScale3[vboOrderCount][i] = dObj.myYScaleOutput[i+0];
					pScale4[vboOrderCount][i] = dObj.myYScaleOutput[i+0];
					//Z POINTS
					p5[vboOrderCount][i] = dObj.myZOutput[i+0];//p5[i] = myZOutput[i*2-1];
					p6[vboOrderCount][i] = dObj.myZOutput[i+0];//p6[i] = myZOutput[i*2+0];
					pRot5[vboOrderCount][i] = dObj.myZRotEulerOutput[i+0];
					pRot6[vboOrderCount][i] = dObj.myZRotEulerOutput[i+0];
					pScale5[vboOrderCount][i] = dObj.myZScaleOutput[i+0];
					pScale6[vboOrderCount][i] = dObj.myZScaleOutput[i+0];
					//X TANGENT
					tangentOutX[vboOrderCount][i] = vec2(dObj.myXOutTangent[i*2-1], dObj.myXOutTangent[i*2+0]);
					tangentInX[vboOrderCount][i] = vec2(dObj.myXInTangent[i*2-1], dObj.myXInTangent[i*2+0]);
					tangentOutXRot[vboOrderCount][i] = vec2(dObj.myXRotEulerOutTangent[i*2-1], dObj.myXRotEulerOutTangent[i*2+0]);
					tangentInXRot[vboOrderCount][i] = vec2(dObj.myXRotEulerInTangent[i*2-1], dObj.myXRotEulerInTangent[i*2+0]);
					tangentOutXScale[vboOrderCount][i] = vec2(dObj.myXScaleOutTangent[i*2-1], dObj.myXScaleOutTangent[i*2+0]);
					tangentInXScale[vboOrderCount][i] = vec2(dObj.myXScaleInTangent[i*2-1], dObj.myXScaleInTangent[i*2+0]);
					//Y TANGENT
					tangentOutY[vboOrderCount][i] = vec2(dObj.myYOutTangent[i*2-1], dObj.myYOutTangent[i*2+0]);
					tangentInY[vboOrderCount][i] = vec2(dObj.myYInTangent[i*2-1], dObj.myYInTangent[i*2+0]);
					tangentOutYRot[vboOrderCount][i] = vec2(dObj.myYRotEulerOutTangent[i*2-1], dObj.myYRotEulerOutTangent[i*2+0]);
					tangentInYRot[vboOrderCount][i] = vec2(dObj.myYRotEulerInTangent[i*2-1], dObj.myYRotEulerInTangent[i*2+0]);
					tangentOutYScale[vboOrderCount][i] = vec2(dObj.myYScaleOutTangent[i*2-1], dObj.myYScaleOutTangent[i*2+0]);
					tangentInYScale[vboOrderCount][i] = vec2(dObj.myYScaleInTangent[i*2-1], dObj.myYScaleInTangent[i*2+0]);
					//Z TANGENT
					tangentOutZ[vboOrderCount][i] = vec2(dObj.myZOutTangent[i*2-1], dObj.myZOutTangent[i*2+0]);
					tangentInZ[vboOrderCount][i] = vec2(dObj.myZInTangent[i*2-1], dObj.myZInTangent[i*2+0]);
					tangentOutZRot[vboOrderCount][i] = vec2(dObj.myZRotEulerOutTangent[i*2-1], dObj.myZRotEulerOutTangent[i*2+0]);
					tangentInZRot[vboOrderCount][i] = vec2(dObj.myZRotEulerInTangent[i*2-1], dObj.myZRotEulerInTangent[i*2+0]);
					tangentOutZScale[vboOrderCount][i] = vec2(dObj.myZScaleOutTangent[i*2-1], dObj.myZScaleOutTangent[i*2+0]);
					tangentInZScale[vboOrderCount][i] = vec2(dObj.myZScaleInTangent[i*2-1], dObj.myZScaleInTangent[i*2+0]);
				}
				else
				{
					//X POINTS
					p1[vboOrderCount][i] = dObj.myXOutput[i+0];//p1[i] = myXOutput[i*2-1];
					p2[vboOrderCount][i] = dObj.myXOutput[i+1];//p2[i] = myXOutput[i*2+0];
					pRot1[vboOrderCount][i] = dObj.myXRotEulerOutput[i+0];
					pRot2[vboOrderCount][i] = dObj.myXRotEulerOutput[i+1];
					pScale1[vboOrderCount][i] = dObj.myXScaleOutput[i+0];
					pScale2[vboOrderCount][i] = dObj.myXScaleOutput[i+1];
					//Y POINTS
					p3[vboOrderCount][i] = dObj.myYOutput[i+0];//p3[i] = myYOutput[i*2-1];
					p4[vboOrderCount][i] = dObj.myYOutput[i+1];//p4[i] = myYOutput[i*2+0];
					pRot3[vboOrderCount][i] = dObj.myYRotEulerOutput[i+0];
					pRot4[vboOrderCount][i] = dObj.myYRotEulerOutput[i+1];
					pScale3[vboOrderCount][i] = dObj.myYScaleOutput[i+0];
					pScale4[vboOrderCount][i] = dObj.myYScaleOutput[i+1];
					//Z POINTS
					p5[vboOrderCount][i] = dObj.myZOutput[i+0];//p5[i] = myZOutput[i*2-1];
					p6[vboOrderCount][i] = dObj.myZOutput[i+1];//p6[i] = myZOutput[i*2+0];
					pRot5[vboOrderCount][i] = dObj.myZRotEulerOutput[i+0];
					pRot6[vboOrderCount][i] = dObj.myZRotEulerOutput[i+1];
					pScale5[vboOrderCount][i] = dObj.myZScaleOutput[i+0];
					pScale6[vboOrderCount][i] = dObj.myZScaleOutput[i+1];
					//X TANGENT
					tangentOutX[vboOrderCount][i] = vec2(dObj.myXOutTangent[i*2-1], dObj.myXOutTangent[i*2+0]);
					tangentInX[vboOrderCount][i] = vec2(dObj.myXInTangent[i*2-1], dObj.myXInTangent[i*2+0]);
					tangentOutXRot[vboOrderCount][i] = vec2(dObj.myXRotEulerOutTangent[i*2-1], dObj.myXRotEulerOutTangent[i*2+0]);
					tangentInXRot[vboOrderCount][i] = vec2(dObj.myXRotEulerInTangent[i*2-1], dObj.myXRotEulerInTangent[i*2+0]);
					tangentOutXScale[vboOrderCount][i] = vec2(dObj.myXScaleOutTangent[i*2-1], dObj.myXScaleOutTangent[i*2+0]);
					tangentInXScale[vboOrderCount][i] = vec2(dObj.myXScaleInTangent[i*2-1], dObj.myXScaleInTangent[i*2+0]);
					//Y TANGENT
					tangentOutY[vboOrderCount][i] = vec2(dObj.myYOutTangent[i*2-1], dObj.myYOutTangent[i*2+0]);
					tangentInY[vboOrderCount][i] = vec2(dObj.myYInTangent[i*2-1], dObj.myYInTangent[i*2+0]);
					tangentOutYRot[vboOrderCount][i] = vec2(dObj.myYRotEulerOutTangent[i*2-1], dObj.myYRotEulerOutTangent[i*2+0]);
					tangentInYRot[vboOrderCount][i] = vec2(dObj.myYRotEulerInTangent[i*2-1], dObj.myYRotEulerInTangent[i*2+0]);
					tangentOutYScale[vboOrderCount][i] = vec2(dObj.myYScaleOutTangent[i*2-1], dObj.myYScaleOutTangent[i*2+0]);
					tangentInYScale[vboOrderCount][i] = vec2(dObj.myYScaleInTangent[i*2-1], dObj.myYScaleInTangent[i*2+0]);
					//Z TANGENT
					tangentOutZ[vboOrderCount][i] = vec2(dObj.myZOutTangent[i*2-1], dObj.myZOutTangent[i*2+0]);
					tangentInZ[vboOrderCount][i] = vec2(dObj.myZInTangent[i*2-1], dObj.myZInTangent[i*2+0]);
					tangentOutZRot[vboOrderCount][i] = vec2(dObj.myZRotEulerOutTangent[i*2-1], dObj.myZRotEulerOutTangent[i*2+0]);
					tangentInZRot[vboOrderCount][i] = vec2(dObj.myZRotEulerInTangent[i*2-1], dObj.myZRotEulerInTangent[i*2+0]);
					tangentOutZScale[vboOrderCount][i] = vec2(dObj.myZScaleOutTangent[i*2-1], dObj.myZScaleOutTangent[i*2+0]);
					tangentInZScale[vboOrderCount][i] = vec2(dObj.myZScaleInTangent[i*2-1], dObj.myZScaleInTangent[i*2+0]);
				}

				vec2 pX, pY, pZ,
					pRotX, pRotY, pRotZ,
					pScaleX, pScaleY, pScaleZ;

				/////////////////////////////////////////////////////////////////////////////

				pX = vec2(h1*p1[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*p2[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutX[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInX[vboOrderCount][i]);
				pVec3Pos[vboOrderCount][i].x = pX.x;//p1[i] = pX.x;

				pY = vec2(h1*p3[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*p4[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutY[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInY[vboOrderCount][i]);
				pVec3Pos[vboOrderCount][i].y = pY.x;//p3[i] = pY.x;

				pZ = vec2(h1*p5[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*p6[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutZ[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInZ[vboOrderCount][i]);
				pVec3Pos[vboOrderCount][i].z = pZ.x;//p5[i] = pZ.x;
				//printf("pVec3 i: %d X: %f Y: %f Z: %f\n", i, pVec3Pos[i].x, pVec3Pos[i].y, pVec3Pos[i].z);

				/////////////////////////////////////////////////////////////////////////////

				pRotX = vec2(h1*pRot1[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*pRot2[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutXRot[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInXRot[vboOrderCount][i]);
				pVec3Rot[vboOrderCount][i].x = pRotX.x;//pRot1[i] = pRotX.x;

				pRotY = vec2(h1*pRot3[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*pRot4[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutYRot[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInYRot[vboOrderCount][i]);
				pVec3Rot[vboOrderCount][i].y = pRotY.x;//pRot3[i] = pRotY.x;

				pRotZ = vec2(h1*pRot5[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*pRot6[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutZRot[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInZRot[vboOrderCount][i]);
				pVec3Rot[vboOrderCount][i].z = pRotZ.x;//pRot5[i] = pRotZ.x;

				/////////////////////////////////////////////////////////////////////////////

				pScaleX = vec2(h1*pScale1[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*pScale2[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutXScale[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInXScale[vboOrderCount][i]);
				pVec3Scale[vboOrderCount][i].x = pScaleX.x;//pScale1[i] = pScaleX.x;

				pScaleY = vec2(h1*pScale3[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*pScale4[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutYScale[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInYScale[vboOrderCount][i]);
				pVec3Scale[vboOrderCount][i].y = pScaleY.x;//pScale3[i] = pScaleY.x;

				pScaleZ = vec2(h1*pScale5[vboOrderCount][i]) +                    // multiply and sum all funtions
					vec2(h2*pScale6[vboOrderCount][i]) +                    // together to build the interpolated
					vec2(h3*tangentOutZScale[vboOrderCount][i]) +                    // point along the curve.
					vec2(h4*tangentInZScale[vboOrderCount][i]);
				pVec3Scale[vboOrderCount][i].z = pScaleZ.x;//pScale5[i] = pScaleZ.x;
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
				trsSwapArray[vboOrderCount] = i;
				//printf("vboOcount: %d i: %d trsSwap: %d\n", vboOrderCount, i, trsSwapArray[vboOrderCount]);
			}
		}


		for(int i = 0; i < dObj.meshCount; i++)
		{
			printf("MESHCOUNT: %d i: %d\n", dObj.meshCount, i);
			//loadmyDAE(modelfile, vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i], daeindices[vboID+i]);
			//indexVBO(vectorvertices[vboID+i], vectoruvs[vboID+i], vectornormals[vboID+i],
			//indices[vboID+i], indexed_vertices[vboID+i], indexed_uvs[vboID+i], indexed_normals[vboID+i]);
			
			//Load the texture
			//Texture[vboID] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
			//Texture[0] = loadPngImage(DAEtexture, imgwidth, imgheight, hasAlpha, &textureImage);

			//Texture[vboID*3+0] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
			dObj.Texture[(vboID+i)*3+0] = loadPngImage("container2.png",          imgwidth, imgheight, hasAlpha, &textureImage);
			dObj.Texture[(vboID+i)*3+1] = loadPngImage("container2_specular.png", imgwidth, imgheight, hasAlpha, &textureImage);
			dObj.Texture[(vboID+i)*3+2] = loadPngImage("matrix.png",              imgwidth, imgheight, hasAlpha, &textureImage);
			printf("vboCHECK: %d, i: %d RESULT: %d\n", vboID, i, (vboID+i)*3+0);
			
			//Texture[vboID] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
			//delete textureImage;//REFRESH GENTEXTURES

			//loadBMP_custom("test.bmp");
			//LoadBMP("test.bmp");
			//loadDDS("uvmap.DDS");
			//Get a handle for our "myTextureSampler" uniform
			//diffuseID[0] = glGetUniformLocation(programID, "myTexture");
			//diffuseID[vboID] = glGetUniformLocation(programID, "myTexture");
			dObj.diffuseID[vboID+i] = glGetUniformLocation(myShader, "material.diffuse");//DIFFUSE(TEXTURE) MAP
			dObj.specularID[vboID+i] = glGetUniformLocation(myShader, "material.specular");//SPECULAR MAP
			dObj.emissionID[vboID+i] = glGetUniformLocation(myShader, "material.emission");//EMISSION MAP


			glGenVertexArrays(1, &dObj.VertexArrayID[vboID+i]);
			glGenBuffers(1, &dObj.vertexbuffer[vboID+i]);
			glGenBuffers(1, &dObj.uvbuffer[vboID+i]);
			glGenBuffers(1, &dObj.normalbuffer[vboID+i]);
			glGenBuffers(1, &dObj.colorbuffer[vboID+i]);
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
			//INDICEBUFFERS
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.elementbuffer[vboID+i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[vboID+i].size() * sizeof(unsigned short), &indices[vboID+i][0], GL_STATIC_DRAW);
			printf("INDSIZE: %d\n", indices[vboID+i].size() * sizeof(unsigned short));
			dObj.loadOnce[vboID+i] = 1;
		}
		vboCount[vboID] = dObj.meshCount;
		printf("vboCount: %d\n", vboCount[vboID]);
		//printf("vboOrderCount: %d\n", vboOrderCount);
		vboOrderCount++;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//rotSwap = 0;
	if(vboNumber >= vboOrderCount)vboNumber = 0;

	for(int ii = 0; ii < vboCount[initalVBO]; ii++)
	{
		//printf("II loop: %d\n", ii);
		if(dObj.drawDisable[vboID+ii] == 0)
		{
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
			//for(int i = vboNumber; i <= vboOrderCount; i++)
			if(vboNumber < vboOrderCount)
			{
				//printf("START1 ");
				//printf("iLoop: %d vboOrderCount: %d\n", vboNumber, vboOrderCount);
				if(vboOrderArray[vboNumber] == vboID)
				{
					//printf("2 ");printf("vboID: %d i: %d testTime: %f vboOrderCount: %d\n", vboID, i, testTime[i], vboOrderCount);
					//printf("trsSwapArray: %d vboNumber: %d\n", trsSwapArray[vboNumber], vboNumber);
					//printf("testTime: %f\n", testTime[vboNumber]);
					//(testTime[vboNumber] <= 1.0f && trsSwapArray[vboNumber] >= 0)
					if(testTime[vboNumber] < 1.0f && trsSwapArray[vboNumber] > 0)
					{
						//if(dObj.myXInterpolation[playLoop[vboNumber]] == 2)//0 AS CUBIC, 1 AS LINEAR, 2 AS STEP (CONSTANT)
						if(savedDoubleArray[vboNumber][playLoop[vboNumber]] == 2)//0 AS CUBIC, 1 AS LINEAR, 2 AS STEP (CONSTANT)
						{
							if(testTime[vboNumber] < 1.0f)
							{
								//LOC
								daeLocX = ((1.0f - 0) * p1[vboNumber][playLoop[vboNumber]] + (0 * p2[vboNumber][playLoop[vboNumber]]));
								daeLocY = ((1.0f - 0) * p3[vboNumber][playLoop[vboNumber]] + (0 * p4[vboNumber][playLoop[vboNumber]]));
								daeLocZ = ((1.0f - 0) * p5[vboNumber][playLoop[vboNumber]] + (0 * p6[vboNumber][playLoop[vboNumber]]));
								//printf("t: %f daeLocX: %f\n", testTime, daeLocX);
								//ROT
								daeRotEulerX = ((1.0f - 0) * pRot1[vboNumber][playLoop[vboNumber]] + (0 * pRot2[vboNumber][playLoop[vboNumber]]));
								daeRotEulerY = ((1.0f - 0) * pRot3[vboNumber][playLoop[vboNumber]] + (0 * pRot4[vboNumber][playLoop[vboNumber]]));
								daeRotEulerZ = ((1.0f - 0) * pRot5[vboNumber][playLoop[vboNumber]] + (0 * pRot6[vboNumber][playLoop[vboNumber]]));
								//printf("daeRot X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);
								//SCALE
								daeScaleX = ((1.0f - 0) * pScale1[vboNumber][playLoop[vboNumber]] + (0 * pScale2[vboNumber][playLoop[vboNumber]]));
								daeScaleY = ((1.0f - 0) * pScale3[vboNumber][playLoop[vboNumber]] + (0 * pScale4[vboNumber][playLoop[vboNumber]]));
								daeScaleZ = ((1.0f - 0) * pScale5[vboNumber][playLoop[vboNumber]] + (0 * pScale6[vboNumber][playLoop[vboNumber]]));
								//printf("1t: %f daeScale X: %f Y: %f Z: %f\n", testTime, daeScaleX, daeScaleY, daeScaleZ);
							}
							else
							{
								//LOC
								daeLocX = ((1.0f - testTime[vboNumber]) * p1[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * p2[vboNumber][playLoop[vboNumber]]));
								daeLocY = ((1.0f - testTime[vboNumber]) * p3[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * p4[vboNumber][playLoop[vboNumber]]));
								daeLocZ = ((1.0f - testTime[vboNumber]) * p5[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * p6[vboNumber][playLoop[vboNumber]]));
								//printf("t: %f daeLocX: %f\n", testTime, daeLocX);
								//ROT
								daeRotEulerX = ((1.0f - testTime[vboNumber]) * pRot1[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pRot2[vboNumber][playLoop[vboNumber]]));
								daeRotEulerY = ((1.0f - testTime[vboNumber]) * pRot3[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pRot4[vboNumber][playLoop[vboNumber]]));
								daeRotEulerZ = ((1.0f - testTime[vboNumber]) * pRot5[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pRot6[vboNumber][playLoop[vboNumber]]));
								//printf("daeRot X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);
								//SCALE
								daeScaleX = ((1.0f - testTime[vboNumber]) * pScale1[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pScale2[vboNumber][playLoop[vboNumber]]));
								daeScaleY = ((1.0f - testTime[vboNumber]) * pScale3[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pScale4[vboNumber][playLoop[vboNumber]]));
								daeScaleZ = ((1.0f - testTime[vboNumber]) * pScale5[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pScale6[vboNumber][playLoop[vboNumber]]));
								//printf("2t: %f daeScale X: %f Y: %f Z: %f\n", testTime, daeScaleX, daeScaleY, daeScaleZ);
							}
							//printf("playLoop: %d testTime: %f\n", playLoop, testTime);
							//printf("DAE STEP CONSTANT\n");

							dObj.TranslationMatrix = glm::mat4(1.0f);
							dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

							dObj.RotationMatrixArray[vboNumber] = glm::mat4(1.0f);
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

							dObj.ScalingMatrix = glm::mat4(1.0f);
							dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
							//printf("STEP\n");
						}
						//else if(dObj.myXInterpolation[playLoop[vboNumber]] == 1)//LINEAR
						else if(savedDoubleArray[vboNumber][playLoop[vboNumber]] == 1)//LINEAR
						{
							//printf("1\n");
							//LOC
							daeLocX = ((1.0f - testTime[vboNumber]) * p1[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * p2[vboNumber][playLoop[vboNumber]]));
							daeLocY = ((1.0f - testTime[vboNumber]) * p3[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * p4[vboNumber][playLoop[vboNumber]]));
							daeLocZ = ((1.0f - testTime[vboNumber]) * p5[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * p6[vboNumber][playLoop[vboNumber]]));
							//printf("t: %f daeLocX: %f\n", testTime, daeLocX);
							//ROT
							daeRotEulerX = ((1.0f - testTime[vboNumber]) * pRot1[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pRot2[vboNumber][playLoop[vboNumber]]));
							daeRotEulerY = ((1.0f - testTime[vboNumber]) * pRot3[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pRot4[vboNumber][playLoop[vboNumber]]));
							daeRotEulerZ = ((1.0f - testTime[vboNumber]) * pRot5[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pRot6[vboNumber][playLoop[vboNumber]]));
							//printf("daeRot X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);
							//SCALE
							daeScaleX = ((1.0f - testTime[vboNumber]) * pScale1[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pScale2[vboNumber][playLoop[vboNumber]]));
							daeScaleY = ((1.0f - testTime[vboNumber]) * pScale3[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pScale4[vboNumber][playLoop[vboNumber]]));
							daeScaleZ = ((1.0f - testTime[vboNumber]) * pScale5[vboNumber][playLoop[vboNumber]] + (testTime[vboNumber] * pScale6[vboNumber][playLoop[vboNumber]]));
							//printf("t: %f daeScale X: %f Y: %f Z: %f\n", testTime, daeScaleX, daeScaleY, daeScaleZ);


							dObj.TranslationMatrix = glm::mat4(1.0f);
							dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

							dObj.RotationMatrixArray[vboNumber] = glm::mat4(1.0f);
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

							dObj.ScalingMatrix = glm::mat4(1.0f);
							dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
							//printf("DAE LINEAR\n");
						}
						//if(dObj.myXInterpolation[playLoop[vboNumber]] == 0)//CUBIC SPLINE
						if(savedDoubleArray[vboNumber][playLoop[vboNumber]] == 0)//CUBIC SPLINE
						{
							//printf("0\n");
							vec3 previousTangent, nextTangent;
							previousTangent = deltaTime * vec3(tangentOutX[vboNumber][playLoop[vboNumber]].x, 
								tangentOutY[vboNumber][playLoop[vboNumber]].x, 
								tangentOutZ[vboNumber][playLoop[vboNumber]].x);
							nextTangent = deltaTime * vec3(tangentInX[vboNumber][playLoop[vboNumber]].x, 
								tangentInY[vboNumber][playLoop[vboNumber]].x, 
								tangentInZ[vboNumber][playLoop[vboNumber]].x);
							//printf("Tangent PREV X: %f Y: %f\n", previousTangent.x, previousTangent.y);
							//printf("Tangent NEXT X: %f Y: %f\n", nextTangent.x, nextTangent.y);

							vec3 tempVec3Pos, tempVec3Rot, tempVec3Scale;
							tempVec3Pos = vec3(p1[vboNumber][playLoop[vboNumber]], p3[vboNumber][playLoop[vboNumber]], p5[vboNumber][playLoop[vboNumber]]) * 
								((1.0f + 2.0f * testTime[vboNumber]) * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
								previousTangent * (testTime[vboNumber] * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
								vec3(p2[vboNumber][playLoop[vboNumber]], p4[vboNumber][playLoop[vboNumber]], p6[vboNumber][playLoop[vboNumber]]) * 
								((testTime[vboNumber] * testTime[vboNumber]) * (3.0f - 2.0f * testTime[vboNumber])) +
								nextTangent * ((testTime[vboNumber] * testTime[vboNumber]) * (testTime[vboNumber] - 1.0f));

							daeLocX = tempVec3Pos.x;
							daeLocY = tempVec3Pos.y;
							daeLocZ = tempVec3Pos.z;
							//printf("v3Pos X: %f Y: %f Z: %f\n", tempVec3Pos.x, tempVec3Pos.y, tempVec3Pos.z);
							//daeLocX = pVec3Pos[i][loopTest[i]].x;
							//daeLocY = pVec3Pos[i][loopTest[i]].y;
							//daeLocZ = pVec3Pos[i][loopTest[i]].z;

							//ROT
							previousTangent = deltaTime * vec3(tangentOutXRot[vboNumber][playLoop[vboNumber]].x, 
								tangentOutYRot[vboNumber][playLoop[vboNumber]].x, 
								tangentOutZRot[vboNumber][playLoop[vboNumber]].x);
							nextTangent = deltaTime * vec3(tangentInXRot[vboNumber][playLoop[vboNumber]].x, 
								tangentInYRot[vboNumber][playLoop[vboNumber]].x, 
								tangentInZRot[vboNumber][playLoop[vboNumber]].x);

							tempVec3Rot = vec3(pRot1[vboNumber][playLoop[vboNumber]], pRot3[vboNumber][playLoop[vboNumber]], pRot5[vboNumber][playLoop[vboNumber]]) * 
								((1.0f + 2.0f * testTime[vboNumber]) * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
								previousTangent * (testTime[vboNumber] * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
								vec3(pRot2[vboNumber][playLoop[vboNumber]], pRot4[vboNumber][playLoop[vboNumber]], pRot6[vboNumber][playLoop[vboNumber]]) * 
								((testTime[vboNumber] * testTime[vboNumber]) * (3.0f - 2.0f * testTime[vboNumber])) +
								nextTangent * ((testTime[vboNumber] * testTime[vboNumber]) * (testTime[vboNumber] - 1.0f));


							daeRotEulerX = tempVec3Rot.x;
							daeRotEulerY = tempVec3Rot.y;
							daeRotEulerZ = tempVec3Rot.z;
							//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX[vboNumber], daeRotEulerY[vboNumber], daeRotEulerZ[vboNumber], vboNumber);
							//daeRotEulerX = pVec3Rot[vboNumber][loopTest[vboNumber]].x;
							//daeRotEulerY = pVec3Rot[vboNumber][loopTest[vboNumber]].y;
							//daeRotEulerZ = pVec3Rot[vboNumber][loopTest[vboNumber]].z;
							//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, i);


							//SCALE
							previousTangent = deltaTime * vec3(tangentOutXScale[vboNumber][playLoop[vboNumber]].x, 
								tangentOutYScale[vboNumber][playLoop[vboNumber]].x, 
								tangentOutZScale[vboNumber][playLoop[vboNumber]].x);
							nextTangent = deltaTime * vec3(tangentInXScale[vboNumber][playLoop[vboNumber]].x, 
								tangentInYScale[vboNumber][playLoop[vboNumber]].x, 
								tangentInZScale[vboNumber][playLoop[vboNumber]].x);

							tempVec3Scale = vec3(pScale1[vboNumber][playLoop[vboNumber]], pScale3[vboNumber][playLoop[vboNumber]], pScale5[vboNumber][playLoop[vboNumber]]) * 
								((1.0f + 2.0f * testTime[vboNumber]) * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
								previousTangent * (testTime[vboNumber] * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
								vec3(pScale2[vboNumber][playLoop[vboNumber]], pScale4[vboNumber][playLoop[vboNumber]], pScale6[vboNumber][playLoop[vboNumber]]) * 
								((testTime[vboNumber] * testTime[vboNumber]) * (3.0f - 2.0f * testTime[vboNumber])) +
								nextTangent * ((testTime[vboNumber] * testTime[vboNumber]) * (testTime[vboNumber] - 1.0f));

							daeScaleX = tempVec3Scale.x;
							daeScaleY = tempVec3Scale.y;
							daeScaleZ = tempVec3Scale.z;
							//printf("playLoop: %d daeScale X: %f Y: %f Z: %f\n", playLoop[i], daeScaleX, daeScaleY, daeScaleZ);//_getch();

							dObj.TranslationMatrix = glm::mat4(1.0f);
							dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

							dObj.RotationMatrixArray[vboNumber] = glm::mat4(1.0f);
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
							dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

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
						vec3 previousTangent, nextTangent;
						previousTangent = deltaTime * vec3(tangentOutX[vboNumber][playLoop[vboNumber]].x, 
							tangentOutY[vboNumber][playLoop[vboNumber]].x, 
							tangentOutZ[vboNumber][playLoop[vboNumber]].x);
						nextTangent = deltaTime * vec3(tangentInX[vboNumber][playLoop[vboNumber]].x, 
							tangentInY[vboNumber][playLoop[vboNumber]].x, 
							tangentInZ[vboNumber][playLoop[vboNumber]].x);
						//printf("Tangent PREV X: %f Y: %f\n", previousTangent.x, previousTangent.y);
						//printf("Tangent NEXT X: %f Y: %f\n", nextTangent.x, nextTangent.y);

						vec3 tempVec3Pos, tempVec3Rot, tempVec3Scale;
						tempVec3Pos = vec3(p1[vboNumber][playLoop[vboNumber]], p3[vboNumber][playLoop[vboNumber]], p5[vboNumber][playLoop[vboNumber]]) * 
							((1.0f + 2.0f * testTime[vboNumber]) * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
							previousTangent * (testTime[vboNumber] * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
							vec3(p2[vboNumber][playLoop[vboNumber]], p4[vboNumber][playLoop[vboNumber]], p6[vboNumber][playLoop[vboNumber]]) * 
							((testTime[vboNumber] * testTime[vboNumber]) * (3.0f - 2.0f * testTime[vboNumber])) +
							nextTangent * ((testTime[vboNumber] * testTime[vboNumber]) * (testTime[vboNumber] - 1.0f));

						daeLocX = tempVec3Pos.x;
						daeLocY = tempVec3Pos.y;
						daeLocZ = tempVec3Pos.z;
						//printf("v3Pos X: %f Y: %f Z: %f\n", tempVec3Pos.x, tempVec3Pos.y, tempVec3Pos.z);
						//daeLocX = pVec3Pos[i][loopTest[i]].x;
						//daeLocY = pVec3Pos[i][loopTest[i]].y;
						//daeLocZ = pVec3Pos[i][loopTest[i]].z;

						//ROT
						previousTangent = deltaTime * vec3(tangentOutXRot[vboNumber][playLoop[vboNumber]].x, 
							tangentOutYRot[vboNumber][playLoop[vboNumber]].x, 
							tangentOutZRot[vboNumber][playLoop[vboNumber]].x);
						nextTangent = deltaTime * vec3(tangentInXRot[vboNumber][playLoop[vboNumber]].x, 
							tangentInYRot[vboNumber][playLoop[vboNumber]].x, 
							tangentInZRot[vboNumber][playLoop[vboNumber]].x);

						tempVec3Rot = vec3(pRot1[vboNumber][playLoop[vboNumber]], pRot3[vboNumber][playLoop[vboNumber]], pRot5[vboNumber][playLoop[vboNumber]]) * 
							((1.0f + 2.0f * testTime[vboNumber]) * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
							previousTangent * (testTime[vboNumber] * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
							vec3(pRot2[vboNumber][playLoop[vboNumber]], pRot4[vboNumber][playLoop[vboNumber]], pRot6[vboNumber][playLoop[vboNumber]]) * 
							((testTime[vboNumber] * testTime[vboNumber]) * (3.0f - 2.0f * testTime[vboNumber])) +
							nextTangent * ((testTime[vboNumber] * testTime[vboNumber]) * (testTime[vboNumber] - 1.0f));

						daeRotEulerX = tempVec3Rot.x;
						daeRotEulerY = tempVec3Rot.y;
						daeRotEulerZ = tempVec3Rot.z;
						//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, vboNumber);
						//daeRotEulerX = pVec3Rot[vboNumber][loopTest[vboNumber]].x;
						//daeRotEulerY = pVec3Rot[vboNumber][loopTest[vboNumber]].y;
						//daeRotEulerZ = pVec3Rot[vboNumber][loopTest[vboNumber]].z;
						//printf("daeRot X: %f Y: %f Z: %f i: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, i);

						//SCALE
						previousTangent = deltaTime * vec3(tangentOutXScale[vboNumber][playLoop[vboNumber]].x, 
							tangentOutYScale[vboNumber][playLoop[vboNumber]].x, 
							tangentOutZScale[vboNumber][playLoop[vboNumber]].x);
						nextTangent = deltaTime * vec3(tangentInXScale[vboNumber][playLoop[vboNumber]].x, 
							tangentInYScale[vboNumber][playLoop[vboNumber]].x, 
							tangentInZScale[vboNumber][playLoop[vboNumber]].x);

						tempVec3Scale = vec3(pScale1[vboNumber][playLoop[vboNumber]], pScale3[vboNumber][playLoop[vboNumber]], pScale5[vboNumber][playLoop[vboNumber]]) * 
							((1.0f + 2.0f * testTime[vboNumber]) * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
							previousTangent * (testTime[vboNumber] * ((1.0f - testTime[vboNumber]) * (1.0f - testTime[vboNumber]))) +
							vec3(pScale2[vboNumber][playLoop[vboNumber]], pScale4[vboNumber][playLoop[vboNumber]], pScale6[vboNumber][playLoop[vboNumber]]) * 
							((testTime[vboNumber] * testTime[vboNumber]) * (3.0f - 2.0f * testTime[vboNumber])) +
							nextTangent * ((testTime[vboNumber] * testTime[vboNumber]) * (testTime[vboNumber] - 1.0f));

						daeScaleX = tempVec3Scale.x;
						daeScaleY = tempVec3Scale.y;
						daeScaleZ = tempVec3Scale.z;


						dObj.TranslationMatrix = glm::mat4(1.0f);
						dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

						dObj.RotationMatrixArray[vboNumber] = glm::mat4(1.0f);
						dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
						dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
						dObj.RotationMatrixArray[vboNumber] = glm::rotate(dObj.RotationMatrixArray[vboNumber], daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

						dObj.ScalingMatrix = glm::mat4(1.0f);
						dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
						

						testTime[vboNumber] = 0.0f;
						if(playLoop[vboNumber] > playCount[vboNumber] - 1)//if(playLoop[i] > playCount[vboID] - 1)
						{
							playLoop[vboNumber] = 0;
						}
						else
						{
							playLoop[vboNumber] += 1;
						}
					}
					if(trsSwapArray[vboNumber] == 0)
					{
						daeLocX = 0.0f;
						daeLocY = 0.0f;
						daeLocZ = 0.0f;
						daeRotEulerX = 0.0f;
						daeRotEulerY = 0.0f;
						daeRotEulerZ = 0.0f;
						daeScaleX = 1.0f;
						daeScaleY = 1.0f;
						daeScaleZ = 1.0f;

						dObj.TranslationMatrix = glm::mat4(1.0f);
						dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(modelX, modelY, modelZ)));

						dObj.RotationMatrixArray[vboNumber] = glm::mat4(1.0f);
						dObj.RotationMatrixArray[vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerY * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
						dObj.RotationMatrixArray[vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerZ * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
						dObj.RotationMatrixArray[vboNumber] = glm::rotate(glm::mat4(1.0f), (glm::mediump_float)daeRotEulerX * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

						dObj.ScalingMatrix = glm::mat4(1.0f);
						dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f))
						//printf("trsSwapArray: %d\n", trsSwapArray[vboNumber]);
					}
					//printf("daeRot X: %f Y: %f Z: %f i: %d playLoop: %d\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ, i, playLoop[i]);
					testTime[vboNumber] += 0.1f;
				}
				else
				{
					//
				}
			}
			else
			{
				//if(vboNumber >= vboOrderCount)vboNumber = 0;
			}

			//dObj.myXInterpolation[playLoop[vboNumber]]
			//printf("vboNum: %d playLtest: %d\n", vboNumber, playLoop[vboNumber]);
			//_getch();


			//vboNumber++;
			//printf("vboNumber: %d\n", vboNumber);

			//dObj.TranslationMatrix = glm::mat4(1.0f);
			//dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));

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

			dObj.ModelMatrix = dObj.TranslationMatrix * dObj.RotationMatrixArray[vboNumber] * dObj.ScalingMatrix;
			glUniformMatrix4fv(dObj.uniformModelVBO, 1, GL_FALSE, glm::value_ptr(dObj.ModelMatrix));
			dObj.MVP = dObj.projection * dObj.view * dObj.ModelMatrix;
			glUniformMatrix4fv(dObj.MatrixIDVBO, 1, GL_FALSE, &dObj.MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform
			

			glUniform4f(glGetUniformLocation(myShader, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4
			glUniform3f(glGetUniformLocation(myShader, "objectColor"), 1.0f, 0.5f, 0.31f);
			//glUniform3f(glGetUniformLocation(myShader, "lightColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader, "lightColor"), 0.5f, 0.5f, 0.5f);


			//glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
			//glm::vec3 lightPos = glm::vec3(4,4,4);
			//glm::vec3 lightPos = glm::vec3(1.0f,1.0f,1.0f);
			//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
			//LightID[vboID] = glGetUniformLocation(myShader, "LightPosition_worldspace");


			//glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX, lightY, lightZ);
			//glUniform3f(glGetUniformLocation(myShader, "lightPos"), 0.0f, 0.0f, 0.0f);
			//glUniform3f(glGetUniformLocation(myShader, "lightPos"), 1.2f, 1.0f, 2.0f);
			//glUniform3f(glGetUniformLocation(myShader, "lightPos"), 0.0f - modelX, 0.0f - modelY, 5.0f - modelZ);
			//glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX - modelX, lightY - modelY, lightZ - modelZ);
			//glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX * sin(glfwGetTime()), lightY, lightZ * cos(glfwGetTime()));
			glUniform3f(glGetUniformLocation(myShader, "lightPos"), lightX * (float)sin(glfwGetTime()) - modelX, lightY - modelY, lightZ * (float)cos(glfwGetTime()) - modelZ);//OUTSIDE_ORBIT
			

			//CAMERA POSITION
			//vec3 tempEye = eye + target;
			//glUniform3f(glGetUniformLocation(myShader, "viewPos"), lightX, lightY, lightZ);
			//glUniform3f(glGetUniformLocation(myShader, "viewPos"), 0.0f, 0.0f, 0.0f);
			//glUniform3f(glGetUniformLocation(myShader, "viewPos"), eyeX, eyeY, eyeZ);
			glUniform3f(glGetUniformLocation(myShader, "viewPos"), eye.x, eye.y, eye.z);
			//printf("EYE X: %f Y: %f Z: %f\n", eye.x, eye.y, eye.z);


			glUniform3f(glGetUniformLocation(myShader, "material.ambient"), 1.0f, 0.5f, 0.31f);
			glUniform3f(glGetUniformLocation(myShader, "material.diffuse"), 1.0f, 0.5f, 0.31f);
			glUniform3f(glGetUniformLocation(myShader, "material.specular"), 0.5f, 0.5f, 0.5f);
			//glUniform3f(glGetUniformLocation(myShader, "material.specular"), 1.0f, 1.0f, 1.0f);
			glUniform1f(glGetUniformLocation(myShader, "material.shininess"), 32.0f);


			//lightingShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
			//lightingShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
			//lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader, "light.ambient"), 0.2f, 0.2f, 0.2f);
			glUniform3f(glGetUniformLocation(myShader, "light.diffuse"), 0.5f, 0.5f, 0.5f);
			glUniform3f(glGetUniformLocation(myShader, "light.specular"), 1.0f, 1.0f, 1.0f);
			
			tempTime = (float)glfwGetTime();
			glUniform1f(glGetUniformLocation(myShader, "time"), tempTime);

			glActiveTexture(GL_TEXTURE0);//Bind our texture in Texture Unit 0
			glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*3+0]);//dTexture
			glUniform1i(dObj.diffuseID[vboID+ii], 0);//Set "myTextureSampler" sampler to use Texture Unit 0
			glActiveTexture(GL_TEXTURE1);//Bind our texture in Texture Unit 1
			glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*3+1]);//sTexture
			glUniform1i(dObj.specularID[vboID+ii], 1);//Set "myTextureSampler" sampler to use Texture Unit 1
			glActiveTexture(GL_TEXTURE2);//Bind our texture in Texture Unit 2
			glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*3+2]);//eTexture
			glUniform1i(dObj.emissionID[vboID+ii], 2);//Set "myTextureSampler" sampler to use Texture Unit 2

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
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawArrays(GL_TRIANGLES, 0, vectorvertices[0].size() * sizeof(glm::vec3));
			//Index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.elementbuffer[vboID+ii]);
			glDrawElements(GL_TRIANGLES, indices[vboID+ii].size(), GL_UNSIGNED_SHORT, (void*)0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(3);
			//printf("vboNumber: %d X: %f Y: %f Z: %f\n", vboNumber, daeRotEulerX[vboNumber], daeRotEulerY[vboNumber], daeRotEulerZ[vboNumber]);
			vboNumber++;
		}
		dObj.VBOloadedID++;
	}
}

void drawVBO_light(int vboID, GLint myShader, char*modelfile)
{
	glCullFace(GL_BACK);
	//glUseProgram(lightShaderID);
	glUseProgram(myShader);
	dObj.meshCount = 0;
	if(dObj.loadOnce[vboID] == 0)
	{
		//vectorverticesLight[vboID].clear(), vectoruvsLight[vboID].clear(), vectornormalsLight[vboID].clear();
		//indicesLight[vboID].clear();
		//indexed_verticesLight[vboID].clear(), indexed_uvsLight[vboID].clear(), indexed_normalsLight[vboID].clear();
				
		loadmyDAE(modelfile, vectorverticesLight[vboID], vectoruvsLight[vboID], vectornormalsLight[vboID], daeindicesLight[vboID]);
		indexVBO(vectorverticesLight[vboID], vectoruvsLight[vboID], vectornormalsLight[vboID], indicesLight[vboID], indexed_verticesLight[vboID], indexed_uvsLight[vboID], indexed_normalsLight[vboID]);
		
		glGenVertexArrays(1, &dObj.VertexArrayIDLight[vboID]);
		glGenBuffers(1, &dObj.vertexbufferLight[vboID]);
		glGenBuffers(1, &dObj.elementbufferLight[vboID]);
		glBindVertexArray(dObj.VertexArrayIDLight[vboID]);
		
		//VERTEXBUFFER
		glBindBuffer(GL_ARRAY_BUFFER, dObj.vertexbufferLight[vboID]);
		//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, indexed_verticesLight[vboID].size() * sizeof(glm::vec3), &indexed_verticesLight[vboID][0], GL_STATIC_DRAW);
		/*
		//UVBUFFER
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
		//glBufferData(GL_ARRAY_BUFFER, vectoruvs[vboLoop].size() * sizeof(glm::vec2), &vectoruvs[vboLoop][0], GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboID].size() * sizeof(glm::vec2), &indexed_uvs[vboID][0], GL_STATIC_DRAW);
		//NORMALBUFFER
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboID]);
		//glBufferData(GL_ARRAY_BUFFER, vectornormals[vboLoop].size() * sizeof(glm::vec3), &vectornormals[vboLoop][0], GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, indexed_normals[vboID].size() * sizeof(glm::vec3), &indexed_normals[vboID][0], GL_STATIC_DRAW);
		*/
		//INDICEBUFFERS
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.elementbufferLight[vboID]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLight[vboID].size() * sizeof(unsigned short), &indicesLight[vboID][0], GL_STATIC_DRAW);
		printf("INDSIZELIGHT: %d\n", indicesLight[vboID].size() * sizeof(unsigned short));
		dObj.loadOnce[vboID] = 1;
		//_getch();
	}
	if(dObj.drawDisable[vboID] == 0)
	{
		dObj.projectionLight = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(dObj.uniformProjectionLight, 1, GL_FALSE, glm::value_ptr(dObj.projectionLight));

		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.RotationMatrixLight = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);
		
		//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		//glm::vec3 lightPos(lightX, lightY, lightZ);//INSIDE
		glm::vec3 lightPos(lightX * sin(glfwGetTime()), lightY, lightZ * cos(glfwGetTime()));//OUTSIDE_ORBIT
		dObj.TranslationMatrixLight = glm::mat4(1.0f);
		dObj.TranslationMatrixLight = glm::translate(dObj.TranslationMatrixLight, lightPos);
		dObj.TranslationMatrixLight = glm::scale(dObj.TranslationMatrixLight, glm::vec3(0.2f));//0.2f
		dObj.ScalingMatrixLight = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));


		//viewLight = LookAt(eye, eye + target, up);
		if(myCam == 0)
		{
			dObj.viewLight = LookAt(eye, eye + dObj.target, dObj.up);
			//printf("myCam: %d\n", myCam);
		}

		else if(myCam == 1)
		{
			dObj.viewLight = dObj.viewCamera1;
			//printf("myCam: %d\n", myCam);
		}

		//viewLight = LookAt(eye, eye + target, up);
		glUniformMatrix4fv(dObj.uniformViewLight, 1, GL_FALSE, glm::value_ptr(dObj.viewLight));

		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		dObj.ModelMatrixLight = dObj.TranslationMatrixLight * dObj.RotationMatrixLight * dObj.ScalingMatrixLight;
		glUniformMatrix4fv(dObj.uniformModelLight, 1, GL_FALSE, glm::value_ptr(dObj.ModelMatrixLight));

		dObj.MVPLight = dObj.projectionLight * dObj.viewLight * dObj.ModelMatrixLight;
		glUniformMatrix4fv(dObj.MatrixIDLight, 1, GL_FALSE, &dObj.MVPLight[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.vertexbufferLight[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		/*
		//2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboID]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		*/
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.elementbufferLight[vboID]);
		glDrawElements(GL_TRIANGLES, indicesLight[vboID].size(), GL_UNSIGNED_SHORT, (void*)0);
		glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
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

/*
void initVBO(char*modelfile, char*texturefile, int vboLoop)
{
	//Load the texture
	Texture[vboLoop] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);	
	//Texture[0] = loadPngImage(DAEtexture, imgwidth, imgheight, hasAlpha, &textureImage);
	//delete textureImage;//REFRESH GENTEXTURES

	//loadBMP_custom("test.bmp");
	//LoadBMP("test.bmp");
	//loadDDS("uvmap.DDS");
	//Get a handle for our "myTextureSampler" uniform
	TextureID[vboLoop] = glGetUniformLocation(programID, "myTexture");
	//TextureID[0] = glGetUniformLocation(programID, "myTexture");


	char getFileExtension[64];
	for(int i = strlen(modelfile)-1; i >= 0; i--)
	{
		//printf("strNum: %d\n", i);
		//printf("strChar: %c\n", modelfile[i]);
		getFileExtension[i] = modelfile[i];
		if(strncmp(&getFileExtension[i],".obj", 4) == 0)//if(getFileExtension == ".obj")
		{
			printf(".obj file detected\n");
			loadOBJ(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
			indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
			break;
		}
		if(strncmp(&getFileExtension[i],".dae", 4) == 0)//if(getFileExtension == ".obj")
		{
			//printf(".fbx file detected\n");
			//loadmyFBX(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
			//indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
			break;
		}
	}


	vectorvertices[vboLoop].clear(), vectoruvs[vboLoop].clear(), vectornormals[vboLoop].clear();
	indices[vboLoop].clear();
	indexed_vertices[vboLoop].clear(), indexed_uvs[vboLoop].clear(), indexed_normals[vboLoop].clear();


	//loadOBJ(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
	//indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
	loadmyDAE(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], daeindices[vboLoop]);
	indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
	

	//for(int iii = 0; iii <= 23; iii++)printf("MeshV %d - %d: %.7f\n", sizeof(meshvertices), verticescount, meshvertices[iii]);
	for(int i = 0; i < 36; i++)
	{
		printf("%d polyV X: %f Y: %f Z: %f\n", i, vectorvertices[vboLoop][i*3+0], vectorvertices[vboLoop][i*3+1], vectorvertices[vboLoop][i*3+2]);
		//printf("%d X: %f Y: %f Z: %f\n", i, vectorvertices[vboLoop][i].x, vectorvertices[vboLoop][i].y, vectorvertices[vboLoop][i].z);
		//printf("%d polyUV X: %f Y: %f\n", i, indexed_uvs[vboLoop][i*2+0], indexed_uvs[vboLoop][i*2+1]);
		//printf("%d polyN X: %f Y: %f Z: %f\n", i, indexed_normals[vboLoop][i*3+0], indexed_normals[vboLoop][i*3+1], indexed_normals[vboLoop][i*3+2]);
	}
	_getch();


	//glGenBuffers(1, &vertexbuffer[vboLoop]);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(meshvertices), meshvertices, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ftest), ftest, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, indexed_vertices[vboLoop].size() * sizeof(glm::vec3), &indexed_vertices[vboLoop][0], GL_STATIC_DRAW);
	//COLOR
	//glGenBuffers(1, &colorbuffer[vboLoop]);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ftest), ftest, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboLoop].size() * sizeof(glm::vec2), &indexed_uvs[vboLoop][0], GL_STATIC_DRAW);
	

	//LightID[0] = glGetUniformLocation(programID, "LightPosition_worldspace");
	glGenVertexArrays(1, &VertexArrayID[vboLoop]);
	glBindVertexArray(VertexArrayID[vboLoop]);


	//VERTEXBUFFER
	glGenBuffers(1, &vertexbuffer[vboLoop]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices[vboLoop].size() * sizeof(glm::vec3), &indexed_vertices[vboLoop][0], GL_STATIC_DRAW);
	//UVBUFFER
	glGenBuffers(1, &uvbuffer[vboLoop]);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectoruvs[vboLoop].size() * sizeof(glm::vec2), &vectoruvs[vboLoop][0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboLoop].size() * sizeof(glm::vec2), &indexed_uvs[vboLoop][0], GL_STATIC_DRAW);
	//NORMALBUFFER
	glGenBuffers(1, &normalbuffer[vboLoop]);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectornormals[vboLoop].size() * sizeof(glm::vec3), &vectornormals[vboLoop][0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals[vboLoop].size() * sizeof(glm::vec3), &indexed_normals[vboLoop][0], GL_STATIC_DRAW);
	//INDICEBUFFERS
	glGenBuffers(1, &elementbuffer[vboLoop]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboLoop]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[vboLoop].size() * sizeof(unsigned short), &indices[vboLoop][0], GL_STATIC_DRAW);
	printf("INDSIZE: %d\n", indices[vboLoop].size() * sizeof(unsigned short));
	//vboLoop++;
}
*/