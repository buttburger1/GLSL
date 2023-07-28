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
	double currentTime;
	double limitFPS = 1.0f/60.0f;
	double lastTime = glfwGetTime();
	double timer = lastTime;
	bool mousefix = 0;


	dObj.VBOloadedID = 0;

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
		drawPoints(dObj.VBOloadedID);
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
		if(currentTime - timer > 1.0f)//Reset after one second
		{
			timer++;
			//printf("FPS %d - %fms Time %f Last %f Delta %f\n", frames, 1000.0/double(frames), currentTime, lastTime, deltaTime);
			frames = 0;
		}
		if((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && glfwWindowShouldClose(window) == 0))break;
	}

	deleteVBOall();
	glfwTerminate();
	return 0;
}
