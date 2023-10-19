#include "Common.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
extern int SCREEN_WIDTH, SCREEN_HEIGHT;

/*
extern glm::mat4 projection,
	view, viewCamera1,
	ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix,
	projectionLight, viewLight, ModelMatrixLight, MVPLight, RotationMatrixLight, TranslationMatrixLight, ScalingMatrixLight;
*/

extern glm::vec3 eye;
//extern glm::vec3 right, target, up;

extern bool hasAlpha;
extern int myCam;
extern int imgwidth, imgheight;

/*
extern int xInputCount, xOutputCount, xInTangentCount, xOutTangentCount,
	yInputCount, yOutputCount, yInTangentCount, yOutTangentCount,
	zInputCount, zOutputCount, zInTangentCount, zOutTangentCount;
*/

extern float deltaTime;

extern float modelX, modelY, modelZ;
extern float lightX, lightY, lightZ;

extern float eyeX, eyeY, eyeZ;
extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
GLuint programID, materialShaderID,
	uniformModel, uniformView, uniformProjection, uniformRotation,
	MatrixID, MatrixIDVBO, uniformModelVBO, uniformViewVBO, uniformProjectionVBO,
	lightShaderID, MatrixIDLight, uniformModelLight, uniformViewLight, uniformProjectionLight;


GLuint diffuseID[90000], specularID[90000], emissionID[90000], Texture[90000], LightID[90000],
	VertexArrayID[90000], vertexbuffer[90000], colorbuffer[90000], uvbuffer[90000], normalbuffer[90000], elementbuffer[90000],
	VertexArrayIDLight[90000], vertexbufferLight[90000], uvbufferLight[90000], normalbufferLight[90000], elementbufferLight[90000];
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<glm::vec3> vectorvertices[90000];
std::vector<glm::vec2> vectoruvs[90000];
std::vector<glm::vec3> vectornormals[90000];
std::vector<glm::vec3> vectorcolors[90000];
std::vector<unsigned short> indices[90000], daeindices[90000];
std::vector<glm::vec3> indexed_vertices[90000];
std::vector<glm::vec2> indexed_uvs[90000];
std::vector<glm::vec3> indexed_normals[90000];
//////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<glm::vec3> vectorverticesLight[90000];
std::vector<glm::vec2> vectoruvsLight[90000];
std::vector<glm::vec3> vectornormalsLight[90000];
std::vector<unsigned short> indicesLight[90000], daeindicesLight[90000];
std::vector<glm::vec3> indexed_verticesLight[90000];
std::vector<glm::vec2> indexed_uvsLight[90000];
std::vector<glm::vec3> indexed_normalsLight[90000];
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
//TEMP X
extern float storedXInput[ARRAYCOUNT];
extern float storedXOutput[ARRAYCOUNT];
extern float storedXInTangent[ARRAYCOUNT];
extern float storedXOutTangent[ARRAYCOUNT];
//TEMP Y
extern float storedYInput[ARRAYCOUNT];
extern float storedYOutput[ARRAYCOUNT];
extern float storedYInTangent[ARRAYCOUNT];
extern float storedYOutTangent[ARRAYCOUNT];
//TEMP Z
extern float storedZInput[ARRAYCOUNT];
extern float storedZOutput[ARRAYCOUNT];
extern float storedZInTangent[ARRAYCOUNT];
extern float storedZOutTangent[ARRAYCOUNT];

//X
float myXInput[ARRAYCOUNT];
float myXOutput[ARRAYCOUNT];
float myXInTangent[ARRAYCOUNT];
float myXOutTangent[ARRAYCOUNT];
//Y
float myYInput[ARRAYCOUNT];
float myYOutput[ARRAYCOUNT];
float myYInTangent[ARRAYCOUNT];
float myYOutTangent[ARRAYCOUNT];
//Z
float myZInput[ARRAYCOUNT];
float myZOutput[ARRAYCOUNT];
float myZInTangent[ARRAYCOUNT];
float myZOutTangent[ARRAYCOUNT];
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////

int steps;
//int storeID;
int playLoop;
int playCount[90000];

//float playTime;
float testTime;

