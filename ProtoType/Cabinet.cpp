#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

#include "Cabinet.h"

extern GLuint texture[17];

void Cabinet::Draw(GLfloat _cabinet_point[][3]) {
	GLfloat cabinet_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			cabinet_point[i][j] = _cabinet_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, cabinet_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);

	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}

}

void Cabinet::DrawObject(GLfloat _cabinet_point[][3]) {
	//Cabinet* cabinet = new Cabinet(this->index);

	this->Draw(_cabinet_point);

	if (this->status > 1) {
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		//����
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); //1
		glVertex3f(-8, -10, -3);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(0.0f, 0.0f); //2
		glVertex3f(-4, -10, -3);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(0.0f, 1.0f); //3

		glVertex3f(-4, 2, -3);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(1.0f, 1.0f); //4
		glVertex3f(-8, 2, -3);    // �ؽ�ó�� ������ ������
		glEnd();

		//�ݰ� �� ����
		glColor3f(0.5, 0.5, 0.8);
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glVertex3f(-8, -10, -2.5);
		glVertex3f(-4, -10, -2.5);
		glVertex3f(-4, 2, -2.5);
		glVertex3f(-8, 2, -2.5);
		glEnd();

		//�ݰ� �� ����

		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glVertex3f(-4, -10, -2.5);
		glVertex3f(-4, -10, -3);
		glVertex3f(-4, 2, -3);
		glVertex3f(-4, 2, -2.5);
		glEnd();

		//�ݰ� �� ����

		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glVertex3f(-8, 2, -3);
		glVertex3f(-4, 2, -3);
		glVertex3f(-4, 2, -2.5);
		glVertex3f(-8, 2, -2.5);
		glEnd();

		/*�ݰ� ����*/
		//���ʸ�
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glVertex3f(-10, -10, 3);
		glVertex3f(-8, -10, 3);
		glVertex3f(-8, 2, 3);
		glVertex3f(-10, 2, 3);
		glEnd();

		//�����ʸ�
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glVertex3f(-10, -10, -3);
		glVertex3f(-8, -10, -3);
		glVertex3f(-8, 2, -3);
		glVertex3f(-10, 2, -3);
		glEnd();

		//����
		glBegin(GL_QUADS);
		glNormal3f(0, -1, 0.0);
		glVertex3f(-10, 2, 3);
		glVertex3f(-8, 2, 3);
		glVertex3f(-8, 2, -3);
		glVertex3f(-10, 2, -3);
		glEnd();

		//�ظ�
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glVertex3f(-10, -10, 3);
		glVertex3f(-8, -10, 3);
		glVertex3f(-8, -10, -3);
		glVertex3f(-10, -10, -3);
		glEnd();

		//�޸�
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glVertex3f(-10, -10, 3);    // �ؽ�ó�� ������ ���ʾƷ�
		glVertex3f(-10, -10, -3);    // �ؽ�ó�� ������ �����ʾƷ�
		glVertex3f(-10, 2, -3);    // �ؽ�ó�� ������ ��������
		glVertex3f(-10, 2, 3);    // �ؽ�ó�� ������ ������
		glEnd();

		//�ݰ� ���� ��ħ�� ����
		glColor3f(0.0, 0.5, 0.5);
		glBegin(GL_QUADS);
		glVertex3f(-8, -1.5, 3);    // �ؽ�ó�� ������ ���ʾƷ�
		glVertex3f(-8, -1.5, -3);    // �ؽ�ó�� ������ �����ʾƷ�
		glVertex3f(-8, -1.02, -3);    // �ؽ�ó�� ������ ��������
		glVertex3f(-8, -1.02, 3);    // �ؽ�ó�� ������ ������
		glEnd();

		//�ݰ� ���� ��ħ�� ����
		glColor3f(0.0, 0.5, 0.5);
		glBegin(GL_QUADS);
		glVertex3f(-10, -1.02, 3);    // �ؽ�ó�� ������ ���ʾƷ�
		glVertex3f(-10, -1.02, -3);    // �ؽ�ó�� ������ �����ʾƷ�
		glVertex3f(-8, -1.02, -3);    // �ؽ�ó�� ������ ��������
		glVertex3f(-8, -1.02, 3);    // �ؽ�ó�� ������ ������
		glEnd();

		//�ݰ� ���� ��ħ�� �Ʒ���
		glColor3f(0.0, 0.5, 0.5);
		glBegin(GL_QUADS);
		glVertex3f(-8, -1.5, 3);    // �ؽ�ó�� ������ ���ʾƷ�
		glVertex3f(-8, -1.5, -3);    // �ؽ�ó�� ������ �����ʾƷ�
		glVertex3f(-10, -1.5, -3);    // �ؽ�ó�� ������ ��������
		glVertex3f(-10, -1.5, 3);    // �ؽ�ó�� ������ ������
		glEnd();

	}
	else if(this->status < 2){
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		//����
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-8, -10, 3);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-8, -10, -3);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-8, 2, -3);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-8, 2, 3);    // �ؽ�ó�� ������ ������
		glEnd();



		//���ʸ�
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-10, -10, 3);
		glVertex3f(-8, -10, 3);
		glVertex3f(-8, 2, 3);
		glVertex3f(-10, 2, 3);
		glEnd();

		//�����ʸ�
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-10, -10, -3);
		glVertex3f(-8, -10, -3);
		glVertex3f(-8, 2, -3);
		glVertex3f(-10, 2, -3);
		glEnd();

		//����
		glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-10, 2, 3);
		glVertex3f(-8, 2, 3);
		glVertex3f(-8, 2, -3);
		glVertex3f(-10, 2, -3);
		glEnd();

		DrawingKeyPad();
	}
}

void Cabinet::DrawingKeyPad() {
	int key_array[2][5] = { {17,18,19,20,21},
							{22,23,24,25,26} };

	glBindTexture(GL_TEXTURE_2D, texture[key_array[key_y][key_x]]);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0);
	glTexCoord2f(1.0f, 0.0f); //1

	glVertex3f(-7.8, -1, -2);
	glTexCoord2f(0.0f, 0.0f); //2
	glVertex3f(-7.8, -1, 2);
	glTexCoord2f(0.0f, 1.0f); //3

	glVertex3f(-7.8, 1, 2);
	glTexCoord2f(1.0f, 1.0f); //4
	glVertex3f(-7.8, 1, -2);
	glEnd();

	glutPostRedisplay();


}

bool Cabinet::ValidAnswer() {
	int k = 0;
	for (int i = 0; i < 16; i++) {
		cout << cabinet_submit[i] << " , " << cabinet_answer[i] << endl;
		if (cabinet_submit[i] == cabinet_answer[i]) {
			k += 1;
		}
		else break;
	}

	cabinet_submit.clear();

	if (k == 16) {
		return true;
	}
	else
		return false;
}