#pragma comment(lib,"glaux.lib")

#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<GL\GLAUX.H>

#include <math.h>
#include <map>
#include <vector>

#include "Frame.h"
#include "Door.h"
#include "Wall.h"
#include "Camera.h"
#include "Card.h"
#include "CardReader.h"
#include "Cabinet.h"
#include "Key.h"
#include "Ruler.h"
#include "Table.h"
#include "Egg.h"
#include "Carpet.h"
#include "Dumpling.h"

using namespace std;

void PickingObject(GLint x, GLint y);
void SelectProcess(GLuint name);

//�̹��� ���� �ؽ��� ����.
GLuint	texture[27];

GLboolean lock_open = false;

//���� ����.
GLuint selectBuff[64];
GLint hits;

//������ ��� admin mode
GLint mode;

//Text����.
string text;

//������ ���� �Ϲ� ������Ʈ ����.
vector<Object*> norm_obj;

//������ �ִ� ����� ������Ʈ ��.
map<GLuint, SpecialObject*> special_obj;

//ī�޶� ��ü.
Camera* camera = new Camera();

//�ð�.
GLint timer = 0;

//Ű�е� ��

//����
GLfloat LightPostion[] = { camera->eye_z, camera->eye_y, camera->eye_x,1.0 };
GLfloat LightDirection[] = { camera->eye_x + camera->center_x, camera->eye_y + camera->center_y, camera->eye_z + camera->center_z };

//�׸��� ����.
GLubyte Object::MyVertexList[24] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

//����Ʈ Object Color
GLfloat Object::MyColors[8][3] = {

	{0.2,0.2,0.2},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}
};

//��ü ���� �� ���� �ʱ�ȭ.
GLfloat wall_color[3] = {0.5, 0.5, 0.5};
GLfloat wall_point[8][3] = { {-10,-10,-10},{-10,10,-10},{10,10,-10},{10,-10,-10}, //��
							  {-10,-10,-11},{-10,10,-11},{10,10,-11},{10,-10,-11} };


GLfloat frame_color[3] = {1.0,1.0,1.0};
GLfloat frame_point[8][3] = { {-3.0,3.0,-9.5},{-3.0,8.0,-9.5},{3.0,8.0,-9.5},{3.0,3.0,-9.5},
							  {-3.0,3.0,-9.9},{-3.0,8.0,-9.9},{3.0,8.0,-9.9},{3.0,3.0,-9.9} };


GLfloat cabinet_color[3] = {0.5,0.5,0.7};
GLfloat cabinet_point[8][3] = {{-10,-10,3},{-10,2,3},{-8,2,3},{-8,-10,3},
	{-10,-10,-3},{-10,2,-3},{-8,2,-3},{-8,-10,-3}};

GLfloat door_color[3] = {0.5,0.5,0.7};
GLfloat door_point[8][3] = {{-3,-10,10},{-3,2,10},{3,2,10},{3,-10,10},
	{-3,-10,9.5},{-3,2,9.5},{3,2,9.5},{3,-10,9.5}};

GLfloat card_color[3] = {0.0,0.0,1.0};
GLfloat card_point[8][3] = {{-8.5,2,-2},{-8.5,2.1,-2},{-8.1,2.1,-2},{-8.1,2,-2},
	{-8.5,2,-3},{-8.5,2.1,-3},{-8.1,2.1,-3},{-8.1,2,-3}};

GLfloat key_color[3] = {0.0,0.0,1.0};
GLfloat key_point[8][3] = { //Ű ����
	{-9.01,-1.01,0.0},{-9.01,-0.99,0.0},{-8.99,-0.99,0.0},{-8.99,-1.01,0.0},
	{-9.01,-1.01,-0.5},{-9.01,-0.99,-0.5},{-8.99,-0.99,-0.5},{-8.99,-1.01,-0.5}};

