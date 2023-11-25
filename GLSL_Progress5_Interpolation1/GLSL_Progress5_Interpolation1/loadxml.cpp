#include "Common.h"

struct xmlVectorArray
{
	float x, y, z;
};

extern drawObjects dObj;


std::vector<glm::vec3> temp_vertices, temp_normals, temp_indicesvertices;
std::vector<glm::vec2> temp_uvs;


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


void loadmyDAE(
	const char * pFilestr,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<unsigned short> & out_indices
	)
{
	dObj.newVecArray = 0;
	dObj.verticesfound = 0, dObj.normalsfound = 0, dObj.uvmapfound = 0, dObj.indicesfound = 0;
	dObj.verticescount = 0, dObj.normalscount = 0, dObj.uvmapscount = 0, dObj.indicescount = 0;

	dObj.xInputCount = 0;
	dObj.yInputCount = 0;
	dObj.zInputCount = 0;


	dObj.initialCount = dObj.meshCount;
	dObj.limitOne = 0;
	dObj.meshSkip = 0;


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


	printf("PUSHING VALUES: %d\n", dObj.meshCount);


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
		dObj.meshvertices[ii] = dObj.storedvertices[ii];
		//printf("MeshV i: %d - %d: %.7f\n", ii, verticescount, meshvertices[ii]);

		glm::vec3 tempvertex;
		tempvertex.x = dObj.storedvertices[ii*3+0];
		tempvertex.y = dObj.storedvertices[ii*3+1];
		tempvertex.z = dObj.storedvertices[ii*3+2];
		//printf("tempVERTS X: %f Y: %f Z: %f\n", tempvertex.x, tempvertex.y, tempvertex.z);

		temp_vertices.push_back(tempvertex);
		//out_vertices.push_back(tempvertex);
	}


	//_getch();

	//meshuvmaps = new float[uvmapscount];
	for(int ii = 0; ii <= dObj.uvmapscount/2; ii++)
	{
		//vectoruvs
		dObj.meshuvmaps[ii] = dObj.storeduvmaps[ii];
		//printf("MeshU %d: %.7f\n", uvmapscount, meshuvmaps[ii]);

		glm::vec3 tempuvmap;
		tempuvmap.x = dObj.storeduvmaps[ii*2+0];
		tempuvmap.y = dObj.storeduvmaps[ii*2+1];
		//printf("tempUV U: %f V: %f\n", tempuvmap.x, tempuvmap.y);

		//glm::vec3 tempUV;
		//tempUV.x = storeduvmaps[ii*3+0];
		//tempUV.y = storeduvmaps[ii*3+1];
		//printf("tempUV U: %f V: %f\n", tempUV.x, tempUV.y);


		temp_uvs.push_back(tempuvmap);
		//out_vertices.push_back(tempUV);
	}

	//meshnormals = new float[normalscount];
	for(int ii = 0; ii <= dObj.normalscount/3; ii++)
	{
		//vectornormals
		dObj.meshnormals[ii] = dObj.storednormals[ii];
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
		glm::vec2 outuvmap = temp_uvs[tempLoop3];
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
		
		dObj.meshvertices[j] = 0;
		dObj.meshnormals[j] = 0;
		dObj.meshuvmaps[j] = 0;
		
		dObj.storedvertices[j] = 0;
		dObj.storednormals[j] = 0;
		dObj.storeduvmaps[j] = 0;

		//storedXInput[j] = 0;
		//storedXOutput[j] = 0;
		//storedXInTangent[j] = 0;
		//storedXOutTangent[j] = 0;
	}

	//_getch();
	//delete vertindices, normindices, uvindices;
	//delete floatarray, intarray, storedvertices, storednormals, storeduvmaps;
	//delete meshvertices, meshnormals, meshuvmaps;
	temp_vertices.clear(), temp_indicesvertices.clear(), temp_uvs.clear(), temp_normals.clear();
}


char meshName[1000];
char *meshPositions = "-positions-array";
char meshAppendPositions[1000];
char *meshNormals = "-normals-array";
char meshAppendNormals[1000];
char *meshMap0 = "-map-0-array";
char meshAppendMap0[1000];

