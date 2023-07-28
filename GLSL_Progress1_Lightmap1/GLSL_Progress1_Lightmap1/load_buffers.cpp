#include "Common.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
extern int SCREEN_WIDTH, SCREEN_HEIGHT;

extern glm::mat4 projection, view, ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix,
	projectionLight, viewLight, ModelMatrixLight, MVPLight, RotationMatrixLight, TranslationMatrixLight, ScalingMatrixLight;

extern glm::vec3 target, right, up, eye;

extern bool hasAlpha;
extern int imgwidth, imgheight;

extern float deltaTime;

extern float modelX, modelY, modelZ;
extern float lightX, lightY, lightZ;

extern float eyeX, eyeY, eyeZ;
extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;
//////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint programID, materialShaderID,
	uniformModel, uniformView, uniformProjection, uniformRotation,
	MatrixID, MatrixIDVBO, uniformModelVBO, uniformViewVBO, uniformProjectionVBO,
	lightShaderID, MatrixIDLight, uniformModelLight, uniformViewLight, uniformProjectionLight;


GLuint diffuseID[90000], specularID[90000], emissionID[90000], Texture[90000], LightID[90000],
	VertexArrayID[90000], vertexbuffer[90000], colorbuffer[90000], uvbuffer[90000], normalbuffer[90000], elementbuffer[90000],
	VertexArrayIDLight[90000], vertexbufferLight[90000], uvbufferLight[90000], normalbufferLight[90000], elementbufferLight[90000];

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