GLfloat table_color[3] = {0.0,0.0,1.0};
GLfloat table_point[8][3] = { //å�� ����
	{5,-5,-3},{5,-4.5,-3},{10,-4.5,-3},{10,-5,-3},
	{5,-5,-10},{5,-4.5,-10},{10,-4.5,-10},{10,-5,-10}};

GLfloat ruler_color[3] = {0.0,0.0,1.0};
GLfloat ruler_point[8][3] = { //å�� ����
	{6.5,-5.1,-4},{6.5,-5.0,-4},{7.0,-5.0,-4},{7.0,-5.1,-4},
	{6.5,-5.1,-6},{6.5,-5.0,-6},{7.0,-5.0,-6},{7.0,-5.1,-6}};

GLfloat card_reader_color[3] = {0.0,0.0,1.0};
GLfloat card_reader_point[8][3] = { //ī�� ������ �� �κ�
	{-5.0,0.03,-9},{-4.5,0.55,-9},{-3.5,0.55,-9},{-3,0.03,-9},
	{-5.0,0.03,-10},{-4.5,0.55,-10},{-3.5,0.55,-10},{-3,0.03,-10}};

GLfloat egg_color[3] = {0.5,0.5,0.5};
GLfloat egg_point[8][3] = { //ī�� ������ �� �κ�
	{6,-4.5,-5},{6,-4.0,-5},{9,-4.0,-5},{9,-4.5,-5},
	{6,-4.5,-9},{6,-4.0,-9},{9,-4.0,-9},{9,-4.5,-9}};

GLfloat carpet_table_color[3] = { 1.0,0.0,0.0 };
GLfloat carpet_table_point[8][3] = {
	{-4,-9.9,4},{-4,-9.8,4},{4,-9.8,4},{4,-9.9,4},
	{-4,-9.9,-4},{-4,-9.8,-4},{4,-9.8,-4},{4,-9.9,-4}};

GLfloat dump_color[3] = { 1.0, 1.0, 1.0 };
GLfloat dump_point[8][3] = { {-2, -10, 9}, {-2, -9.7, 9}, {2, -9.7, 9}, {2, -10, 9},
{-2, -10, 7}, {-2, -9.7, 7}, {2, -9.7, 7}, {2, -10, 7} };


//�ؽ��� ���� �� �Լ�.
AUX_RGBImageRec *LoadBMP(const char *Filename)                    // ��Ʈ�� �̹����� �о��
{
	FILE *File = NULL;
	if (!Filename)                                // �����̸��� ���޵Ǿ����� Ȯ��
	{
		return NULL;                            // �׷��� �ʴٸ� NULL�� ��ȯ
	}
	File = fopen(Filename, "r");
	if (File)                                // ������ �����ϴ°�?
	{
		fclose(File);                            // �ڵ��� ����
		return auxDIBImageLoad(Filename);                // ��Ʈ���� �о���̰� �����͸� ��ȯ
	}
	return NULL;                                // �ε��� �����ϸ� NULL�� ��ȯ
}

