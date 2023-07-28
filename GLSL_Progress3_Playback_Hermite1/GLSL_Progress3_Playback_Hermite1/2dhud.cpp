#include "Common.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
extern GLFWwindow*window;
extern bool hasAlpha;
extern int imgwidth, imgheight;


GLuint fontText, programFontID, fontMatrixID, fontUniformModel, fontUniformView, fontUniformProjection, fontVertexArrayID[90000],
	fontVertexBuffer[1000][10000], fontElementBuffer[1000][10000];

glm::mat4 fontProjection, fontView, fontModelMatrix, fontMVP, fontRotationMatrix, fontTranslationMatrix, fontScalingMatrix;


//GLuint hudTexture;
//GLuint MatrixID2D, TextureID2D, program2DshaderID, program2DuniformID, hud2dVertexBufferID, hud2dUVBufferID;

extern GLuint programID, MatrixID,
	diffuseID[90000], specularID[90000], emissionID[90000], Texture[90000], LightID[90000],
	VertexArrayID[90000], vertexbuffer[90000], colorbuffer[90000], uvbuffer[90000], normalbuffer[90000], elementbuffer[90000],
	uniformModel, uniformView, uniformProjection;


//extern glm::mat4 projection, view, ModelMatrix;
extern glm::mat4 projection, view, ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix;
//glm::mat4 projection2D, view2D, ModelMatrix2D, MVP2D, RotationMatrix2D, TranslationMatrix2D, ScalingMatrix2D;


//GLuint uniformModel2D[10], uniformView2D[10], uniformProjection2D[10];
//extern float eyeX, eyeY, eyeZ; //Initial position : on +Z
//extern glm::vec3 eye;
//extern glm::mat4 projection, view, ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix;

//////////////////////////////////////////////////////////////////////////////////////////////////////


float myUV[] =
{
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
};

