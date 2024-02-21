#include "Common.h"

struct xmlVectorArray
{
	float x, y, z;
};

extern drawObjects dObj;

std::vector<glm::vec3> temp_vertices, temp_normals, temp_uvs, temp_indicesvertices;
bool meshuv, meshcolor;


char storedMesh1DoubleArray[1000][255];
char storedMesh2DoubleArray[3000][64];

extern int vboOrderCount;



/*
bool verticesfound, normalsfound, uvmapfound, indicesfound,
	xInputFound, xOutputFound, xInTangentFound, xOutTangentFound,
	yInputFound, yOutputFound, yInTangentFound, yOutTangentFound,
	zInputFound, zOutputFound, zInTangentFound, zOutTangentFound;

int verticescount, normalscount, uvmapscount, indicescount,
	xInputCount, xOutputCount, xInTangentCount, xOutTangentCount,
	yInputCount, yOutputCount, yInTangentCount, yOutTangentCount,
	zInputCount, zOutputCount, zInTangentCount, zOutTangentCount;
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
int vertindices[ARRAYCOUNT];
int normindices[ARRAYCOUNT];
int uvindices[ARRAYCOUNT];


//int *intarray = new int;
//float *floatarray = new float;
//int *intarray;
//float *floatarray;

int intarray[ARRAYCOUNT];
float floatarray[ARRAYCOUNT];



//float*storedvertices;
//float*storednormals;
//float*storeduvmaps;
float storedvertices[ARRAYCOUNT];
float storednormals[ARRAYCOUNT];
float storeduvmaps[ARRAYCOUNT];


float storedXInput[ARRAYCOUNT];
float storedXOutput[ARRAYCOUNT];
float storedXInTangent[ARRAYCOUNT];
float storedXOutTangent[ARRAYCOUNT];

float storedYInput[ARRAYCOUNT];
float storedYOutput[ARRAYCOUNT];
float storedYInTangent[ARRAYCOUNT];
float storedYOutTangent[ARRAYCOUNT];

float storedZInput[ARRAYCOUNT];
float storedZOutput[ARRAYCOUNT];
float storedZInTangent[ARRAYCOUNT];
float storedZOutTangent[ARRAYCOUNT];


//float *meshvertices = new float;
//float *meshnormals = new float;
//float *meshuvmaps = new float;
//float *meshvertices;
//float *meshnormals;
//float *meshuvmaps;

float meshvertices[ARRAYCOUNT];
float meshnormals[ARRAYCOUNT];
float meshuvmaps[ARRAYCOUNT];
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////

//LOAD MULTIPLE
//extern int limitOne;
//extern int meshCount;
//XML
//int initialCount;
//int meshSkip;
//int newVecArray;

//////////////////////////////////////////////////////////////////////////////////////////////////////

char meshName[1000];
char *meshPositions = "-positions-array";
char meshAppendPositions[1000];
char *meshNormals = "-normals-array";
char meshAppendNormals[1000];
char *meshMap0 = "-map-0-array";
char meshAppendMap0[1000];
char *meshColors = "-colors-Col-array";
char meshAppendColors[1000];

//TEST
//LOCATION
char *locationXinput = "_location_X-input-array", *locationYinput = "_location_Y-input-array", *locationZinput = "_location_Z-input-array";
char meshAppendlocationXinput[1000], meshAppendlocationYinput[1000], meshAppendlocationZinput[1000];
char *locationXoutput = "_location_X-output-array", *locationYoutput = "_location_Y-output-array", *locationZoutput = "_location_Z-output-array";
char meshAppendlocationXoutput[1000], meshAppendlocationYoutput[1000], meshAppendlocationZoutput[1000];
char *locationXinterpolation = "_location_X-interpolation-array", *locationYinterpolation = "_location_Y-interpolation-array", *locationZinterpolation = "_location_Z-interpolation-array";
char meshAppendlocationXinterpolation[1000], meshAppendlocationYinterpolation[1000], meshAppendlocationZinterpolation[1000];
char *locationXintangent = "_location_X-intangent-array", *locationYintangent = "_location_Y-intangent-array", *locationZintangent = "_location_Z-intangent-array";
char meshAppendlocationXintangent[1000], meshAppendlocationYintangent[1000], meshAppendlocationZintangent[1000];
char *locationXouttangent = "_location_X-outtangent-array", *locationYouttangent = "_location_Y-outtangent-array", *locationZouttangent = "_location_Z-outtangent-array";
char meshAppendlocationXouttangent[1000], meshAppendlocationYouttangent[1000], meshAppendlocationZouttangent[1000];
//ROTATION EULER
char *rotationeulerXinput = "_rotation_euler_X-input-array", *rotationeulerYinput = "_rotation_euler_Y-input-array", *rotationeulerZinput = "_rotation_euler_Z-input-array";
char meshAppendrotationeulerXinput[1000], meshAppendrotationeulerYinput[1000], meshAppendrotationeulerZinput[1000];
char *rotationeulerXoutput = "_rotation_euler_X-output-array", *rotationeulerYoutput = "_rotation_euler_Y-output-array", *rotationeulerZoutput = "_rotation_euler_Z-output-array";
char meshAppendrotationeulerXoutput[1000], meshAppendrotationeulerYoutput[1000], meshAppendrotationeulerZoutput[1000];
char *rotationeulerXinterpolation = "_rotation_euler_X-interpolation-array", *rotationeulerYinterpolation = "_rotation_euler_Y-interpolation-array", *rotationeulerZinterpolation = "_rotation_euler_Z-interpolation-array";
char meshAppendrotationeulerXinterpolation[1000], meshAppendrotationeulerYinterpolation[1000], meshAppendrotationeulerZinterpolation[1000];
char *rotationeulerXintangent = "_rotation_euler_X-intangent-array", *rotationeulerYintangent = "_rotation_euler_Y-intangent-array", *rotationeulerZintangent = "_rotation_euler_Z-intangent-array";
char meshAppendrotationeulerXintangent[1000], meshAppendrotationeulerYintangent[1000], meshAppendrotationeulerZintangent[1000];
char *rotationeulerXouttangent = "_rotation_euler_X-outtangent-array", *rotationeulerYouttangent = "_rotation_euler_Y-outtangent-array", *rotationeulerZouttangent = "_rotation_euler_Z-outtangent-array";
char meshAppendrotationeulerXouttangent[1000], meshAppendrotationeulerYouttangent[1000], meshAppendrotationeulerZouttangent[1000];
//SCALE
char *scaleXinput = "_scale_X-input-array", *scaleYinput = "_scale_Y-input-array", *scaleZinput = "_scale_Z-input-array";
char meshAppendscaleXinput[1000], meshAppendscaleYinput[1000], meshAppendscaleZinput[1000];
char *scaleXoutput = "_scale_X-output-array", *scaleYoutput = "_scale_Y-output-array", *scaleZoutput = "_scale_Z-output-array";
char meshAppendscaleXoutput[1000], meshAppendscaleYoutput[1000], meshAppendscaleZoutput[1000];
char *scaleXinterpolation = "_scale_X-interpolation-array", *scaleYinterpolation = "_scale_Y-interpolation-array", *scaleZinterpolation = "_scale_Z-interpolation-array";
char meshAppendscaleXinterpolation[1000], meshAppendscaleYinterpolation[1000], meshAppendscaleZinterpolation[1000];
char *scaleXintangent = "_scale_X-intangent-array", *scaleYintangent = "_scale_Y-intangent-array", *scaleZintangent = "_scale_Z-intangent-array";
char meshAppendscaleXintangent[1000], meshAppendscaleYintangent[1000], meshAppendscaleZintangent[1000];
char *scaleXouttangent = "_scale_X-outtangent-array", *scaleYouttangent = "_scale_Y-outtangent-array", *scaleZouttangent = "_scale_Z-outtangent-array";
char meshAppendscaleXouttangent[1000], meshAppendscaleYouttangent[1000], meshAppendscaleZouttangent[1000];

//////////////////////////////////////////////////////////////////////////////////////////////////////

void loadmyDAE(
	const char * pFilestr,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec3> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<unsigned short> & out_indices
	)
{
	dObj.newVecArray = 0;
	dObj.verticesfound = 0, dObj.normalsfound = 0, dObj.uvmapfound = 0, dObj.colorsfound = 0, dObj.indicesfound = 0, dObj.matrixtransformfound = 0;
	dObj.verticescount = 0, dObj.normalscount = 0, dObj.uvmapscount = 0, dObj.colorscount = 0, dObj.indicescount = 0, dObj.matrixtransformcount = 0;

	dObj.xInputCount = 0;
	dObj.yInputCount = 0;
	dObj.zInputCount = 0;


	dObj.initialCount = dObj.meshCount;
	dObj.limitOne = 0;
	dObj.meshSkip = 0;
	

	//dObj.meshLock = 0;//TEST
	dObj.meshIndicesIncrement = 0;//TEST
	dObj.meshTransform = 0;//TEST
	//dObj.meshVBO = 0;//TEST
	dObj.testMeshCount = 0;//TEST


	//TEST CLEAR APPEND STRING
	//int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//memset(array, 0, sizeof(array));
	memset(meshAppendPositions, 0, sizeof(meshAppendPositions));//meshAppendPositions
	memset(meshAppendNormals, 0, sizeof(meshAppendNormals));//meshAppendNormals
	memset(meshAppendMap0, 0, sizeof(meshAppendMap0));//meshAppendMap0
	memset(meshAppendColors, 0, sizeof(meshAppendColors));//meshAppendColors

	if(dObj.meshVBOi == 0)
	{
		memset(storedMesh1DoubleArray, 0, sizeof(storedMesh1DoubleArray));//storedMesh1DoubleArray
		memset(storedMesh2DoubleArray, 0, sizeof(storedMesh2DoubleArray));//storedMesh2DoubleArray
		dObj.meshLock = 0;
		printf("RESET MEMORY\n");
	}

	for(int j = 0; j < ARRAYCOUNT; j++)
	{
		//X
		dObj.storedXInput[j] = 0,
			dObj.storedXOutput[j] = 0,
			dObj.storedXInTangent[j] = 0,
			dObj.storedXOutTangent[j] = 0;

		dObj.storedXRotEulerInput[j] = 0,
			dObj.storedXRotEulerOutput[j] = 0,
			dObj.storedXRotEulerInTangent[j] = 0,
			dObj.storedXRotEulerOutTangent[j] = 0;

		dObj.storedXScaleInput[j] = 0,
			dObj.storedXScaleOutput[j] = 0,
			dObj.storedXScaleInTangent[j] = 0,
			dObj.storedXScaleOutTangent[j] = 0;
		
		//Y
		dObj.storedYInput[j] = 0,
			dObj.storedYOutput[j] = 0,
			dObj.storedYInTangent[j] = 0,
			dObj.storedYOutTangent[j] = 0;

		dObj.storedYRotEulerInput[j] = 0,
			dObj.storedYRotEulerOutput[j] = 0,
			dObj.storedYRotEulerInTangent[j] = 0,
			dObj.storedYRotEulerOutTangent[j] = 0;

		dObj.storedYScaleInput[j] = 0,
			dObj.storedYScaleOutput[j] = 0,
			dObj.storedYScaleInTangent[j] = 0,
			dObj.storedYScaleOutTangent[j] = 0;
		
		//Z
		dObj.storedZInput[j] = 0,
			dObj.storedZOutput[j] = 0,
			dObj.storedZInTangent[j] = 0,
			dObj.storedZOutTangent[j] = 0;

		dObj.storedZRotEulerInput[j] = 0,
			dObj.storedZRotEulerOutput[j] = 0,
			dObj.storedZRotEulerInTangent[j] = 0,
			dObj.storedZRotEulerOutTangent[j] = 0;

		dObj.storedZScaleInput[j] = 0,
			dObj.storedZScaleOutput[j] = 0,
			dObj.storedZScaleInTangent[j] = 0,
			dObj.storedZScaleOutTangent[j] = 0;
	}


	htmlDocPtr doc;
	xmlNode *roo_element = NULL;

	//FILE * pFile;
	//pFile = fopen("test.dae","r");
	//const char*fname = "test.dae";
	//doc = htmlReadFile(argv[1], NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	doc = htmlReadFile(pFilestr, NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	if(doc == NULL)
	{
		fprintf(stderr, "Document not parsed successfully.\n");
		//return 0;
	}
	roo_element = xmlDocGetRootElement(doc);
	if(roo_element == NULL)
	{
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		//return 0;
	}
	printf("Root Node is %s\n", roo_element->name);
	traverse_dom_trees(roo_element);

	xmlFreeDoc(doc);   //free document
	xmlCleanupParser();//free globals


	//printf("PUSHING VALUES: %d\n", dObj.meshCount);
	
	//int *vertindices = new int[indicescount];
	//int *normindices = new int[indicescount];
	//int *uvindices = new int[indicescount];
	for(int i = 0; i <= dObj.indicescount/3; i++)
	{
		dObj.vertindices[i] = dObj.intarray[i*3+0];
		dObj.normindices[i] = dObj.intarray[i*3+1];
		dObj.uvindices[i] = dObj.intarray[i*3+2];

		//printf("%d VertI %d: %d\n", i, indicescount/3, vertindices[i]);
		//printf("%d NormI %d: %d\n", i, indicescount/3, normindices[i]);
		//printf("%d UvI %d: %d\n", i, indicescount/3, uvindices[i]);
	}
	//std::vector<glm::vec3> vectorvertices[10];
	//meshvertices = new float[verticescount];
	for(int ii = 0; ii <= dObj.verticescount/3; ii++)
	{
		//dObj.meshvertices[ii] = dObj.storedvertices[ii];
		//printf("MeshV i: %d - %d: %.7f\n", ii, verticescount, meshvertices[ii]);

		glm::vec3 tempvertex;
		tempvertex.x = dObj.storedvertices[ii*3+0];
		tempvertex.y = dObj.storedvertices[ii*3+1];
		tempvertex.z = dObj.storedvertices[ii*3+2];
		//printf("tempVERTS X: %f Y: %f Z: %f\n", tempvertex.x, tempvertex.y, tempvertex.z);

		temp_vertices.push_back(tempvertex);
		//out_vertices.push_back(tempvertex);
	}


	//DO UV OR COLOR CHECK HERE
	if(meshcolor == 1)
	{
		//printf("COLORS: %d\n", dObj.colorscount);
		for(int ii = 0; ii <= dObj.colorscount/3; ii++)
		{
			//dObj.meshcolors[ii] = dObj.storedcolors[ii];
			//printf("MeshU %d: %.7f\n", uvmapscount, meshuvmaps[ii]);
			glm::vec3 tempcolors;
			tempcolors.x = dObj.storedcolors[ii*3+0];
			tempcolors.y = dObj.storedcolors[ii*3+1];
			tempcolors.z = dObj.storedcolors[ii*3+2];
			//printf("tempColor X: %f Y: %f Z: %f\n", tempcolors.x, tempcolors.y, tempcolors.z);
			temp_uvs.push_back(tempcolors);
			//out_vertices.push_back(tempUV);
		}
		//meshcolor = 0;
	}
	else if(meshuv == 1)
	{
		//printf("UVMAPS: %d\n", dObj.uvmapscount);
		//meshuvmaps = new float[uvmapscount];
		for(int ii = 0; ii <= dObj.uvmapscount/2; ii++)
		{
			//dObj.meshuvmaps[ii] = dObj.storeduvmaps[ii];
			//printf("MeshU %d: %.7f\n", uvmapscount, meshuvmaps[ii]);
			glm::vec3 tempuvmap;
			tempuvmap.x = dObj.storeduvmaps[ii*2+0];
			tempuvmap.y = dObj.storeduvmaps[ii*2+1];
			//printf("tempUV U: %f V: %f\n", tempuvmap.x, tempuvmap.y);
			temp_uvs.push_back(tempuvmap);
			//out_vertices.push_back(tempUV);
		}
		//meshuv = 0;
	}
	
	//meshnormals = new float[normalscount];
	for(int ii = 0; ii <= dObj.normalscount/3; ii++)
	{
		//vectornormals
		//dObj.meshnormals[ii] = dObj.storednormals[ii];
		//printf("MeshN %d: %.7f\n", normalscount, meshnormals[ii]);
		glm::vec3 tempnormals;
		tempnormals.x = dObj.storednormals[ii*3+0];
		tempnormals.y = dObj.storednormals[ii*3+1];
		tempnormals.z = dObj.storednormals[ii*3+2];
		//printf("tempNORMS X: %f Y: %f Z: %f\n", tempnormals.x, tempnormals.y, tempnormals.z);
		temp_normals.push_back(tempnormals);
		//out_normals.push_back(tempnormals);
	}

	for(int iii = 0; iii <= dObj.indicescount/3; iii++)
	{
		int tempLoop1 = dObj.vertindices[iii];
		int tempLoop2 = dObj.normindices[iii];
		int tempLoop3 = dObj.uvindices[iii];
		glm::vec3 outvertex = temp_vertices[tempLoop1];
		glm::vec3 outnormal = temp_normals[tempLoop2];
		glm::vec3 outuvmap = temp_uvs[tempLoop3];
		//glm::vec3 tv = temp_vertices[0];
		//printf("TEST VertIND X: %f Y: %f Z: %f\n", tv[0], tv[1], tv[2]);
		//printf("%d VINDICES x: %f y: %f z: %f\n", iii, vertindices[iii*3+0], vertindices[iii*3+1], vertindices[iii*3+2]);
		//printf("INDCOUNT: %d\n", iii);


		//printf("INDVERT: %d %d outV X: %f Y: %f Z: %f\n", iii, tempLoop1, outvertex[0], outvertex[1], outvertex[2]);
		//printf("INDNORM: %d %d outV X: %f Y: %f Z: %f\n", iii, tempLoop2, outnormal[0], outnormal[1], outnormal[2]);
		//printf("INDUV: %d %d outU X: %f V: %f\n", iii, tempLoop3, outuvmap[0], outuvmap[1]);

		out_vertices.push_back(outvertex);
		out_uvs.push_back(outuvmap);
		out_normals.push_back(outnormal);
		//temp_indicesvertices.push_back(outvertex);
		out_indices.push_back(dObj.intarray[iii]);
	}

	//for(int x1 = 0; x1 <= xInputCount;      x1++)printf("xInput: %f\n",      storedXInput[x1]);
	//for(int x2 = 0; x2 <= xOutputCount;     x2++)printf("xOutput: %f\n",     storedXOutput[x2]);
	//for(int x3 = 0; x3 <= xInTangentCount;  x3++)printf("xInTangent: %f\n",  storedXInTangent[x3]);
	//for(int x4 = 0; x4 <= xOutTangentCount; x4++)printf("xOutTangent: %f\n", storedXOutTangent[x4]);

	for(int j = 0; j < ARRAYCOUNT; j++)
	{
		dObj.vertindices[j] = 0;
		dObj.normindices[j] = 0;
		dObj.uvindices[j] = 0;
		dObj.intarray[j] = 0;
		dObj.floatarray[j] = 0;
		
		/*
		dObj.meshvertices[j] = 0;
		dObj.meshnormals[j] = 0;
		dObj.meshuvmaps[j] = 0;
		dObj.meshcolors[j] = 0;
		*/
		
		dObj.storedvertices[j] = 0;
		dObj.storednormals[j] = 0;
		dObj.storeduvmaps[j] = 0;
		dObj.storedcolors[j] = 0;

		//storedXInput[j] = 0;
		//storedXOutput[j] = 0;
		//storedXInTangent[j] = 0;
		//storedXOutTangent[j] = 0;
	}

	//delete vertindices, normindices, uvindices;
	//delete floatarray, intarray, storedvertices, storednormals, storeduvmaps;
	//delete meshvertices, meshnormals, meshuvmaps;
	temp_vertices.clear(), temp_indicesvertices.clear(), temp_uvs.clear(), temp_normals.clear();
}