//�ؽ��� �ε� �Լ�.
int LoadGLTextures()                                // ��Ʈ���� �ε��ϰ� �ؽ�ó�� ��ȯ
{
	int Status = FALSE;
	AUX_RGBImageRec *TextureImage[27];
	memset(TextureImage, 0, sizeof(void *) * 27);
	// ��Ʈ���� �ε��ϰ� ������ �˻��Ѵ�. ��Ʈ���� �߰ߵ��� �ʾҴٸ� �����Ѵ�.

	if (TextureImage[0] = LoadBMP("../res/wall.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����

		glGenTextures(1, &texture[0]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[0])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[0]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[0]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[0]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[1] = LoadBMP("../res/flower.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[1]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[1])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[1]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[1]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[1]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[2] = LoadBMP("../res/floor.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[2]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[2]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[2])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[2]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[2]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[2]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[3] = LoadBMP("../res/table.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[3]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[3]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[3])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[3]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[3]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[3]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[4] = LoadBMP("../res/door.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[4]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[4]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->sizeX, TextureImage[4]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[4])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[4]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[4]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[4]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[5] = LoadBMP("../res/lock.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[5]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[5]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[5]->sizeX, TextureImage[5]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[5]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[5])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[5]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[5]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[5]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[6] = LoadBMP("../res/reader.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[6]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[6]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[6]->sizeX, TextureImage[6]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[6]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[6])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[6]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[6]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[6]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[7] = LoadBMP("../res/card.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[7]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[7]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[7]->sizeX, TextureImage[7]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[7]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[7])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[7]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[7]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[7]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[8] = LoadBMP("../res/ruler.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[8]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[8]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[8]->sizeX, TextureImage[8]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[8]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[8])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[8]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[8]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[8]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[9] = LoadBMP("../res/frame.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[9]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[9]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[9]->sizeX, TextureImage[9]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[9]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[9])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[9]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[9]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[9]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[10] = LoadBMP("../res/door_below.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[10]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[10]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[10]->sizeX, TextureImage[10]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[10]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[10])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[10]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[10]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[10]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[11] = LoadBMP("../res/carpet.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[11]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[11]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[11]->sizeX, TextureImage[11]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[11]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[11])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[11]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[11]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[11]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[12] = LoadBMP("../res/book.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[12]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[12]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[12]->sizeX, TextureImage[12]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[12]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[12])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[12]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[12]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[12]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[13] = LoadBMP("../res/open_book.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[13]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[13]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[13]->sizeX, TextureImage[13]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[13]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[13])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[13]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[13]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[13]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[14] = LoadBMP("../res/memo.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[14]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[14]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[14]->sizeX, TextureImage[14]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[14]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[14])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[14]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[14]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[14]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[15] = LoadBMP("../res/dumbling.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[15]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[15]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[15]->sizeX, TextureImage[15]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[15]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[15])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[15]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[15]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[15]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[16] = LoadBMP("../res/door_below_2.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[16]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[16]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[16]->sizeX, TextureImage[16]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[16]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[16])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[16]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[16]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[16]);                        // �̹��� ����ü�� ����
	}
	if (TextureImage[17] = LoadBMP("../res/KeyPad0.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[17]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[17]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[17]->sizeX, TextureImage[17]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[17]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[17])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[17]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[17]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[17]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[18] = LoadBMP("../res/KeyPad1.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[18]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[18]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[18]->sizeX, TextureImage[18]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[18]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[18])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[18]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[18]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[18]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[19] = LoadBMP("../res/KeyPad2.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[19]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[19]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[19]->sizeX, TextureImage[19]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[19]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[19])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[19]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[19]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[19]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[20] = LoadBMP("../res/KeyPad3.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[20]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[20]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[20]->sizeX, TextureImage[20]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[20]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[20])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[20]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[20]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[20]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[21] = LoadBMP("../res/KeyPad4.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[21]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[21]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[21]->sizeX, TextureImage[21]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[21]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[21])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[21]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[21]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[21]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[22] = LoadBMP("../res/KeyPad5.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[22]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[22]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[22]->sizeX, TextureImage[22]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[22]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[22])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[22]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[22]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[22]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[23] = LoadBMP("../res/KeyPad6.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[23]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[23]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[23]->sizeX, TextureImage[23]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[23]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[23])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[23]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[23]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[23]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[24] = LoadBMP("../res/KeyPad7.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[24]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[24]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[24]->sizeX, TextureImage[24]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[24]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[24])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[24]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[24]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[24]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[25] = LoadBMP("../res/KeyPad8.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[25]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[25]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[25]->sizeX, TextureImage[25]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[25]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[25])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[25]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[25]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[25]);                        // �̹��� ����ü�� ����
	}

	if (TextureImage[26] = LoadBMP("../res/KeyPad9.bmp"))
	{
		Status = TRUE;                            // Status�� TRUE�� ����
		printf("yes");
		glGenTextures(1, &texture[26]);                    // �ؽ�ó�� ����

			// ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
		glBindTexture(GL_TEXTURE_2D, texture[26]);

		// �ؽ�ó�� �����
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[26]->sizeX, TextureImage[26]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[26]->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	}
	if (TextureImage[26])                            // �ؽ�ó�� �����ϴ��� Ȯ��
	{
		if (TextureImage[26]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
		{
			free(TextureImage[26]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
		}

		free(TextureImage[26]);                        // �̹��� ����ü�� ����
	}

	/********Ű�е� �׸��� ��********/

	return Status;                                       // Status�� ��ȯ
}

void ObjectInit() {
	Object* normal;
	SpecialObject *special;

	normal = new Wall();
	normal->setColors(wall_color);
	norm_obj.push_back(normal);

	//100
	special = new Frame(100);
	special->setColors(frame_color);
	special_obj[special->getIndex()] = special;

	//101
	special = new Cabinet(101);
	special->setColors(cabinet_color);
	special_obj[special->getIndex()] = special;


	//102
	special = new Door(102);
	special->setColors(door_color);
	special_obj[special->getIndex()] = special;


	//103
	special = new Card(103);
	special->setColors(card_color);
	special_obj[special->getIndex()] = special;


	//104
	special = new Key(104);
	special->setColors(key_color);
	special_obj[special->getIndex()] = special;

	normal = new Table();
	normal->setColors(table_color);
	norm_obj.push_back(normal);

	//105
	special = new Ruler(105);
	special->setColors(ruler_color);
	special_obj[special->getIndex()] = special;

	//106
	special = new CardReader(106);
	special->setColors(card_reader_color);
	special_obj[special->getIndex()] = special;

	normal = new Egg();
	normal->setColors(egg_color);
	norm_obj.push_back(normal);

	//107
	special = new Carpet(107);
	special->setColors(carpet_table_color);
	special_obj[107] = special;

	//108
	special = new Dumpling(108);
	special->setColors(dump_color);
	special_obj[108] = special;
}

void InitLight() {

	//GLfloat LightPostion[] = { eye_x,eye_y,eye_z,1.0 };
	//GLfloat LightDirection[] = { eye_x + center_x, eye_y + center_y, eye_z + center_z };
	GLfloat SpotAngle[] = { 25.0 };

	GLfloat light0_ambient[] = { 0.0, 0.0, 0.0 ,0.0 };
	GLfloat light0_diffuse[] = { 0.5,0.5,0.5,1.0 };
	GLfloat light0_specular[] = { 0.0,0.0,0.0,0.0 };

	GLfloat material_ambient[] = { 0.5,0.5,0.5,1.0 };
	GLfloat material_diffuse[] = { 0.8,0.8,0.8,1.0 };
	GLfloat material_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat material_shininess[] = { 30.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);


	glLightfv(GL_LIGHT0, GL_POSITION, LightPostion);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, SpotAngle);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.16);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.08);

}


