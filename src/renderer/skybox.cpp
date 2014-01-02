#include "stdafx.hpp"
#include "skybox.hpp"



CSkybox::CSkybox(void)
{


}



CSkybox::~CSkybox()
{


}





void CSkybox::load(void)
{
	CTimer t;
	t.start();

	front.Load("resources/s_front5.bmp", GL_NEAREST, GL_NEAREST);
	back.Load("resources/s_back6.bmp", GL_NEAREST, GL_NEAREST);
	right.Load("resources/s_right1.bmp", GL_NEAREST, GL_NEAREST);
	left.Load("resources/s_left2.bmp", GL_NEAREST, GL_NEAREST);
	top.Load("resources/s_top3.bmp", GL_NEAREST, GL_NEAREST);
	bottom.Load("resources/s_bottom4.bmp", GL_NEAREST, GL_NEAREST);

	t.stop();
	std::cout << "Skybox loaded, took " << t.getElapsedMilliseconds() << "ms" << std::endl;
}



void CSkybox::draw(void)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);


	/*float m_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);*/


#pragma region skybox

#pragma region Przednia sciana
	{
		glBindTexture(GL_TEXTURE_2D, front());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Tylna sciana
	{
		glBindTexture(GL_TEXTURE_2D, back());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Lewa sciana
	{
		glBindTexture(GL_TEXTURE_2D, left());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Prawa sciana
	{
		glBindTexture(GL_TEXTURE_2D, right());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Podloga
	{
		glBindTexture(GL_TEXTURE_2D, bottom());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Sufit
	{
		glBindTexture(GL_TEXTURE_2D, top());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma endregion


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}





