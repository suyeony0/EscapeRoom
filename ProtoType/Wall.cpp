#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

extern GLuint texture[17];

#include "Wall.h"

void Wall::Draw(GLfloat _wall_point[][3]) {
	GLfloat wall_point[8][3];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			wall_point[i][j] = _wall_point[i][j];
		}

	}

	glColor3f(colors[0], colors[1], colors[2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, wall_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}

}

void Wall::DrawObject(GLfloat _wall_point[][3]) {

	GLfloat wall_point[8][3];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			wall_point[i][j] = _wall_point[i][j];
		}

	}

	GLfloat wall_point2[8][3] = { {-10,-10,10},{-10,10,10},{10,10,10},{10,-10,10}, //��
							  {-10,-10,11},{-10,10,11},{10,10,11},{10,-10,11} };

	GLfloat wall_point3[8][3] = { {-11,-10,10},{-11,10,10},{-10,10,10},{-10,-10,10}, //��
								  {-11,-10,-10},{-10,10,-10},{10,10,-10},{10,-10,-10} };

	GLfloat wall_point4[8][3] = { {10,-10,10},{10,10,10},{11,10,10},{11,-10,10}, //��
								  {10,-10,-10},{10,10,-10},{11,10,-10},{11,-10,-10} };

	GLfloat wall_point5[8][3] = { {-10,10,10},{-10,11,10},{10,11,10},{10,10,10}, //��
								  {-10,10,-10},{-10,11,-10},{10,11,-10},{10,10,-10} };

	GLfloat wall_point6[8][3] = { {-10,-11,10},{-10,-10,10},{10,-10,10},{10,-11,10}, //�Ʒ�
								  {-10,-11,-10},{-10,-10,-10},{10,-10,-10},{10,-11,-10} };



	glPushMatrix();


	glFrontFace(GL_CCW); //ǥ���� �������� �� ���ΰ�, CCW�� �ݽð�������� ǥ���� ǥ���ϰڴٴ� ����
//glEnable(GL_CULL_FACE); // �������� �κ��߿��� �Ⱥ��̴� �κ��� �����ϴ� �Լ�. ��, �츮���� �Ⱥ��̴� �ڿ� �鿡 ���ؼ��� �� �׷��� �ǹǷ� �� �κ��� �ȱ׸�.
//glEnableClientState(GL_COLOR_ARRAY); //�÷��� ����Ʈ�� �����Ϸ��� �̰� ����ϸ� ��
	glEnableClientState(GL_VERTEX_ARRAY);//�����迭��� Ȱ��ȭ�� ����

	Wall* wall = new Wall();

	wall->Draw(wall_point);
	wall->Draw(wall_point2);
	wall->Draw(wall_point3);
	wall->Draw(wall_point4);
	wall->Draw(wall_point5);
	wall->Draw(wall_point6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glFrontFace(GL_CW);



	/*******�ؽ��� ����********/

	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		//����

		glColor3f(0.94, 0.94, 0.94);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ������
		glEnd();

		//�޸�
		glRotatef(180, 0, 1, 0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ������
		glEnd();

		//����
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ������
		glEnd();

		//������
		glRotatef(180, 0, 1, 0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ������
		glEnd();
	}
	{
		//��
		glRotatef(90, 1, 0, 0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ������
		glEnd();

		//����
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glColor3f(1.0, 0.72, 0.43);

		glRotatef(180, 1, 0, 0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0, -10.0, -10.0);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0, -10.0, -10.0);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0, 10.0, -10.0);    // �ؽ�ó�� ������ ������
		glEnd();

		glPopMatrix();
		//glRotatef(-90, 0, 1, 0);

	}

}