void RenderBitmapCharacter(int x, int y, const char* str) {

	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2f(x, y);
	const char* c;
	for (c = str; *c != '\n'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

}

void MyMouse(GLint button, GLint state, GLint x, GLint y) {
	//Object Picking �� �Լ� ����.

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		PickingObject(x, y);

		if (hits  < 3) {
			cout << "////////" << endl;
			for (int i = 0; i < hits; i++) {
				int index = i * 4 + 3;
				GLuint name = selectBuff[index];
				cout << name << endl;

				for (map<GLuint, SpecialObject*>::iterator iter = special_obj.begin(); iter != special_obj.end(); iter++) {
					if (iter->first == name) {
						SelectProcess((GLuint)name);
						
					}
				}
			}
			cout << camera->eye_x << " // " << camera->eye_y << "//" << camera->eye_z << endl;
			cout << "////////" << endl;

			hits = 0;
		}
	}
	
	glutPostRedisplay();
}

void MySpecialKey(int key, int x, int y) {
	if (camera->status == CAM_STAT_FIX) {
		Cabinet* cab = dynamic_cast<Cabinet*>(special_obj[101]);
		switch (key) {
		case GLUT_KEY_LEFT:
			cab->key_x--;
			if (cab->key_x < 0)
				cab->key_x = 4;
			break;
		case GLUT_KEY_RIGHT:
			cab->key_x++;
			if (cab->key_x > 4)
				cab->key_x = 0;
			break;
		case GLUT_KEY_UP:
			cab->key_y++;
			if (cab->key_y >= 2)
				cab->key_y = 0;
			break;
		case GLUT_KEY_DOWN:
			cab->key_y--;
			if (cab->key_y < 0)
				cab->key_y = 1;
			break;


		case GLUT_KEY_F1:
			if (special_obj[101]->getStatus() == 1) {
				special_obj[101]->setStatus(0);
				camera->CameraStand();
				Cabinet* cab = dynamic_cast<Cabinet*>(special_obj[101]);
				cab->cabinet_submit.clear();
			}
			cout << "ESC" << endl;
			break;

		}
	}



	glutPostRedisplay();



}

