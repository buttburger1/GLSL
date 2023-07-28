//BY BUTTBURGER 7/28/2023 EXPORT
//LIGHTING TUTORIAL
//https://learnopengl.com/
#include "Common.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
GLFWwindow*window;
int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

int imgwidth, imgheight;
bool hasAlpha;

float horizontalAngle = 3.14f;//Initial horizontal angle : toward -Z
float verticalAngle = 0.0f;//Initial vertical angle : none

float mouseSpeed = 0.005f;
float speed = 1.0f;
float deltaTime;
double currentTime;


//INSIDE
float modelX = 0.0f, modelY = 0.0f, modelZ = 0.0f;
float lightX = 5.0f, lightY = 0.0f, lightZ = 5.0f;
//OUTSIDE
//float modelX = 5.0f, modelY = 0.0f, modelZ = 5.0f;
//float lightX = 0.0f, lightY = 0.0f, lightZ = 0.0f;



float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
float scalingX = 1.0f, scalingY = 1.0f, scalingZ = 1.0f;
float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 3.0f;//Initial position : on +Z

glm::vec3 eye = glm::vec3(eyeX, eyeY, eyeZ);
glm::vec3 target, right, up;


glm::mat4 projection, view, ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix,
	mat4Rot,
	projectionLight, viewLight, ModelMatrixLight, MVPLight, RotationMatrixLight, TranslationMatrixLight, ScalingMatrixLight;


extern GLuint Texture[90000];
//GLuint MatrixID;//MOVED
//GLuint uniformModel[10], uniformView[10], uniformProjection[10];//MOVED
extern GLuint programID, MatrixID, uniformModel, uniformView, uniformProjection, uniformRotation,
	MatrixIDVBO, uniformModelVBO, uniformViewVBO, uniformProjectionVBO;

extern GLuint materialShaderID, lightShaderID,
	MatrixIDLight, uniformModelLight, uniformViewLight, uniformProjectionLight;

extern GLuint programFontID, fontMatrixID, fontUniformModel, fontUniformView, fontUniformProjection;//fontText
extern GLuint programShapesShaderID, shapesMatrixID, shapesUniformModel, shapesUniformView, shapesUniformProjection;

//////////////////////////////////////////////////////////////////////////////////////////////////////

char loadtexture[] = "texture.png", loadtexture1[] = "texture1.png", loadtexture2[] = "texture2.png";
char DAEfile[] = "box.dae";
char DAEtexture[] = "container2.png";
char DAEsphere[] = "sphere.dae";


int dostuff = 0, hasloaded = 0, loadonce = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////

drawObjects dObj;

int changeScene = 0;

