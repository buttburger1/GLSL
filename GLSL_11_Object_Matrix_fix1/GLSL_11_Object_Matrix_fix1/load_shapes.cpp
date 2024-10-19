#include "Common.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
extern int SCREEN_WIDTH, SCREEN_HEIGHT;


//GLuint programShapeShaderID;
//GLuint programShapesShaderID, shapesMatrixID, shapesUniformModel, shapesUniformView, shapesUniformProjection,
	//shapeVertexArrayID[90000], shapesVertexBuffer[90000], shapesColorBuffer[90000], shapesUVBuffer[90000], shapesNormalBuffer[90000], shapesElementBuffer[90000];


//extern glm::mat4 view; //projection, ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix;
//glm::mat4 shapesProjection, shapesModelMatrix, shapesMVP, shapesRotationMatrix, shapesTranslationMatrix, shapesScalingMatrix;

extern int myCam;

extern float deltaTime;
extern float modelX, modelY, modelZ;
extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;

extern quat gOrientation2[90000];


extern glm::vec3 eye;
//extern glm::vec3 right, target, up;
//extern glm::mat4 projection, view, ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix;

//////////////////////////////////////////////////////////////////////////////////////////////////////

extern drawObjects dObj;

//////////////////////////////////////////////////////////////////////////////////////////////////////

extern float radius;//const
extern float cam1X;// = sin(currentTime) * radius;
extern float cam1Y;
extern float cam1Z;// = cos(currentTime) * radius;
extern glm::vec3 cameraPos1;// = glm::vec3(cam1X, cam1Y, cam1Z);
extern glm::vec3 objectPos1;// = glm::vec3(0.0f, 0.0f, 0.0f);
extern glm::vec3 up1;// = glm::vec3(0.0f, 1.0f, 0.0f);
//extern glm::mat4 viewCamera1;// = glm::lookAt(cameraPos1, objectPos1, up1);

//////////////////////////////////////////////////////////////////////////////////////////////////////