void MyDisplay() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, camera->width / camera->height, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, LightPostion); //�ݵ�� �� ��ġ�� �;� ������ ���� ������
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);

	if (camera->status != CAM_STAT_FIX) {
		if (mode == 0) //��ڸ��
			gluLookAt(camera->eye_x, camera->eye_y, camera->eye_z,
				camera->eye_x + camera->center_x, camera->eye_y + camera->center_y, camera->eye_z + camera->center_z,
				camera->axis_x, camera->axis_y, camera->axis_z);
		else //����� ���
			gluLookAt(camera->eye_x, 0, camera->eye_z, camera->eye_x + camera->center_x, 0 + camera->center_y, camera->eye_z + camera->center_z,
				camera->axis_x, camera->axis_y, camera->axis_z);
	}
	else
		gluLookAt(-6, 0, 0, -10, 0, 0, 0, 1, 0);

	norm_obj[0]->DrawObject(wall_point);
	glEnable(GL_DEPTH_TEST);

	norm_obj[1]->DrawObject(table_point);
	norm_obj[2]->DrawObject(egg_point);

	special_obj[100]->DrawObject(frame_point);
	special_obj[101]->DrawObject(cabinet_point);
	special_obj[102]->DrawObject(door_point);
	special_obj[103]->DrawObject(card_point);
	special_obj[104]->DrawObject(key_point);
	special_obj[105]->DrawObject(ruler_point);
	special_obj[106]->DrawObject(card_reader_point);
	special_obj[107]->DrawObject(carpet_table_point);
	special_obj[108]->DrawObject(dump_point);
	//DrawingKeyPad();
	
	glDisable(GL_DEPTH_TEST);

	glFlush();

	glutSwapBuffers();

}

void PickingObject(GLint x, GLint y) {
	GLint viewport[4];

	glSelectBuffer(64, selectBuff);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glRenderMode(GL_SELECT);

	glInitNames();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix(x, viewport[3] - y, 2, 2, viewport);
	gluPerspective(120, (GLdouble)camera->width / (GLdouble)camera->height, 0.1, 1000);
	glPushName(0);
	
	glLoadName(100);
	special_obj[100]->DrawObject(frame_point);
	if (camera->status != CAM_STAT_FIX) {
		glLoadName(101);
		special_obj[101]->DrawObject(cabinet_point);
	}
	glLoadName(102);
	special_obj[102]->DrawObject(door_point);
	glLoadName(103);
	special_obj[103]->DrawObject(card_point);
	glLoadName(104);
	special_obj[104]->DrawObject(key_point);
	glLoadName(105);
	special_obj[105]->DrawObject(ruler_point);
	glLoadName(106);
	special_obj[106]->DrawObject(card_reader_point);
	glLoadName(107);
	special_obj[107]->DrawObject(carpet_table_point);
	glLoadName(108);
	special_obj[108]->DrawObject(dump_point);


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	//������ ��� ����,

}

