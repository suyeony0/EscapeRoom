#include "Egg.h"

void Egg::Draw(GLfloat _egg_point[][3]) {
	//������� ��������.

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			_egg_point[i][j] = _egg_point[i][j];
		}

	}

	glColor3f(colors[0], colors[1], colors[2]);

	glVertexPointer(3, GL_FLOAT, 0, _egg_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Egg::DrawObject(GLfloat _egg_point[][3]) {
	glFrontFace(GL_CCW); //ǥ���� �������� �� ���ΰ�, CCW�� �ݽð�������� ǥ���� ǥ���ϰڴٴ� ����
	glEnable(GL_CULL_FACE); // �������� �κ��߿��� �Ⱥ��̴� �κ��� �����ϴ� �Լ�. ��, �츮���� �Ⱥ��̴� �ڿ� �鿡 ���ؼ��� �� �׷��� �ǹǷ� �� �κ��� �ȱ׸�.

	//glEnableClientState(GL_COLOR_ARRAY); //�÷��� ����Ʈ�� �����Ϸ��� �̰� ����ϸ� ��
	glEnableClientState(GL_VERTEX_ARRAY);//�����迭��� Ȱ��ȭ�� ����

	//�� �׸���
	glNormal3f(0, 1, 0.0);
	Egg* egg = new Egg();
	egg->Draw(_egg_point);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//�� ������
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	//����
	glVertex3f(6, -4, -5);
	glVertex3f(6, -4, -9);
	glVertex3f(7, -4, -5);
	glVertex3f(7, -4, -9);
	glVertex3f(8, -4, -5);
	glVertex3f(8, -4, -9);
	glVertex3f(9, -4, -9);
	glVertex3f(9, -4, -5);
	glEnd();
	//����
	glBegin(GL_LINES);
	glVertex3f(6, -4, -5);
	glVertex3f(9, -4, -5);
	glVertex3f(6, -4, -6);
	glVertex3f(9, -4, -6);
	glVertex3f(6, -4, -7);
	glVertex3f(9, -4, -7);
	glVertex3f(6, -4, -8);
	glVertex3f(9, -4, -8);
	glVertex3f(6, -4, -9);
	glVertex3f(9, -4, -9);
	glEnd();
	//����
	glBegin(GL_LINES);
	glVertex3f(6, -4.5, -5);
	glVertex3f(6, -4.0, -5);
	glVertex3f(9, -4.5, -5);
	glVertex3f(9, -4.0, -5);
	glVertex3f(6, -4.5, -9);
	glVertex3f(6, -4.0, -9);
	glVertex3f(9, -4.5, -9);
	glVertex3f(9, -4.0, -9);
	glEnd();

	//�ظ�

	glBegin(GL_LINES);
	glVertex3f(6, -4.5, -5);
	glVertex3f(9, -4.5, -5);
	glVertex3f(6, -4.5, -5);
	glVertex3f(6, -4.5, -9);
	glVertex3f(9, -4.5, -5);
	glVertex3f(9, -4.5, -9);
	glVertex3f(6, -4.5, -9);
	glVertex3f(9, -4.5, -9);
	glEnd();

	//���
	glColor3f(1.0, 0.7216, 0.4392);
	glNormal3f(0, 1, 0.0);
	glPushMatrix();
	glTranslatef(8.5, -4.2, -7.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.5, -4.2, -6.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5, -4.2, -8.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, -4.2, -7.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, -4.2, -6.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, -4.2, -5.5);
	glutSolidSphere(0.4, 20, 10);
	glPopMatrix();

}