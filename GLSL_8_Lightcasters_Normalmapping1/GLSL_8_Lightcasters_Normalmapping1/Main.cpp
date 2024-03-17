//BY BUTTBURGER 3/17/2024 EXPORT
//TRS IDENTITY
//https://stackoverflow.com/questions/70617006/how-to-rotate-an-object-around-a-point-with-glm-opengl-c
//ROTATION
////https://stackoverflow.com/questions/8844585/glm-rotate-usage-in-opengl?rq=3
//LIGHTING TUTORIAL
//https://learnopengl.com/
//ANIMATION
//https://blender.stackexchange.com/questions/2533/is-there-a-way-to-convert-a-constraint-to-a-keyframe
//CAMERA
//https://stackoverflow.com/questions/70079733/opengl-camera-rotation-around-x
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
//////////////////////////////////////////////////////////////////////////////////////////////////////

//PLAYBACK
int ticks;
int tickCount;
float tickTime;
float playStart = 0.0f;
float playEnd = 0.0f;
float playDelta = 0.0f;
float playDeltaPercent = 0.0f;
float playLength = 10.0f;
float animationLength;

//////////////////////////////////////////////////////////////////////////////////////////////////////

//INSIDE
float modelX = 0.0f, modelY = 0.0f, modelZ = 0.0f;
float lightX = 5.0f, lightY = 0.0f, lightZ = 5.0f;
//OUTSIDE
//float modelX = 5.0f, modelY = 0.0f, modelZ = 5.0f;
//float lightX = 0.0f, lightY = 0.0f, lightZ = 0.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////

int myCam = 0;

float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
float scalingX = 1.0f, scalingY = 1.0f, scalingZ = 1.0f;
float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 20.0f;//Initial position : on +Z

glm::vec3 eye = glm::vec3(eyeX, eyeY, eyeZ);
//glm::vec3 target, right, up;

/*
float radius;//const
float cam1X;// = sin(currentTime) * radius;
float cam1Y;
float cam1Z;// = cos(currentTime) * radius;
glm::vec3 cameraPos1;// = glm::vec3(cam1X, cam1Y, cam1Z);
glm::vec3 objectPos1;// = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 up1;// = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::mat4 viewCamera1;// = glm::lookAt(cameraPos1, objectPos1, up1);
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
glm::mat4 projection,
	view, viewCamera1,
	ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix,
	mat4Rot,
	projectionLight, viewLight, ModelMatrixLight, MVPLight, RotationMatrixLight, TranslationMatrixLight, ScalingMatrixLight;
*/


//GLuint MatrixID;//MOVED
//GLuint uniformModel[10], uniformView[10], uniformProjection[10];//MOVED

//extern GLuint Texture[90000];

//extern GLuint programID, MatrixID, uniformModel, uniformView, uniformProjection, uniformRotation,
	//MatrixIDVBO, uniformModelVBO, uniformViewVBO, uniformProjectionVBO;

//extern GLuint materialShaderID, lightShaderID,
	//MatrixIDLight, uniformModelLight, uniformViewLight, uniformProjectionLight;

//extern GLuint programFontID, fontMatrixID, fontUniformModel, fontUniformView, fontUniformProjection;//fontText
//extern GLuint programShapesShaderID, shapesMatrixID, shapesUniformModel, shapesUniformView, shapesUniformProjection;

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