void SelectProcess(GLuint name) {
	switch (name) {
	case 100://������.
		if(special_obj[105]->getStatus() > 0)
			special_obj[100]->setStatus(special_obj[100]->getStatus() + 1);
		return;
	case 101://ĳ���.
		if (camera->eye_x > -7.8 && camera->eye_x < -5.0 && camera->eye_z > -2.1 && camera->eye_z < 2.1) {
			if (special_obj[107]->getStatus() > 1 && special_obj[100]->getStatus() > 0) {
				if (special_obj[101]->getStatus() == 0) {
					special_obj[101]->setStatus(special_obj[101]->getStatus() + 1);
				}
				if (special_obj[101]->getStatus() == 1) {
					camera->status = CAM_STAT_FIX;
				}
			}
		}
		return;
	case 102://��
		
		if(special_obj[104]->getStatus() > 0)
			special_obj[102]->setStatus(special_obj[102]->getStatus() + 1);
		if (special_obj[102]->getStatus() > 1) {
			exit(0);
		}
		return;
	case 103://ī��.
		special_obj[103]->setStatus(special_obj[103]->getStatus() + 1);
		return;
	case 104://Ű.
		if(special_obj[101]->getStatus() > 0)
			special_obj[104]->setStatus(special_obj[104]->getStatus() + 1);
		return;
	case 105://��.
		if (camera->status == CAM_STAT_SIT) {
			special_obj[105]->setStatus(special_obj[105]->getStatus() + 1);
		}
		return;
	case 106://ī�帮��.
		if(special_obj[108]->getStatus() == 0 && special_obj[103]->getStatus() > 0)
			special_obj[108]->setStatus(special_obj[108]->getStatus() + 1);
		return;
	case 107://ī��.
		if (camera->status == CAM_STAT_SIT) {
			special_obj[107]->setStatus(special_obj[107]->getStatus() + 1);
		}
		return;
	case 108://����.
		special_obj[108]->setStatus(special_obj[108]->getStatus() + 1);
		return;
	default:
		return;
	}
}

void MyReshape(int w, int h) {
	camera->width = w;
	camera->height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (GLdouble)w / (GLdouble)h, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();

}

void MyPassiveMouse(GLint x, GLint y) {
	if(camera->status != CAM_STAT_FIX){
	//������ �����Ӱ� ���� ������ ������ ���� ���
		GLfloat xoffset = x - camera->width / 2.0; //x
		GLfloat yoffset = camera->height / 2.0 - y; //y

		SetCursorPos(camera->width / 2.0, camera->height / 2.0);

		//���콺 ���� ����
		GLfloat sensitivity = 0.03;
		xoffset *= sensitivity;
		yoffset *= sensitivity;



		camera->yaw += xoffset;
		camera->pitch += yoffset;

		if (camera->pitch > 89.0)
			camera->pitch = 89.0;
		if (camera->pitch < -89.0)
			camera->pitch = -89.0;

		GLfloat pi = PI;

		GLfloat front_x = cos(camera->pitch*pi / 180.0) * cos(camera->yaw*pi / 180.0);
		GLfloat front_y = sin(camera->pitch*pi / 180.0);
		GLfloat front_z = cos(camera->pitch*pi / 180.0) * sin(camera->yaw*pi / 180.0);


	

		//front ���� ����ȭ
		GLfloat normalized_front = sqrt(pow(front_x, 2) + pow(front_y, 2) + pow(front_z, 2));

		camera->center_x = front_x / normalized_front;
		camera->center_y = front_y / normalized_front;
		camera->center_z = front_z / normalized_front;
	}
	glutPostRedisplay();

}

