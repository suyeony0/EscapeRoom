#include "CardReader.h"

extern GLuint texture[17];

void CardReader::Draw(GLfloat _card_reader_point[][3]) {
	GLfloat card_reader_point[8][3];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			card_reader_point[i][j] = _card_reader_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, card_reader_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void CardReader::DrawObject(GLfloat _card_reader_point[][3]) {
	//ī�帮���� ���κ��� ��������.
	//CardReader* card_reader = new CardReader(this->index);


	glBindTexture(GL_TEXTURE_2D, texture[6]);
	//����
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0, -0.55, -9);    // �ؽ�ó�� ������ ���ʾƷ�
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0, -0.55, -9);    // �ؽ�ó�� ������ �����ʾƷ�
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0, 0.55, -9);    // �ؽ�ó�� ������ ��������
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0, 0.55, -9);    // �ؽ�ó�� ������ ������
	glEnd();

	//���ʸ�
	glColor3f(188.0 / 255.0, 151.0 / 255.0, 143.0 / 255.0);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0.0);
	glVertex3f(-5.0, -0.55, -10);
	glVertex3f(-5.0, -0.55, -9);
	glVertex3f(-5.0, 0.55, -9);
	glVertex3f(-5.0, 0.55, -10);
	glEnd();

	//�����ʸ�
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0.0);
	glVertex3f(-3.0, -0.55, -10);
	glVertex3f(-3.0, -0.55, -9);
	glVertex3f(-3.0, 0.55, -9);
	glVertex3f(-3.0, 0.55, -10);
	glEnd();

	//�Ʒ�
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0.0);
	glVertex3f(-5.0, -0.55, -10);
	glVertex3f(-3.0, -0.55, -10);
	glVertex3f(-3.0, -0.55, -9);
	glVertex3f(-5.0, -0.55, -9);
	glEnd();

	//��
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0.0);
	glVertex3f(-5.0, 0.55, -10);
	glVertex3f(-5.0, 0.55, -9);
	glVertex3f(-3.0, 0.55, -9);
	glVertex3f(-3.0, 0.55, -10);
	glEnd();
}
