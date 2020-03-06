#include "Key.h"

void Key::Draw(GLfloat _key_point[][3]) {
	GLfloat key_point[8][3];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			key_point[i][j] = _key_point[i][j];
		}

	}

	glColor3f(MyColors[0][0], MyColors[0][1], MyColors[0][2]);


	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, key_point); // ���� ������ǥ�� ������ MyVertex����

	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList);


	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	}
}

void Key::DrawObject(GLfloat _key_point[][3]) {
	if (this->status == 0) {

		GLfloat _key_point2[8][3] = { //Ű ��
		{-9.03,-1.01,-0.35},{-9.03,-0.99,-0.35},{-9.01,-0.99,-0.35},{-9.01,-1.01,-0.35},
		{-9.03,-1.01,-0.40},{-9.03,-0.99,-0.40},{-9.01,-0.99,-0.40},{-9.01,-1.01,-0.40}};
		GLfloat _key_point3[8][3] = { //Ű �߰�
		{-9.04,-1.01,-0.45},{-9.04,-0.99,-0.45},{-9.01,-0.99,-0.45},{-9.01,-1.01,-0.45},
		{-9.04,-1.01,-0.5},{-9.04,-0.99,-0.5},{-9.01,-0.99,-0.5},{-9.01,-1.01,-0.5}};

		Key* key = new Key(this->index);
		glFrontFace(GL_CCW); //ǥ���� �������� �� ���ΰ�, CCW�� �ݽð�������� ǥ���� ǥ���ϰڴٴ� ����
		glEnable(GL_CULL_FACE); // �������� �κ��߿��� �Ⱥ��̴� �κ��� �����ϴ� �Լ�. ��, �츮���� �Ⱥ��̴� �ڿ� �鿡 ���ؼ��� �� �׷��� �ǹǷ� �� �κ��� �ȱ׸�.
		glEnableClientState(GL_COLOR_ARRAY); //�÷��� ����Ʈ�� �����Ϸ��� �̰� ����ϸ� ��
		glEnableClientState(GL_VERTEX_ARRAY);//�����迭��� Ȱ��ȭ�� ����

		glNormal3f(1, 0, 0.0);
		key->Draw(_key_point); //Ű
		key->Draw(_key_point2);
		key->Draw(_key_point3);


		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CW);


		//������
		key->DrawHandle(0.05);

	}
}

void Key::DrawHandle(GLfloat size) {
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-9, -1, 0);
	glutWireSphere(size, 20, 5);
	glTranslatef(9, 1, 0);
}
