#include "Common.h"

extern GLFWwindow*window;

extern glm::vec3 eye, right, target;

extern float speed;

extern float modelX, modelY, modelZ;
extern float lightX, lightY, lightZ;

extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;

extern bool hasloaded;
extern int dostuff;
int keyB = 0, keyN = 0, keyM = 0;

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
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)eye += target * speed;//Move forward
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)eye -= target * speed;//Move backward
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)eye +=  right * speed;//Strafe right
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)eye -=  right * speed;//Strafe left

	//LIGHT TRANSLATIONS
	//X AXIS TRANSLATION
	if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)lightX += 1.5;
	if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)lightX -= 1.5;
	//Y AXIS TRANSLATION
	if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)lightY += 1.5;
	if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)lightY -= 1.5;
	//Z AXIS TRANSLATION
	if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)lightZ += 1.5;
	if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)lightZ -= 1.5;

	//MODEL TRANSLATIONS
	//X AXIS TRANSLATION
	if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)modelX += 1.5;
	if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)modelX -= 1.5;
	//Y AXIS TRANSLATION
	if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)modelY += 1.5;
	if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)modelY -= 1.5;
	//Z AXIS TRANSLATION
	if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)modelZ += 1.5;
	if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)modelZ -= 1.5;

	//EULER X ROTATION
	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)rotX += 3;
	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)rotX -= 3;
	//EULER Y ROTATION
	if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)rotY += 3;
	if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)rotY -= 3;
	//EULER Z ROTATION
	if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)rotZ += 3;
	if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)rotZ -= 3;
	//X AXIS SCALING
	if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)scalingX += 3;
	if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)scalingX -= 3;
	//Y AXIS SCALING
	if(glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)scalingY += 3;
	if(glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)scalingY -= 3;
	//Z AXIS SCALING
	if(glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)scalingZ += 3;
	if(glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS)scalingZ -= 3;

	//LOAD MODELS
	keyB = keylift(GLFW_KEY_B, keyB, 0);
	keyN = keylift(GLFW_KEY_N, keyN, 1);
	keyM = keylift(GLFW_KEY_M, keyM, 2);
}
