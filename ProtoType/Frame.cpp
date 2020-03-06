#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Frame.h"

extern GLuint texture[17];

void Frame::Draw(GLfloat _frame_point[][3]) {
	GLfloat frame_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			frame_point[i][j] = _frame_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, frame_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Frame::DrawObject(GLfloat _frame_point[][3]) {
	glFrontFace(GL_CCW); //ǥ���� �������� �� ���ΰ�, CCW�� �ݽð�������� ǥ���� ǥ���ϰڴٴ� ����
	glEnable(GL_CULL_FACE); // �������� �κ��߿��� �Ⱥ��̴� �κ��� �����ϴ� �Լ�. ��, �츮���� �Ⱥ��̴� �ڿ� �鿡 ���ؼ��� �� �׷��� �ǹǷ� �� �κ��� �ȱ׸�.
	//glEnableClientState(GL_COLOR_ARRAY); //�÷��� ����Ʈ�� �����Ϸ��� �̰� ����ϸ� ��
	glEnableClientState(GL_VERTEX_ARRAY);//�����迭��� Ȱ��ȭ�� ����

	this->Draw(_frame_point);
	this->DrawFlower();

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CW);

}

void Frame::DrawFlower() {
	
	if (this->status != 0) {
		glBindTexture(GL_TEXTURE_2D, texture[9]);
		//flower
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0, 3.0, -9.4999);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3.0, 3.0, -9.4999);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3.0, 8.0, -9.4999);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3.0, 8.0, -9.4999);    // �ؽ�ó�� ������ ������
		glEnd();
	}
	else{
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		//flower
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0, 3.0, -9.4999);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3.0, 3.0, -9.4999);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3.0, 8.0, -9.4999);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3.0, 8.0, -9.4999);    // �ؽ�ó�� ������ ������
		glEnd();
	}
}