void traverse_dom_trees(xmlNode*a_node)
{
	xmlNode*cur_node = NULL;
	if(NULL == a_node)
	{
		//printf("Invalid argument a_node %p\n", a_node);
		return;
	}
	for(cur_node = a_node; cur_node; cur_node = cur_node->next)
	{
		if(cur_node->type == XML_ELEMENT_NODE)
		{
			/* Check for if current node should be exclude or not */
			//EXTRAS
			//printf("EleNode type: %s\n", cur_node->name);

			if(strcmp((char*)cur_node->name, "p") == 0)
			{
				//INCREMENT AND LIMIT HERE
				//if(dObj.meshVBOi == dObj.meshIndicesIncrement)
				if(dObj.meshVBOi == dObj.meshIndicesIncrement)
				{
					//printf("meshInc1: %d meshVBOi: %d\n", dObj.meshIndicesIncrement, dObj.meshVBOi);
					printf("INDICES\n");
					dObj.indicesfound = 1;
					dObj.meshIndicesIncrement++;
				}
				else
				{
					dObj.meshIndicesIncrement++;
				}
				//printf("meshInc2: %d meshVBOi: %d\n", dObj.meshIndicesIncrement, dObj.meshVBOi);


				/*
				if(dObj.meshVBOi == 1 && dObj.meshIndicesIncrement == 0)
				{
					printf("meshInc2\n");
				}
				*/
				//printf("INDICES\n");
				//dObj.indicesfound = 1;
				//dObj.meshIndicesIncrement++;
			}

			xmlAttr* attribute = cur_node->properties;
			while(attribute)
			{
				//xmlChar* value = xmlNodeListGetString(cur_node->doc, attribute->children, 1);
				dObj.newVecArray = atoi((char*)attribute->children->content);
				//HIDE EXTRA DATA
				//printf("EleAttr: %s - Contents: %d\n", attribute->name, newarraytest);
				if(strcmp((char*)cur_node->name, "node") == 0)
				{
					//SAVE MESH NAME STRING DOUBLE ARRAY
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						//AFTER APPENDING
						for(int i = 0; i <= dObj.meshVBO; i++)
						{
							if(strcmp((char*)attribute->children->content, storedMesh1DoubleArray[i]) == 0)//if(strcmp(meshName, storedMesh1DoubleArray[i]) == 0)
							{
								//printf("Hello1 there: %s %d - %d\n", storedMesh1DoubleArray[i], i, dObj.meshVBO);
							}
							if(strcmp((char*)attribute->children->content, storedMesh1DoubleArray[i]) != 0)//if(strcmp((char*)attribute->children->content, storedMesh1DoubleArray[vboOrderCount]) != 0)
							{
								if(dObj.meshLock == 1)
								{
									//strcpy(storedMesh1DoubleArray[i], meshName);//strcpy(storedMesh1DoubleArray[vboOrderCount], meshName);
									//dObj.meshVBO++;
									//printf("Node: %s count: %d meshVBO: %d\n", storedMesh1DoubleArray[vboOrderCount], vboOrderCount, dObj.meshVBO);
									//printf("ID: %s name: %s count: %d meshVBO: %d lock: %d\n", storedMesh1DoubleArray[i], (char*)attribute->children->content, vboOrderCount, dObj.meshVBO, dObj.meshLock);
								}
								//dObj.meshLock = 2;
							}
						}
					}
				}
				
				if(strcmp((char*)cur_node->name, "matrix") == 0)
				{
					if(strcmp((char*)attribute->name, "sid") == 0)
					{
						printf("TRANSFORM1: %s test: %d - %d\n", attribute->children->content, dObj.currentMesh, dObj.meshCount);
						dObj.matrixtransformfound = 1;
					}
					/*
					else if(strcmp((char*)attribute->children->content, "transform") == 0 && dObj.matrixtransformfound == 0)
					{
						printf("TRANSFORM2: %s\n", attribute->children->content);
						dObj.matrixtransformfound = 1;
					}
					*/
				}

				//instance_geometry url
				//if(strcmp((char*)cur_node->name, "instance_geometry") == 0)printf("INSTANCE_GEOMETRY: %s\n", cur_node->name);
				//if(strcmp((char*)cur_node->name, "node") == 0)
				if(strcmp((char*)cur_node->name, "geometry") == 0)
				{
					printf("GEOMETRY OR NODE: %s\n", cur_node->name);
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						//printf("ID: %s\n", attribute->name);
						if(strcmp((char*)attribute->children->content, "Cube-mesh") == 0)//printf("CUBE MESH\n");
						if(strcmp((char*)attribute->children->content, "Cube_001-mesh") == 0)
						{
							//if(dObj.meshVBOi)
							//printf("CUBE001 MESH: %d\n", dObj.meshVBOi);
							//dObj.meshLock = 0;
							//break;
						}
						if(dObj.meshVBOi == 0)
						{
							dObj.meshIncrementCount++;
						}
						//printf("MESH NAME: %s\n", attribute->children->content);
						strcpy(meshName, (char*)attribute->children->content);
						printf("MESH NAME: %s meshIncrement: %d meshIncrementCount: %d\n", meshName, dObj.meshIncrement, dObj.meshIncrementCount);
						//if(dObj.meshVBO == dObj.meshLock)
						//printf("TESTVALUES: %d - %d\n", dObj.meshVBO, dObj.currentMesh);
						//if(dObj.meshVBO == dObj.currentMesh)dObj.meshLock = 0;
						
						for(int i = 0; i <= dObj.meshVBOi; i++)
						{
							//printf("meshVBOi: %d\n", i);
							if(strcmp((char*)attribute->children->content, storedMesh1DoubleArray[i]) == 0)
							{
								printf("TEST1: %d str: %s\n", i, storedMesh1DoubleArray[i]);
								//if(i == dObj.meshVBO)dObj.meshLock = 0;
								dObj.currentMesh++;
							}
							else if(strcmp((char*)attribute->children->content, storedMesh1DoubleArray[i]) != 0)
							{
								printf("TEST2: %d str1: %s str2: %s meshCount: %d meshVBO: %d vboI: %d\n", i, (char*)attribute->children->content, storedMesh1DoubleArray[i], dObj.meshCount, dObj.meshVBO, dObj.meshVBOi);
								
								//if(dObj.currentMesh == dObj.meshVBOi && i == dObj.currentMesh)
								//if(dObj.meshVBO == dObj.meshVBOi)
								//if(i == dObj.meshVBO && i == dObj.meshVBOi)
								if(i == dObj.meshIncrement)
								{
									printf("APPENDING1: %d - %d\n", dObj.currentMesh, dObj.meshCount);
									strcpy(storedMesh1DoubleArray[i], meshName);//strcpy(storedMesh1DoubleArray[dObj.meshVBO], meshName);
									printf("storedMesh1: %s\n", storedMesh1DoubleArray[i]);//printf("storedMesh1: %s\n", storedMesh1DoubleArray[dObj.meshCount])
									//APPEND POS
									strcpy(meshAppendPositions, meshName);
									strncat(meshAppendPositions, meshPositions, strlen(meshPositions));
									//APPEND NORMALS
									strcpy(meshAppendNormals, meshName);
									strncat(meshAppendNormals, meshNormals, strlen(meshNormals));
									//APPEND UVS
									strcpy(meshAppendMap0, meshName);
									strncat(meshAppendMap0, meshMap0, strlen(meshMap0));
									//APPEND COLORS
									strcpy(meshAppendColors, meshName);
									strncat(meshAppendColors, meshColors, strlen(meshColors));
									printf("APPENDPOS: %s\nAPPENDNORMALS: %s\nAPPENDUVS: %s\nAPPENDCOLORS: %s\n", meshAppendPositions, meshAppendNormals, meshAppendMap0, meshAppendColors);
									dObj.meshLock = 1;
									printf("mVBO1: %d i: %d mInc: %d mIncCount: %d\n", dObj.meshVBO, i, dObj.meshIncrement, dObj.meshIncrementCount);
									//if(i == dObj.meshIncrement)
									
									/*
									if(i == dObj.meshIncrementCount)
									{
										dObj.meshVBO--;
										printf("mVBO4: %d i: %d mInc: %d mIncCount: %d\n", dObj.meshVBO, i, dObj.meshIncrement, dObj.meshIncrementCount);
									}
									*/
									//dObj.meshVBO++;
								}
								else
								{
									if(i < dObj.meshIncrementCount)
									{
										printf("mVBO2: %d i: %d mInc: %d mIncCount: %d\n", dObj.meshVBO, i, dObj.meshIncrement, dObj.meshIncrementCount);
										//if(dObj.meshVBO == dObj.meshIncrementCount - 1)
										dObj.meshVBO++;
										printf("mVBO3: %d i: %d mInc: %d mIncCount: %d\n", dObj.meshVBO, i, dObj.meshIncrement, dObj.meshIncrementCount);
										//if(i != 0 && dObj.meshVBO == dObj.meshIncrementCount)
										if(dObj.meshVBO == dObj.meshIncrementCount)
										{
											printf("meshVBO--\n");
											dObj.meshVBO--;
										}
									}									
									//dObj.meshVBO++;
									//printf("mVBO: %d mLock: %d\n", dObj.meshVBO, dObj.meshLock);
								}
							}
						}
						
						//if(dObj.meshCount != 0 && strcmp(storedMeshDoubleArray[dObj.meshCount], storedMeshDoubleArray[i]) == 0)
						//if(strcmp(storedMeshDoubleArray[dObj.meshCount], storedMeshDoubleArray[i]) == 0)
						//if(dObj.meshCount != 0)
						//else if(dObj.meshCount == 0)
					}
					//ACCEPT ONE ONLY
					if(strcmp((char*)attribute->name, "name") == 0)
					{
						//printf("TESTNAME: %s\n", attribute->children->content);
						strcpy(meshName, (char*)attribute->children->content);
						printf("TESTNAME: %s\n", meshName);
						//for(int i = 0; i <= dObj.meshVBO; i++)
						for(int i = 0; i <= dObj.meshVBOi; i++)
						{
							if(strcmp(meshName, storedMesh2DoubleArray[i]) == 0)
							{
								//printf("Hello2 there: %s %d - %d\n", storedMesh2DoubleArray[i], i, dObj.meshVBO);
								//printf("Hello2 there: %s %d - %d\n", storedMesh2DoubleArray[i], i, dObj.meshVBOi);
							}
							if(strcmp((char*)attribute->children->content, storedMesh2DoubleArray[i]) != 0)
							{
								if(dObj.meshLock == 0)
								{
									strcpy(storedMesh2DoubleArray[i], meshName);
									//printf("Hello3 there: %s %d - %d\n", storedMesh2DoubleArray[i], i, dObj.meshVBOi);
									//dObj.meshVBO++;
								}
								//dObj.meshLock = 1;
								//printf("Node: %s count: %d meshVBO: %d\n", storedMesh2DoubleArray[vboOrderCount], vboOrderCount, dObj.meshVBO);
								//printf("Mesh: %s name: %s count: %d meshVBO: %d lock: %d\n", storedMesh2DoubleArray[i], (char*)attribute->children->content, vboOrderCount, dObj.meshVBO, dObj.meshLock);
							}
						}
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//if(dObj.meshVBO == 0)
						//if(dObj.meshLock == 0)
						//{
						//if(dObj.meshVBOi == 0 || dObj.meshVBOi < dObj.meshVBO)
						//if(dObj.currentMesh == dObj.meshVBOi)
						//if(dObj.meshCount == dObj.meshVBO)
						//if(dObj.meshLock == 1 && dObj.meshVBO != dObj.meshCount)
						if(dObj.meshLock == 1)
						{
							printf("APPENDING2: %d - %d - %d\n", dObj.currentMesh, dObj.meshVBOi, dObj.meshCount);
							//APPEND LOCATION INPUT
							strcpy(meshAppendlocationXinput, meshName);strncat(meshAppendlocationXinput, locationXinput, strlen(locationXinput));//X
							strcpy(meshAppendlocationYinput, meshName);strncat(meshAppendlocationYinput, locationYinput, strlen(locationYinput));//Y
							strcpy(meshAppendlocationZinput, meshName);strncat(meshAppendlocationZinput, locationZinput, strlen(locationZinput));//Z
							//APPEND LOCATION OUTPUT
							strcpy(meshAppendlocationXoutput, meshName);strncat(meshAppendlocationXoutput, locationXoutput, strlen(locationXoutput));//X
							strcpy(meshAppendlocationYoutput, meshName);strncat(meshAppendlocationYoutput, locationYoutput, strlen(locationYoutput));//Y
							strcpy(meshAppendlocationZoutput, meshName);strncat(meshAppendlocationZoutput, locationZoutput, strlen(locationZoutput));//Z
							//APPEND LOCATION INTERPOLATION
							strcpy(meshAppendlocationXinterpolation, meshName);strncat(meshAppendlocationXinterpolation, locationXinterpolation, strlen(locationXinterpolation));//X
							strcpy(meshAppendlocationYinterpolation, meshName);strncat(meshAppendlocationYinterpolation, locationYinterpolation, strlen(locationYinterpolation));//Y
							strcpy(meshAppendlocationZinterpolation, meshName);strncat(meshAppendlocationZinterpolation, locationZinterpolation, strlen(locationZinterpolation));//Z
							//APPEND LOCATION INTANGENT
							strcpy(meshAppendlocationXintangent, meshName);strncat(meshAppendlocationXintangent, locationXintangent, strlen(locationXintangent));//X
							strcpy(meshAppendlocationYintangent, meshName);strncat(meshAppendlocationYintangent, locationYintangent, strlen(locationYintangent));//Y
							strcpy(meshAppendlocationZintangent, meshName);strncat(meshAppendlocationZintangent, locationZintangent, strlen(locationZintangent));//Z
							//APPEND LOCATION OUTTANGENT
							strcpy(meshAppendlocationXouttangent, meshName);strncat(meshAppendlocationXouttangent, locationXouttangent, strlen(locationXouttangent));//X
							strcpy(meshAppendlocationYouttangent, meshName);strncat(meshAppendlocationYouttangent, locationYouttangent, strlen(locationYouttangent));//Y
							strcpy(meshAppendlocationZouttangent, meshName);strncat(meshAppendlocationZouttangent, locationZouttangent, strlen(locationZouttangent));//Z
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							//APPEND ROTATION EULER INPUT
							strcpy(meshAppendrotationeulerXinput, meshName);strncat(meshAppendrotationeulerXinput, rotationeulerXinput, strlen(rotationeulerXinput));//X
							strcpy(meshAppendrotationeulerYinput, meshName);strncat(meshAppendrotationeulerYinput, rotationeulerYinput, strlen(rotationeulerYinput));//Y
							strcpy(meshAppendrotationeulerZinput, meshName);strncat(meshAppendrotationeulerZinput, rotationeulerZinput, strlen(rotationeulerZinput));//Z
							//APPEND ROTATION EULER OUTPUT
							strcpy(meshAppendrotationeulerXoutput, meshName);strncat(meshAppendrotationeulerXoutput, rotationeulerXoutput, strlen(rotationeulerXoutput));//X
							strcpy(meshAppendrotationeulerYoutput, meshName);strncat(meshAppendrotationeulerYoutput, rotationeulerYoutput, strlen(rotationeulerYoutput));//Y
							strcpy(meshAppendrotationeulerZoutput, meshName);strncat(meshAppendrotationeulerZoutput, rotationeulerZoutput, strlen(rotationeulerZoutput));//Z
							//APPEND ROTATION EULER INTERPOLATION
							strcpy(meshAppendrotationeulerXinterpolation, meshName);strncat(meshAppendrotationeulerXinterpolation, rotationeulerXinterpolation, strlen(rotationeulerXinterpolation));//X
							strcpy(meshAppendrotationeulerYinterpolation, meshName);strncat(meshAppendrotationeulerYinterpolation, rotationeulerYinterpolation, strlen(rotationeulerYinterpolation));//Y
							strcpy(meshAppendrotationeulerZinterpolation, meshName);strncat(meshAppendrotationeulerZinterpolation, rotationeulerZinterpolation, strlen(rotationeulerZinterpolation));//Z
							//APPEND ROTATION EULER INTANGENT
							strcpy(meshAppendrotationeulerXintangent, meshName);strncat(meshAppendrotationeulerXintangent, rotationeulerXintangent, strlen(rotationeulerXintangent));//X
							strcpy(meshAppendrotationeulerYintangent, meshName);strncat(meshAppendrotationeulerYintangent, rotationeulerYintangent, strlen(rotationeulerYintangent));//Y
							strcpy(meshAppendrotationeulerZintangent, meshName);strncat(meshAppendrotationeulerZintangent, rotationeulerZintangent, strlen(rotationeulerZintangent));//Z
							//APPEND ROTATION EULER OUTTANGENT
							strcpy(meshAppendrotationeulerXouttangent, meshName);strncat(meshAppendrotationeulerXouttangent, rotationeulerXouttangent, strlen(rotationeulerXouttangent));//X
							strcpy(meshAppendrotationeulerYouttangent, meshName);strncat(meshAppendrotationeulerYouttangent, rotationeulerYouttangent, strlen(rotationeulerYouttangent));//Y
							strcpy(meshAppendrotationeulerZouttangent, meshName);strncat(meshAppendrotationeulerZouttangent, rotationeulerZouttangent, strlen(rotationeulerZouttangent));//Z
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							//APPEND SCALE INPUT
							strcpy(meshAppendscaleXinput, meshName);strncat(meshAppendscaleXinput, scaleXinput, strlen(scaleXinput));//X
							strcpy(meshAppendscaleYinput, meshName);strncat(meshAppendscaleYinput, scaleYinput, strlen(scaleYinput));//Y
							strcpy(meshAppendscaleZinput, meshName);strncat(meshAppendscaleZinput, scaleZinput, strlen(scaleZinput));//Z
							//APPEND SCALE OUTPUT
							strcpy(meshAppendscaleXoutput, meshName);strncat(meshAppendscaleXoutput, scaleXoutput, strlen(scaleXoutput));//X
							strcpy(meshAppendscaleYoutput, meshName);strncat(meshAppendscaleYoutput, scaleYoutput, strlen(scaleYoutput));//Y
							strcpy(meshAppendscaleZoutput, meshName);strncat(meshAppendscaleZoutput, scaleZoutput, strlen(scaleZoutput));//Z
							//APPEND SCALE INTERPOLATION
							strcpy(meshAppendscaleXinterpolation, meshName);strncat(meshAppendscaleXinterpolation, scaleXinterpolation, strlen(scaleXinterpolation));//X
							strcpy(meshAppendscaleYinterpolation, meshName);strncat(meshAppendscaleYinterpolation, scaleYinterpolation, strlen(scaleYinterpolation));//Y
							strcpy(meshAppendscaleZinterpolation, meshName);strncat(meshAppendscaleZinterpolation, scaleZinterpolation, strlen(scaleZinterpolation));//Z
							//APPEND SCALE INTANGENT
							strcpy(meshAppendscaleXintangent, meshName);strncat(meshAppendscaleXintangent, scaleXintangent, strlen(scaleXintangent));//X
							strcpy(meshAppendscaleYintangent, meshName);strncat(meshAppendscaleYintangent, scaleYintangent, strlen(scaleYintangent));//Y
							strcpy(meshAppendscaleZintangent, meshName);strncat(meshAppendscaleZintangent, scaleZintangent, strlen(scaleZintangent));//Z
							//APPEND SCALE OUTTANGENT
							strcpy(meshAppendscaleXouttangent, meshName);strncat(meshAppendscaleXouttangent, scaleXouttangent, strlen(scaleXouttangent));//X
							strcpy(meshAppendscaleYouttangent, meshName);strncat(meshAppendscaleYouttangent, scaleYouttangent, strlen(scaleYouttangent));//Y
							strcpy(meshAppendscaleZouttangent, meshName);strncat(meshAppendscaleZouttangent, scaleZouttangent, strlen(scaleZouttangent));//Z
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							//TEST
							dObj.testMeshCount += 1;
							//printf("testMeshCount: %d\n", dObj.testMeshCount);
							//SAVE NAME TO ARRAY TO APPEND
							//LIMIT TO ONE
							//if(meshCount == initialCount) {
							dObj.meshSkip = 0;
							//dObj.meshSkip += dObj.meshCount;
							//dObj.meshSkip *= 49;//dObj.meshSkip += 1;
							dObj.meshCount += 1;
							dObj.meshLock = 0;
							//dObj.meshVBO++;//TEST
						}
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//printf("MESHUP: %d INITIAL: %d MESHSKIP: %d\n", dObj.meshCount, dObj.initialCount, dObj.meshSkip);
						//}
						//if(dObj.meshIncrement < dObj.meshIncrementCount)
						dObj.meshIncrement++;
						//dObj.meshIncrementCount = dObj.meshIncrement;
						printf("TESTINCREMENT: %d - %d mVBO: %d\n", dObj.meshIncrement, dObj.meshIncrementCount, dObj.meshVBO);
					}
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-positions-array") == 0)
				if(strcmp((char*)attribute->children->content, meshAppendPositions) == 0 && dObj.verticesfound == 0)
				{
					dObj.verticesfound = 1;
					printf("FOUND: %s\n", meshAppendPositions);
				}
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-normals-array") == 0)
				if(strcmp((char*)attribute->children->content, meshAppendNormals) == 0 && dObj.normalsfound == 0)
				{
					dObj.normalsfound = 1;
					printf("FOUND: %s\n", meshAppendNormals);
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-map-0-array") == 0)
				if(strcmp((char*)attribute->children->content, meshAppendMap0) == 0 && dObj.uvmapfound == 0)
				{
					dObj.uvmapfound = 1;
					printf("FOUND: %s\n", meshAppendMap0);
					meshuv = 1;
				}
				if(strcmp((char*)attribute->children->content, meshAppendColors) == 0 && dObj.colorsfound == 0)
				{
					dObj.colorsfound = 1;
					printf("FOUND: %s\n", meshAppendColors);
					meshcolor = 1;
				}
				//char *meshColors = "-mesh-colors-Col-array";
				//char meshAppendColors[1000];
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(strcmp((char*)cur_node->name, "float_array") == 0)
				{
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						if(strcmp((char*)attribute->children->content, meshAppendlocationXinput) == 0 && dObj.xInputFound == 0)//"Cube_location_X-input-array"//meshAppendlocationXinput
						{
							dObj.xInputFound = 1;
							printf("FOUND: %s\n", meshAppendlocationXinput);//printf("FOUND: Cube_location_X-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationXoutput) == 0 && dObj.xOutputFound == 0)//"Cube_location_X-output-array"//meshAppendlocationXoutput
						{
							dObj.xOutputFound = 1;
							printf("FOUND: %s\n", meshAppendlocationXoutput);//printf("FOUND: Cube_location_X-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationXintangent) == 0 && dObj.xInTangentFound == 0)//"Cube_location_X-intangent-array"//meshAppendlocationXintangent
						{
							dObj.xInTangentFound = 1;
							printf("FOUND: %s\n", meshAppendlocationXintangent);//printf("FOUND: Cube_location_X-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationXouttangent) == 0 && dObj.xOutTangentFound == 0)//"Cube_location_X-outtangent-array"//meshAppendlocationXouttangent
						{
							dObj.xOutTangentFound = 1;
							printf("FOUND: %s\n", meshAppendlocationXouttangent);//printf("FOUND: Cube_location_X-outtangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationYinput) == 0 && dObj.yInputFound == 0)//"Cube_location_Y-input-array"//meshAppendlocationYinput
						{
							dObj.yInputFound = 1;
							printf("FOUND: %s\n", meshAppendlocationYinput);//printf("FOUND: Cube_location_Y-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationYoutput) == 0 && dObj.yOutputFound == 0)//"Cube_location_Y-output-array"//meshAppendlocationYoutput
						{
							dObj.yOutputFound = 1;
							printf("FOUND: %s\n", meshAppendlocationYoutput);//printf("FOUND: Cube_location_Y-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationYintangent) == 0 && dObj.yInTangentFound == 0)//"Cube_location_Y-intangent-array"//meshAppendlocationYintangent
						{
							dObj.yInTangentFound = 1;
							printf("FOUND: %s\n", meshAppendlocationYintangent);//printf("FOUND: Cube_location_Y-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationYouttangent) == 0 && dObj.yOutTangentFound == 0)//"Cube_location_Y-outtangent-array"//meshAppendlocationYouttangent
						{
							dObj.yOutTangentFound = 1;
							printf("FOUND: %s\n", meshAppendlocationYouttangent);//printf("FOUND: Cube_location_Y-outtangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationZinput) == 0 && dObj.zInputFound == 0)//"Cube_location_Z-input-array"//meshAppendlocationZinput
						{
							dObj.zInputFound = 1;
							printf("FOUND: %s\n", meshAppendlocationZinput);//printf("FOUND: Cube_location_Z-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationZoutput) == 0 && dObj.zOutputFound == 0)//"Cube_location_Z-output-array"//meshAppendlocationZoutput
						{
							dObj.zOutputFound = 1;
							printf("FOUND: %s\n", meshAppendlocationZoutput);//printf("FOUND: Cube_location_Z-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationZintangent) == 0 && dObj.zInTangentFound == 0)//"Cube_location_Z-intangent-array"//meshAppendlocationZintangent
						{
							dObj.zInTangentFound = 1;
							printf("FOUND: %s\n", meshAppendlocationZintangent);//printf("FOUND: Cube_location_Z-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationZouttangent) == 0 && dObj.zOutTangentFound == 0)//"Cube_location_Z-outtangent-array"//meshAppendlocationZouttangent
						{
							dObj.zOutTangentFound = 1;
							printf("FOUND: %s\n", meshAppendlocationZouttangent);//printf("FOUND: Cube_location_Z-outtangent-array\n");
						}
						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerXinput) == 0 && dObj.xRotEulerInputFound == 0)//"Cube_rotation_euler_X-input-array"//meshAppendrotationeulerXinput
						{
							dObj.xRotEulerInputFound = 1;
							printf("FOUND: Cube_rotation_euler_X-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerXoutput) == 0 && dObj.xRotEulerOutputFound == 0)//"Cube_rotation_euler_X-output-array"//meshAppendrotationeulerXoutput
						{
							dObj.xRotEulerOutputFound = 1;
							printf("FOUND: Cube_rotation_euler_X-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerXintangent) == 0 && dObj.xRotEulerInTangentFound == 0)//"Cube_rotation_euler_X-intangent-array"//meshAppendrotationeulerXintangent
						{
							dObj.xRotEulerInTangentFound = 1;
							printf("FOUND: Cube_rotation_euler_X-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerXouttangent) == 0 && dObj.xRotEulerOutTangentFound == 0)//"Cube_rotation_euler_X-outtangent-array"//meshAppendrotationeulerXouttangent
						{
							dObj.xRotEulerOutTangentFound = 1;
							printf("FOUND: Cube_rotation_euler_X-outtangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerYinput) == 0 && dObj.yRotEulerInputFound == 0)//"Cube_rotation_euler_Y-input-array"//meshAppendrotationeulerYinput
						{
							dObj.yRotEulerInputFound = 1;
							printf("FOUND: Cube_location_Y-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerYoutput) == 0 && dObj.yRotEulerOutputFound == 0)//"Cube_rotation_euler_Y-output-array"//meshAppendrotationeulerYoutput
						{
							dObj.yRotEulerOutputFound = 1;
							printf("FOUND: Cube_location_Y-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerYintangent) == 0 && dObj.yRotEulerInTangentFound == 0)//"Cube_rotation_euler_Y-intangent-array"//meshAppendrotationeulerYintangent
						{
							dObj.yRotEulerInTangentFound = 1;
							printf("FOUND: Cube_location_Y-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerYouttangent) == 0 && dObj.yRotEulerOutTangentFound == 0)//"Cube_rotation_euler_Y-outtangent-array"//meshAppendrotationeulerYouttangent
						{
							dObj.yRotEulerOutTangentFound = 1;
							printf("FOUND: Cube_location_Y-outtangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerZinput) == 0 && dObj.zRotEulerInputFound == 0)//"Cube_rotation_euler_Z-input-array"//meshAppendrotationeulerZinput
						{
							dObj.zRotEulerInputFound = 1;
							printf("FOUND: Cube_rotation_euler_Z-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerZoutput) == 0 && dObj.zRotEulerOutputFound == 0)//"Cube_rotation_euler_Z-output-array"//meshAppendrotationeulerZoutput
						{
							dObj.zRotEulerOutputFound = 1;
							printf("FOUND: Cube_rotation_euler_Z-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerZintangent) == 0 && dObj.zRotEulerInTangentFound == 0)//"Cube_rotation_euler_Z-intangent-array"//meshAppendrotationeulerZintangent
						{
							dObj.zRotEulerInTangentFound = 1;
							printf("FOUND: Cube_rotation_euler_Z-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerZouttangent) == 0 && dObj.zRotEulerOutTangentFound == 0)//"Cube_rotation_euler_Z-outtangent-array"//meshAppendrotationeulerZouttangent
						{
							dObj.zRotEulerOutTangentFound = 1;
							printf("FOUND: Cube_rotation_euler_Z-outtangent-array\n");
						}
						////////////////////////////////////////////////////////////////////////////////
						if(strcmp((char*)attribute->children->content, meshAppendscaleXinput) == 0 && dObj.xScaleInputFound == 0)//"Cube_scale_X-input-array"//meshAppendscaleXinput
						{
							dObj.xScaleInputFound = 1;
							printf("FOUND: Cube_scale_X-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleXoutput) == 0 && dObj.xScaleOutputFound == 0)//"Cube_scale_X-output-array"//meshAppendscaleXoutput
						{
							dObj.xScaleOutputFound = 1;
							printf("FOUND: Cube_scale_X-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleXintangent) == 0 && dObj.xScaleInTangentFound == 0)//"Cube_scale_X-intangent-array"//meshAppendscaleXintangent
						{
							dObj.xScaleInTangentFound = 1;
							printf("FOUND: Cube_scale_X-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleXouttangent) == 0 && dObj.xScaleOutTangentFound == 0)//"Cube_scale_X-outtangent-array"//meshAppendscaleXouttangent
						{
							dObj.xScaleOutTangentFound = 1;
							printf("FOUND: Cube_scale_X-outtangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleYinput) == 0 && dObj.yScaleInputFound == 0)//"Cube_scale_Y-input-array"//meshAppendscaleYinput
						{
							dObj.yScaleInputFound = 1;
							printf("FOUND: Cube_scale_Y-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleYoutput) == 0 && dObj.yScaleOutputFound == 0)//"Cube_scale_Y-output-array"//meshAppendscaleYoutput
						{
							dObj.yScaleOutputFound = 1;
							printf("FOUND: Cube_scale_Y-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleYintangent) == 0 && dObj.yScaleInTangentFound == 0)//"Cube_scale_Y-intangent-array"//meshAppendscaleYintangent
						{
							dObj.yScaleInTangentFound = 1;
							printf("FOUND: Cube_scale_Y-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleYouttangent) == 0 && dObj.yScaleOutTangentFound == 0)//"Cube_scale_Y-outtangent-array"//meshAppendscaleYouttangent
						{
							dObj.yScaleOutTangentFound = 1;
							printf("FOUND: Cube_scale_Y-outtangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleZinput) == 0 && dObj.zScaleInputFound == 0)//"Cube_scale_Z-input-array"//meshAppendscaleZinput
						{
							dObj.zScaleInputFound = 1;
							printf("FOUND: Cube_scale_Z-input-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleZoutput) == 0 && dObj.zScaleOutputFound == 0)//"Cube_scale_Z-output-array"//meshAppendscaleZoutput
						{
							dObj.zScaleOutputFound = 1;
							printf("FOUND: Cube_scale_Z-output-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleZintangent) == 0 && dObj.zScaleInTangentFound == 0)//"Cube_scale_Z-intangent-array"//meshAppendscaleZintangent
						{
							dObj.zScaleInTangentFound = 1;
							printf("FOUND: Cube_scale_Z-intangent-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendscaleZouttangent) == 0 && dObj.zScaleOutTangentFound == 0)//"Cube_scale_Z-outtangent-array"//meshAppendscaleZouttangent
						{
							dObj.zScaleOutTangentFound = 1;
							printf("FOUND: Cube_scale_Z-outtangent-array\n");
						}						
					}
				}
				if(strcmp((char*)cur_node->name, "name_array") == 0)
				{
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						if(strcmp((char*)attribute->children->content, meshAppendlocationXinterpolation) == 0 && dObj.xInterpolationFound == 0)//"Cube_location_X-interpolation-array"
						{
							dObj.xInterpolationFound = 1;
							printf("FOUND: Cube_location_X-interpolation-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationYinterpolation) == 0 && dObj.yInterpolationFound == 0)//"Cube_location_Y-interpolation-array"
						{
							dObj.yInterpolationFound = 1;
							printf("FOUND: Cube_location_Y-interpolation-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendlocationZinterpolation) == 0 && dObj.zInterpolationFound == 0)//"Cube_location_Z-interpolation-array"
						{
							dObj.zInterpolationFound = 1;
							printf("FOUND: Cube_location_Z-interpolation-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerXinterpolation) == 0 && dObj.xRotEulerInterpolationFound == 0)//"Cube_rotation_euler_X-interpolation-array"
						{
							dObj.xRotEulerInterpolationFound = 1;
							printf("FOUND: Cube_rotation_euler_X-interpolation-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerYinterpolation) == 0 && dObj.yRotEulerInterpolationFound == 0)//"Cube_rotation_euler_Y-interpolation-array"
						{
							dObj.yRotEulerInterpolationFound = 1;
							printf("FOUND: Cube_rotation_euler_Y-interpolation-array\n");
						}
						if(strcmp((char*)attribute->children->content, meshAppendrotationeulerZinterpolation) == 0 && dObj.zRotEulerInterpolationFound == 0)//"Cube_rotation_euler_Z-interpolation-array"
						{
							dObj.zRotEulerInterpolationFound = 1;
							printf("FOUND: Cube_rotation_euler_Z-interpolation-array\n");
						}
					}
					if(strcmp((char*)attribute->children->content, meshAppendscaleXinterpolation) == 0 && dObj.xScaleInterpolationFound == 0)//"Cube_scale_X-interpolation-array"
					{
						dObj.xScaleInterpolationFound = 1;
						printf("FOUND: Cube_scale_X-interpolation-array\n");
					}
					if(strcmp((char*)attribute->children->content, meshAppendscaleYinterpolation) == 0 && dObj.yScaleInterpolationFound == 0)//"Cube_scale_Y-interpolation-array"
					{
						dObj.yScaleInterpolationFound = 1;
						printf("FOUND: Cube_scale_Y-interpolation-array\n");
					}
					if(strcmp((char*)attribute->children->content, meshAppendscaleZinterpolation) == 0 && dObj.zScaleInterpolationFound == 0)//"Cube_scale_Z-interpolation-array"
					{
						dObj.zScaleInterpolationFound = 1;
						printf("FOUND: Cube_scale_Z-interpolation-array\n");
					}
				}

				/*
				if(limitOne < (meshCount * 4) && strcmp((char*)attribute->children->content, "Cube_location_X") == 0)
				{
					if(meshSkip <= limitOne)
					{
						xInputfound = 1;
						printf("FOUND: Cube_location_X\n");
					}
					limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", limitOne, (meshCount*4));
				}
				if(limitOne < (meshCount * 8) && strcmp((char*)attribute->children->content, meshAppendXOutput) == 0)
				{
					if(meshSkip <= limitOne)
					{
						xOutputfound = 1;
						printf("FOUND: %s\n", meshAppendXOutput);
					}
					limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", limitOne, (meshCount*3));
				}
				if(limitOne < (meshCount * 8) && strcmp((char*)attribute->children->content, meshAppendXInterpolation) == 0)
				{
					if(meshSkip <= limitOne)
					{
						xInterpolationfound = 1;
						printf("FOUND: %s\n", meshAppendXInterpolation);
					}
					limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", limitOne, (meshCount*3));
				}
				if(limitOne < (meshCount * 8) && strcmp((char*)attribute->children->content, meshAppendXIntangent) == 0)
				{
					if(meshSkip <= limitOne)
					{
						xIntangentfound = 1;
						printf("FOUND: %s\n", meshAppendXIntangent);
					}
					limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", limitOne, (meshCount*3));
				}
				if(limitOne < (meshCount * 8) && strcmp((char*)attribute->children->content, meshAppendXOuttangent) == 0)
				{
					if(meshSkip <= limitOne)
					{
						xOuttangentfound = 1;
						printf("FOUND: %s\n", meshAppendXOuttangent);
					}
					limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", limitOne, (meshCount*3));
				}
				*/
				
				//xmlFree(value);//do something with value
				attribute = attribute->next;
			}
		}

		if(cur_node->type == XML_TEXT_NODE)
		{
			/* Process here text node, It is available in cpStr :TODO: */
			//char *newChar;
			//char *stringarray;
			char newChar[255];
			char stringarray[255];
			int slen = strlen((char*)cur_node->content);
			//printf("TxtNode Content: %s - Content Length %d\n", (char*)cur_node->content, slen);//HIDE
			if(dObj.matrixtransformfound)// && dObj.meshTransform == dObj.currentMesh)
			{
				int lastLoop2 = 0;
				int loopCount2 = 0;
				int loopIncrement2 = 0;
				int slen2 = strlen((char*)cur_node->content);
				std::string transformMatrixArray;
				transformMatrixArray.reserve(100000);
				if(dObj.meshTransform == dObj.currentMesh)
				{
					printf("LIST: %s mesh: %d - %d vboNum: %d total: %d\n", (char*)cur_node->content, dObj.meshTransform, dObj.currentMesh, dObj.vboNumber, dObj.vboNumber + dObj.currentMesh);
					for(int i = 0; i <= slen2; i++)
					{
						transformMatrixArray[i] = (char)cur_node->content[i];
						//printf("i: %d Char: %c\n", i, transformMatrixArray[i]);
						if((int)cur_node->content[i] == 32 || (char)cur_node->content[i] == '\0')
						{
							//printf("loopCount: %d SLEN2: %d / %d\n", loopCount2, i, slen2);
							int diff2 = i - lastLoop2 + 1;
							for(int ii = 1; lastLoop2 <= i; ii++ && lastLoop2++)
							{
								//newChar[ii] = transformMatrixArray[lastLoop2];
								//printf("%c\n", newChar[ii]);
							}
							for(int iii = -1; iii < diff2; iii++)
							{
								stringarray[iii] = transformMatrixArray[lastLoop2-diff2+iii];
								//printf("i: %d iii: %d STRINGARRAY: %c\n", i, iii, stringarray[iii]);
								//printf("total: %d lastLoop2: %d diff2: %d i: %d iii: %d STRINGARRAY: %c\n", lastLoop2-diff2+iii, lastLoop2, diff2, i, iii, transformMatrixArray[lastLoop2-diff2+iii]);
							}
							//dObj.storedmatrixtransform[loopCount2] = (float)atof((char*)stringarray);
							//dObj.storedmatrixtransform[dObj.meshTransform][loopIncrement2] = (float)atof((char*)stringarray);
							dObj.storedmatrixtransform[dObj.vboNumber + dObj.currentMesh][loopIncrement2] = (float)atof((char*)stringarray);
							//printf("loopInc: %d loopCount: %d storedmatrixtransform: %.7f\n", loopIncrement2, loopCount2, dObj.storedmatrixtransform[loopCount2]);
							//printf("loopInc: %d loopCount: %d storedmatrixtransform: %.7f\n", loopIncrement2, loopCount2, dObj.storedmatrixtransform[loopIncrement2]);
							//dObj.matrixtransformcount = loopCount2;
							//lastLoop2++;
							loopIncrement2++;
						}
					}
				}
				lastLoop2++;
				dObj.meshTransform++;
			}
			
			//printf("Content Length %d\n", slen);//HIDE
			xmlVectorArray *xmlVec;
			//int size = 10;
			xmlVec = new xmlVectorArray[dObj.newVecArray];
			//xmlVec[0].x = 5;

			/*
			if(indicesfound == 1)
			{
				printf("INDICES START HERE\n");
				indicesfound = 0;
			}
			*/

			if(dObj.newVecArray > 0 || dObj.indicesfound == 1)
			{
				int lastLoop = 0;
				int loopCount = 0;

				//char testarray[86000];
				//KEEP WITHIN 20000 TRIANGLES
				std::string testarray;
				testarray.reserve(10000000);


				//intarray = new int[slen];
				//floatarray = new float[slen];
				//printf("LIST: %s mesh: %d - %d\n", (char*)cur_node->content, dObj.meshTransform, dObj.currentMesh);
				for(int i = 0; i <= slen; i++)
				{
					testarray[i] = (char)cur_node->content[i];
					//printf("%c", testarray[i]);
					//printf("%c\n", (char*)cur_node->content[i]);
					if((int)cur_node->content[i] == 32 || (char)cur_node->content[i] == '\0')
					{
						//printf("loopCount: %d SLEN: %d / %d\n", loopCount, i, slen);
						//if(verticesfound == 1)
						//{
						int diff = i - lastLoop + 1;
						//newChar = new char[diff];
						//stringarray = new char[diff];

						for(int ii = 1; lastLoop <= i; ii++ && lastLoop++)
						{
							//printf("LOOP %d - %d - %d\n", lastLoop, i, diff);
							//newChar[ii] = testarray[lastLoop];
							//newChar[ii] = testarray[lastLoop];
							newChar[ii] = testarray[lastLoop];
							//printf("%c\n", newChar[ii]);
						}

						for(int iii = -1; iii < diff; iii++)
						{
							//stringarray[iii] = testarray[lastLoop-diff+iii];
							//stringarray[iii] = testarray[lastLoop-diff+iii];
							stringarray[iii] = testarray[lastLoop-diff+iii];
							//printf("STRINGARRAY: %c\n", stringarray[iii]);
							//printf("total: %d lastLoop: %d diff: %d i: %d iii: %d STRINGARRAY: %c\n", lastLoop-diff+iii, lastLoop, diff, i, iii, testarray[lastLoop-diff+iii]);
						}
						//printf("STRING RESULT: %s\n", stringarray);

						/*
						printf("SIZE: %d\n", testarray.size());
						printf("LENGTH: %d\n", testarray.length());
						printf("CAPACITY: %d\n", testarray.capacity());
						printf("MAX_SIZE: %u\n", testarray.max_size());
						*/

						//floatarray[loopCount] = atof((char*)stringarray);
						//printf("FLOATARRAY: %.7f\n", floatarray[loopCount]);

						if(dObj.verticesfound)
						{
							//printf("VERTICES\n");
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", dObj.floatarray[loopCount]);
							dObj.storedvertices[loopCount] = dObj.floatarray[loopCount];
							dObj.verticescount = loopCount;
						}
						if(dObj.normalsfound)
						{
							//printf("NORMAL\n");
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", floatarray[loopCount]);
							dObj.storednormals[loopCount] = dObj.floatarray[loopCount];
							dObj.normalscount = loopCount;
						}
						if(dObj.uvmapfound)
						{
							//printf("UVMAP\n");
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", dObj.floatarray[loopCount]);
							dObj.storeduvmaps[loopCount] = dObj.floatarray[loopCount];
							dObj.uvmapscount = loopCount;
						}
						if(dObj.colorsfound)
						{
							//printf("COLOR\n");
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", dObj.floatarray[loopCount]);
							dObj.storedcolors[loopCount] = dObj.floatarray[loopCount];
							dObj.colorscount = loopCount;
						}
						if(dObj.indicesfound)
						{
							dObj.intarray[loopCount] = atoi((char*)stringarray);
							//printf("INTARRAY: %d\n", dObj.intarray[loopCount]);
							dObj.indicescount = loopCount;
						}

						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						//XLOC
						if(dObj.xInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXInput[loopCount] = dObj.floatarray[loopCount];
							dObj.xInputCount = loopCount;
						}
						if(dObj.xOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xOutput: %d - %f\n", stuff, floatarray[loopCount]);
							dObj.storedXOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.xOutputCount = loopCount;
						}
						//COMPARE STRING THEN CHANGE TO ID NUMBER
						if(dObj.xInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedXInterpolation[loopCount] = 2;
								//printf("xInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedXInterpolation[loopCount] = 1;
								//printf("xInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedXInterpolation[loopCount] = 0;
								//printf("xInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.xInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.xInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.xInTangentCount = loopCount;
						}
						if(dObj.xOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.xOutTangentCount = loopCount;
						}

						//XROT
						if(dObj.xRotEulerInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXRotEulerInput[loopCount] = dObj.floatarray[loopCount];
							dObj.xRotEulerInputCount = loopCount;
						}
						if(dObj.xRotEulerOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXRotEulerOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.xRotEulerOutputCount = loopCount;
						}
						if(dObj.xRotEulerInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedXRotEulerInterpolation[loopCount] = 2;
								//printf("xRotEulerInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedXRotEulerInterpolation[loopCount] = 1;
								//printf("xRotEulerInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedXRotEulerInterpolation[loopCount] = 0;
								//printf("xRotEulerInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.xRotEulerInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.xRotEulerInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXRotEulerInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.xRotEulerInTangentCount = loopCount;
						}
						if(dObj.xRotEulerOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXRotEulerOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.xRotEulerOutTangentCount = loopCount;
						}

						//XSCALE
						if(dObj.xScaleInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXScaleInput[loopCount] = dObj.floatarray[loopCount];
							dObj.xScaleInputCount = loopCount;
						}
						if(dObj.xScaleOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXScaleOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.xScaleOutputCount = loopCount;
						}
						if(dObj.xScaleInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedXScaleInterpolation[loopCount] = 2;
								//printf("xScaleInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedXScaleInterpolation[loopCount] = 1;
								//printf("xScaleInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedXScaleInterpolation[loopCount] = 0;
								//printf("xScaleInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.xInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.xScaleInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXScaleInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.xScaleInTangentCount = loopCount;
						}
						if(dObj.xScaleOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("xOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedXScaleOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.xScaleOutTangentCount = loopCount;
						}

						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						//YLOC
						if(dObj.yInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYInput[loopCount] = dObj.floatarray[loopCount];
							dObj.yInputCount = loopCount;
						}
						if(dObj.yOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.yOutputCount = loopCount;
						}
						if(dObj.yInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedYInterpolation[loopCount] = 2;
								//printf("yInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedYInterpolation[loopCount] = 1;
								//printf("yInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedYInterpolation[loopCount] = 0;
								//printf("yInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.yInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.yInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.yInTangentCount = loopCount;
						}
						if(dObj.yOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.yOutTangentCount = loopCount;
						}

						//YROT
						if(dObj.yRotEulerInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYRotEulerInput[loopCount] = dObj.floatarray[loopCount];
							dObj.yRotEulerInputCount = loopCount;
						}
						if(dObj.yRotEulerOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYRotEulerOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.yRotEulerOutputCount = loopCount;
						}
						if(dObj.yRotEulerInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedYRotEulerInterpolation[loopCount] = 2;
								//printf("yRotEulerInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedYRotEulerInterpolation[loopCount] = 1;
								//printf("yRotEulerInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedYRotEulerInterpolation[loopCount] = 0;
								//printf("yRotEulerInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.yInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.yRotEulerInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYRotEulerInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.yRotEulerInTangentCount = loopCount;
						}
						if(dObj.yRotEulerOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYRotEulerOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.yRotEulerOutTangentCount = loopCount;
						}

						//YSCALE
						if(dObj.yScaleInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYScaleInput[loopCount] = dObj.floatarray[loopCount];
							dObj.yScaleInputCount = loopCount;
						}
						if(dObj.yScaleOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYScaleOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.yScaleOutputCount = loopCount;
						}
						if(dObj.yScaleInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedYScaleInterpolation[loopCount] = 2;
								//printf("yScaleInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedYScaleInterpolation[loopCount] = 1;
								//printf("yScaleInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedYScaleInterpolation[loopCount] = 0;
								//printf("yScaleInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.yInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.yScaleInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYScaleInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.yScaleInTangentCount = loopCount;
						}
						if(dObj.yScaleOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("yOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedYScaleOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.yScaleOutTangentCount = loopCount;
						}

						/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						//ZLOC
						if(dObj.zInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZInput[loopCount] = dObj.floatarray[loopCount];
							dObj.zInputCount = loopCount;
						}
						if(dObj.zOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.zOutputCount = loopCount;
						}
						if(dObj.zInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedZInterpolation[loopCount] = 2;
								//printf("zInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedZInterpolation[loopCount] = 1;
								//printf("zInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedZInterpolation[loopCount] = 0;
								//printf("zInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.yInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.zInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.zInTangentCount = loopCount;
						}
						if(dObj.zOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.zOutTangentCount = loopCount;
						}

						//ZROT
						if(dObj.zRotEulerInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZRotEulerInput[loopCount] = dObj.floatarray[loopCount];
							dObj.zRotEulerInputCount = loopCount;
						}
						if(dObj.zRotEulerOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZRotEulerOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.zRotEulerOutputCount = loopCount;
						}
						if(dObj.zRotEulerInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedZRotEulerInterpolation[loopCount] = 2;
								//printf("zRotEulerInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedZRotEulerInterpolation[loopCount] = 1;
								//printf("zRotEulerInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedZRotEulerInterpolation[loopCount] = 0;
								//printf("zRotEulerInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.yInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.zRotEulerInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZRotEulerInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.zRotEulerInTangentCount = loopCount;
						}
						if(dObj.zRotEulerOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZRotEulerOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.zRotEulerOutTangentCount = loopCount;
						}

						//ZSCALE
						if(dObj.zScaleInputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zInput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZScaleInput[loopCount] = dObj.floatarray[loopCount];
							dObj.zScaleInputCount = loopCount;
						}
						if(dObj.zScaleOutputFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zOutput: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZScaleOutput[loopCount] = dObj.floatarray[loopCount];
							dObj.zScaleOutputCount = loopCount;
						}
						if(dObj.zScaleInterpolationFound)
						{
							//CONSTANT
							if(strcmp((char*)stringarray, "STEP ") == 0 || strcmp((char*)stringarray, "STEP") == 0)
							{
								dObj.storedZScaleInterpolation[loopCount] = 2;
								//printf("zScaleInterpolation: %d STEP\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "LINEAR ") == 0 || strcmp((char*)stringarray, "LINEAR") == 0)
							{
								dObj.storedZScaleInterpolation[loopCount] = 1;
								//printf("zScaleInterpolation: %d LINEAR\n", loopCount);
							}
							else if(strcmp((char*)stringarray, "BEZIER ") == 0 || strcmp((char*)stringarray, "BEZIER") == 0)
							{
								dObj.storedZScaleInterpolation[loopCount] = 0;
								//printf("zScaleInterpolation: %d BEZIER\n", loopCount);
							}
							dObj.yInterpolationCount = loopCount;
							//printf("%s - %d\n", stringarray, loopCount);
						}
						if(dObj.zScaleInTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zInTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZScaleInTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.zScaleInTangentCount = loopCount;
						}
						if(dObj.zScaleOutTangentFound)
						{
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("zOutTangent: %d - %f\n", loopCount, floatarray[loopCount]);
							dObj.storedZScaleOutTangent[loopCount] = dObj.floatarray[loopCount];
							dObj.zScaleOutTangentCount = loopCount;
						}
						loopCount++;
					}
				}
				//if(verticesfound == 1)for(int aaa = 0; aaa < 24; aaa++)printf("aaa: %.7f\n", morearray[aaa]);
				if(dObj.verticesfound == 1)dObj.verticesfound = 0;
				if(dObj.normalsfound == 1)dObj.normalsfound = 0;
				if(dObj.uvmapfound == 1)dObj.uvmapfound = 0;
				if(dObj.colorsfound == 1)dObj.colorsfound = 0;
				if(dObj.indicesfound == 1)dObj.indicesfound = 0;
				if(dObj.matrixtransformfound == 1)dObj.matrixtransformfound = 0;

				//XLOC
				if(dObj.xInputFound == 1)dObj.xInputFound = 0;
				if(dObj.xOutputFound == 1)dObj.xOutputFound = 0;
				if(dObj.xInterpolationFound == 1)dObj.xInterpolationFound = 0;
				if(dObj.xInTangentFound == 1)dObj.xInTangentFound = 0;
				if(dObj.xOutTangentFound == 1)dObj.xOutTangentFound = 0;
				//XROT
				if(dObj.xRotEulerInputFound == 1)dObj.xRotEulerInputFound = 0;
				if(dObj.xRotEulerOutputFound == 1)dObj.xRotEulerOutputFound = 0;
				if(dObj.xRotEulerInterpolationFound == 1)dObj.xRotEulerInterpolationFound = 0;
				if(dObj.xRotEulerInTangentFound == 1)dObj.xRotEulerInTangentFound = 0;
				if(dObj.xRotEulerOutTangentFound == 1)dObj.xRotEulerOutTangentFound = 0;
				//XSCALE
				if(dObj.xScaleInputFound == 1)dObj.xScaleInputFound = 0;
				if(dObj.xScaleOutputFound == 1)dObj.xScaleOutputFound = 0;
				if(dObj.xScaleInterpolationFound == 1)dObj.xScaleInterpolationFound = 0;
				if(dObj.xScaleInTangentFound == 1)dObj.xScaleInTangentFound = 0;
				if(dObj.xScaleOutTangentFound == 1)dObj.xScaleOutTangentFound = 0;

				//YLOC
				if(dObj.yInputFound == 1)dObj.yInputFound = 0;
				if(dObj.yOutputFound == 1)dObj.yOutputFound = 0;
				if(dObj.yInterpolationFound == 1)dObj.yInterpolationFound = 0;
				if(dObj.yInTangentFound == 1)dObj.yInTangentFound = 0;
				if(dObj.yOutTangentFound == 1)dObj.yOutTangentFound = 0;
				//YROT
				if(dObj.yRotEulerInputFound == 1)dObj.yRotEulerInputFound = 0;
				if(dObj.yRotEulerOutputFound == 1)dObj.yRotEulerOutputFound = 0;
				if(dObj.yRotEulerInterpolationFound == 1)dObj.yRotEulerInterpolationFound = 0;
				if(dObj.yRotEulerInTangentFound == 1)dObj.yRotEulerInTangentFound = 0;
				if(dObj.yRotEulerOutTangentFound == 1)dObj.yRotEulerOutTangentFound = 0;
				//YSCALE
				if(dObj.yScaleInputFound == 1)dObj.yScaleInputFound = 0;
				if(dObj.yScaleOutputFound == 1)dObj.yScaleOutputFound = 0;
				if(dObj.yScaleInterpolationFound == 1)dObj.yScaleInterpolationFound = 0;
				if(dObj.yScaleInTangentFound == 1)dObj.yScaleInTangentFound = 0;
				if(dObj.yScaleOutTangentFound == 1)dObj.yScaleOutTangentFound = 0;

				//ZLOC
				if(dObj.zInputFound == 1)dObj.zInputFound = 0;
				if(dObj.zOutputFound == 1)dObj.zOutputFound = 0;
				if(dObj.zInterpolationFound == 1)dObj.zInterpolationFound = 0;
				if(dObj.zInTangentFound == 1)dObj.zInTangentFound = 0;
				if(dObj.zOutTangentFound == 1)dObj.zOutTangentFound = 0;
				//ZROT
				if(dObj.zRotEulerInputFound == 1)dObj.zRotEulerInputFound = 0;
				if(dObj.zRotEulerOutputFound == 1)dObj.zRotEulerOutputFound = 0;
				if(dObj.zRotEulerInterpolationFound == 1)dObj.zRotEulerInterpolationFound = 0;
				if(dObj.zRotEulerInTangentFound == 1)dObj.zRotEulerInTangentFound = 0;
				if(dObj.zRotEulerOutTangentFound == 1)dObj.zRotEulerOutTangentFound = 0;
				//ZSCALE
				if(dObj.zScaleInputFound == 1)dObj.zScaleInputFound = 0;
				if(dObj.zScaleOutputFound == 1)dObj.zScaleOutputFound = 0;
				if(dObj.zScaleInterpolationFound == 1)dObj.zScaleInterpolationFound = 0;
				if(dObj.zScaleInTangentFound == 1)dObj.zScaleInTangentFound = 0;
				if(dObj.zScaleOutTangentFound == 1)dObj.zScaleOutTangentFound = 0;
			}
		}
		traverse_dom_trees(cur_node->children);
	}
	//printf("END\n");
}