void drawVBO(int vboID, GLint myShader, char*modelfile, char*texturefile)
{
	glCullFace(GL_BACK);
	//glUseProgram(programID);//BASIC SHADER
	glUseProgram(myShader);
	//materialShaderID
	//lightShaderID



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


	//GEN BUFFERS
	if(dObj.loadOnce[vboID] == 0)
	{
		//Load the texture
		//Texture[vboID] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
		//Texture[0] = loadPngImage(DAEtexture, imgwidth, imgheight, hasAlpha, &textureImage);

		//Texture[vboID*3+0] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
		Texture[vboID*3+0] = loadPngImage("container2.png",          imgwidth, imgheight, hasAlpha, &textureImage);
		Texture[vboID*3+1] = loadPngImage("container2_specular.png", imgwidth, imgheight, hasAlpha, &textureImage);
		Texture[vboID*3+2] = loadPngImage("matrix.png",              imgwidth, imgheight, hasAlpha, &textureImage);


		//Texture[vboID] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
		//delete textureImage;//REFRESH GENTEXTURES

		//loadBMP_custom("test.bmp");
		//LoadBMP("test.bmp");
		//loadDDS("uvmap.DDS");
		//Get a handle for our "myTextureSampler" uniform
		//diffuseID[0] = glGetUniformLocation(programID, "myTexture");
		//diffuseID[vboID] = glGetUniformLocation(programID, "myTexture");
		diffuseID[vboID] = glGetUniformLocation(myShader, "material.diffuse");//DIFFUSE(TEXTURE) MAP
		specularID[vboID] = glGetUniformLocation(myShader, "material.specular");//SPECULAR MAP
		emissionID[vboID] = glGetUniformLocation(myShader, "material.emission");//EMISSION MAP


		//USE IF RELOADING
		vectorvertices[vboID].clear(), vectoruvs[vboID].clear(), vectornormals[vboID].clear();
		indices[vboID].clear();
		indexed_vertices[vboID].clear(), indexed_uvs[vboID].clear(), indexed_normals[vboID].clear();


		//loadOBJ(modelfile, vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID]);
		//indexVBO(vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID], indices[vboID], indexed_vertices[vboID], indexed_uvs[vboID], indexed_normals[vboID]);
		loadmyDAE(modelfile, vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID], daeindices[vboID]);
		indexVBO(vectorvertices[vboID], vectoruvs[vboID], vectornormals[vboID], indices[vboID], indexed_vertices[vboID], indexed_uvs[vboID], indexed_normals[vboID]);


		glGenVertexArrays(1, &VertexArrayID[vboID]);
		glGenBuffers(1, &vertexbuffer[vboID]);
		glGenBuffers(1, &uvbuffer[vboID]);
		glGenBuffers(1, &normalbuffer[vboID]);
		glGenBuffers(1, &elementbuffer[vboID]);


		glBindVertexArray(VertexArrayID[vboID]);
		//VERTEXBUFFER
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboID]);
		//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, indexed_vertices[vboID].size() * sizeof(glm::vec3), &indexed_vertices[vboID][0], GL_STATIC_DRAW);
		//UVBUFFER
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
		//glBufferData(GL_ARRAY_BUFFER, vectoruvs[vboLoop].size() * sizeof(glm::vec2), &vectoruvs[vboLoop][0], GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboID].size() * sizeof(glm::vec2), &indexed_uvs[vboID][0], GL_STATIC_DRAW);
		//NORMALBUFFER
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboID]);
		//glBufferData(GL_ARRAY_BUFFER, vectornormals[vboLoop].size() * sizeof(glm::vec3), &vectornormals[vboLoop][0], GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, indexed_normals[vboID].size() * sizeof(glm::vec3), &indexed_normals[vboID][0], GL_STATIC_DRAW);
		//INDICEBUFFERS
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboID]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[vboID].size() * sizeof(unsigned short), &indices[vboID][0], GL_STATIC_DRAW);
		printf("INDSIZE: %d\n", indices[vboID].size() * sizeof(unsigned short));

		dObj.loadOnce[vboID] = 1;
		//_getch();
	}


	if(dObj.drawDisable[vboID] == 0)
	{
		projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);

		RotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);


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


			//ORIGINAL
			//TranslationMatrix = translate(mat4(), glm::vec3(modelX, modelY, modelZ));
			ScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));

			//MOVE MATRIX WITH LIGHT
			//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
			//glm::vec3 lightPos(lightX, lightY, lightZ);

			TranslationMatrix = glm::mat4(1.0f);
			TranslationMatrix = glm::translate(TranslationMatrix, (glm::vec3(modelX, modelY, modelZ)));//INSIDE
			//TranslationMatrix = glm::translate(TranslationMatrix, (glm::vec3(modelX * sin(glfwGetTime()), modelY, modelZ * cos(glfwGetTime()))));//OUTSIDE

			//TranslationMatrix = translate(mat4(), glm::vec3(modelX, modelY, modelZ));
			//TranslationMatrix = glm::translate(TranslationMatrix, lightPos);//NOWORK
			//TranslationMatrix = glm::translate(TranslationMatrix, lightPos * (glm::vec3(modelX, modelY, modelZ)));
		}
		*/


		view = LookAt(eye, eye + target, up);
		//glm::mat4 view = LookAt(eye, eye+target, up);
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));

		ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

		MVP = projection * view * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

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
		glBindTexture(GL_TEXTURE_2D, Texture[vboID*3+0]);//dTexture
		glUniform1i(diffuseID[vboID], 0);//Set "myTextureSampler" sampler to use Texture Unit 0

		glActiveTexture(GL_TEXTURE1);//Bind our texture in Texture Unit 1
		glBindTexture(GL_TEXTURE_2D, Texture[vboID*3+1]);//sTexture
		glUniform1i(specularID[vboID], 1);//Set "myTextureSampler" sampler to use Texture Unit 1

		glActiveTexture(GL_TEXTURE2);//Bind our texture in Texture Unit 2
		glBindTexture(GL_TEXTURE_2D, Texture[vboID*3+2]);//eTexture
		glUniform1i(emissionID[vboID], 2);//Set "myTextureSampler" sampler to use Texture Unit 2
		//}
		

		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboID]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//4th attribute buffer : color4v
		//glEnableVertexAttribArray(3);
		//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[vboID]);
		//glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawArrays(GL_TRIANGLES, 0, vectorvertices[0].size() * sizeof(glm::vec3));
		//Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboID]);
		glDrawElements(GL_TRIANGLES, indices[vboID].size(), GL_UNSIGNED_SHORT, (void*)0);
	}
	dObj.VBOloadedID++;


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
	if(dObj.loadOnce[vboID] == 0)
	{
		//vectorverticesLight[vboID].clear(), vectoruvsLight[vboID].clear(), vectornormalsLight[vboID].clear();
		//indicesLight[vboID].clear();
		//indexed_verticesLight[vboID].clear(), indexed_uvsLight[vboID].clear(), indexed_normalsLight[vboID].clear();

		loadmyDAE(modelfile, vectorverticesLight[vboID], vectoruvsLight[vboID], vectornormalsLight[vboID], daeindicesLight[vboID]);
		indexVBO(vectorverticesLight[vboID], vectoruvsLight[vboID], vectornormalsLight[vboID], indicesLight[vboID], indexed_verticesLight[vboID], indexed_uvsLight[vboID], indexed_normalsLight[vboID]);

		glGenVertexArrays(1, &VertexArrayIDLight[vboID]);
		glGenBuffers(1, &vertexbufferLight[vboID]);
		glGenBuffers(1, &elementbufferLight[vboID]);
		glBindVertexArray(VertexArrayIDLight[vboID]);

		//VERTEXBUFFER
		glBindBuffer(GL_ARRAY_BUFFER, vertexbufferLight[vboID]);
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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferLight[vboID]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLight[vboID].size() * sizeof(unsigned short), &indicesLight[vboID][0], GL_STATIC_DRAW);
		printf("INDSIZELIGHT: %d\n", indicesLight[vboID].size() * sizeof(unsigned short));
		dObj.loadOnce[vboID] = 1;
		//_getch();
	}
	if(dObj.drawDisable[vboID] == 0)
	{
		projectionLight = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(uniformProjectionLight, 1, GL_FALSE, glm::value_ptr(projectionLight));

		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		RotationMatrixLight = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);

		//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		//glm::vec3 lightPos(lightX, lightY, lightZ);//INSIDE
		glm::vec3 lightPos(lightX * sin(glfwGetTime()), lightY, lightZ * cos(glfwGetTime()));//OUTSIDE_ORBIT
		TranslationMatrixLight = glm::mat4(1.0f);
		TranslationMatrixLight = glm::translate(TranslationMatrixLight, lightPos);
		TranslationMatrixLight = glm::scale(TranslationMatrixLight, glm::vec3(0.2f));//0.2f
		ScalingMatrixLight = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));

		viewLight = LookAt(eye, eye + target, up);
		glUniformMatrix4fv(uniformViewLight, 1, GL_FALSE, glm::value_ptr(viewLight));

		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		ModelMatrixLight = TranslationMatrixLight * RotationMatrixLight * ScalingMatrixLight;
		glUniformMatrix4fv(uniformModelLight, 1, GL_FALSE, glm::value_ptr(ModelMatrixLight));

		MVPLight = projectionLight * viewLight * ModelMatrixLight;
		glUniformMatrix4fv(MatrixIDLight, 1, GL_FALSE, &MVPLight[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbufferLight[vboID]);
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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferLight[vboID]);
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
	glDeleteVertexArrays(1, VertexArrayID);
	glDeleteBuffers(1, vertexbuffer);
	glDeleteBuffers(1, uvbuffer);
	glDeleteBuffers(1, normalbuffer);
	glDeleteBuffers(1, elementbuffer);
	glDeleteTextures(1, Texture);
	glDeleteProgram(programID);
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