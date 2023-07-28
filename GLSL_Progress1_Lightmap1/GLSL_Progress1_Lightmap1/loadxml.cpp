#include "Common.h"

struct xmlVectorArray
{
	float x, y, z;
};

int newarraytest;
bool verticesfound, normalsfound, uvmapfound, indicesfound;
int verticescount, normalscount, uvmapscount, indicescount;

//////////////////////////////////////////////////////////////////////////////////////////////////////

float*storedvertices;
float*storednormals;
float*storeduvmaps;

//////////////////////////////////////////////////////////////////////////////////////////////////////

//int *intarray = new int;
//float *floatarray = new float;
int *intarray;
float *floatarray;

//float *meshvertices = new float;
//float *meshnormals = new float;
//float *meshuvmaps = new float;
float *meshvertices;
float *meshnormals;
float *meshuvmaps;

std::vector<glm::vec3> temp_vertices, temp_normals, temp_indicesvertices;
std::vector<glm::vec2> temp_uvs;

//////////////////////////////////////////////////////////////////////////////////////////////////////

void loadmyDAE(
	const char * pFilestr,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<unsigned short> & out_indices
	)
{
	newarraytest = 0;
	verticesfound = 0, normalsfound = 0, uvmapfound = 0, indicesfound = 0;
	verticescount = 0, normalscount = 0, uvmapscount = 0, indicescount = 0;

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


	int *vertindices = new int[indicescount];
	int *normindices = new int[indicescount];
	int *uvindices = new int[indicescount];
	for(int i = 0; i <= indicescount/3; i++)
	{
		vertindices[i] = intarray[i*3+0];
		normindices[i] = intarray[i*3+1];
		uvindices[i] = intarray[i*3+2];

		//printf("%d VertI %d: %d\n", i, indicescount/3, vertindices[i]);
		//printf("%d NormI %d: %d\n", i, indicescount/3, normindices[i]);
		//printf("%d UvI %d: %d\n", i, indicescount/3, uvindices[i]);
	}
	//std::vector<glm::vec3> vectorvertices[10];
	//meshvertices = new float[verticescount];
	for(int ii = 0; ii <= verticescount/3; ii++)
	{
		//meshvertices[ii] = storedvertices[ii];
		//printf("MeshV i: %d - %d: %.7f\n", ii, verticescount, meshvertices[ii]);

		glm::vec3 tempvertex;
		tempvertex.x = storedvertices[ii*3+0];
		tempvertex.y = storedvertices[ii*3+1];
		tempvertex.z = storedvertices[ii*3+2];
		//printf("tempVERTS X: %f Y: %f Z: %f\n", tempvertex.x, tempvertex.y, tempvertex.z);

		temp_vertices.push_back(tempvertex);
		//out_vertices.push_back(tempvertex);
	}
	//_getch();

	meshuvmaps = new float[uvmapscount];
	for(int ii = 0; ii <= uvmapscount/2; ii++)
	{
		//vectoruvs
		meshuvmaps[ii] = storeduvmaps[ii];
		//printf("MeshU %d: %.7f\n", uvmapscount, meshuvmaps[ii]);

		glm::vec3 tempuvmap;
		tempuvmap.x = storeduvmaps[ii*2+0];
		tempuvmap.y = storeduvmaps[ii*2+1];
		//printf("tempUV U: %f V: %f\n", tempuvmap.x, tempuvmap.y);

		//glm::vec3 tempUV;
		//tempUV.x = storeduvmaps[ii*3+0];
		//tempUV.y = storeduvmaps[ii*3+1];
		//printf("tempUV U: %f V: %f\n", tempUV.x, tempUV.y);


		temp_uvs.push_back(tempuvmap);
		//out_vertices.push_back(tempUV);
	}

	meshnormals = new float[normalscount];
	for(int ii = 0; ii <= normalscount/3; ii++)
	{
		//vectornormals
		meshnormals[ii] = storednormals[ii];
		//printf("MeshN %d: %.7f\n", normalscount, meshnormals[ii]);

		glm::vec3 tempnormals;
		tempnormals.x = storednormals[ii*3+0];
		tempnormals.y = storednormals[ii*3+1];
		tempnormals.z = storednormals[ii*3+2];

		//printf("tempNORMS X: %f Y: %f Z: %f\n", tempnormals.x, tempnormals.y, tempnormals.z);

		temp_normals.push_back(tempnormals);
		//out_normals.push_back(tempnormals);
	}

	for(int iii = 0; iii <= indicescount/3; iii++)
	{
		int tempstuff1 = vertindices[iii];
		int tempstuff2 = normindices[iii];
		int tempstuff3 = uvindices[iii];
		glm::vec3 outvertex = temp_vertices[tempstuff1];
		glm::vec3 outnormal = temp_normals[tempstuff2];
		glm::vec2 outuvmap = temp_uvs[tempstuff3];
		//glm::vec3 tv = temp_vertices[0];
		//printf("TEST VertIND X: %f Y: %f Z: %f\n", tv[0], tv[1], tv[2]);
		//printf("%d VINDICES x: %f y: %f z: %f\n", iii, vertindices[iii*3+0], vertindices[iii*3+1], vertindices[iii*3+2]);
		//printf("INDCOUNT: %d\n", iii);


		//printf("INDVERT: %d %d outV X: %f Y: %f Z: %f\n", iii, tempstuff1, outvertex[0], outvertex[1], outvertex[2]);
		//printf("INDNORM: %d %d outV X: %f Y: %f Z: %f\n", iii, tempstuff2, outnormal[0], outnormal[1], outnormal[2]);
		//printf("INDUV: %d %d outU X: %f V: %f\n", iii, tempstuff3, outuvmap[0], outuvmap[1]);

		out_vertices.push_back(outvertex);
		out_uvs.push_back(outuvmap);
		out_normals.push_back(outnormal);
		//temp_indicesvertices.push_back(outvertex);
		out_indices.push_back(intarray[iii]);
	}
	//_getch();





	delete vertindices, normindices, uvindices, meshuvmaps, meshnormals;
	delete floatarray, intarray, storedvertices, storednormals, storeduvmaps;
	delete meshvertices, meshnormals, meshuvmaps;
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

			//HIDE EXTRA DATA
			//printf("EleNode type: %s\n", cur_node->name);

			if(strcmp((char*)cur_node->name, "p") == 0)
			{
				printf("INDICES!\n");
				indicesfound = 1;
			}

			xmlAttr* attribute = cur_node->properties;
			while(attribute)
			{
				//xmlChar* value = xmlNodeListGetString(cur_node->doc, attribute->children, 1);
				newarraytest = atoi((char*)attribute->children->content);

				//HIDE EXTRA DATA
				//printf("EleAttr: %s - Contents: %d\n", attribute->name, newarraytest);

				//if(strcmp((char*)attribute->children->content, "Sphere-mesh-positions-array") == 0)
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-positions-array") == 0)
				if(strcmp((char*)attribute->children->content, "Cube-mesh-positions-array") == 0
					|| strcmp((char*)attribute->children->content, "Sphere-mesh-positions-array") == 0)
				{
					verticesfound = 1;
					printf("Cube-mesh-positions-array!\n");
					//_getch();
				}
				//if(strcmp((char*)attribute->children->content, "Sphere-mesh-normals-array") == 0)
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-normals-array") == 0)
				if(strcmp((char*)attribute->children->content, "Cube-mesh-normals-array") == 0
					|| strcmp((char*)attribute->children->content, "Sphere-mesh-normals-array") == 0)
				{
					normalsfound = 1;
					printf("Cube-mesh-normals-array!\n");
					//_getch();
				}
				//if(strcmp((char*)attribute->children->content, "Sphere-mesh-map-0-array") == 0)
				//if(strcmp((char*)attribute->children->content, "Cube-mesh-map-0-array") == 0)
				if(strcmp((char*)attribute->children->content, "Cube-mesh-map-0-array") == 0
					|| strcmp((char*)attribute->children->content, "Sphere-mesh-map-0-array") == 0)
				{
					uvmapfound = 1;
					printf("Cube-mesh-map-0-array!\n");
					//_getch();
				}
				//xmlFree(value);//do something with value
				attribute = attribute->next;
			}
		}

		if(cur_node->type == XML_TEXT_NODE)
		{
			/* Process here text node, It is available in cpStr :TODO: */
			char *newChar;
			char *stringarray;

			int slen = strlen((char*)cur_node->content);
			//HIDE
			//printf("TxtNode Content: %s - Content Length %d\n", (char*)cur_node->content, slen);

			//HIDE
			//printf("Content Length %d\n", slen);


			xmlVectorArray *xmlVec;
			//int size = 10;
			xmlVec = new xmlVectorArray[newarraytest];
			//xmlVec[0].x = 5;

			/*
			if(indicesfound == 1)
			{
				printf("INDICES START HERE!\n");
				indicesfound = 0;
			}
			*/

			if(newarraytest > 0 || indicesfound == 1)
			{
				int lastLoop = 0;
				int stuff = 0;

				//char testarray[86000];
				//KEEP WITHIN 20000 TRIANGLES
				std::string testarray;
				testarray.reserve(10000000);


				intarray = new int[slen];
				floatarray = new float[slen];

				for(int i = 0; i <= slen; i++)
				{
					testarray[i] = (char)cur_node->content[i];
					//printf("%c", testarray[i]);
					//printf("%c\n", (char*)cur_node->content[i]);
					if((int)cur_node->content[i] == 32 || (char)cur_node->content[i] == '\0')
					{
						//printf("STUFF: %d SLEN: %d / %d\n", stuff, i, slen);
						//if(verticesfound == 1)
						//{
						int diff = i - lastLoop + 1;
						newChar = new char[diff];
						stringarray = new char[diff];

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

						//floatarray[stuff] = atof((char*)stringarray);
						//printf("FLOATARRAY: %.7f\n", floatarray[stuff]);

						if(verticesfound)
						{
							//printf("VERTICES!\n");
							floatarray[stuff] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", floatarray[stuff]);
							//_getch();
							storedvertices = floatarray;
							verticescount = stuff;
						}

						if(normalsfound)
						{
							//printf("NORMAL!\n");
							floatarray[stuff] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", floatarray[stuff]);
							//_getch();
							storednormals = floatarray;
							normalscount = stuff;
						}
						if(uvmapfound)
						{
							//printf("UVMAP!\n");
							floatarray[stuff] = (float)atof((char*)stringarray);
							//printf("FLOATARRAY: %.7f\n", floatarray[stuff]);
							//_getch();
							storeduvmaps = floatarray;
							uvmapscount = stuff;
						}

						if(indicesfound)
						{
							intarray[stuff] = atoi((char*)stringarray);
							//printf("INTARRAY: %d\n", intarray[stuff]);
							indicescount = stuff;
						}

						//}					
						stuff++;
						//_getch();
					}
				}

				//if(verticesfound == 1)for(int aaa = 0; aaa < 24; aaa++)printf("aaa: %.7f\n", morearray[aaa]);
				if(indicesfound == 1)indicesfound = 0;
				if(verticesfound == 1)verticesfound = 0;
				if(normalsfound == 1)normalsfound = 0;
				if(uvmapfound == 1)uvmapfound = 0;


			}

		}

		traverse_dom_trees(cur_node->children);

	}

}
