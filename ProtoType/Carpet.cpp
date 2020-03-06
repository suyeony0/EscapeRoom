#include "Carpet.h"

extern GLuint texture[17];

void Carpet::Draw(GLfloat _carpet_point[][3]) {
	GLfloat carpet_point[8][3];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			carpet_point[i][j] = _carpet_point[i][j];
		}

	}

	glColor3f(colors[0], colors[1], colors[2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, carpet_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Carpet::DrawObject(GLfloat carpet_point[][3]) {
	this->Draw(carpet_point);
	if (status == 0) {
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		//carpet
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-4, -9.799, 4);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4, -9.799, 4);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.799, -4);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-4, -9.799, -4);    // �ؽ�ó�� ������ ������
		glEnd();


		glFrontFace(GL_CCW); //ǥ���� �������� �� ���ΰ�, CCW�� �ݽð�������� ǥ���� ǥ���ϰڴٴ� ����
		glEnable(GL_CULL_FACE); // �������� �κ��߿��� �Ⱥ��̴� �κ��� �����ϴ� �Լ�. ��, �츮���� �Ⱥ��̴� �ڿ� �鿡 ���ؼ��� �� �׷��� �ǹǷ� �� �κ��� �ȱ׸�.

		//glEnableClientState(GL_COLOR_ARRAY); //�÷��� ����Ʈ�� �����Ϸ��� �̰� ����ϸ� ��
		glEnableClientState(GL_VERTEX_ARRAY);//�����迭��� Ȱ��ȭ�� ����

		//�� �׸���

		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CW);

	}
	else if(this->status == 1){
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		//carpet
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-4, -9.7999, 4);    // �ؽ�ó�� ������ ���ʾƷ�

		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(0, -9.7999, 4);    // �ؽ�ó�� ������ ���ʾƷ�

		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(4, -9.7999, 0);    // �ؽ�ó�� ������ �����ʾƷ�

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7999, -4);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-4, -9.7999, -4);    // �ؽ�ó�� ������ ������
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[12]);
		//book
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.5, -9.7, 4);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4, -9.7, 4);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7, 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(2.5, -9.7, 2);
		glEnd();

		//���ʸ�
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glVertex3f(2.5, -10, 2);
		glVertex3f(2.5, -10, 4);
		glVertex3f(2.5, -9.7, 4);
		glVertex3f(2.5, -9.7, 2);
		glEnd();

		//�����ʸ�
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -10, 4);
		glVertex3f(4, -9.7, 4);
		glVertex3f(4, -9.7, 2);
		glEnd();

		//����
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glVertex3f(2.5, -10, 2);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -9.7, 2);
		glVertex3f(2.5, -9.7, 2);
		glEnd();

		//�ĸ�
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glVertex3f(4, -10, 4);
		glVertex3f(2.5, -10, 4);
		glVertex3f(2.5, -9.7, 4);
		glVertex3f(4, -9.7, 4);
		glEnd();

	}

	else {

		glBindTexture(GL_TEXTURE_2D, texture[11]);
		//carpet
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-4, -9.7999, 4);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(0, -9.7999, 4);    // �ؽ�ó�� ������ ���ʾƷ�
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(4, -9.7999, 0);    // �ؽ�ó�� ������ �����ʾƷ�
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7999, -4);    // �ؽ�ó�� ������ ��������
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-4, -9.7999, -4);    // �ؽ�ó�� ������ ������
		glEnd();
			
		glBindTexture(GL_TEXTURE_2D, texture[13]);
		//open_book
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, -9.7, 4);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(4, -9.7, 4);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(4, -9.7, 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5, -9.7, 2);
		glEnd();
			
		glBindTexture(GL_TEXTURE_2D, texture[14]);
		//memo
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.7, -9.699, 3.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(3.0, -9.699, 3.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(3.0, -9.699, 2.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.7, -9.699, 2.5);
		glEnd();

		//���ʸ�
		glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0.0);
		glVertex3f(0.5, -10, 2);
		glVertex3f(0.5, -10, 4);
		glVertex3f(0.5, -9.7, 4);
		glVertex3f(0.5, -9.7, 2);
		glEnd();

		//�����ʸ�
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0.0);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -10, 4);
		glVertex3f(4, -9.7, 4);
		glVertex3f(4, -9.7, 2);
		glEnd();
			
		//�ĸ�
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glVertex3f(0.5, -10, 2);
		glVertex3f(4, -10, 2);
		glVertex3f(4, -9.7, 2);
		glVertex3f(0.5, -9.7, 2);
		glEnd();
	
		//����
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1.0);
		glVertex3f(4, -10, 4);
		glVertex3f(0.5, -10, 4);
		glVertex3f(0.5, -9.7, 4);
		glVertex3f(4, -9.7, 4);
		glEnd();
	}
}
