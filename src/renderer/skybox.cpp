#include "stdafx.hpp"
#include "skybox.hpp"



CSkybox::CSkybox(void)
{
	version = "4";

#ifdef _DEBUG
	size = "512";
#else
	size = "2048";
#endif

}


CSkybox::~CSkybox()
{

}


void CSkybox::load(void)
{

	front.Load("resources/skybox/" + version + "/" + size + "_front5.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	back.Load("resources/skybox/" + version + "/" + size + "_back6.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	right.Load("resources/skybox/" + version + "/" + size + "_right1.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	left.Load("resources/skybox/" + version + "/" + size + "_left2.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	top.Load("resources/skybox/" + version + "/" + size + "_top3.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	bottom.Load("resources/skybox/" + version + "/" + size + "_bottom4.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	CTimer t;
	t.start();

	frontHandle = glGenLists(1);
	backHandle = glGenLists(1);
	rightHandle = glGenLists(1);
	leftHandle = glGenLists(1);
	topHandle = glGenLists(1);
	bottomHandle = glGenLists(1);


#pragma region Przednia sciana
	glNewList(frontHandle, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, front());
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
	glDisable(GL_TEXTURE_2D);
	glEndList();
#pragma endregion

#pragma region Tylnia sciana
	glNewList(backHandle, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, back());
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

	glDisable(GL_TEXTURE_2D);
	glEndList();
#pragma endregion

#pragma region Lewa sciana
	glNewList(leftHandle, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

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

	glDisable(GL_TEXTURE_2D);
	glEndList();
#pragma endregion

#pragma region Prawa sciana
	glNewList(rightHandle, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, right());
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

	glDisable(GL_TEXTURE_2D);
	glEndList();
#pragma endregion

#pragma region Podloga
	glNewList(bottomHandle, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, bottom());
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

	glDisable(GL_TEXTURE_2D);
	glEndList();
#pragma endregion

#pragma region Sufit
	glNewList(topHandle, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, top());
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

	glDisable(GL_TEXTURE_2D);
	glEndList();
#pragma endregion



	t.stop();
	std::cout << "skybox: " << t.getElapsedMilliseconds() << "ms" << std::endl;
}



void CSkybox::draw(void)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);

	float m_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

	glCallList(frontHandle);
	glCallList(backHandle);
	glCallList(leftHandle);
	glCallList(rightHandle);
	glCallList(topHandle);
	glCallList(bottomHandle);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}