void drawPoints(int vboID, vec3 pointVec, vec4 pointVecColor)
{
	float pointVertex[] = {
		pointVec.x, pointVec.y, pointVec.z
	};
	
	GLfloat pointColor[] = {
		pointVecColor.x, pointVecColor.y, pointVecColor.z, pointVecColor.w
	};
	
	if(dObj.loadOnce[vboID] == 0)
	{
		//glGenVertexArrays(1, &shapeVertexArrayID[vboID]);
		//glBindVertexArray(shapeVertexArrayID[vboID]);
		//GLuint vertexbuffer;
		glGenBuffers(1, &dObj.shapesVertexBuffer[vboID]);
		glGenBuffers(1, &dObj.shapesColorBuffer[vboID]);
		
		//GLuint uvbuffer;
		//GLuint elementbuffer;
		//glGenBuffers(1, &shapeelementbuffer[vboID]);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapeInd), shapeInd, GL_STATIC_DRAW);
		dObj.loadOnce[vboID] = 1;
	}


	glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertex), pointVertex, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointColor), pointColor, GL_STATIC_DRAW);
	

	if(dObj.drawDisable[vboID] == 0)
	{
		glCullFace(GL_BACK);
		glUseProgram(dObj.programShapesShaderID);
		//FOR 2D
		//shapesProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		//FOR 3D
		dObj.shapesProjection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(dObj.shapesUniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.shapesProjection));


		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.shapesRotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);

		//FOR 2D
		//shapesTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//modelX, modelY, modelZ));
		//FOR 3D
		dObj.shapesTranslationMatrix = translate(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));//modelX, modelY, modelZ));

		//shapesScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
		dObj.shapesScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
		dObj.shapesModelMatrix = dObj.shapesTranslationMatrix * dObj.shapesRotationMatrix * dObj.shapesScalingMatrix;

		//SET VIEW TO 2D
		//view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//SET VIEW TO 3D
		//glm::mat4 view = LookAt(eye, eye+target, up);

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

		//view = LookAt(eye, eye + target, up);
		glUniformMatrix4fv(dObj.shapesUniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		glUniformMatrix4fv(dObj.shapesUniformModel, 1, GL_FALSE, glm::value_ptr(dObj.shapesModelMatrix));
		dObj.shapesMVP = dObj.shapesProjection * dObj.view * dObj.shapesModelMatrix;
		glUniformMatrix4fv(dObj.shapesMatrixID, 1, GL_FALSE, &dObj.shapesMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform


		//glm::vec3 lightPos = glm::vec3(4,4,4);
		//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
		//SEND TO SHADER
		//glUniform4f(glGetUniformLocation(programShapeShaderID, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4

		//glPointSize(3);
		
		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		//2nd attribute buffer : Color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glDrawElements(GL_TRIANGLES, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);
		

		//glBindVertexArray(shapeVertexArrayID[vboID]);
		//glBindBuffer(GL_ARRAY_BUFFER, shapesVertexBuffer[vboID]);

		glDrawArrays(GL_POINTS, 0, 2);


		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}



void drawLine(int vboID, vec4 startColor4f, vec4 endColor4f, vec3 point1, vec3 point2)
{
	/*
	float line[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 300.0f, 0.0f,
	};
	*/


	float line[] = {
		point1.x, point1.y, point1.z,
		point2.x, point2.y, point2.z,
	};


	GLfloat lineColor[] = {
		//1.0f, 0.0f, 0.0f, 1.0f,
		//0.0f, 1.0f, 0.0f, 1.0f,

		startColor4f.x, startColor4f.y, startColor4f.z, startColor4f.w,
		endColor4f.x, endColor4f.y, endColor4f.z, endColor4f.w,
	};


	if(dObj.loadOnce[vboID] == 0)
	{
		glGenVertexArrays(1, &dObj.shapeVertexArrayID[vboID]);
		glBindVertexArray(dObj.shapeVertexArrayID[vboID]);
		//GLuint vertexbuffer;
		glGenBuffers(1, &dObj.shapesVertexBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
		//GLuint uvbuffer;
		glGenBuffers(1, &dObj.shapesColorBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineColor), lineColor, GL_STATIC_DRAW);
		//GLuint elementbuffer;
		//glGenBuffers(1, &shapeelementbuffer[vboID]);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapeInd), shapeInd, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		dObj.loadOnce[vboID] = 1;
	}

	if(dObj.drawDisable[vboID] == 0)
	{
		glCullFace(GL_BACK);
		glUseProgram(dObj.programShapesShaderID);
		//2D
		//shapesProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		//3D
		dObj.shapesProjection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(dObj.shapesUniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.shapesProjection));


		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.shapesRotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);

		//2D
		//shapesTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//modelX, modelY, modelZ));
		//3D
		dObj.shapesTranslationMatrix = translate(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));//modelX, modelY, modelZ));

		//shapesScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
		dObj.shapesScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));

		dObj.shapesModelMatrix = dObj.shapesTranslationMatrix * dObj.shapesRotationMatrix * dObj.shapesScalingMatrix;
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		glUniformMatrix4fv(dObj.shapesUniformModel, 1, GL_FALSE, glm::value_ptr(dObj.shapesModelMatrix));
		

		//SET VIEW TO 2D
		//view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//SET VIEW TO 3D

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

		//view = LookAt(eye, eye + target, up);
		//glm::mat4 view = LookAt(eye, eye+target, up);
		glUniformMatrix4fv(dObj.shapesUniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));


		
		dObj.shapesMVP = dObj.shapesProjection * dObj.view * dObj.shapesModelMatrix;
		glUniformMatrix4fv(dObj.shapesMatrixID, 1, GL_FALSE, &dObj.shapesMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform
		


		//glm::vec3 lightPos = glm::vec3(4,4,4);
		//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
		//SEND TO SHADER
		//glUniform4f(glGetUniformLocation(programShapeShaderID, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4


		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : Color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glDrawElements(GL_TRIANGLES, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(dObj.shapeVertexArrayID[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		
		glDrawArrays(GL_LINES, 0, 2);
		//glDrawArrays(GL_LINES, 0, sizeof(line));

		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}


void drawLineStrip(int vboID)
{
	float lineStrip[] = {
		/*
		0.0f, 0.0f, 0.0f,
		50.0f, 50.0f, 0.0f,
		
		100.0f, 0.0f, 0.0f,
		150.0f, 50.0f, 0.0f,

		200.0f, 0.0f, 0.0f,
		250.0f, 50.0f, 0.0f,
		*/

		//point1.x, point1.y, point1.z,
		//point2.x, point2.y, point2.z,
		
		-100.0f, -50.0f, 0.0f,
		-90.0f, -40.0f, 0.0f,
		-80.0f, -50.0f, 0.0f,
		-70.0f, -40.0f, 0.0f,
		-60.0f, -50.0f, 0.0f,
	};





	GLfloat lineStripColor[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};


	if(dObj.loadOnce[vboID] == 0)
	{
		glGenVertexArrays(1, &dObj.shapeVertexArrayID[vboID]);
		glBindVertexArray(dObj.shapeVertexArrayID[vboID]);
		//GLuint vertexbuffer;
		glGenBuffers(1, &dObj.shapesVertexBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineStrip), lineStrip, GL_STATIC_DRAW);
		//GLuint uvbuffer;
		glGenBuffers(1, &dObj.shapesColorBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineStripColor), lineStripColor, GL_STATIC_DRAW);
		//GLuint elementbuffer;
		//glGenBuffers(1, &shapeelementbuffer[vboID]);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapeInd), shapeInd, GL_STATIC_DRAW);
		dObj.loadOnce[vboID] = 1;
	}

	if(dObj.drawDisable[vboID] == 0)
	{
		glCullFace(GL_BACK);
		glUseProgram(dObj.programShapesShaderID);
		//2D
		//shapesProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		//3D
		dObj.shapesProjection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(dObj.shapesUniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.shapesProjection));


		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.shapesRotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);

		//2D
		//shapesTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//modelX, modelY, modelZ));
		//3D
		dObj.shapesTranslationMatrix = translate(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));//modelX, modelY, modelZ));

		//shapesScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
		dObj.shapesScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
		dObj.shapesModelMatrix = dObj.shapesTranslationMatrix * dObj.shapesRotationMatrix * dObj.shapesScalingMatrix;

		//SET VIEW TO 2D
		//view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//SET VIEW TO 3D
		//glm::mat4 view = LookAt(eye, eye+target, up);

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

		//view = LookAt(eye, eye + target, up);
		glUniformMatrix4fv(dObj.shapesUniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		glUniformMatrix4fv(dObj.shapesUniformModel, 1, GL_FALSE, glm::value_ptr(dObj.shapesModelMatrix));
		dObj.shapesMVP = dObj.shapesProjection * dObj.view * dObj.shapesModelMatrix;
		glUniformMatrix4fv(dObj.shapesMatrixID, 1, GL_FALSE, &dObj.shapesMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform


		//glm::vec3 lightPos = glm::vec3(4,4,4);
		//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
		//SEND TO SHADER
		//glUniform4f(glGetUniformLocation(programShapeShaderID, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4


		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		//2nd attribute buffer : Color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glDrawElements(GL_TRIANGLES, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);
		

		//glBindVertexArray(shapeVertexArrayID[vboID]);
		//glBindBuffer(GL_ARRAY_BUFFER, shapesVertexBuffer[vboID]);

		//glDrawArrays(GL_LINES, 0, 2);
		//glDrawArrays(GL_LINE_STRIP, 0, 6);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
		//glDrawArrays(GL_LINE_STRIP, 0, sizeof(lineStrip)/sizeof(float));
		
		//glDrawArrays(GL_LINE_STRIP, 0, sizeof(lineStrip));
		glDrawArrays(GL_LINE_STRIP, 0, 5);
		//glDrawArrays(GL_LINE_STRIP, 0, 10);



		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}


void drawLineLoop(int vboID)//, vec4 color4f, vec3 point1, vec3 point2)
{
	float lineLoop[] = {
		-40.0f, -40.0f, 0.0f,
		-30.0f, -40.0f, 0.0f,
		-30.0f, -50.0f, 0.0f,
		-40.0f, -50.0f, 0.0f,
	};

	GLfloat lineLoopColor[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};

	if(dObj.loadOnce[vboID] == 0)
	{
		glGenVertexArrays(1, &dObj.shapeVertexArrayID[vboID]);
		glBindVertexArray(dObj.shapeVertexArrayID[vboID]);
		//GLuint vertexbuffer;
		glGenBuffers(1, &dObj.shapesVertexBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineLoop), lineLoop, GL_STATIC_DRAW);
		//GLuint uvbuffer;
		glGenBuffers(1, &dObj.shapesColorBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineLoopColor), lineLoopColor, GL_STATIC_DRAW);
		//GLuint elementbuffer;
		//glGenBuffers(1, &shapeelementbuffer[vboID]);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapeInd), shapeInd, GL_STATIC_DRAW);
		dObj.loadOnce[vboID] = 1;
	}

	if(dObj.drawDisable[vboID] == 0)
	{
		glCullFace(GL_BACK);
		glUseProgram(dObj.programShapesShaderID);
		//2D
		//shapesProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		//3D
		dObj.shapesProjection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(dObj.shapesUniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.shapesProjection));


		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.shapesRotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);

		//2D
		//shapesTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//modelX, modelY, modelZ));
		//3D
		dObj.shapesTranslationMatrix = translate(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));//modelX, modelY, modelZ));

		//shapesScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
		dObj.shapesScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
		dObj.shapesModelMatrix = dObj.shapesTranslationMatrix * dObj.shapesRotationMatrix * dObj.shapesScalingMatrix;


		//SET VIEW TO 2D
		//view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//SET VIEW TO 3D

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

		//view = LookAt(eye, eye + target, up);
		//glm::mat4 view = LookAt(eye, eye+target, up);
		glUniformMatrix4fv(dObj.shapesUniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));


		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		glUniformMatrix4fv(dObj.shapesUniformModel, 1, GL_FALSE, glm::value_ptr(dObj.shapesModelMatrix));
		dObj.shapesMVP = dObj.shapesProjection * dObj.view * dObj.shapesModelMatrix;
		glUniformMatrix4fv(dObj.shapesMatrixID, 1, GL_FALSE, &dObj.shapesMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform


		//glm::vec3 lightPos = glm::vec3(4,4,4);
		//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
		//SEND TO SHADER
		//glUniform4f(glGetUniformLocation(programShapeShaderID, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4


		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		//2nd attribute buffer : Color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeelementbuffer[vboID]);
		//glDrawElements(GL_TRIANGLES, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);
		
		//glBindVertexArray(shapeVertexArrayID[vboID]);
		//glBindBuffer(GL_ARRAY_BUFFER, shapesVertexBuffer[vboID]);

		glDrawArrays(GL_LINE_LOOP, 0, 4);
		//glDrawArrays(GL_LINE_LOOP, 0, sizeof(lineLoop));
				
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}



