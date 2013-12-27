#include "stdafx.hpp"
#include "ui.hpp"




CUI::CUI()
{
	font = GLUT_BITMAP_HELVETICA_18;
}


CUI::~CUI()
{

}


void CUI::drawUI(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);

	//glutPrint(2, 10, glutFonts[4], its(sfps) + " fps; " + its(todrawquads) + " quads drawing; ");


	displayHUD();
	displayFPS();


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

		for (int i = 0; i<text.size(); i++)
		{
			glutBitmapCharacter(font, text[i]);
		}
}



void CUI::displayHUD(void)
{


}



void CUI::displayFPS(void)
{
	printOnScreen(10, 10, "FPS: ?");
}



/*


for (int i = 0; i<text.size(); i++)
{
	glutBitmapCharacter(font, text[i]);
}


void glutPrint(float x, float y, LPVOID font, string text)
{
	glRasterPos2f(x, y);

	for (int i = 0; i<text.size(); i++)
	{
		glutBitmapCharacter(font, text[i]);
	}
}

Every frame in DisplayFunction in drawing HUD section(calling DrawHUD()) :

void DrawHUD(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3f(0.2f, 0.2f, 0.2f);

	glutPrint(2, 10, glutFonts[4], its(sfps) + " fps; " + its(todrawquads) + " quads drawing; ");

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}


string its(int i)
{
	stringstream out;
	out << i;
	return out.str();
}*/























