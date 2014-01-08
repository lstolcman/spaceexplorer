#include "stdafx.hpp"
#include "ui.hpp"




CUI::CUI(SData *data)
{
	this->data = data;
	font = GLUT_BITMAP_HELVETICA_12;
	textLines = 0;
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

	displayDebug();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	textLines = 0;
}


void CUI::setFont(void* font)
{
	this->font = font;
}





void CUI::printOnScreen(std::string &text)
{
	glRasterPos2f(10, 20 + 16 * textLines);
	glutBitmapString(font, (const unsigned char *)text.c_str());
	++textLines;
}




void CUI::printOnScreen(int x, int y, std::string &text)
{
	glRasterPos2f(x, y);
	glutBitmapString(font, (const unsigned char *)text.c_str());
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
	if (data->drawDebug)
	{
		std::stringstream s;
		s << std::fixed << std::setprecision(4);
		s << "pos=" << data->camera->pos.x << "x" << data->camera->pos.y << "x" << data->camera->pos.z;
		printOnScreen(s.str());
		s.str("");
		s << "view=" << data->camera->view.x << "x" << data->camera->view.y << "x" << data->camera->view.z;
		printOnScreen(s.str());
		s.str("");
		s << "up=" << data->camera->up.x << "x" << data->camera->up.y << "x" << data->camera->up.z;
		printOnScreen(s.str());
		s.str("");
		s << "speed=" << data->camera->speed;
		printOnScreen(s.str());
		s.str("");
		s << "velRX:" << data->camera->velRX << "  velRY:" << data->camera->velRY << "  velRZ:" << data->camera->velRZ;
		printOnScreen(s.str());
		s.str("");
		s << std::setprecision(2) << "angleX:" << (data->camera->angleX * 180) / PI
			<< "  angleY:" << (data->camera->angleY * 180) / PI
			<< "  angleZ:" << (data->camera->angleZ * 180) / PI;
		printOnScreen(s.str());
		s.str("");
		s << "Keys: ";
		for (int i = 0; i < 93; ++i)
		if (data->inputState->keys[i + 32] == KEYDOWN)
			s << char(i + 32) << " ";
		printOnScreen(s.str());
		s.str("");
		s << "Mouse: ";
		if (data->inputState->mouse.state == KEYDOWN)
		{
			switch (data->inputState->mouse.button)
			{
			case LEFT_BUTTON:
				s << "LEFT ";
				break;
			case MIDDLE_BUTTON:
				s << "MIDDLE ";
				break;
			case RIGHT_BUTTON:
				s << "RIGHT ";
				break;
			}
		}
		printOnScreen(s.str());
	}
}


void CUI::displayFPS(void)
{
	if (data->drawFPS)
	{
		std::stringstream s;
		s << "FPS: " << data->last_fps;
		printOnScreen(s.str());
	}
}