void MyKeyboard(unsigned char key, int X, int Y) {
	
	
	if (camera->status == CAM_STAT_FIX) {
		Cabinet* cab = dynamic_cast<Cabinet*>(special_obj[101]);
		switch (key) {
		case 13:
			if (cab->key_y == 0) {
				cab->cabinet_submit.push_back(cab->key_x);


			}
			else {
				cab->cabinet_submit.push_back(cab->key_x + 5);

			}

			if (cab->cabinet_submit.size() == 16) {
				bool isAns = cab->ValidAnswer();
				camera->CameraStand();
				if (isAns) {
					special_obj[101]->setStatus(special_obj[101]->getStatus() + 1);
				}
				else {
					special_obj[101]->setStatus(special_obj[101]->getStatus() - 1);
				}
			}

			break;
		}

	}
	else{
		switch (key) {


		case 'w':
			switch (camera->move_state) {
			case 4: camera->move_state = 7; break;
			case 6: camera->move_state = 9; break;
			default: camera->move_state = 8; break;
			}

			break;

		case 's':
			switch (camera->move_state) {
			case 4: camera->move_state = 1; break;
			case 6: camera->move_state = 3; break;
			default: camera->move_state = 2; break;
			}

			break;

		case 'a':
			switch (camera->move_state) {
			case 8: camera->move_state = 7; break;
			case 2: camera->move_state = 1; break;
			default: camera->move_state = 4; break;
			}

			break;
		case 'd':
			switch (camera->move_state) {
			case 8: camera->move_state = 9; break;
			case 2: camera->move_state = 3; break;
			default: camera->move_state = 6; break;
			}

			break;

		case 'm':
			if (mode == 0)
				mode = 1;
			else mode = 0;
			break;

		case 27:
			exit(0);


			//�ɱ� Ű c
		case 'c':
			if (camera->status == CAM_STAT_STAND) {
				camera->CameraSit();
			}

			else if(camera->status == CAM_STAT_SIT){
				camera->CameraStand();
			}
			break;

			//����Ű �����̽�.
		case ' ':
			if (camera->y_vel == 0)
				camera->y_vel = 0.8;
			break;
		}
	}

	glutPostRedisplay();
}

void MyKeyUp(unsigned char key, int x, int y) {

	switch (key) {


	case 'w':
		switch (camera->move_state) {
		case 7: camera->move_state = 4; break;
		case 9: camera->move_state = 6; break;
		default: camera->move_state = 0; break;
		}

		break;

	case 's':
		switch (camera->move_state) {
		case 1: camera->move_state = 4; break;
		case 3: camera->move_state = 6; break;
		default: camera->move_state = 0; break;
		}

		break;

	case 'a':
		switch (camera->move_state) {
		case 7: camera->move_state = 8; break;
		case 1: camera->move_state = 2; break;
		default: camera->move_state = 0; break;
		}

		break;

	case 'd':
		switch (camera->move_state) {
		case 9: camera->move_state = 8; break;
		case 3: camera->move_state = 2; break;
		default: camera->move_state = 0; break;
		}

		break;

	}
	glutPostRedisplay();
}

void MyTimer(int val) {
	timer += 30;
	
	//���� ����.
	if (camera->y_vel != 0) {
		camera->eye_y += camera->y_vel;
		camera->y_vel -= 0.05;

		if (camera->eye_y < 0) {
			camera->eye_y = 0;
			camera->y_vel = 0;
		}
	}

	GLint sec = timer / 1000;
	GLint min = sec / 60;
	//���� ���� ����.
	if (min > 10) {

	}

	camera->Moving();
	camera->CameraBound();

	glutPostRedisplay();
	glutTimerFunc(30, MyTimer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(camera->width, camera->height);

	glutCreateWindow("Escape Room");

	if (!LoadGLTextures())                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
	{
		return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
	}

	ObjectInit();

	glClearDepth(10.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	InitLight();

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	SetCursorPos(glutGet(camera->width) / 2.0, glutGet(camera->height) / 2.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutKeyboardUpFunc(MyKeyUp);
	glutMouseFunc(MyMouse);
	glutTimerFunc(60, MyTimer, 1);
	glutPassiveMotionFunc(MyPassiveMouse);
	glutSpecialFunc(MySpecialKey);

	glutMainLoop();

	return 0;

}