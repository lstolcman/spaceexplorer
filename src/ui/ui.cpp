#include "stdafx.hpp"
#include "ui.hpp"




CUI::CUI(SData *data)
{
	this->data = data;
	font = GLUT_BITMAP_HELVETICA_12;
}


CUI::~CUI()
{
}


void CUI::drawUI(void)
{

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3f(0.1f, 0.1f, 0.1f);

	displayHUD();
	displayFPS();
#ifdef _DEBUG
	displayDebug();
#endif


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void CUI::setFont(void* font)
{
	this->font = font;
}





void CUI::printOnScreen(int x, int y, std::string text)
{
	glRasterPos2f(x, y);

	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(font, text[i]);
	}
}



void CUI::displayHUD(void)
{
	if (data->drawHUD)
	{
		unsigned width = glutGet(GLUT_WINDOW_WIDTH);
		unsigned height = glutGet(GLUT_WINDOW_HEIGHT);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.1f);
		//glBindTexture(GL_TEXTURE_2D, texture());
		glTexCoord2f(0, 0);
		glVertex2f(100, 100);
		glTexCoord2f(0, 1);
		glVertex2f(100, 200);
		glTexCoord2f(1, 1);
		glVertex2f(200, 200);
		glTexCoord2f(1, 0);
		glVertex2f(200, 100);
		glEnd();
		glDisable(GL_TEXTURE_2D);


	}
}


void CUI::displayDebug(void)
{
	std::stringstream s;
	s	<< std::fixed << std::setprecision(4)
		<< "pos=" << data->camera->pos.x << "x" << data->camera->pos.y << "x" << data->camera->pos.z << "  "
		<< "view=" << data->camera->view.x << "x" << data->camera->view.y << "x" << data->camera->view.z << "  "
		<< "velRX:" << data->camera->velRX << "  velRY:" << data->camera->velRY;
	printOnScreen(10, 36, s.str());
	s.str("");
	s << "Keys: ";
	for (int i = 0; i < 93; ++i)
	if (data->inputState->keys[i + 32] == KEYDOWN)
		s << char(i+32)  << " ";
	printOnScreen(10, 52, s.str());

}


void CUI::displayFPS(void)
{
	std::stringstream s;
	s << "FPS: " << data->last_fps;
	printOnScreen(10, 20, s.str());
}