void drawTriangle(int vboID)
{
	GLfloat Vertices[] = {
		20.0f, -50.0f, 0.0f,
		30.0f, -40.0f, 0.0f,
		40.0f, -50.0f, 0.0f,
	};

	GLfloat Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};

	unsigned int shapeInd[] =
	{
		//1,2,0,
		//1,3,2,

		//0,1,2,
		//0,2,3,
		2,1,0,
	};
	

	if(dObj.loadOnce[vboID] == 0)
	{
		glGenVertexArrays(1, &dObj.shapeVertexArrayID[vboID]);
		glBindVertexArray(dObj.shapeVertexArrayID[vboID]);
		//GLuint vertexbuffer;
		glGenBuffers(1, &dObj.shapesVertexBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		//GLuint uvbuffer;
		glGenBuffers(1, &dObj.shapesColorBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
		//GLuint elementbuffer;
		glGenBuffers(1, &dObj.shapesElementBuffer[vboID]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.shapesElementBuffer[vboID]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapeInd), shapeInd, GL_STATIC_DRAW);
		dObj.loadOnce[vboID] = 1;
	}
	
	if(dObj.drawDisable[vboID] == 0)
	{
		 //int length = sizeof(Vertices)/sizeof(Vertices[0]);
		 //printf("triangleLength: %d\n", length);

		glCullFace(GL_BACK);
		glUseProgram(dObj.programShapesShaderID);
		//2D
		//shapesProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		//3D
		dObj.shapesProjection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);

		glUniformMatrix4fv(dObj.shapesUniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.shapesProjection));
		
		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.shapesRotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);


		//2D
		//shapesTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//modelX, modelY, modelZ));
		//3D
		dObj.shapesTranslationMatrix = translate(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));//modelX, modelY, modelZ));


		//shapesScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
		dObj.shapesScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
		dObj.shapesModelMatrix = dObj.shapesTranslationMatrix * dObj.shapesRotationMatrix * dObj.shapesScalingMatrix;
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		glUniformMatrix4fv(dObj.shapesUniformModel, 1, GL_FALSE, glm::value_ptr(dObj.shapesModelMatrix));

		//SET VIEW TO 2D
		//glm::mat4 view = LookAt(eye, eye+target, up);

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

		//view = LookAt(eye, eye+target, up);
		//SET VIEW TO 3D
		//view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(dObj.shapesUniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));
		

		dObj.shapesMVP = dObj.shapesProjection * dObj.view * dObj.shapesModelMatrix;
		glUniformMatrix4fv(dObj.shapesMatrixID, 1, GL_FALSE, &dObj.shapesMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform



		//glm::vec3 lightPos = glm::vec3(4,4,4);
		//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
		//SEND TO SHADER
		//glUniform4f(glGetUniformLocation(programShapeShaderID, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4


		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : Color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dObj.shapesElementBuffer[vboID]);
		glDrawElements(GL_TRIANGLES, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}