unsigned int myInd[] =
{
	0,1,2,
	0,2,3,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

extern drawObjects dObj;

//////////////////////////////////////////////////////////////////////////////////////////////////////


/*
void init2dhud(int vboID, char*fName, float x, float y, float xwidth, float yheight)
{
	printf("init2dhud shader!\n");
	loadShaders(programID, "shaders/vert_shader.glsl", "shaders/frag_shader.glsl");
	//loadShaders(program2DshaderID, "shaders/vert_2dhud.glsl", "shaders/frag_2dhud.glsl");//programID//program2DshaderID
	MatrixID = glGetUniformLocation(programID, "MVP");
	uniformModel[0] = glGetUniformLocation(programID, "model");
	uniformView[0] = glGetUniformLocation(programID, "view");
	uniformProjection[0] = glGetUniformLocation(programID, "projection");


	Texture[vboID] = loadPngImage(fName, imgwidth, imgheight, hasAlpha, &textureImage);//hudTexture
	//glGenBuffers(1, &hud2dVertexBufferID);
	//glGenBuffers(1, &hud2dUVBufferID);
	//TextureID[0] = glGetUniformLocation(programID, "myTexture");
	TextureID[vboID] = glGetUniformLocation(programID, "myTexture");


	glGenVertexArrays(1, &VertexArrayID[vboID]);
	glBindVertexArray(VertexArrayID[vboID]);


	float left = x, top = y, right = x + xwidth, bottom = y + yheight;
	float myVT[] =
	{
		//-0.50f,  0.50f, -1.0f,
		//-0.50f, -0.50f, -1.0f,
		// 0.50f,  0.50f, -1.0f,
		// 0.50f, -0.50f, -1.0f,

		//original
		//left, top, 0,
		//left, bottom, 0,
		//right, top, 0,
		//right, bottom, 0,

		//fixed
		left, bottom, 0,
		left, top, 0,
		right, top, 0,
		right, bottom, 0,
	};


	//GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer[vboID]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(myVT), myVT, GL_STATIC_DRAW);
	//GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer[vboID]);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(myUV), myUV, GL_STATIC_DRAW);
	//GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer[vboID]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboID]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myInd), myInd, GL_STATIC_DRAW);
}
*/


//void draw2dhud(int vboID)
void draw2dhud(int vboID, char*fName, float x, float y, float xwidth, float yheight)
{
	if(dObj.loadOnce[vboID] == 0)
	{
		Texture[vboID*3+0] = loadPngImage(fName, imgwidth, imgheight, hasAlpha, &textureImage);//hudTexture
		//glGenBuffers(1, &hud2dVertexBufferID);
		//glGenBuffers(1, &hud2dUVBufferID);
		//TextureID[0] = glGetUniformLocation(programID, "myTexture");
		diffuseID[vboID] = glGetUniformLocation(programID, "myTexture");

		glGenVertexArrays(1, &VertexArrayID[vboID]);
		glBindVertexArray(VertexArrayID[vboID]);
		
		float left = x, top = y, right = x + xwidth, bottom = y + yheight;
		float myVT[] =
		{
			left, bottom, 0,
			left, top, 0,
			right, top, 0,
			right, bottom, 0,
		};

		//GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(myVT), myVT, GL_STATIC_DRAW);
		//GLuint uvbuffer;
		glGenBuffers(1, &uvbuffer[vboID]);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(myUV), myUV, GL_STATIC_DRAW);
		//GLuint elementbuffer;
		glGenBuffers(1, &elementbuffer[vboID]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboID]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myInd), myInd, GL_STATIC_DRAW);

		dObj.loadOnce[vboID] = 1;
	}


	if(dObj.drawDisable[vboID] == 0)
	{
		glCullFace(GL_BACK);
		glUseProgram(programID);//program2DshaderID
		//glUseProgram(program2DshaderID);//program2DshaderID
		int sw, sh;
		glfwGetWindowSize(window, &sw, &sh);
		double mxpos, mypos;
		glfwGetCursorPos(window, &mxpos, &mypos);
		//printf("Mouse X: %f Y: %f Screen W: %d H: %d\n", mxpos, mypos, sw, sh);
		////////////////////////////////////////////////////////////////////////////
		/*
		TextureID[vboID] = glGetUniformLocation(program2DshaderID, "myTexture2D");//program2DshaderID
		MatrixID2D = glGetUniformLocation(program2DshaderID, "MVP2D");//program2DshaderID

		uniformModel2D[0] = glGetUniformLocation(program2DshaderID, "model2D");//program2DshaderID
		uniformView2D[0] = glGetUniformLocation(program2DshaderID, "view2D");//program2DshaderID
		uniformProjection2D[0] = glGetUniformLocation(program2DshaderID, "projection2D");//program2DshaderID
		*/


		projection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		//projection2D = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		//projection2D = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 1000.0f);
		//projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		//GLuint uniformView = glGetUniformLocation(programID, "view");//program2DshaderID
		//glUniformMatrix4fv(uniformView[0], 1, GL_FALSE, glm::value_ptr(view));
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		//glUniformMatrix4fv(uniformModel[0], 1, GL_FALSE, glm::value_ptr(model));


		TranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//ORIGIN AT BOTTOM LEFT
		//TranslationMatrix2D = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//ORIGIN AT BOTTOM LEFT
		//TranslationMatrix2D = translate(mat4(), glm::vec3(0.0f, 0.5f * yheight, 0.0f));//ORIGIN AT TOP LEFT
		//TranslationMatrix2D = translate(mat4(), glm::vec3(-0.5f * xwidth, -0.5f * yheight, 0.0f));//ORIGIN AT CENTER
		//TranslationMatrix2D = translate(mat4(), glm::vec3(0.5f * xwidth, 0.0f, 0.0f));//ORIGIN AT BOTTOM RIGHT
		//TranslationMatrix2D = translate(mat4(), glm::vec3(0.5f * xwidth, 0.5f * yheight, 0.0f));//ORIGIN AT TOP RIGHT

		//RotationMatrix2D = rotate(mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		RotationMatrix = rotate(mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));//scalingX, scalingY, scalingZ));
		//ScalingMatrix2D = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));//scalingX, scalingY, scalingZ));


		//ModelMatrix2D = TranslationMatrix2D * RotationMatrix2D * ScalingMatrix2D;
		ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
		//glUniformMatrix4fv(uniformModel2D[0], 1, GL_FALSE, glm::value_ptr(ModelMatrix2D));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ModelMatrix));



		//view2D = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glm::mat4 view = LookAt(eye, eye+target, up);
		//glUniformMatrix4fv(uniformView2D[0], 1, GL_FALSE, glm::value_ptr(view2D));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));



		MVP = projection * view * ModelMatrix;
		//glUniformMatrix4fv(uniformModel[0], 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(MatrixID2D, 1, GL_FALSE, &MVP2D[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform
		//MVP2D = projection2D * view2D * ModelMatrix2D;



		/*
		////////////////////////////////////////////////////////////////////////////
		//draw2dhud(-0.5f, 0.5f, 1.0f, -1.0f);
		//printf("L: %f R: %f T: %f B: %f\n", left, right, top, bottom);
		//LEFT
		if(x < sw/2)left = -1*((float)x / sw);
		if(x > sw/2)left = (float)x / sw;
		//BOTTOM
		if(y < sh/2)top = 1*((float)y / sh);
		if(y > sh/2)top = -(float)y / sh;
		right  = left + (float)xwidth / sw;//RIGHT
		bottom = top - (float)yheight / sh;//TOP

		//printf("L: %f R: %f T: %f B: %f\n", left, right, top, bottom);

		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

		//left = x;
		//right = x + xwidth;
		//top = y;
		//bottom = y + yheight;
		*/



		//Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture[vboID*3+0]);//hudTexture
		//Set "program2DuniformID" to use Texture Unit 0
		//glUniform1i(program2DuniformID, 1);


		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboID]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//INDICES
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboID]);
		glDrawElements(GL_TRIANGLES, sizeof(myInd), GL_UNSIGNED_INT, (void*)0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}