float rotMat = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//BEZIER STUFFS
//https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
//https://gamedev.stackexchange.com/questions/49148/bezier-curve-not-drawn-correctly
//https://stackoverflow.com/questions/39173955/how-to-draw-a-bezier-curve-with-c-in-opengl-using-floating-point-values
//https://stackoverflow.com/questions/8307015/evaluating-3d-splines-exported-from-max-in-a-c-program
//https://stackoverflow.com/questions/9963551/replicating-blender-bezier-curves-in-a-c-program
//https://stackoverflow.com/questions/25453159/getting-consistent-normals-from-a-3d-cubic-bezier-path
//https://stackoverflow.com/questions/19605179/drawing-tangent-lines-for-each-point-in-bezier-curve
//https://cubic.org/docs/hermite.htm
//https://answers.unity.com/questions/451030/how-to-interprete-keyframeintangent-and-outtangent.html
//https://answers.unity.com/questions/438407/the-algorithm-of-curve-in-shuriken-particle-system.html
//https://medium.com/geekculture/2d-and-3d-b%C3%A9zier-curves-in-c-499093ef45a9
//https://greweb.me/2012/02/bezier-curve-based-easing-functions-from-concept-to-implementation
//https://www.geeksforgeeks.org/cubic-bezier-curve-implementation-in-c/
//CALCULATORS, GRAPHS, INTERPOLATION
//https://byjus.com/interpolation-calculator/
//https://www3.nd.edu/~gconant/bezier/
//https://www.geogebra.org/m/YGqtDGzK
//https://www.codesansar.com/numerical-methods/linear-interpolation-method-using-cpp-output.htm
//////////////////////////////////////////////////////////////////////////////////////////////////////
float getPt(float n1, float n2, float perc)
{
	float diff = n2 - n1;
	return n1 + (diff * perc);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//TEST
float testScaledValue;
float animScaleTime;

float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = animationTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////


void wait(float seconds)
{
	clock_t endwait;
	endwait = clock() + (clock_t)seconds * CLOCKS_PER_SEC;
	while(clock() < endwait){}
}


int main()
{
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLSL TEST!", NULL, NULL);//Open a window and create its OpenGL context

	if(window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(window, 5, 25);//glfwSetWindowPos(window, (mode->width - 200) / 2, (mode->height - 200) / 2);

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//GLFW_CURSOR_DISABLED);
	glfwPollEvents();
	//glfwSetCursorPos(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);//Set the mouse at the center of the screen
	glewExperimental = true;//Needed for core profile
	if(glewInit() != GLEW_OK)//Initialize GLEW
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	//Get version info
	const GLubyte*renderer = glGetString(GL_RENDERER);//get renderer string
	const GLubyte*version = glGetString(GL_VERSION);//version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	//glClearColor(0.0f, 1.0f, 0.0f, 0.0f);//Green background
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);//Blue background
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);//Accept fragment if it closer to the camera than the former one
	glEnable(GL_CULL_FACE);//Cull triangles which normal is not towards the camera
	glCullFace(GL_BACK);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glClearDepth(1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	int frames = 0;
	//double currentTime;//MOVED
	double limitFPS = 1.0f/60.0f;
	double lastTime = glfwGetTime();
	double timer = lastTime;
	bool mousefix = 0;

	dObj.VBOloadedID = 0;


	animScaleTime = 0.0f;
	//animScaleTime = 1.0f;


	for(;;)
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		double xpos, ypos;
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if(mousefix == 0)
			{
				xpos = float(SCREEN_WIDTH /2);
				ypos = float(SCREEN_HEIGHT/2);
				mousefix = 1;
				//printf("TEST XYPOS: %f - %f\n", xpos, ypos);
			}
			else
			{
				glfwGetCursorPos(window, &xpos, &ypos);
			}
			glfwGetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
			glfwSetCursorPos(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);//Reset mouse position for next frame
			//Compute new orientation
			horizontalAngle += mouseSpeed * float(SCREEN_WIDTH /2 - xpos);
			verticalAngle   += mouseSpeed * float(SCREEN_HEIGHT/2 - ypos);
			//printf("hA: %f vA: %f xPos: %f yPos: %f\n", horizontalAngle, verticalAngle, xpos, ypos);
		}
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//GLFW_CURSOR_DISABLED);
			mousefix = 0;
		}
		glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);
		//printf("SW: %d SH: %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);

		//projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		//glUniformMatrix4fv(uniformProjection[0], 1, GL_FALSE, glm::value_ptr(projection));

		//Direction : Spherical coordinates to Cartesian coordinates conversion
		target = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle));

		//Right vector
		right = glm::vec3(sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f));

		up = glm::cross(right, target);
		view = LookAt(eye, eye + target, up);

		keyPress();

		if(hasloaded == 0)
		{
			if(loadonce == 0)
			{
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//INIT BASIC TEXTURED SHADER
				printf("init VBO basic shader!\n");
				loadShaders(programID, "shaders/basic_vert.glsl", "shaders/basic_frag.glsl");
				MatrixID = glGetUniformLocation(programID, "MVP");
				uniformModel = glGetUniformLocation(programID, "model");
				uniformView = glGetUniformLocation(programID, "view");
				uniformProjection = glGetUniformLocation(programID, "projection");
				//////////////////////////////////////////////////////////////////////////////////////////////////////

				//INIT TEXTURED WITH MATERIAL SHADER
				printf("init VBO Material shader!\n");
				loadShaders(materialShaderID, "shaders/standard_vert.glsl", "shaders/standard_frag.glsl");
				MatrixIDVBO = glGetUniformLocation(materialShaderID, "MVP");
				uniformModelVBO = glGetUniformLocation(materialShaderID, "model");
				uniformViewVBO = glGetUniformLocation(materialShaderID, "view");
				uniformProjectionVBO = glGetUniformLocation(materialShaderID, "projection");

				uniformRotation = glGetUniformLocation(materialShaderID, "mat4Rot");

				//////////////////////////////////////////////////////////////////////////////////////////////////////

				//INIT LIGHT SHADER
				printf("init Light Material shader!\n");
				//loadShaders(lightShaderID, "standard_vert_lightcube.glsl", "shaders/standard_frag.glsl");
				loadShaders(lightShaderID, "shaders/standard_vert_lightcube.glsl", "shaders/standard_frag_lightcube.glsl");
				//loadShaders(lightShaderID, "shaders/standard_vert_lightcube.glsl", "shaders/standard_frag_lightcube.glsl");
				MatrixIDLight = glGetUniformLocation(lightShaderID, "MVP");
				uniformModelLight = glGetUniformLocation(lightShaderID, "model");
				uniformViewLight = glGetUniformLocation(lightShaderID, "view");
				uniformProjectionLight = glGetUniformLocation(lightShaderID, "projection");

				//////////////////////////////////////////////////////////////////////////////////////////////////////

				//INIT 2D FONT SHADER
				printf("init font shader!\n");
				loadShaders(programFontID, "shaders/2dfont_vert.glsl", "shaders/2dfont_frag.glsl");
				fontMatrixID = glGetUniformLocation(programFontID, "fontMVP");
				fontUniformModel = glGetUniformLocation(programFontID, "fontModel");
				fontUniformView = glGetUniformLocation(programFontID, "fontView");
				fontUniformProjection = glGetUniformLocation(programFontID, "fontProjection");

				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//INIT SHAPES SHADER
				printf("init shapes shader!\n");
				loadShaders(programShapesShaderID, "shaders/shapes_vert.glsl", "shaders/shapes_frag.glsl");
				shapesMatrixID = glGetUniformLocation(programShapesShaderID, "shapeMVP");
				shapesUniformModel = glGetUniformLocation(programShapesShaderID, "shapemodel");
				shapesUniformView = glGetUniformLocation(programShapesShaderID, "shapeview");
				shapesUniformProjection = glGetUniformLocation(programShapesShaderID, "shapeprojection");
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				loadonce = 1;
			}
			hasloaded = 1;
		}
		if(dostuff == 1)//N
		{
			//RELOAD
			printf("RELOAD: %d - %d\n", dostuff, hasloaded);

			//dObj.loadOnce[0] = 0;
			//dObj.drawDisable[0] = 0;
			changeScene = 0;


			//hasloaded = 0;
			dostuff = 0;
		}
		if(dostuff == 2)//M
		{
			printf("DELETE: %d - %d\n", dostuff, hasloaded);

			//deleteVBO(0);
			//deleteVBO(1);
			//for(int i=0;i<2;i++)deleteVBO(i);

			//dObj.drawDisable[0] = 1;
			changeScene = 1;

			//hasloaded = 1;
			dostuff = 0;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		//REFRESH LIST
		dObj.VBOloadedID = 0;

		//DRAW POINTS
		float x1 = 0.0f, x2 = 20.0f, x3 = 50.0f;
		float y1 = 0.0f, y2 = 20.0f, y3 = 15.0f;

		glPointSize(5);
		drawPoints(dObj.VBOloadedID, vec3(x1, y1, 0.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f));
		drawPoints(dObj.VBOloadedID, vec3(x2, y2, 0.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f));
		drawPoints(dObj.VBOloadedID, vec3(x3, y3, 0.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f));


		//BEZIER
		for(float i = 0.0f; i <= 1.0f; i += 0.001f)//60FPS//0.0166666666666667
		{			
			//The Green Line
			float xa = getPt( x1 , x2 , i );
			float ya = getPt( y1 , y2 , i );
			float xb = getPt( x2 , x3 , i );
			float yb = getPt( y2 , y3 , i );

			//The Black Dot
			float x = getPt( xa , xb , i );
			float y = getPt( ya , yb , i );

			glPointSize(1);
			//drawPixel( x , y , COLOR_RED );
			drawPoints(dObj.VBOloadedID, vec3(x, y, 0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
		}


		//The Green Line
		float xa = getPt( x1 , x2 , animScaleTime);
		float ya = getPt( y1 , y2 , animScaleTime);
		float xb = getPt( x2 , x3 , animScaleTime);
		float yb = getPt( y2 , y3 , animScaleTime);
		//The Black Dot
		float x = getPt( xa , xb , animScaleTime);
		float y = getPt( ya , yb , animScaleTime);

		//testScaledValue = GetScaleFactor(0.5f + currentTime, 3.0f + currentTime, currentTime + animScaleTime);
		testScaledValue = GetScaleFactor(0.0f + (float)currentTime, 1.0f + (float)currentTime, (float)currentTime + animScaleTime);
		//printf("testScale: %f\n", testScaledValue);
		//if(animScaleTime <= 2.5f)drawPoints(dObj.VBOloadedID, vec3(x, y, 0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));


		//INTERPOLATE TWO VECTORS
		glm::vec3 finalPosition = glm::mix(vec3(x1, y1, 0.0f),
			vec3(x2, y2, 0.0f),
			animScaleTime);

		//printf("TESTVEC X: %f Y: %f\n", finalPosition.x, finalPosition.y);

		glPointSize(7);
		if(animScaleTime <= 1.0f)drawPoints(dObj.VBOloadedID, vec3(x, y, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f));

		animScaleTime += 0.001f;
		//printf("animScale: %f\n", animScaleTime);
		//printf("testScale: %f animScale: %f\n", testScaledValue, animScaleTime);
		//if(animScaleTime >= 2.5f)animScaleTime = 1.0f;
		if(animScaleTime >= 1.0f)animScaleTime = 0.0f;




		//DRAW LINE
		drawLine(dObj.VBOloadedID, vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec3(-1000.0f, 0.0f, 0.0f), vec3(1000.0f, 0.0f, 0.0f));
		drawLine(dObj.VBOloadedID, vec4(0.0f, 1.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec3(0.0f, -1000.0f, 0.0f), vec3(0.0f, 1000.0f, 0.0f));
		drawLine(dObj.VBOloadedID, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, -1000.0f), vec3(0.0f, 0.0f, 1000.0f));
		//DRAW LINESTRIPS
		drawLineStrip(dObj.VBOloadedID);
		//DRAW LINELOOP
		drawLineLoop(dObj.VBOloadedID);
		//DRAW TRIANGLE
		drawTriangle(dObj.VBOloadedID);
		//DRAW TRIANGLE STRIP
		drawTriangleStrip(dObj.VBOloadedID, 0);
		//DRAW TRIANGLE FAN
		drawTriangleFan(dObj.VBOloadedID, 0);
		//LOAD 3D BOX
		drawVBO(dObj.VBOloadedID, materialShaderID, DAEfile, DAEtexture);
		//LOAD 3D LIGHT
		//drawVBO_light(dObj.VBOloadedID, lightShaderID, DAEfile);
		drawVBO_light(dObj.VBOloadedID, lightShaderID, DAEsphere);


		//LOAD 2D
		draw2dhud(dObj.VBOloadedID, loadtexture1, 10.0f, 10.0f, 100.0f, 100.0f);//draw2dhud(300.0f, 300.0f, 300.0f, -300.0f);//2DHUD
		draw2dhud(dObj.VBOloadedID, loadtexture2, 10.0f, 500.0f, 75.0f, 75.0f);//draw2dhud(300.0f, 300.0f, 300.0f, -300.0f);//2DHUD
		//DRAW FONT
		draw2dfont(dObj.VBOloadedID, "THIS IS A TEST STRING!", 150.0f, 50.0f, 100.0f, 100.0f);
		draw2dfont(dObj.VBOloadedID, "SCENE 1", 30.0f, 450.0f, 100.0f, 100.0f);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);

		glfwSwapInterval(0);
		glfwSwapBuffers(window);
		glfwPollEvents();

		frames++;
		lastTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = (float)(currentTime - lastTime);
		wait((float)limitFPS - deltaTime);

		/*
		double calcFrame;
		if(calcFrame >= 1.0f)calcFrame = 0.0f;
		//calcFrame += frames;
		//calcFrame /= 1000.0f;
		calcFrame += 0.01666665f;
		if(calcFrame > 1.0f)calcFrame = 1.0f;
		printf("FRAME: %d MS: %f\n", frames, calcFrame);

		//float animSpeedCounter;
		//if(animSpeedCounter > 1.0f)animSpeedCounter = 1.0f;
		//animSpeedCounter += deltaTime;
		//animSpeedCounter += calcFrame;
		//printf("animFPS: %f delta: %f\n", animSpeedCounter, deltaTime);
		*/



		if(currentTime - timer > 1.0f)//Reset after one second
		{
			timer++;
			//printf("FPS %d - %fms Time %f Last %f Delta %f\n", frames, 1000.0f/double(frames), currentTime, lastTime, deltaTime);
			//printf("FPS %d - %fms Time %f Last %f Delta %f animFPS: %f\n", frames, 1000.0/double(frames), currentTime, lastTime, deltaTime, animSpeedCounter);
			frames = 0;
			//animSpeedCounter = 0;
		}

		//https://www.glfw.org/docs/latest/group__input.html#gaa6cf4e7a77158a3b8fd00328b1720a4a
		//RESET TIME IN 24 HOURS
		if(currentTime >= 86400.0f)//if(currentTime >= 15.0f)
		{
			timer = 0;
			glfwSetTime(0);
		}

		if((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && glfwWindowShouldClose(window) == 0))break;
	}

	deleteVBOall();
	glfwTerminate();
	return 0;
}