void drawTriangleStrip(int vboID, int facing)
{
	GLfloat Vertices[] = {
		/*
		100.0f, 0.0f, 0.0f,
		200.0f, 0.0f, 0.0f,
		100.0f, -100.0f, 0.0f,
		200.0f, -100.0f, 0.0f,
		

		100.0f, 0.0f, 0.0f,
		100.0f, 100.0f, 0.0f,
		200.0f, 0.0f, 0.0f,
		200.0f, 100.0f, 0.0f,
		300.0f, 0.0f, 0.0f,
		*/


		60.0f, -50.0f, 0.0f,
		70.0f, -40.0f, 0.0f,
		80.0f, -50.0f, 0.0f,
		90.0f, -40.0f, 0.0f,
		100.0f, -50.0f, 0.0f,
		110.0f, -40.0f, 0.0f,
	};
	
	GLfloat Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};

	/*
	unsigned int shapeInd[] =
	{
		0,1,2,3,
		//3,2,1,0,
	};
	*/
	

	if(dObj.loadOnce[vboID] == 0)
	{
		printf("TRIANGLE STRIP SIZE: %d\n", sizeof(Vertices)/sizeof(GLfloat)/3);

		glGenVertexArrays(1, &dObj.shapeVertexArrayID[vboID]);
		glBindVertexArray(dObj.shapeVertexArrayID[vboID]);
		//GLuint vertexbuffer;
		glGenBuffers(1, &dObj.shapesVertexBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		//GLuint uvbuffer;
		glGenBuffers(1, &dObj.shapesColorBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
		//GLuint elementbuffer;
		//glGenBuffers(1, &shapesElementBuffer[vboID]);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapesElementBuffer[vboID]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapeInd), shapeInd, GL_STATIC_DRAW);
		dObj.loadOnce[vboID] = 1;
	}
	
	if(dObj.drawDisable[vboID] == 0)
	{
		if(facing == 0)glCullFace(GL_FRONT);
		else if(facing == 1)glCullFace(GL_BACK);
		glUseProgram(dObj.programShapesShaderID);
		//shapesProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		dObj.shapesProjection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(dObj.shapesUniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.shapesProjection));


		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.shapesRotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);


		//2D
		//shapesTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//modelX, modelY, modelZ));
		//3D
		dObj.shapesTranslationMatrix = translate(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));//modelX, modelY, modelZ));


		//shapesScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
		dObj.shapesScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
		dObj.shapesModelMatrix = dObj.shapesTranslationMatrix * dObj.shapesRotationMatrix * dObj.shapesScalingMatrix;
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		glUniformMatrix4fv(dObj.shapesUniformModel, 1, GL_FALSE, glm::value_ptr(dObj.shapesModelMatrix));


		//SET VIEW TO 2D
		//view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//SET VIEW TO 3D

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

		//view = LookAt(eye, eye + target, up);
		//glm::mat4 view = LookAt(eye, eye+target, up);
		glUniformMatrix4fv(dObj.shapesUniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));
		

		dObj.shapesMVP = dObj.shapesProjection * dObj.view * dObj.shapesModelMatrix;
		glUniformMatrix4fv(dObj.shapesMatrixID, 1, GL_FALSE, &dObj.shapesMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform



		//glm::vec3 lightPos = glm::vec3(4,4,4);
		//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
		//SEND TO SHADER
		//glUniform4f(glGetUniformLocation(programShapeShaderID, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4


		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : Color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapesElementBuffer[vboID]);
		//glDrawElements(GL_TRIANGLES, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);
		//glDrawElements(GL_TRIANGLE_STRIP, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);

		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(Vertices)/sizeof(GLfloat)/3);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}