GLuint hud2dVertexBufferID;


//Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;  //ID handle of the glyph texture
	glm::ivec2 Size;   //Size of glyph
	glm::ivec2 Bearing;//Offset from baseline to left/top of glyph
	GLuint Advance;    //Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;


int fontLoop[1000];
int chID[1000][1000];

unsigned int fontInd[] =
{
	0,2,1,
	0,1,3,
};


//void init2dfont()//char*fName)
void draw2dfont(int vboID, std::string text, float tempX, float tempY, float xwidth, float yheight)
{
	if(dObj.loadOnce[vboID] == 0)
	{
		//hudTexture = loadPngImage(fName, imgwidth, imgheight, hasAlpha, &textureImage);
		//glGenBuffers(1, &hud2dVertexBufferID);
		//loadShaders(programFontID, "shaders/vert_2dfont.glsl", "shaders/frag_2dfont.glsl");
		//FreeType
		FT_Library ft;
		//All functions return a value different than 0 whenever an error occurred
		if(FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		}
		else
		{
			printf("FREETYPE INIT!\n");
		}
		//Load font as face
		FT_Face face;
		if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		}
		else
		{
			printf("FREETYPE FONT LOADED!\n");
		}
		//Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);
		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//Load first 128 characters of ASCII set
		for (GLubyte c = 0; c < 128; c++)
		{
			//Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			//Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
				);
			//Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		//Destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		///////////////////////////////////////////////////////////////////////////////////
		fontLoop[vboID] = 0;
		//std::string text = "THIS IS A TEST STRING!";

		GLfloat x = 0;
		GLfloat y = 0;
		//GLfloat x = xwidth;
		//GLfloat y = yheight;

		GLfloat scale = 1.0f;
		// Iterate through all characters
		std::string::const_iterator c;
		for(c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			GLfloat xpos = x + ch.Bearing.x * scale;
			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
			//GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			GLfloat w = ch.Size.x * scale;
			GLfloat h = ch.Size.y * scale;
			float myVT[] =
			{
				/*
				xpos, ypos,         0,1,
				xpos + w, ypos + h, 1,0,
				xpos + w, ypos,     1,1,
				xpos, ypos + h,     0,0,
				*/

				tempX+xpos,         tempY+ypos,     0,1,
				tempX+xpos + w,     tempY+ypos + h, 1,0,
				tempX+xpos + w,     tempY+ypos,     1,1,
				tempX+xpos,         tempY+ypos + h, 0,0,
			};
			//printf("xpos: %f xw: %f ypos: %f yh: %f\n", xpos, xpos + w, ypos, ypos + h);

			//Bind texture
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, ch.TextureID);

			chID[vboID][fontLoop[vboID]] = ch.TextureID;

			//GLuint vertexbuffer;
			glGenBuffers(1, &fontVertexBuffer[vboID][fontLoop[vboID]]);
			glBindBuffer(GL_ARRAY_BUFFER, fontVertexBuffer[vboID][fontLoop[vboID]]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(myVT), myVT, GL_STATIC_DRAW);
			//GLuint elementbuffer;
			glGenBuffers(1, &fontElementBuffer[vboID][fontLoop[vboID]]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fontElementBuffer[vboID][fontLoop[vboID]]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fontInd), fontInd, GL_STATIC_DRAW);
			///////////////////////////////////////////////////////////////////////////////////

			fontLoop[vboID]++;
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
			//printf("xTest: %f\n", x);
		}
		dObj.loadOnce[vboID] = 1;
	}

	if(dObj.drawDisable[vboID] == 0)
	{
		glCullFace(GL_BACK);
		glUseProgram(programFontID);//program2DshaderID
		int sw, sh;
		glfwGetWindowSize(window, &sw, &sh);
		double mxpos, mypos;
		glfwGetCursorPos(window, &mxpos, &mypos);
		//printf("Mouse X: %f Y: %f Screen W: %d H: %d\n", mxpos, mypos, sw, sh);
		////////////////////////////////////////////////////////////////////////////
		fontProjection = glm::ortho(0.0f, 800.f, 0.0f, 600.f, 0.1f, 100.0f);
		glUniformMatrix4fv(fontUniformProjection, 1, GL_FALSE, glm::value_ptr(fontProjection));

		fontTranslationMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f));//ORIGIN AT BOTTOM LEFT
		fontRotationMatrix = rotate(mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		fontScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));//scalingX, scalingY, scalingZ));

		fontModelMatrix = fontTranslationMatrix * fontRotationMatrix * fontScalingMatrix;
		glUniformMatrix4fv(fontUniformModel, 1, GL_FALSE, glm::value_ptr(fontModelMatrix));

		fontView = LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glm::mat4 view = LookAt(eye, eye+target, up);
		//glUniformMatrix4fv(uniformView2D[0], 1, GL_FALSE, glm::value_ptr(view2D));
		glUniformMatrix4fv(fontUniformView, 1, GL_FALSE, glm::value_ptr(fontView));

		fontMVP = fontProjection * fontView * fontModelMatrix;
		//glUniformMatrix4fv(uniformModel[0], 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(MatrixID2D, 1, GL_FALSE, &MVP2D[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform
		glUniformMatrix4fv(fontMatrixID, 1, GL_FALSE, &fontMVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

		glUniform3f(glGetUniformLocation(programFontID, "textColor"), 1.0f, 1.0f, 0.0f);
		///////////////////////////////////////////////////////////////////////////////////
		for(int i = 0; i < fontLoop[vboID]; i++)
		{
			//Bind texture
			glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			glBindTexture(GL_TEXTURE_2D, chID[vboID][i]);
			//1st attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, fontVertexBuffer[vboID][i]);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
			//INDICES
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fontElementBuffer[vboID][i]);
			glDrawElements(GL_TRIANGLES, sizeof(fontInd), GL_UNSIGNED_INT, (void*)0);
			glDisableVertexAttribArray(0);
		}
		//glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);
	}
	dObj.VBOloadedID++;
}
