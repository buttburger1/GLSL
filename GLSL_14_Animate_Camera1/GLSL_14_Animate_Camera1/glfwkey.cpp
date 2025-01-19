#include "Common.h"

extern GLFWwindow*window;

extern drawObjects dObj;

extern glm::vec3 eye;//right, target;

extern bool hasloaded;

extern int dostuff;
extern int myCam;

extern float speed;
extern float playbackSpeed;

extern float modelX, modelY, modelZ;
extern float lightX, lightY, lightZ;
extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;

int keylift(int key, int oldState, int function)
{
	//printf("oldState: %d\n", oldState);
	int newState = glfwGetKey(window, key);
	if(newState == GLFW_RELEASE && oldState == GLFW_PRESS)
	{
		printf("%d - %d - %d\n", oldState, newState, key);
		dostuff = function;
	}
	oldState = newState;
	return oldState;
}

void keyPress()
{
	//MOVE KEYS
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)eye -= dObj.target * speed;//Move backward
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)eye += dObj.target * speed;//Move forward
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)eye -=  dObj.right * speed;//Strafe left
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)eye +=  dObj.right * speed;//Strafe right

	//CAMERA
	if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){myCam = 0;printf("myCam: %d\n", myCam);}
	if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){myCam = 1;printf("myCam: %d\n", myCam);}
	if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){myCam = 2;printf("myCam: %d\n", myCam);}

	//ANIMATION PLAYBACK
	if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){playbackSpeed -= 0.01f;printf("playbackSpeed: %f\n", playbackSpeed);}
	if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){playbackSpeed += 0.01f;printf("playbackSpeed: %f\n", playbackSpeed);}
}