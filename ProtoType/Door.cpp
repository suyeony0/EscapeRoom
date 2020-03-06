#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Door.h"

extern GLuint texture[17];

void Door::Draw(GLfloat _door_point[][3]) {
	GLfloat door_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			door_point[i][j] = _door_point[i][j];
		}

	}
	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, door_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Door::DrawHandle(GLfloat size) {
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-2.5, -4, 10);
	glutSolidSphere(size, 20, 5);
	glTranslatef(2.5, 4, -10);
}

void Door::DrawObject(GLfloat _door_point[][3]) {
	//door_open = true;
	
	if (status == 1) {
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		//����
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); //1

		glVertex3f(3.5, -10, 10);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(0.0f, 0.0f); //2
		glVertex3f(3.5, -10, 4);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(0.0f, 1.0f); //3
		glVertex3f(3.5, 2, 4);    // �ؽ�ó�� ������ ��������

		glTexCoord2f(1.0f, 1.0f); //4
		glVertex3f(3.5, 2, 10);    // �ؽ�ó�� ������ ������
		glEnd();

		//�ĸ�
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);  //1

		glVertex3f(3, -10, 10);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(0.0f, 0.0f); //2
		glVertex3f(3, -10, 4);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(0.0f, 1.0f); //3
		glVertex3f(3, 2, 4);    // �ؽ�ó�� ������ ��������

		glTexCoord2f(1.0f, 1.0f); //4
		glVertex3f(3, 2, 10);    // �ؽ�ó�� ������ ������
		glEnd();

		//����
		glColor3f(159.0 / 255.0, 84.0 / 255.0, 45.0 / 255.0);
		glBegin(GL_QUADS);
		glVertex3f(3, -10, 4);
		glVertex3f(3.5, -10, 4);
		glVertex3f(3.5, 2, 4);
		glVertex3f(3, 2, 4);
		glEnd();
		//����
		glBegin(GL_QUADS);
		glVertex3f(3.5, 2, 10);
		glVertex3f(3.5, 2, 4);
		glVertex3f(3, 2, 4);
		glVertex3f(3, 2, 10);
		glEnd();

		//����ġ�� �ٱ� ����
		glBindTexture(GL_TEXTURE_2D, texture[16]);
		//����
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3, -10, 10);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3, -10, 10);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3, 2, 10);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3, 2, 10);    // �ؽ�ó�� ������ ������
		glEnd();

	}
	else {
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		//����
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3, -10, 9.49);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3, -10, 9.49);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3, 2, 9.49);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3, 2, 9.49);    // �ؽ�ó�� ������ ������
		glNormal3f(0, 0, 1.0);
		glEnd();


		glFrontFace(GL_CCW); //ǥ���� �������� �� ���ΰ�, CCW�� �ݽð�������� ǥ���� ǥ���ϰڴٴ� ����
		//glEnable(GL_CULL_FACE); // �������� �κ��߿��� �Ⱥ��̴� �κ��� �����ϴ� �Լ�. ��, �츮���� �Ⱥ��̴� �ڿ� �鿡 ���ؼ��� �� �׷��� �ǹǷ� �� �κ��� �ȱ׸�.
		glEnableClientState(GL_COLOR_ARRAY); //�÷��� ����Ʈ�� �����Ϸ��� �̰� ����ϸ� ��
		glEnableClientState(GL_VERTEX_ARRAY);//�����迭��� Ȱ��ȭ�� ����

		this->Draw(_door_point);
		this->DoorBelow();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		//glDisable(GL_CULL_FACE);
		glFrontFace(GL_CW);


		//������
		//door_1->Drawing(0.3);
	}

}

void Door::DoorBelow() {
	if (status == 0) {
		glBindTexture(GL_TEXTURE_2D, texture[10]);
		//����
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1, -9, 9.489);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1, -9, 9.489);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1, -7, 9.489);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1, -7, 9.489);    // �ؽ�ó�� ������ ������
		glEnd();
	}
}