void drawTriangleFan(int vboID, int facing)
{
	GLfloat TriangleFanVertices[] = {
		160.0f, -70.0f, 0.0f,

		130.0f, -50.0f, 0.0f,
		140.0f, -40.0f, 0.0f,
		150.0f, -30.0f, 0.0f,

		160.0f, -20.0f, 0.0f,

		170.0f, -30.0f, 0.0f,
		180.0f, -40.0f, 0.0f,
		190.0f, -50.0f, 0.0f,
	};
	
	GLfloat TriangleFanColors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
	};
	
	if(dObj.loadOnce[vboID] == 0)
	{
		printf("TRIANGLE FAN SIZE: %d\n", sizeof(TriangleFanVertices)/sizeof(GLfloat)/3);
		glGenVertexArrays(1, &dObj.shapeVertexArrayID[vboID]);
		glBindVertexArray(dObj.shapeVertexArrayID[vboID]);
		//GLuint vertexbuffer;
		glGenBuffers(1, &dObj.shapesVertexBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleFanVertices), TriangleFanVertices, GL_STATIC_DRAW);
		//GLuint uvbuffer;
		glGenBuffers(1, &dObj.shapesColorBuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleFanColors), TriangleFanColors, GL_STATIC_DRAW);
		//GLuint elementbuffer;
		//glGenBuffers(1, &shapesElementBuffer[vboID]);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapesElementBuffer[vboID]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapeInd), shapeInd, GL_STATIC_DRAW);
		dObj.loadOnce[vboID] = 1;
	}
	
	if(dObj.drawDisable[vboID] == 0)
	{
		if(facing == 0)glCullFace(GL_FRONT);
		else if(facing == 1)glCullFace(GL_BACK);
		glUseProgram(dObj.programShapesShaderID);
		//shapesProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		dObj.shapesProjection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		glUniformMatrix4fv(dObj.shapesUniformProjection, 1, GL_FALSE, glm::value_ptr(dObj.shapesProjection));


		vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		dObj.shapesRotationMatrix = mat4_cast(gOrientation2[vboID]);
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);
		

		//2D
		//shapesTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//modelX, modelY, modelZ));
		//3D
		dObj.shapesTranslationMatrix = translate(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));//modelX, modelY, modelZ));


		//shapesScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
		dObj.shapesScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
		dObj.shapesModelMatrix = dObj.shapesTranslationMatrix * dObj.shapesRotationMatrix * dObj.shapesScalingMatrix;
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		glUniformMatrix4fv(dObj.shapesUniformModel, 1, GL_FALSE, glm::value_ptr(dObj.shapesModelMatrix));


		//SET VIEW TO 2D
		//view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//SET VIEW TO 3D

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

		//view = LookAt(eye, eye + target, up);
		//glm::mat4 view = LookAt(eye, eye+target, up);
		glUniformMatrix4fv(dObj.shapesUniformView, 1, GL_FALSE, glm::value_ptr(dObj.view));
		

		dObj.shapesMVP = dObj.shapesProjection * dObj.view * dObj.shapesModelMatrix;
		glUniformMatrix4fv(dObj.shapesMatrixID, 1, GL_FALSE, &dObj.shapesMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform



		//glm::vec3 lightPos = glm::vec3(4,4,4);
		//glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);
		//SEND TO SHADER
		//glUniform4f(glGetUniformLocation(programShapeShaderID, "testColor"), 1.0f, 1.0f, 0.0f, 1.0f); //glUniform4f SHADERS REQ FRAG AS VEC4


		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesVertexBuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : Color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, dObj.shapesColorBuffer[vboID]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapesElementBuffer[vboID]);
		//glDrawElements(GL_TRIANGLES, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);
		//glDrawElements(GL_TRIANGLE_STRIP, sizeof(shapeInd), GL_UNSIGNED_INT, (void*)0);

		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
		glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(TriangleFanVertices)/sizeof(GLfloat)/3);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}