/*
char *meshXInput = "_location_X";
char meshAppendXInput[1000];
char *meshYInput = "_location_Y";
char meshAppendYInput[1000];
char *meshZInput = "_location_Z";
char meshAppendZInput[1000];
*/


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
				printf("INDICES\n");
				dObj.indicesfound = 1;
			}
			
			xmlAttr* attribute = cur_node->properties;
			while(attribute)
			{
				//xmlChar* value = xmlNodeListGetString(cur_node->doc, attribute->children, 1);
				dObj.newVecArray = atoi((char*)attribute->children->content);

				//HIDE EXTRA DATA
				//printf("EleAttr: %s - Contents: %d\n", attribute->name, newarraytest);
				
				//instance_geometry url
				//if(strcmp((char*)cur_node->name, "instance_geometry") == 0)printf("INSTANCE_GEOMETRY: %s\n", cur_node->name);
				if(strcmp((char*)cur_node->name, "geometry") == 0)
				{
					printf("GEOMETRY: %s\n", cur_node->name);
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						//printf("ID: %s\n", attribute->name);
						if(strcmp((char*)attribute->children->content, "Cube-mesh") == 0)
						{
							printf("CUBE MESH\n");
						}
						//printf("MESH NAME: %s\n", attribute->children->content);
						strcpy(meshName, (char*)attribute->children->content);
						printf("MESH NAME: %s\n", meshName);
						//APPEND POS
						strcpy(meshAppendPositions, meshName);
						strncat(meshAppendPositions, meshPositions, strlen(meshPositions));
						//APPEND NORMALS
						strcpy(meshAppendNormals, meshName);
						strncat(meshAppendNormals, meshNormals, strlen(meshNormals));
						//APPEND INDICES
						strcpy(meshAppendMap0, meshName);
						strncat(meshAppendMap0, meshMap0, strlen(meshMap0));
						printf("APPENDPOS: %s\nAPPENDNORMALS: %s\nAPPENDINDICES: %s\n", meshAppendPositions, meshAppendNormals, meshAppendMap0);
					}
					//ACCEPT ONE ONLY
					if(strcmp((char*)attribute->name, "name") == 0)
					{
						printf("TESTNAME: %s\n", attribute->children->content);
						//LIMIT TO ONE
						//if(meshCount == initialCount) {
						dObj.meshSkip += dObj.meshCount;
						dObj.meshSkip *= 48;


						dObj.meshCount += 1;
						printf("MESHUP: %d INITIAL: %d MESHSKIP: %d\n", dObj.meshCount, dObj.initialCount, dObj.meshSkip);
						//}
					}
				}


				/*
				else if(strcmp((char*)cur_node->name, "animation") == 0)
				{
					//printf("CurNodeName: %s\n", cur_node->name);
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						//printf("ID: %s\n", attribute->name);
						strcpy(meshName, (char*)attribute->children->content);
						//printf("MESH NAME: %s\n", meshName);
					}
				}
				else if(strcmp((char*)cur_node->name, "float_array") == 0)
				{
					//printf("CurNodeName: %s\n", cur_node->name);
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						if(strcmp((char*)attribute->children->content, "Cube_location_X-input-array") == 0)
						{
							//printf("INPUTARR\n");
						}
					}
					if(strcmp((char*)attribute->name, "count") == 0)
					{
						//printf("count: %s\n", attribute->children->content);
					}
				}
				*/

				
				//meshSkip

				//if(strcmp((char*)attribute->children->content, "Cube-mesh-positions-array") == 0)
				if(dObj.limitOne < (dObj.meshCount * 48) && strcmp((char*)attribute->children->content, meshAppendPositions) == 0)
				{
					if(dObj.meshSkip <= dObj.limitOne)
					{
						dObj.verticesfound = 1;
						printf("FOUND: %s\n", meshAppendPositions);
					}

					//_getch();
					dObj.limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
				}
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-normals-array") == 0)
				if(dObj.limitOne < (dObj.meshCount * 48) && strcmp((char*)attribute->children->content, meshAppendNormals) == 0)
				{
					if(dObj.meshSkip <= dObj.limitOne)
					{
						dObj.normalsfound = 1;
						printf("FOUND: %s\n", meshAppendNormals);
					}

					//_getch();
					dObj.limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
				}
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-map-0-array") == 0)
				if(dObj.limitOne < (dObj.meshCount * 48) && strcmp((char*)attribute->children->content, meshAppendMap0) == 0)
				{
					if(dObj.meshSkip <= dObj.limitOne)
					{
						dObj.uvmapfound = 1;
						printf("FOUND: %s\n", meshAppendMap0);
					}

					//_getch();
					dObj.limitOne+=1;
					printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
				}





				if(strcmp((char*)cur_node->name, "float_array") == 0)
				{
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						if(strcmp((char*)attribute->children->content, "Cube_location_X-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xInputFound = 1;
								printf("FOUND: Cube_location_X-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_X-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xOutputFound = 1;
								printf("FOUND: Cube_location_X-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_X-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xInTangentFound = 1;
								printf("FOUND: Cube_location_X-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_X-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xOutTangentFound = 1;
								printf("FOUND: Cube_location_X-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Y-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yInputFound = 1;
								printf("FOUND: Cube_location_Y-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Y-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yOutputFound = 1;
								printf("FOUND: Cube_location_Y-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Y-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yInTangentFound = 1;
								printf("FOUND: Cube_location_Y-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Y-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yOutTangentFound = 1;
								printf("FOUND: Cube_location_Y-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Z-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zInputFound = 1;
								printf("FOUND: Cube_location_Z-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Z-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zOutputFound = 1;
								printf("FOUND: Cube_location_Z-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Z-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zInTangentFound = 1;
								printf("FOUND: Cube_location_Z-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_location_Z-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zOutTangentFound = 1;
								printf("FOUND: Cube_location_Z-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						////////////////////////////////////////////////////////////////////////////////
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_X-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xRotEulerInputFound = 1;
								printf("FOUND: Cube_rotation_euler_X-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_X-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xRotEulerOutputFound = 1;
								printf("FOUND: Cube_rotation_euler_X-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_X-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xRotEulerInTangentFound = 1;
								printf("FOUND: Cube_rotation_euler_X-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_X-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xRotEulerOutTangentFound = 1;
								printf("FOUND: Cube_rotation_euler_X-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Y-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yRotEulerInputFound = 1;
								printf("FOUND: Cube_location_Y-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Y-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yRotEulerOutputFound = 1;
								printf("FOUND: Cube_location_Y-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Y-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yRotEulerInTangentFound = 1;
								printf("FOUND: Cube_location_Y-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Y-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yRotEulerOutTangentFound = 1;
								printf("FOUND: Cube_location_Y-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Z-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zRotEulerInputFound = 1;
								printf("FOUND: Cube_rotation_euler_Z-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Z-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zRotEulerOutputFound = 1;
								printf("FOUND: Cube_rotation_euler_Z-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Z-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zRotEulerInTangentFound = 1;
								printf("FOUND: Cube_rotation_euler_Z-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Z-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zRotEulerOutTangentFound = 1;
								printf("FOUND: Cube_rotation_euler_Z-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						////////////////////////////////////////////////////////////////////////////////
						if(strcmp((char*)attribute->children->content, "Cube_scale_X-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xScaleInputFound = 1;
								printf("FOUND: Cube_scale_X-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_X-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xScaleOutputFound = 1;
								printf("FOUND: Cube_scale_X-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_X-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xScaleInTangentFound = 1;
								printf("FOUND: Cube_scale_X-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_X-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xScaleOutTangentFound = 1;
								printf("FOUND: Cube_scale_X-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Y-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yScaleInputFound = 1;
								printf("FOUND: Cube_scale_Y-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Y-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yScaleOutputFound = 1;
								printf("FOUND: Cube_scale_Y-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Y-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yScaleInTangentFound = 1;
								printf("FOUND: Cube_scale_Y-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Y-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yScaleOutTangentFound = 1;
								printf("FOUND: Cube_scale_Y-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Z-input-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zScaleInputFound = 1;
								printf("FOUND: Cube_scale_Z-input-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Z-output-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zScaleOutputFound = 1;
								printf("FOUND: Cube_scale_Z-output-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Z-intangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zScaleInTangentFound = 1;
								printf("FOUND: Cube_scale_Z-intangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						if(strcmp((char*)attribute->children->content, "Cube_scale_Z-outtangent-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zScaleOutTangentFound = 1;
								printf("FOUND: Cube_scale_Z-outtangent-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}						
					}
				}

				if(strcmp((char*)cur_node->name, "name_array") == 0)
				{
					if(strcmp((char*)attribute->name, "id") == 0)
					{
						//Cube_location_X-interpolation-array
						if(strcmp((char*)attribute->children->content, "Cube_location_X-interpolation-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xInterpolationFound = 1;
								printf("FOUND: Cube_location_X-interpolation-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						//Cube_location_Y-interpolation-array
						if(strcmp((char*)attribute->children->content, "Cube_location_Y-interpolation-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yInterpolationFound = 1;
								printf("FOUND: Cube_location_Y-interpolation-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						//Cube_location_Z-interpolation-array
						if(strcmp((char*)attribute->children->content, "Cube_location_Z-interpolation-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zInterpolationFound = 1;
								printf("FOUND: Cube_location_Z-interpolation-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}

						//Cube_rotation_euler_X-interpolation-array
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_X-interpolation-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.xRotEulerInterpolationFound = 1;
								printf("FOUND: Cube_rotation_euler_X-interpolation-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						//Cube_rotation_euler_Y-interpolation-array
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Y-interpolation-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.yRotEulerInterpolationFound = 1;
								printf("FOUND: Cube_rotation_euler_Y-interpolation-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
						//Cube_rotation_euler_Z-interpolation-array
						if(strcmp((char*)attribute->children->content, "Cube_rotation_euler_Z-interpolation-array") == 0)
						{
							if(dObj.meshSkip <= dObj.limitOne)
							{
								dObj.zRotEulerInterpolationFound = 1;
								printf("FOUND: Cube_rotation_euler_Z-interpolation-array\n");
							}
							dObj.limitOne+=1;
							printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
						}
					}

					//Cube_scale_X-interpolation-array
					if(strcmp((char*)attribute->children->content, "Cube_scale_X-interpolation-array") == 0)
					{
						if(dObj.meshSkip <= dObj.limitOne)
						{
							dObj.xScaleInterpolationFound = 1;
							printf("FOUND: Cube_scale_X-interpolation-array\n");
						}
						dObj.limitOne+=1;
						printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
					}
					//Cube_scale_Y-interpolation-array
					if(strcmp((char*)attribute->children->content, "Cube_scale_Y-interpolation-array") == 0)
					{
						if(dObj.meshSkip <= dObj.limitOne)
						{
							dObj.yScaleInterpolationFound = 1;
							printf("FOUND: Cube_scale_Y-interpolation-array\n");
						}
						dObj.limitOne+=1;
						printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
					}
					//Cube_scale_Z-interpolation-array
					if(strcmp((char*)attribute->children->content, "Cube_scale_Z-interpolation-array") == 0)
					{
						if(dObj.meshSkip <= dObj.limitOne)
						{
							dObj.zScaleInterpolationFound = 1;
							printf("FOUND: Cube_scale_Z-interpolation-array\n");
						}
						dObj.limitOne+=1;
						printf("LIMIT: %d MESHC: %d\n", dObj.limitOne, (dObj.meshCount*48));
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
			//HIDE
			//printf("TxtNode Content: %s - Content Length %d\n", (char*)cur_node->content, slen);

			//HIDE
			//printf("Content Length %d\n", slen);


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
							//printf("FLOATARRAY: %.7f\n", floatarray[loopCount]);
							//_getch();
							dObj.storedvertices[loopCount] = dObj.floatarray[loopCount];
							dObj.verticescount = loopCount;
						}

						if(dObj.normalsfound)
						{
							//printf("NORMAL\n");
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", floatarray[loopCount]);
							//_getch();
							dObj.storednormals[loopCount] = dObj.floatarray[loopCount];
							dObj.normalscount = loopCount;
						}
						if(dObj.uvmapfound)
						{
							//printf("UVMAP\n");
							dObj.floatarray[loopCount] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", floatarray[loopCount]);
							//_getch();
							dObj.storeduvmaps[loopCount] = dObj.floatarray[loopCount];
							dObj.uvmapscount = loopCount;
						}
						if(dObj.indicesfound)
						{
							dObj.intarray[loopCount] = atoi((char*)stringarray);
							//printf("INTARRAY: %d\n", intarray[loopCount]);
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
						//_getch();
					}
				}
				//if(verticesfound == 1)for(int aaa = 0; aaa < 24; aaa++)printf("aaa: %.7f\n", morearray[aaa]);
				if(dObj.indicesfound == 1)dObj.indicesfound = 0;
				if(dObj.verticesfound == 1)dObj.verticesfound = 0;
				if(dObj.normalsfound == 1)dObj.normalsfound = 0;
				if(dObj.uvmapfound == 1)dObj.uvmapfound = 0;

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
}