float daeLocX, daeLocY, daeLocZ;
float daeRotEulerX, daeRotEulerY, daeRotEulerZ;
float daeScaleX, daeScaleY, daeScaleZ;

float p1[9000], p2[9000], p3[9000], p4[9000], p5[9000], p6[9000];
float pRot1[9000], pRot2[9000], pRot3[9000], pRot4[9000], pRot5[9000], pRot6[9000];
float pScale1[9000], pScale2[9000], pScale3[9000], pScale4[9000], pScale5[9000], pScale6[9000];

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

int initalVBO;
int vboCount[90000];

void drawVBO(int vboID, GLint myShader, char*modelfile, char*texturefile)
{
	glCullFace(GL_BACK);
	//glUseProgram(programID);//BASIC SHADER
	glUseProgram(myShader);
	//materialShaderID
	//lightShaderID
	dObj.meshCount = 0;


	/*
	char getFileExtension[64];
	for(int i = strlen(modelfile)-1; i >= 0; i--)
	{
		//printf("strNum: %d\n", i);
		//printf("strChar: %c\n", modelfile[i]);
		getFileExtension[i] = modelfile[i];
		if(strncmp(&getFileExtension[i],".obj", 4) == 0)//if(getFileExtension == ".obj")
		{
			printf(".obj file detected!\n");
			loadOBJ(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
			indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
			break;
		}
		if(strncmp(&getFileExtension[i],".dae", 4) == 0)//if(getFileExtension == ".obj")
		{
			//printf(".fbx file detected!\n");
			//loadmyFBX(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
			//indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
			break;
		}
	}


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
	*/


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
		
		int x1 = 0, x2 = 0, x3 = 0, x4 = 0;
		for(;x1 <= dObj.xInputCount; x1++)//TIME
		{
			//printf("xInput: %f\n", storedXInput[x1]);
			dObj.myXInput[x1] = dObj.storedXInput[x1];
			//printf("xInput: %f\n", myXInput[storeID][x1]);

			dObj.myXRotEulerInput[x1] = dObj.storedXRotEulerInput[x1];
			//printf("xRotInput: %f\n", dObj.myXRotEulerInput[x1]);
			dObj.myXScaleInput[x1] = dObj.storedXScaleInput[x1];
			//printf("xScaleInput: %f\n", dObj.myXScaleInput[x1]);
		}
		for(;x2 <= dObj.xOutputCount; x2++)//POS
		{
			//printf("xOutput: %f\n", storedXOutput[x2]);
			dObj.myXOutput[x2] = dObj.storedXOutput[x2];
			//printf("xOutput: %f\n", dObj.myXOutput[x2]);
			//steps++;
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
			//printf("TESTX!\n");
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
			//printf("TESTY!\n");
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
			//printf("TESTZ!\n");
			//steps++;
			printf("TESTXYZ!\n");
			steps++;
		}


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

				playCount[vboID] = dObj.xInputCount - 2;
				
				//X TANGENT
				vec2 tangentOutX;//(myXOutTangent[i*2+0], myXOutTangent[i*2+1]);
				vec2 tangentInX;//(myXInTangent[i*2+0], myXInTangent[i*2+1]);
				vec2 tangentOutXRot;
				vec2 tangentInXRot;
				vec2 tangentOutXScale;
				vec2 tangentInXScale;
				//Y TANGENT
				vec2 tangentOutY;//(myYOutTangent[i*2+0], myYOutTangent[i*2+1]);
				vec2 tangentInY;//(myYInTangent[i*2+0], myYInTangent[i*2+1]);
				vec2 tangentOutYRot;
				vec2 tangentInYRot;
				vec2 tangentOutYScale;
				vec2 tangentInYScale;
				//Z TANGENT
				vec2 tangentOutZ;//(myZOutTangent[i*2+0], myZOutTangent[i*2+1]);
				vec2 tangentInZ;//(myZInTangent[i*2+0], myZInTangent[i*2+1]);
				vec2 tangentOutZRot;
				vec2 tangentInZRot;
				vec2 tangentOutZScale;
				vec2 tangentInZScale;
				
				if(i == 0)
				{
					//X TANGENT
					tangentOutX = vec2(dObj.myXOutTangent[i*2+0], dObj.myXOutTangent[i*2+1]);
					tangentInX = vec2(dObj.myXInTangent[i*2+0], dObj.myXInTangent[i*2+1]);
					tangentOutXRot = vec2(dObj.myXRotEulerOutTangent[i*2+0], dObj.myXRotEulerOutTangent[i*2+1]);
					tangentInXRot = vec2(dObj.myXRotEulerInTangent[i*2+0], dObj.myXRotEulerInTangent[i*2+1]);
					tangentOutXScale = vec2(dObj.myXScaleOutTangent[i*2+0], dObj.myXScaleOutTangent[i*2+1]);
					tangentInXScale = vec2(dObj.myXScaleInTangent[i*2+0], dObj.myXScaleInTangent[i*2+1]);
					//Y TANGENT
					tangentOutY = vec2(dObj.myYOutTangent[i*2+0], dObj.myYOutTangent[i*2+1]);
					tangentInY = vec2(dObj.myYInTangent[i*2+0], dObj.myYInTangent[i*2+1]);
					tangentOutYRot = vec2(dObj.myYRotEulerOutTangent[i*2+0], dObj.myYRotEulerOutTangent[i*2+1]);
					tangentInYRot = vec2(dObj.myYRotEulerInTangent[i*2+0], dObj.myYRotEulerInTangent[i*2+1]);
					tangentOutYScale = vec2(dObj.myYScaleOutTangent[i*2+0], dObj.myYScaleOutTangent[i*2+1]);
					tangentInYScale = vec2(dObj.myYScaleInTangent[i*2+0], dObj.myYScaleInTangent[i*2+1]);
					//Z TANGENT
					tangentOutZ = vec2(dObj.myZOutTangent[i*2+0], dObj.myZOutTangent[i*2+1]);
					tangentInZ = vec2(dObj.myZInTangent[i*2+0], dObj.myZInTangent[i*2+1]);
					tangentOutZRot = vec2(dObj.myZRotEulerOutTangent[i*2+0], dObj.myZRotEulerOutTangent[i*2+1]);
					tangentInZRot = vec2(dObj.myZRotEulerInTangent[i*2+0], dObj.myZRotEulerInTangent[i*2+1]);
					tangentOutZScale = vec2(dObj.myZScaleOutTangent[i*2+0], dObj.myZScaleOutTangent[i*2+1]);
					tangentInZScale = vec2(dObj.myZScaleInTangent[i*2+0], dObj.myZScaleInTangent[i*2+1]);


					//X POINTS
					p1[i] = dObj.myXOutput[i*2+0];
					p2[i] = dObj.myXOutput[i*2+1];
					pRot1[i] = dObj.myXRotEulerOutput[i*2+0];
					pRot2[i] = dObj.myXRotEulerOutput[i*2+1];
					pScale1[i] = dObj.myXScaleOutput[i*2+0];
					pScale2[i] = dObj.myXScaleOutput[i*2+1];
					//Y POINTS
					p3[i] = dObj.myYOutput[i*2+0];
					p4[i] = dObj.myYOutput[i*2+1];
					pRot3[i] = dObj.myYRotEulerOutput[i*2+0];
					pRot4[i] = dObj.myYRotEulerOutput[i*2+1];
					pScale3[i] = dObj.myYScaleOutput[i*2+0];
					pScale4[i] = dObj.myYScaleOutput[i*2+1];
					//Z POINTS
					p5[i] = dObj.myZOutput[i*2+0];
					p6[i] = dObj.myZOutput[i*2+1];
					pRot5[i] = dObj.myZRotEulerOutput[i*2+0];
					pRot6[i] = dObj.myZRotEulerOutput[i*2+1];
					pScale5[i] = dObj.myZScaleOutput[i*2+0];
					pScale6[i] = dObj.myZScaleOutput[i*2+1];
					//vec2 p1(0.0f,0.0f);//vec2 p2(8.0f,0.0f);
				}
				else
				{
					//X TANGENT
					tangentOutX = vec2(dObj.myXOutTangent[i*2-1], dObj.myXOutTangent[i*2+0]);
					tangentInX = vec2(dObj.myXInTangent[i*2-1], dObj.myXInTangent[i*2+0]);
					tangentOutXRot = vec2(dObj.myXRotEulerOutTangent[i*2-1], dObj.myXRotEulerOutTangent[i*2+0]);
					tangentInXRot = vec2(dObj.myXRotEulerInTangent[i*2-1], dObj.myXRotEulerInTangent[i*2+0]);
					tangentOutXScale = vec2(dObj.myXScaleOutTangent[i*2-1], dObj.myXScaleOutTangent[i*2+0]);
					tangentInXScale = vec2(dObj.myXScaleInTangent[i*2-1], dObj.myXScaleInTangent[i*2+0]);
					//Y TANGENT
					tangentOutY = vec2(dObj.myYOutTangent[i*2-1], dObj.myYOutTangent[i*2+0]);
					tangentInY = vec2(dObj.myYInTangent[i*2-1], dObj.myYInTangent[i*2+0]);
					tangentOutYRot = vec2(dObj.myYRotEulerOutTangent[i*2-1], dObj.myYRotEulerOutTangent[i*2+0]);
					tangentInYRot = vec2(dObj.myYRotEulerInTangent[i*2-1], dObj.myYRotEulerInTangent[i*2+0]);
					tangentOutYScale = vec2(dObj.myYScaleOutTangent[i*2-1], dObj.myYScaleOutTangent[i*2+0]);
					tangentInYScale = vec2(dObj.myYScaleInTangent[i*2-1], dObj.myYScaleInTangent[i*2+0]);
					//Z TANGENT
					tangentOutZ = vec2(dObj.myZOutTangent[i*2-1], dObj.myZOutTangent[i*2+0]);
					tangentInZ = vec2(dObj.myZInTangent[i*2-1], dObj.myZInTangent[i*2+0]);
					tangentOutZRot = vec2(dObj.myZRotEulerOutTangent[i*2-1], dObj.myZRotEulerOutTangent[i*2+0]);
					tangentInZRot = vec2(dObj.myZRotEulerInTangent[i*2-1], dObj.myZRotEulerInTangent[i*2+0]);
					tangentOutZScale = vec2(dObj.myZScaleOutTangent[i*2-1], dObj.myZScaleOutTangent[i*2+0]);
					tangentInZScale = vec2(dObj.myZScaleInTangent[i*2-1], dObj.myZScaleInTangent[i*2+0]);

					//X POINTS
					p1[i] = dObj.myXOutput[i+0];//p1[i] = myXOutput[i*2-1];
					p2[i] = dObj.myXOutput[i+1];//p2[i] = myXOutput[i*2+0];
					pRot1[i] = dObj.myXRotEulerOutput[i+0];
					pRot2[i] = dObj.myXRotEulerOutput[i+1];
					pScale1[i] = dObj.myXScaleOutput[i+0];
					pScale2[i] = dObj.myXScaleOutput[i+1];
					//Y POINTS
					p3[i] = dObj.myYOutput[i+0];//p3[i] = myYOutput[i*2-1];
					p4[i] = dObj.myYOutput[i+1];//p4[i] = myYOutput[i*2+0];
					pRot3[i] = dObj.myYRotEulerOutput[i+0];
					pRot4[i] = dObj.myYRotEulerOutput[i+1];
					pScale3[i] = dObj.myYScaleOutput[i+0];
					pScale4[i] = dObj.myYScaleOutput[i+1];
					//Z POINTS
					p5[i] = dObj.myZOutput[i+0];//p5[i] = myZOutput[i*2-1];
					p6[i] = dObj.myZOutput[i+1];//p6[i] = myZOutput[i*2+0];
					pRot5[i] = dObj.myZRotEulerOutput[i+0];
					pRot6[i] = dObj.myZRotEulerOutput[i+1];
					pScale5[i] = dObj.myZScaleOutput[i+0];
					pScale6[i] = dObj.myZScaleOutput[i+1];
				}

				vec2 pX, pY, pZ,
					pRotX, pRotY, pRotZ,
					pScaleX, pScaleY, pScaleZ;

				/////////////////////////////////////////////////////////////////////////////
								
				pX = vec2(h1*p1[i]) +                    // multiply and sum all funtions
					vec2(h2*p2[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutX) +                    // point along the curve.
					vec2(h4*tangentInX);
				p1[i] = pX.x;

				pY = vec2(h1*p3[i]) +                    // multiply and sum all funtions
					vec2(h2*p4[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutY) +                    // point along the curve.
					vec2(h4*tangentInY);
				p3[i] = pY.x;

				pZ = vec2(h1*p5[i]) +                    // multiply and sum all funtions
					vec2(h2*p6[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutZ) +                    // point along the curve.
					vec2(h4*tangentInZ);
				p5[i] = pZ.x;

				/////////////////////////////////////////////////////////////////////////////

				pRotX = vec2(h1*pRot1[i]) +                    // multiply and sum all funtions
					vec2(h2*pRot2[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutXRot) +                    // point along the curve.
					vec2(h4*tangentInXRot);
				pRot1[i] = pRotX.x;

				pRotY = vec2(h1*pRot3[i]) +                    // multiply and sum all funtions
					vec2(h2*pRot4[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutYRot) +                    // point along the curve.
					vec2(h4*tangentInYRot);
				pRot3[i] = pRotY.x;

				pRotZ = vec2(h1*pRot5[i]) +                    // multiply and sum all funtions
					vec2(h2*pRot6[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutZRot) +                    // point along the curve.
					vec2(h4*tangentInZRot);
				pRot5[i] = pRotZ.x;
				
				/////////////////////////////////////////////////////////////////////////////

				pScaleX = vec2(h1*pScale1[i]) +                    // multiply and sum all funtions
					vec2(h2*pScale2[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutXScale) +                    // point along the curve.
					vec2(h4*tangentInXScale);
				pScale1[i] = pScaleX.x;

				pScaleY = vec2(h1*pScale3[i]) +                    // multiply and sum all funtions
					vec2(h2*pScale4[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutYScale) +                    // point along the curve.
					vec2(h4*tangentInYScale);
				pScale3[i] = pScaleY.x;

				pScaleZ = vec2(h1*pScale5[i]) +                    // multiply and sum all funtions
					vec2(h2*pScale6[i]) +                    // together to build the interpolated
					vec2(h3*tangentOutZScale) +                    // point along the curve.
					vec2(h4*tangentInZScale);
				pScale5[i] = pScaleZ.x;

				/////////////////////////////////////////////////////////////////////////////

				//lineto (p)                            // draw to calculated point on the curve
				//printf("t: %f X: %f Y: %f\n", t, p.x, p.y);
				//printf("t: %d storeID: %d X: %f Y: %f Z: %f\n", t, steps, pX.x, pY.x, pZ.x);
				//printf("t: %d storeID: %d X: %f Y: %f Z: %f\n", t, steps, pRotX.x, pRotY.x, pRotZ.x);
				//printf("t: %d storeID: %d X: %f Y: %f Z: %f\n", t, steps, pScaleX.x, pScaleY.x, pScaleZ.x);
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
			glGenBuffers(1, &dObj.elementbuffer[vboID+i]);


			glBindVertexArray(dObj.VertexArrayID[vboID+i]);
			//VERTEXBUFFER
			glBindBuffer(GL_ARRAY_BUFFER, dObj.vertexbuffer[vboID+i]);
			//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, indexed_vertices[vboID+i].size() * sizeof(glm::vec3), &indexed_vertices[vboID+i][0], GL_STATIC_DRAW);
			//UVBUFFER
			glBindBuffer(GL_ARRAY_BUFFER, dObj.uvbuffer[vboID+i]);
			//glBufferData(GL_ARRAY_BUFFER, vectoruvs[vboLoop].size() * sizeof(glm::vec2), &vectoruvs[vboLoop][0], GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboID+i].size() * sizeof(glm::vec2), &indexed_uvs[vboID+i][0], GL_STATIC_DRAW);
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
	}

	for(int ii = 0; ii < vboCount[initalVBO]; ii++)
	{
		if(dObj.drawDisable[vboID+ii] == 0)
		{
			//printf("II loop: %d\n", ii);
			dObj.projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
			glUniformMatrix4fv(dObj.uniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.projection));
			
			if(testTime < 1.0f)
			{
				//P = (1-t)P1 + tP2

				//LOC
				daeLocX = ((1.0f - testTime) * p1[playLoop] + (testTime * p2[playLoop]));
				daeLocY = ((1.0f - testTime) * p3[playLoop] + (testTime * p4[playLoop]));
				daeLocZ = ((1.0f - testTime) * p5[playLoop] + (testTime * p6[playLoop]));
				//ROT
				daeRotEulerX = ((1.0f - testTime) * pRot1[playLoop] + (testTime * pRot2[playLoop]));
				daeRotEulerY = ((1.0f - testTime) * pRot3[playLoop] + (testTime * pRot4[playLoop]));
				daeRotEulerZ = ((1.0f - testTime) * pRot5[playLoop] + (testTime * pRot6[playLoop]));
				//printf("daeRot X: %f Y: %f Z: %f\n", daeRotEulerX, daeRotEulerY, daeRotEulerZ);
				//SCALE
				daeScaleX = ((1.0f - testTime) * pScale1[playLoop] + (testTime * pScale2[playLoop]));
				daeScaleY = ((1.0f - testTime) * pScale3[playLoop] + (testTime * pScale4[playLoop]));
				daeScaleZ = ((1.0f - testTime) * pScale5[playLoop] + (testTime * pScale6[playLoop]));

				//printf("t: %f daeLocX: %f\n", testTime, daeLocX);
				//testTime += 0.001f;
				testTime += 0.01f;
			}
			else
			{
				//printf("playLoop: %d xInputCount: %d\n", playLoop, xInputCount);
				testTime = 0.0f;

				if(playLoop > playCount[vboID])
				{
					playLoop = 0;
				}
				else
				{
					playLoop += 1;
				}
			}
			
			vec3 desiredDir = glm::vec3(daeRotEulerX, daeRotEulerY, daeRotEulerZ);//rotX, rotY, rotZ);//gPosition1-gPosition2;
			vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
			//EULER TO QUATERNION
			quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
			gOrientation2[vboID+ii] = RotateTowards(gOrientation2[vboID+ii], targetOrientation, 1.0f*deltaTime);//And interpolate
			//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
			dObj.RotationMatrix = mat4_cast(gOrientation2[vboID+ii]);
			//dObj.RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);


			/*
			if(vboID == 9)
			{
				//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
				glm::vec3 lightPos(lightX, lightY, lightZ);//INSIDE
				//glm::vec3 lightPos(lightX * sin(glfwGetTime()), lightY, lightZ * cos(glfwGetTime()));//OUTSIDE
				TranslationMatrix = glm::mat4(1.0f);
				TranslationMatrix = glm::translate(TranslationMatrix, lightPos);
				//TranslationMatrix = glm::scale(TranslationMatrix, glm::vec3(1.0f/5.0f));//0.2f
				TranslationMatrix = glm::scale(TranslationMatrix, glm::vec3(1.0f));//0.2f

				//translate(mat4(), glm::vec3(modelX, modelY, modelZ));

				ScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
			}
			else if(vboID == 8)
			{
				//mat4Rot = rotationMatrix(vec3(0.0f, 1.0f, 0.0f), rotMat);
				//RotationMatrix = mat4Rot;
				//glUniformMatrix4fv(uniformRotation[0], 1, GL_FALSE, glm::value_ptr(RotationMatrix));
				//rotMat += 0.05f;
			}
			*/


			//ORIGINAL
			//TranslationMatrix = translate(mat4(), glm::vec3(modelX, modelY, modelZ));
			dObj.ScalingMatrix = scale(mat4(), vec3(daeScaleX, daeScaleY, daeScaleZ));//scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));

			//MOVE MATRIX WITH LIGHT
			//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
			//glm::vec3 lightPos(lightX, lightY, lightZ);

			dObj.TranslationMatrix = glm::mat4(1.0f);
			//TranslationMatrix = glm::translate(TranslationMatrix, (glm::vec3(modelX, modelY, modelZ)));//INSIDE
			dObj.TranslationMatrix = glm::translate(dObj.TranslationMatrix, (glm::vec3(daeLocX, daeLocY, daeLocZ)));//INSIDE
			//TranslationMatrix = glm::translate(TranslationMatrix, (glm::vec3(modelX * sin(glfwGetTime()), modelY, modelZ * cos(glfwGetTime()))));//OUTSIDE

			//TranslationMatrix = translate(mat4(), glm::vec3(modelX, modelY, modelZ));
			//TranslationMatrix = glm::translate(TranslationMatrix, lightPos);//NOWORK
			//TranslationMatrix = glm::translate(TranslationMatrix, lightPos * (glm::vec3(modelX, modelY, modelZ)));
			//}


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

			//glm::mat4 view = LookAt(eye, eye+target, up);
			glUniformMatrix4fv(dObj.uniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));
			//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));

			dObj.ModelMatrix = dObj.TranslationMatrix * dObj.RotationMatrix * dObj.ScalingMatrix;
			glUniformMatrix4fv(dObj.uniformModel, 1, GL_FALSE, glm::value_ptr(dObj.ModelMatrix));

			dObj.MVP = dObj.projection * dObj.view * dObj.ModelMatrix;
			glUniformMatrix4fv(dObj.MatrixID, 1, GL_FALSE, &dObj.MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

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



			//if(vboID == 8){
			glActiveTexture(GL_TEXTURE0);//Bind our texture in Texture Unit 0
			glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*3+0]);//dTexture
			glUniform1i(dObj.diffuseID[vboID+ii], 0);//Set "myTextureSampler" sampler to use Texture Unit 0

			glActiveTexture(GL_TEXTURE1);//Bind our texture in Texture Unit 1
			glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*3+1]);//sTexture
			glUniform1i(dObj.specularID[vboID+ii], 1);//Set "myTextureSampler" sampler to use Texture Unit 1

			glActiveTexture(GL_TEXTURE2);//Bind our texture in Texture Unit 2
			glBindTexture(GL_TEXTURE_2D, dObj.Texture[(vboID+ii)*3+2]);//eTexture
			glUniform1i(dObj.emissionID[vboID+ii], 2);//Set "myTextureSampler" sampler to use Texture Unit 2
			//}

			

			//1st attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, dObj.vertexbuffer[vboID+ii]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			//2nd attribute buffer : UVs
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, dObj.uvbuffer[vboID+ii]);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
			//3rd attribute buffer : normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, dObj.normalbuffer[vboID+ii]);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			//4th attribute buffer : color4v
			//glEnableVertexAttribArray(3);
			//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[vboID]);
			//glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

			//glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawArrays(GL_TRIANGLES, 0, vectorvertices[0].size() * sizeof(glm::vec3));
			//Index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.elementbuffer[vboID+ii]);
			glDrawElements(GL_TRIANGLES, indices[vboID+ii].size(), GL_UNSIGNED_SHORT, (void*)0);
		}
		dObj.VBOloadedID++;
	}

	/*
	//for(int stuffs = 0; stuffs < 8; stuffs++)printf("MESHV X: %f Y: %f Z: %f\n", meshvertices[stuffs*3+0], meshvertices[stuffs*3+1], meshvertices[stuffs*3+2]);//_getch();
	//2nd attribute buffer:UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//3rd attribute buffer:normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboID]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboID]);
	glDrawElements(GL_TRIANGLES, indices[vboID].size(), GL_UNSIGNED_SHORT, (void*)0);


	if(vboID == 1)
	{
		vec3 desiredDir = glm::vec3(0.01f, 90.0f, 0.01f);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		RotationMatrix = mat4_cast(gOrientation2[vboID]);

		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);
		TranslationMatrix = translate(mat4(), glm::vec3(6.0f, modelY, modelZ));
		ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));//scaling[0], scaling[1], scaling[2]));
		ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
		MVP = projection * view * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

		glActiveTexture(GL_TEXTURE0);//Bind our texture in Texture Unit 0
		glBindTexture(GL_TEXTURE_2D, Texture[1]);
		glUniform1i(TextureID, 0);//Set "myTextureSampler" sampler to use Texture Unit 0

		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[1]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[1]);
		glDrawElements(GL_TRIANGLES, indices[1].size(), GL_UNSIGNED_SHORT, (void*)0);
	}
	*/
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
			printf(".obj file detected!\n");
			loadOBJ(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
			indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
			break;
		}
		if(strncmp(&getFileExtension[i],".dae", 4) == 0)//if(getFileExtension == ".obj")
		{
			//printf(".fbx file detected!\n");
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