float percent(float a, float b)
{
	float result = 0;
	//result = ((b - a) * 100) / a;
	result = a / b;

	return result;
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
	if(!glfwInit())//Initialise GLFW
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
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLSL TEST", NULL, NULL);//Open a window and create its OpenGL context

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

	//glClearColor(0.0f, 1.0f, 0.0f, 1.0f);//Green background
	//glClearColor(0.0f, 0.0f, 0.5f, 1.0f);//Blue background
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);//Grey background
	glEnable(GL_DEPTH_TEST);//Enable depth test
	glDepthFunc(GL_LESS);//Accept fragment if it closer to the camera than the former one
	glEnable(GL_CULL_FACE);//Cull triangles which normal is not towards the camera
	glCullFace(GL_BACK);//DEFAULT FACE

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glClearDepth(1.0f);//glClearDepth(1.0f); //Set background depth to farthest
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	int frames = 0;
	//double currentTime;//MOVED
	double limitFPS = 1.0f/60.0f;//1.0/60.0f;//MAXFPS
	double lastTime = glfwGetTime();
	double timer = lastTime;
	bool mousefix = 0;

	dObj.VBOloadedID = 0;


	animScaleTime = 0.0f;
	//animScaleTime = 1.0f;


	for(;;)//for(float i = 0.0f; i < 1.0f; i += 0.1f)
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		double xpos, ypos;
		xpos = float(SCREEN_WIDTH /2);
		ypos = float(SCREEN_HEIGHT/2);
		glfwGetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if(mousefix == 0)
			{
				//xpos = float(SCREEN_WIDTH /2);
				//ypos = float(SCREEN_HEIGHT/2);
				mousefix = 1;
				//printf("TEST XYPOS: %f - %f\n", xpos, ypos);
			}
			else
			{
				glfwGetCursorPos(window, &xpos, &ypos);
			}
			//glfwGetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
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

		keyPress();
		
		//projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		//glUniformMatrix4fv(uniformProjection[0], 1, GL_FALSE, glm::value_ptr(projection));

		//Direction : Spherical coordinates to Cartesian coordinates conversion
		dObj.target = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle));

		//Right vector
		dObj.right = glm::vec3(sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f));

		dObj.up = glm::cross(dObj.right, dObj.target);
		//view = LookAt(eye, eye + target, up);
		
		/*
		if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		{
		if(myCam == 1)myCam = 0;
		else
		{
			myCam += 1;
		}
		printf("myCam: %d\n", myCam);
		}
		*/
		
		dObj.radius = 20.0f;
		dObj.cam1X = (float)sin(currentTime) * dObj.radius;
		//cam1Y = 5.0f;
		dObj.cam1Y = lightY;
		dObj.cam1Z = (float)cos(currentTime) * dObj.radius;
		dObj.cameraPos1 = glm::vec3(dObj.cam1X, dObj.cam1Y, dObj.cam1Z);//glm::vec3
		dObj.objectPos1 = glm::vec3(0.0f, 0.0f, 0.0f);//glm::vec3
		dObj.up1 = glm::vec3(0.0f, 1.0f, 0.0f);//glm::vec3
		dObj.viewCamera1 = glm::lookAt(dObj.cameraPos1, dObj.objectPos1, dObj.up1);//glm::mat4


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


		/*
		switch(myCam)
		{
		case 0:
			view = LookAt(eye, eye + target, up);
			break;

		case 1:
			view = viewCamera1;
			break;
		
		default:
			printf("myCam: %d\n", myCam);
		}
		printf("myCam1: %d\n", myCam);
		*/


		//START HERE
		if(hasloaded == 0)
		{
			printf("STARTING\n");
			if(loadonce == 0)
			{
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//INIT BASIC TEXTURED SHADER
				printf("init VBO basic shader\n");
				loadShaders(dObj.programID, "shaders/basic_vert.glsl", "shaders/basic_frag.glsl");
				dObj.MatrixID = glGetUniformLocation(dObj.programID, "MVP");
				dObj.uniformModel = glGetUniformLocation(dObj.programID, "model");
				dObj.uniformView = glGetUniformLocation(dObj.programID, "view");
				dObj.uniformProjection = glGetUniformLocation(dObj.programID, "projection");

				//dObj.ModelView3x3MatrixID = glGetUniformLocation(dObj.programID, "MV3x3");

				//////////////////////////////////////////////////////////////////////////////////////////////////////

				//INIT TEXTURED WITH MATERIAL SHADER
				printf("init VBO Material shader\n");
				loadShaders(dObj.materialShaderID, "shaders/standard_vert.glsl", "shaders/standard_frag.glsl");
				dObj.MatrixIDVBO = glGetUniformLocation(dObj.materialShaderID, "MVP");
				dObj.uniformModelVBO = glGetUniformLocation(dObj.materialShaderID, "model");
				dObj.uniformViewVBO = glGetUniformLocation(dObj.materialShaderID, "view");
				dObj.uniformProjectionVBO = glGetUniformLocation(dObj.materialShaderID, "projection");

				dObj.uniformRotation = glGetUniformLocation(dObj.materialShaderID, "mat4Rot");
				//dObj.ModelView3x3MatrixID = glGetUniformLocation(dObj.materialShaderID, "MV3x3");
				
				//////////////////////////////////////////////////////////////////////////////////////////////////////

				//INIT LIGHT SHADER
				printf("init Light Material shader\n");
				//loadShaders(lightShaderID, "standard_vert_lightcube.glsl", "shaders/standard_frag.glsl");
				loadShaders(dObj.lightShaderID, "shaders/standard_vert_lightcube.glsl", "shaders/standard_frag_lightcube.glsl");
				//loadShaders(lightShaderID, "shaders/standard_vert_lightcube.glsl", "shaders/standard_frag_lightcube.glsl");
				dObj.MatrixIDLight = glGetUniformLocation(dObj.lightShaderID, "MVP");
				dObj.uniformModelLight = glGetUniformLocation(dObj.lightShaderID, "model");
				dObj.uniformViewLight = glGetUniformLocation(dObj.lightShaderID, "view");
				dObj.uniformProjectionLight = glGetUniformLocation(dObj.lightShaderID, "projection");

				//////////////////////////////////////////////////////////////////////////////////////////////////////

				//INIT 2D FONT SHADER
				printf("init font shader\n");
				loadShaders(dObj.programFontID, "shaders/2dfont_vert.glsl", "shaders/2dfont_frag.glsl");
				dObj.fontMatrixID = glGetUniformLocation(dObj.programFontID, "fontMVP");
				dObj.fontUniformModel = glGetUniformLocation(dObj.programFontID, "fontModel");
				dObj.fontUniformView = glGetUniformLocation(dObj.programFontID, "fontView");
				dObj.fontUniformProjection = glGetUniformLocation(dObj.programFontID, "fontProjection");

				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//INIT SHAPES SHADER
				printf("init shapes shader\n");
				loadShaders(dObj.programShapesShaderID, "shaders/shapes_vert.glsl", "shaders/shapes_frag.glsl");
				dObj.shapesMatrixID = glGetUniformLocation(dObj.programShapesShaderID, "shapeMVP");
				dObj.shapesUniformModel = glGetUniformLocation(dObj.programShapesShaderID, "shapemodel");
				dObj.shapesUniformView = glGetUniformLocation(dObj.programShapesShaderID, "shapeview");
				dObj.shapesUniformProjection = glGetUniformLocation(dObj.programShapesShaderID, "shapeprojection");
				//////////////////////////////////////////////////////////////////////////////////////////////////////
				//initVBO(DAEfile, DAEtexture, 0);//LOAD OBJ MODEL
				//loadTriangle(1);
				//init2dhud(2, loadtexture1, 10.0f, 10.0f, 100.0f, 100.0f);
				//init2dhud(3, loadtexture2, 10.0f, 500.0f, 75.0f, 75.0f);
				loadonce = 1;
			}

			/*
			if(notrender == 1)
			{
				initVBO(DAEfile, DAEtexture, 0);//LOAD OBJ MODEL
				//delete textureImage;//REFRESH GENTEXTURES
				//Texture[0] = loadPngImage(DAEtexture, imgwidth, imgheight, hasAlpha, &textureImage);
				//delete textureImage;//REFRESH GENTEXTURES
				notrender = 0;

				//initVBO(loadmodel, loadtexture);//LOAD FBX MODEL
				//initVBO(DAEfile, DAEtexture, 1);//LOAD OBJ MODEL

				//init2dhud(0, loadtexture1);
				//initVBO(DAEfile, DAEtexture, 1);//LOAD OBJ MODEL

				//initVBO(loadmodel, loadtexture, 0);//LOAD OBJ MODEL
				//initVBO(loadmodel2, loadtexture2, 1);//LOAD OBJ MODEL
			}
			*/


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
		drawPoints(dObj.VBOloadedID, vec3(x1, y1, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f));
		drawPoints(dObj.VBOloadedID, vec3(x2, y2, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f));
		drawPoints(dObj.VBOloadedID, vec3(x3, y3, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f));


		//for(; tickTime <= currentTime; tickCount++)
		for(; tickTime <= currentTime - 0.6f; tickCount++)
		{
			tickTime = tickCount * 0.6f;

			//printf("TICKS: %d TICKTIME: %f ACTUAL TIME: %f\n", ticks, tickTime, currentTime);
			//printf("FPS %d - %fms Time %f Last %f Delta %f\n", frames, 1000.0/double(frames), currentTime, lastTime, deltaTime);
		}


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//PLAY ANIMATION
		if(playStart == 0.0f)
		{
			playStart = (float)currentTime;
			playEnd = (float)currentTime + playLength;
		}
		//playDeltaPercent = playStart / currentTime;


		if(currentTime <= playEnd)
		{
			//ASCENDING(FORWARD)
			//playDeltaPercent = currentTime / playEnd;//old
			playDeltaPercent = (((float)currentTime - playStart) * 1.0f) / (playEnd - playStart);
			//DESCENDING(BACKWARD)
			//playDeltaPercent = playStart / currentTime;//old
			//playDeltaPercent = 1.0f - ((((float)currentTime - playStart) * 1.0f) / (playEnd - playStart));



			//if(playDeltaPercent > 1.0f) playStart = 0.0f;
			//printf("1Start: %f End: %f Time: %f DP: %f\n", playStart, playEnd, currentTime, playDeltaPercent);
		}
		else if(currentTime > playEnd)//REPLAY
		{
			playStart = (float)currentTime;
			playEnd = (float)currentTime + playLength;
			//playDeltaPercent = playStart / currentTime;
			//printf("2Start: %f End: %f Time: %f DP: %f\n", playStart, playEnd, currentTime, playDeltaPercent);
		}


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//BEZIER
		//https://www.jasondavies.com/animated-bezier/
		//https://pomax.github.io/bezierinfo/
		//https://supermicrofun.com/curves/
		//https://svg-path-visualizer.netlify.app/bezier-curve/
		//DeCasteljau
		//https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
		//https://stackoverflow.com/questions/37642168/how-to-convert-quadratic-bezier-curve-code-into-cubic-bezier-curve
		for(float i = 0.0f; i <= 1.0f; i += 0.001f)
		{
			//The Green Line
			float xa = getPt( x1 , x2 , i );
			float ya = getPt( y1 , y2 , i );
			float xb = getPt( x2 , x3 , i );
			float yb = getPt( y2 , y3 , i );
			//xc = getPt( x3 , x4 , i );
			//yc = getPt( y3 , y4 , i );

			//The Black Dot
			float x = getPt( xa , xb , i );//xm = getPt( xa , xb , i );
			float y = getPt( ya , yb , i );//ym = getPt( ya , yb , i );
			//xn = getPt( xb , xc , i );
			//yn = getPt( yb , yc , i );


			vec2 test3P = (pow((1-i), 2) * vec2(x1, y1)) + (2*(1-i)*(i * vec2(x2, y2))) + (pow(i, 2) * vec2(x3, y3));
			//printf("test3P X: %f Y: %f\n", test3P.x, test3P.y);


			glPointSize(1);
			//drawPixel( x , y , COLOR_RED );
			//drawPoints(dObj.VBOloadedID, vec3(x, y, 0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
			drawPoints(dObj.VBOloadedID, vec3(test3P.x, test3P.y, 0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));


			vec2 p0(0.0f, 0.0f);
			vec2 p1(0.0f, 0.0f);
			vec2 p2(8.0f, 0.0f);
			vec2 p3(8.0f, 0.0f);

			//https://stackoverflow.com/questions/71100719/calculate-bezier-curve-and-draw
			//vec2 testP = (1.0f-i)^3 * P0 + 3*i*(1.0f-i)^2*P1 + 3*i^2*(1.0f-i)*P2 + i^3*P3;
			vec2 testP = pow((1-i),3) * p0 + 3 * pow((1-i),2) * i * p1 + 3 * (1-i) * pow(i,2) * p2 + pow(i,3) * p3;
			//printf("i: %f testP X: %f Y: %f\n", i, testP.x, testP.y);

			
		}


		//https://javascript.info/bezier-curve
		//The formula for a 2-points curve:
		//P = (1-t)P1 + tP2

		//For 3 control points:
		//P = (1-t)^2P1 + 2(1-t)tP2 + t^2P3

		//For 4 control points:
		//P = (1-t)^3P1 + 3(1?t)^2tP2 +3(1-t)t^2P3 + t^3P4


		//Bezier 4 points
		//https://stackoverflow.com/questions/71100719/calculate-bezier-curve-and-draw
		//p = (1-t)^3 *P0 + 3*t*(1-t)^2*P1 + 3*t^2*(1-t)*P2 + t^3*P3
		//Cubic quadratics
		//p = (1-t)^2 *P0 + 2*(1-t)*t*P1 + t*t*P2


		//De Casteljau
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
		if(animScaleTime <= 1.0f)drawPoints(dObj.VBOloadedID, vec3(x, y, 0.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f));

		//WHEN AND WHERE TO RENDER
		//animScaleTime += 0.001f;//TEST
		animScaleTime = playDeltaPercent;

		//printf("animScaleTime: %f\n", animScaleTime);
		//printf("testScale: %f animScale: %f\n", testScaledValue, animScaleTime);
		//if(animScaleTime >= 2.5f)animScaleTime = 1.0f;
		if(animScaleTime >= 1.0f)animScaleTime = 0.0f;


		//HERMITE CURVE INTERPOLATION (STEPS)
		//https://cubic.org/docs/hermite.htm
		//https://discussions.unity.com/t/how-to-interprete-keyframe-intangent-and-outtangent-values/70249
		//for(int t=0; t < steps; t++)
		//for(float t = 0.0f; t < 2.0f; t += 1.0f)
		for(int t = 0; t < 2; t += 1)
		{
			//float s = (float)t / (float)steps;    // scale s to go from 0 to 1
			float s = (float)t / 1.0f;    // scale s to go from 0 to 1
			//float h1 =  2s^3 - 3s^2 + 1;          // calculate basis function 1
			float h1 = 2* pow(s, 3) - 3* pow(s, 2) + 1;          // calculate basis function 1
			//float h2 = -2s^3 + 3s^2;              // calculate basis function 2
			float h2 = -2* pow(s, 3) + 3* pow(s, 2);              // calculate basis function 2
			//float h3 =   s^3 - 2*s^2 + s;         // calculate basis function 3
			float h3 = pow(s,3) - 2* pow(s, 2) + s;         // calculate basis function 3
			//float h4 =   s^3 -  s^2;              // calculate basis function 4
			float h4 = pow(s,3) - pow(s,2);              // calculate basis function 4

			//X POINTS
			//vec2 p1(0.0f,0.0f);
			float p1 = 0.0f;
			//vec2 p2(8.0f,0.0f);
			float p2 = 8.0f;

			//TEST X TANGENT 1
			vec2 tangentOut1(0.4107311f, 0.0f);
			vec2 tangentIn1(-0.3440644f, 0.0f);
			//TEST X TANGENT 2
			vec2 tangentOut2(1.377398f, 8.0f);
			vec2 tangentIn2(0.6226022f, 8.0f);

			vec2 p;
			if(t == 0)
			{
				p = vec2(h1*p1) +                    // multiply and sum all funtions
					vec2(h2*p2) +                    // together to build the interpolated
					vec2(h3*tangentOut1) +                    // point along the curve.
					vec2(h4*tangentIn1);
			}
			if(t == 1)
			{
				p = vec2(h1*p1) +                    // multiply and sum all funtions
					vec2(h2*p2) +                    // together to build the interpolated
					vec2(h3*tangentOut2) +                    // point along the curve.
					vec2(h4*tangentIn2);
			}
			//lineto (p)                            // draw to calculated point on the curve
			//printf("t: %f X: %f Y: %f\n", t, p.x, p.y);
			//printf("t: %d X: %f Y: %f\n", t, p.x, p.y);
		}


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
		//printf("FIRST VBO\n");
		//drawVBO(dObj.VBOloadedID, dObj.materialShaderID, DAEfile, DAEtexture, 0);
		//printf("SECOND VBO\n");
		//drawVBO(dObj.VBOloadedID, dObj.programShapesShaderID, "box_red.dae", DAEtexture, 0);
		//printf("THIRD VBO\n");
		//drawVBO(dObj.VBOloadedID, dObj.programShapesShaderID, "box_green.dae", DAEtexture, 0);
		//drawVBO(dObj.VBOloadedID, dObj.materialShaderID, "box_green.dae", 0, 0);//TESTCOLORMATERIAL2
		//printf("FOURTH VBO\n");
		//drawVBO(dObj.VBOloadedID, dObj.programShapesShaderID, "box_blue.dae", DAEtexture, 0);
		//printf("FIFTH VBO\n");
		
		//drawVBO(dObj.VBOloadedID, dObj.materialShaderID, "test.dae", 0, 0);
		//drawVBO(dObj.VBOloadedID, dObj.materialShaderID, "test.dae", DAEtexture, 0);
		//drawVBO(dObj.VBOloadedID, dObj.lightShaderID, "test.dae", DAEtexture, 0);

		//MULTIPLE OBJECTS
		drawVBO(dObj.VBOloadedID, dObj.materialShaderID, "box5.dae", DAEtexture, 0);
		//drawVBO(dObj.VBOloadedID, dObj.programShapesShaderID, "untitled.dae", DAEtexture, 0);
		//drawVBO(dObj.VBOloadedID, dObj.materialShaderID, "untitled.dae", DAEtexture, 0);
		//drawVBO(dObj.VBOloadedID, dObj.lightShaderID, "untitled.dae", 0, 0);
		
		//LOAD 3D LIGHT SOURCE, AVOID USING MATERIALS
		//drawVBO(dObj.VBOloadedID, dObj.lightShaderID, "untitled.dae", 0);
		//drawVBO(dObj.VBOloadedID, dObj.lightShaderID, DAEsphere, DAEtexture);
		drawVBO(dObj.VBOloadedID, dObj.lightShaderID, DAEsphere, 0, 1);
		//drawVBO_light(dObj.VBOloadedID, dObj.lightShaderID, DAEsphere);
		
		//LOAD 2D
		draw2dhud(dObj.VBOloadedID, loadtexture1, 10.0f, 10.0f, 100.0f, 100.0f);//draw2dhud(300.0f, 300.0f, 300.0f, -300.0f);//2DHUD
		draw2dhud(dObj.VBOloadedID, loadtexture2, 10.0f, 500.0f, 75.0f, 75.0f);//draw2dhud(300.0f, 300.0f, 300.0f, -300.0f);//2DHUD
		//DRAW FONT
		draw2dfont(dObj.VBOloadedID, "THIS IS A TEST STRING", 150.0f, 50.0f, 100.0f, 100.0f);
		draw2dfont(dObj.VBOloadedID, "SCENE 1", 30.0f, 450.0f, 100.0f, 100.0f);


		//////////////////////////////////////////////////////////////////////////////////////////////////////
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);

		glfwSwapInterval(0);//UNLOCKFPS?
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
			//printf("FPS %d - %fms Time %f Last %f Delta %f\n", frames, 1000.0/double(frames), currentTime, lastTime, deltaTime);
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