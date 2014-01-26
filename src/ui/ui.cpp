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
	if (data->debugMode)
	{
		float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color);
	}
	else
	{
		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color);
	}

	//reset light
	float amb[] = { 1.0f, 1.0f, 1.0f };
	float dif[] = { 0.0f, 0.0f, 0.0f };
	float spe[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);


	glDisable(GL_DEPTH_TEST);
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
	glEnable(GL_DEPTH_TEST);
	textLines = 0;
}


void CUI::setFont(void* font)
{
	this->font = font;
}





void CUI::printOnScreen(std::string &text)
{
	glRasterPos2f((GLfloat)10, (GLfloat)20 + 16 * textLines);
	glutBitmapString(font, (const unsigned char *)text.c_str());
	++textLines;
}




void CUI::printOnScreen(int x, int y, std::string &text)
{
	glRasterPos2f((GLfloat)x, (GLfloat)y);
	glutBitmapString(font, (const unsigned char *)text.c_str());
}




void CUI::displayHUD(void)
{
	width = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
	height = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
	glEnable(GL_TEXTURE_2D);
	if (data->drawHUD && data->gameState == PLAYING)
	{
		if (data->camera->speed >= 8.0f)
			glBindTexture(GL_TEXTURE_2D, speed8());
		else if (data->camera->speed >= 6.0f)
			glBindTexture(GL_TEXTURE_2D, speed6());
		else if (data->camera->speed >= 4.0f)
			glBindTexture(GL_TEXTURE_2D, speed4());
		else if (data->camera->speed >= 2.0f)
			glBindTexture(GL_TEXTURE_2D, speed2());
		else
			glBindTexture(GL_TEXTURE_2D, speed0());

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(10, height-10);
		glTexCoord2f(1, 0);
		glVertex2f(40, height-10);
		glTexCoord2f(1, 1);
		glVertex2f(40, height-110);
		glTexCoord2f(0, 1);
		glVertex2f(10, height-110);
		glEnd();
	}
	if (data->gameState == LOOSE)
	{
		glBindTexture(GL_TEXTURE_2D, loose());
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 1);
		glVertex2f(0, 0);
		glTexCoord2f(1, 0);
		glVertex2f(0, height);
		glTexCoord2f(0, 0);
		glVertex2f(width, height);
		glTexCoord2f(0, 1);
		glVertex2f(width, 0);
		glEnd();

	}
	if (data->gameState == WIN)
	{
		glBindTexture(GL_TEXTURE_2D, win());
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 1);
		glVertex2f(0, 0);
		glTexCoord2f(1, 0);
		glVertex2f(0, height);
		glTexCoord2f(0, 0);
		glVertex2f(width, height);
		glTexCoord2f(0, 1);
		glVertex2f(width, 0);
		glEnd();

	}
	glDisable(GL_TEXTURE_2D);
}


void CUI::displayDebug(void)
{
	if (data->debugMode)
	{
		printOnScreen(100, 20, std::string("Debug mode"));
		if (data->drawCollisionEdges)
		{
			std::stringstream s;

			printOnScreen(200, 20, std::string(s.str()));

			int asti = 0;
			for (std::vector<SAsteroid>::iterator i = data->asteroids->begin(); i != data->asteroids->end(); ++i)
			{
				s.str("");
				s << i->pos.x << "A: x" << i->pos.y << "x" << i->pos.z << " d:" << i->distance
					<< " near:" << data->vehicleNearestAsteroidDistance << "scale:" << data->vehicleNearestAsteroidScale;
				if (i->collision)
					s << "\tCollision";
				printOnScreen(500, 20 + asti * 16, s.str());

				++asti;
			}
		}

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
			s << "velRX:" << data->camera->velRX << "  velRY:" << data->camera->velRY << "  velRZ:" << data->camera->velRZ << "  velM:" << data->camera->velM << "  velS:" << data->camera->velS;
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


void CUI::loadUIData(void)
{
	win.Load("resources/win.jpg");
	loose.Load("resources/loose.jpg");
	speed8.Load("resources/speed8.jpg");
	speed6.Load("resources/speed6.jpg");
	speed4.Load("resources/speed4.jpg");
	speed2.Load("resources/speed2.jpg");
	speed0.Load("resources/speed0.jpg");
}







