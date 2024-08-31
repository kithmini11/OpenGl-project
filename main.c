#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <GL/glu.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void sea();
void ground();
void tree();
void house(float wallR,float wallG,float wallB);
void fruitTree();
void flowerpot();
void horse();
void ManBoat();
void flowers();
void fish();
void fish2();
void flowerpot2();
void drawCircle(float cx, float cy, float r, int num_segments,float CircleR, float CircleG,float CircleB);
void drawEllipse(float cx, float cy, float rx, float ry, int num_segments, float red, float green, float blue);
void LoadTexture(const char* filename);
void sun();

float tailR = 0.0;
float tailDirection = 1.0;

float fishFinAngle = 0.0;
float fishFinDirection = 1.0;

float boatPosition = 0.0;
bool boatMoving = false;

float horsePosition = 0.0;
bool horseMoving = false;

float fishPosition = 0.0;
bool fishMoving = false;

float flowerpot2Scale = 1.0;
float fish2Scale = 1.0;
float fruittreeScale = 1.0;
float sunX = 0.8;


GLuint texture;
void LoadTexture(const char* filename) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    } else {
        printf("Failed to load texture\n");
    }
}

void sun(){
    glPushMatrix();
    glTranslatef(sunX, 0.0, 0.0);
    drawCircle(0.05,0.7,0.1,80,1.0,0.5,0.0);
    glPopMatrix();
}

void drawCircle(float cx, float cy, float r, int num_segments,float CircleR, float CircleG,float CircleB) {
    glColor3f( CircleR,CircleG, CircleB);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int num_segments, float red, float green, float blue) {
    int i;
    float theta, x, y;

    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (i = 0; i < num_segments; i++) {
        theta = 2.0f * M_PI * (float)i / (float)num_segments;
        x = rx * cosf(theta);
        y = ry * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void flowerpot2() {
    glPushMatrix();
    glScalef(flowerpot2Scale, flowerpot2Scale, 1.0);

    glColor3f(1.0, 1.0, 0.941);
    drawEllipse(0.85, -0.45, 0.07, 0.025, 100, 0.9, 0.4, 0.1);
    drawEllipse(0.85, -0.35, 0.07, 0.025, 100, 0.9, 0.4, 0.1);

    glBegin(GL_QUADS);
    glVertex2f(0.78, -0.45);
    glVertex2f(0.78, -0.35);
    glVertex2f(0.92, -0.35);
    glVertex2f(0.92, -0.45);
    glEnd();

    glColor3f(0.212, 0.271, 0.310);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0.85, -0.33);
    glVertex2f(0.85, -0.20);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.85, -0.30);
    glVertex2f(0.89, -0.22);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.85, -0.30);
    glVertex2f(0.81, -0.22);
    glEnd();

    drawCircle(0.85, -0.20, 0.02, 20, 1.0, 0.85, 0.9);
    drawCircle(0.89, -0.22, 0.02, 20, 0.5, 0.0, 0.5);
    drawCircle(0.81, -0.22, 0.02, 20, 1.0, 0.0, 0.0);

    glPopMatrix();
}

void drawFishFins(float finAngle) {
    glPushMatrix();
    glTranslatef(-0.575, -0.65, 0.0);
    glRotatef(finAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.575, 0.65, 0.0);

    glColor3f(1.0, 0.647, 0.0); // fish top fin
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.575,-0.6);
    glVertex2f(-0.575,-0.65);
    glVertex2f(-0.6,-0.65);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.575, -0.75, 0.0);
    glRotatef(-finAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.575, 0.75, 0.0);

    glColor3f(1.0, 0.647, 0.0); // fish bottom fin
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6,-0.75);
    glVertex2f(-0.575,-0.75);
    glVertex2f(-0.575,-0.8);
    glEnd();

    glPopMatrix();
}


void fish2(){

    glPushMatrix();
    glTranslatef(fishPosition, 0.0, 0.0);
    glScalef(fish2Scale, fish2Scale, 1.0);

    glColor3f(1.0, 1.0, 0.0); // fish
    glBegin(GL_QUADS);
    glVertex2f(-0.65,-0.7);
    glVertex2f(-0.6,-0.65);
    glVertex2f(-0.55,-0.7);
    glVertex2f(-0.6,-0.75);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // fish
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.65,-0.7);
    glVertex2f(-0.6,-0.65);
    glVertex2f(-0.55,-0.7);
    glVertex2f(-0.6,-0.75);
    glEnd();

    glColor3f(1.0, 1.0, 0.0); // fish back fin
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.56,-0.7);
    glVertex2f(-0.5,-0.65);
    glVertex2f(-0.5,-0.75);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // fish back fin
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.56,-0.7);
    glVertex2f(-0.5,-0.65);
    glVertex2f(-0.5,-0.75);
    glEnd();

    drawFishFins(fishFinAngle);

    glColor3f(0.0,0.0,0.0);  // fish eye
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2f(-0.625,-0.7);
    glEnd();

    glColor3f(.0, 1.0, 1.0);  // fish body lines
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.6,-0.65);
    glVertex2f(-0.6,-0.75);
    glEnd();

    glColor3f(.0, 1.0, 1.0);  // fish body lines
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.585,-0.66);
    glVertex2f(-0.585,-0.75);
    glEnd();

    glColor3f(.0, 1.0, 1.0);  // fish body lines
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.565,-0.67);
    glVertex2f(-0.565,-0.74);
    glEnd();

    glPopMatrix();

}

void fish(){
    glPushMatrix();
    glTranslatef(fishPosition, 0.0, 0.0);

    glColor3f(0.85, 0.44, 0.84); // fish
    glBegin(GL_QUADS);
    glVertex2f(-0.65,-0.7);
    glVertex2f(-0.6,-0.65);
    glVertex2f(-0.55,-0.7);
    glVertex2f(-0.6,-0.75);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // fish
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.65,-0.7);
    glVertex2f(-0.6,-0.65);
    glVertex2f(-0.55,-0.7);
    glVertex2f(-0.6,-0.75);
    glEnd();

    glColor3f(0.85, 0.44, 0.84); // fish back fin
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.56,-0.7);
    glVertex2f(-0.5,-0.65);
    glVertex2f(-0.5,-0.75);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // fish back fin
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.56,-0.7);
    glVertex2f(-0.5,-0.65);
    glVertex2f(-0.5,-0.75);
    glEnd();

    drawFishFins(fishFinAngle);

    glColor3f(0.0,0.0,0.0);  // fish eye
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2f(-0.625,-0.7);
    glEnd();

    glColor3f(.0, 1.0, 1.0);  // fish body lines
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.6,-0.65);
    glVertex2f(-0.6,-0.75);
    glEnd();

    glColor3f(.0, 1.0, 1.0);  // fish body lines
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.585,-0.66);
    glVertex2f(-0.585,-0.75);
    glEnd();

    glColor3f(.0, 1.0, 1.0);  // fish body lines
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.565,-0.67);
    glVertex2f(-0.565,-0.74);
    glEnd();

    glPopMatrix();

}

void ManBoat(){

    glPushMatrix();
    glTranslatef(boatPosition, 0.0, 0.0); // Move the boat

    glColor3f(0.0, 0.0, 0.0);//man hair
    glBegin(GL_QUADS);
    glVertex2f(-0.3875,-0.28);
    glVertex2f(-0.375,-0.27);
    glVertex2f(-0.375,-0.3);
    glVertex2f(-0.3875,-0.3);
    glEnd();

    glColor3f(0.96, 0.96, 0.86); //man face
    glBegin(GL_POLYGON);
    glVertex2f(-0.3875,-0.3);
    glVertex2f(-0.375,-0.3);
    glVertex2f(-0.35,-0.33);
    glVertex2f(-0.36,-0.33);
    glVertex2f(-0.36,-0.37);
    glVertex2f(-0.3875,-0.37);
    glEnd();

    glColor3f(0.0,0.0,0.0);  // man eye
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex2f(-0.375,-0.33);
    glEnd();

    glColor3f(0.85, 0.2, 0.11); //man body
    glBegin(GL_POLYGON);
    glVertex2f(-0.39,-0.37);
    glVertex2f(-0.35,-0.37);
    glVertex2f(-0.38,-0.58);
    glVertex2f(-0.31,-0.5);
    glVertex2f(-0.3,-0.62);
    glVertex2f(-0.39,-0.62);
    glEnd();

    glColor3f(1.0, 0.647, 0.0); //boat
    glBegin(GL_QUADS);
    glVertex2f(-0.45,-0.62);
    glVertex2f(-0.0,-0.62);
    glVertex2f(-0.1,-0.8);
    glVertex2f(-0.38,-0.8);
    glEnd();

    glColor3f(0.0, 0.0, 0.0); //paddle
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.31,-0.5);
    glVertex2f(-0.4,-0.8);
    glVertex2f(-0.42,-0.8);
    glEnd();

    glPopMatrix();

}


void horse(){

    glPushMatrix();
    glTranslatef(horsePosition, 0.0, 0.0);

    glColor3f(0.6, 0.4, 0.2); // horse head
    glBegin(GL_POLYGON);
    glVertex2f(-0.27,-0.1);
    glVertex2f(-0.25,-0.23);
    glVertex2f(-0.3,-0.23);
    glVertex2f(-0.31,-0.18);
    glVertex2f(-0.33,-0.17);
    glVertex2f(-0.33,-0.12);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);  // horse muzzle line
    glLineWidth(9.0);
    glBegin(GL_LINES);
    glVertex2f(-0.33,-0.12);
    glVertex2f(-0.33,-0.17);
    glEnd();

    glColor3f(0.0,0.0,0.0);  // horse eye
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(-0.29,-0.13);
    glEnd();

    glColor3f(1.0,1.0,1.0); // horse hair
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.27,-0.1);
    glVertex2f(-0.22,-0.23);
    glVertex2f(-0.25,-0.23);
    glEnd();

    glColor3f(0.6, 0.4, 0.2); //horse body
    glBegin(GL_QUADS);
    glVertex2f(-0.3,-0.23);
    glVertex2f(-0.1,-0.23);
    glVertex2f(-0.1,-0.35);
    glVertex2f(-0.3,-0.35);
    glEnd();

    glColor3f(1.0,1.0,1.0); //horse left leg
    glBegin(GL_QUADS);
    glVertex2f(-0.3,-0.35);
    glVertex2f(-0.28,-0.35);
    glVertex2f(-0.28,-0.45);
    glVertex2f(-0.3,-0.45);
    glEnd();

    glColor3f(1.0,1.0,1.0); //horse right leg
    glBegin(GL_QUADS);
    glVertex2f(-0.12,-0.35);
    glVertex2f(-0.1,-0.35);
    glVertex2f(-0.1,-0.45);
    glVertex2f(-0.12,-0.45);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.1, -0.23, 0.0); // Translate to the tail's pivot point
    glRotatef(tailR, 0.0, 0.0, 1.0); // Rotate the tail
    glTranslatef(0.1, 0.23, 0.0);


    glColor3f(1.0,1.0,1.0); // horse tail
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.1,-0.23);
    glVertex2f(-0.06,-0.23);
    glVertex2f(-0.08,-0.39);
    glEnd();

    glPopMatrix();

    glColor3f(0.6, 0.4, 0.2); //horse muzzle
    glBegin(GL_QUADS);
    glVertex2f(-0.34,-0.12);
    glVertex2f(-0.33,-0.12);
    glVertex2f(-0.33,-0.17);
    glVertex2f(-0.34,-0.17);
    glEnd();

    glPopMatrix();

}
void flowerpot(){

glColor3f(1.0,0.65,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.78,-0.35);
    glVertex2f(-0.7,-0.35);
    glVertex2f(-0.72,-0.45);
    glVertex2f(-0.76,-0.45);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.78,-0.35);
    glVertex2f(-0.7,-0.35);
    glVertex2f(-0.72,-0.45);
    glVertex2f(-0.76,-0.45);
    glEnd();
}

void flowers(){
    glColor3f(1.0,0.65,0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(-0.74,-0.35);
    glVertex2f(-0.74,-0.25);
    glEnd();

glColor3f(1.0,0.65,0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(-0.74,-0.32);
    glVertex2f(-0.70,-0.28);
    glEnd();

glColor3f(1.0,0.65,0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(-0.74,-0.335);
    glVertex2f(-0.78,-0.28);
    glEnd();

drawCircle(-0.74,-0.25,0.02,20,1.0,0.75,0.8);
drawCircle(-0.70,-0.28,0.02,20,0.5,0.0,0.5);
drawCircle(-0.78,-0.30,0.02,20,1.0,0.0,0.0);


}

void fruitTree(){

    glPushMatrix();
    glLineWidth(5.0);
    glScalef(fruittreeScale, fruittreeScale, 1.0);

    glColor3f(0.0, 0.39, 0.0); //leaves of the fruit tree
    glBegin(GL_POLYGON);
    glVertex2f(-0.1,0.8);
    glVertex2f(-0.05,0.65);
    glVertex2f(-0.075,0.65);
    glVertex2f(-0.025,0.45);
    glVertex2f(-0.075,0.45);
    glVertex2f(0.0,0.2);
    glVertex2f(-0.2,0.2);
    glVertex2f(-0.125,0.45);
    glVertex2f(-0.175,0.45);
    glVertex2f(-0.125,0.65);
    glVertex2f(-0.15,0.65);
    glEnd();

    glColor3f(0.0, 1.0, 0.0); //border of the fruit tree
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1,0.8);
    glVertex2f(-0.05,0.65);
    glVertex2f(-0.075,0.65);
    glVertex2f(-0.025,0.45);
    glVertex2f(-0.075,0.45);
    glVertex2f(0.0,0.2);
    glVertex2f(-0.2,0.2);
    glVertex2f(-0.125,0.45);
    glVertex2f(-0.175,0.45);
    glVertex2f(-0.125,0.65);
    glVertex2f(-0.15,0.65);
    glEnd();

    glColor3f(0.4, 0.2, 0.0); //trunk of the fruit tree
    glBegin(GL_QUADS);
    glVertex2f(-0.125,0.2);
    glVertex2f(-0.075,0.2);
    glVertex2f(-0.075,-0.125);
    glVertex2f(-0.125,-0.125);
    glEnd();

    glColor3f(0.4,0.2,0.0);//right fruit
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-0.045,0.2);
    glVertex2f(-0.045,0.1);
    glEnd();

    glColor3f(0.4,0.2,0.0); //left fruit
    glBegin(GL_LINES);
    glVertex2f(-0.15,0.2);
    glVertex2f(-0.15,0.1);
    glEnd();

    drawCircle(-0.045, 0.1, 0.02, 20, 1.0, 0.0, 0.0); // Right fruit
    drawCircle(-0.15, 0.1, 0.02, 20, 1.0, 0.0, 0.0);  // Left fruit
    glPopMatrix();

}

void house(float wallR,float wallG,float wallB){

    glEnable(GL_TEXTURE_2D);     // add texture to the roof
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2f(-0.53, 0.35);
    glTexCoord2f(1.0, 1.0); glVertex2f(-0.37, 0.35);
    glTexCoord2f(1.0, 0.0); glVertex2f(-0.3, 0.25);
    glTexCoord2f(0.0, 0.0); glVertex2f(-0.6, 0.25);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);    // add border to the roof
    glBindTexture(GL_TEXTURE_2D, texture);
    glLineWidth(4.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glTexCoord2f(0.0, 1.0); glVertex2f(-0.53, 0.35);
    glTexCoord2f(1.0, 1.0); glVertex2f(-0.37, 0.35);
    glTexCoord2f(1.0, 0.0); glVertex2f(-0.3, 0.25);
    glTexCoord2f(0.0, 0.0); glVertex2f(-0.6, 0.25);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor3f(wallR,wallG,wallB); // wall of the house
    glBegin(GL_QUADS);
    glVertex2f(-0.55, 0.25);
    glVertex2f(-0.35, 0.25);
    glVertex2f(-0.35, -0.1);
    glVertex2f(-0.55, -0.1);
    glEnd();

    glColor3f(0.0, 0.0, 0.0); // wall of the house
    glLineWidth(4.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.35, 0.25);
    glVertex2f(-0.35, -0.1);
    glVertex2f(-0.55, -0.1);
    glVertex2f(-0.55, 0.25);
    glEnd();

    glEnable(GL_TEXTURE_2D); //add texture to the door
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5, 0.1);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(-0.4, 0.1);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(-0.4, -0.1);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5, -0.1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


void tree(){
    glColor3f(0.0, 0.39, 0.0); //leaves of the tree
    glBegin(GL_POLYGON);
    glVertex2f(-0.8,0.6);
    glVertex2f(-0.75,0.4);
    glVertex2f(-0.775,0.4);
    glVertex2f(-0.725,0.2);
    glVertex2f(-0.775,0.2);
    glVertex2f(-0.7,0.0);
    glVertex2f(-0.9,0.0);
    glVertex2f(-0.825,0.2);
    glVertex2f(-0.875,0.2);
    glVertex2f(-0.825,0.4);
    glVertex2f(-0.85,0.4);
    glEnd();

    glColor3f(0.0, 1.0, 0.0); //border of the tree
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8,0.6);
    glVertex2f(-0.75,0.4);
    glVertex2f(-0.775,0.4);
    glVertex2f(-0.725,0.2);
    glVertex2f(-0.775,0.2);
    glVertex2f(-0.7,0.0);
    glVertex2f(-0.9,0.0);
    glVertex2f(-0.825,0.2);
    glVertex2f(-0.875,0.2);
    glVertex2f(-0.825,0.4);
    glVertex2f(-0.85,0.4);
    glEnd();

    glColor3f(0.4, 0.2, 0.0); //trunk of the tree
    glBegin(GL_QUADS);
    glVertex2f(-0.825,0.0);
    glVertex2f(-0.775,0.0);
    glVertex2f(-0.775,-0.2);
    glVertex2f(-0.825,-0.2);
    glEnd();
}

void sea(){

    glColor3f(0.0, 1.0, 1.0); // sea
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -0.5);
    glVertex2f(1.0, -0.5);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    glColor3f(0.0, 0.1216, 0.2471); // sea
    glLineWidth(8.0);
    glBegin(GL_LINES);
    glVertex2f(-1.0, -0.5);
    glVertex2f(1.0, -0.5);
    glEnd();
}

void ground(){

    glColor3f(0.0, 0.39, 0.0); // ground
    glLineWidth(10.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-1.0, -0.5);
    glVertex2f(-1.0,-0.2);
    glVertex2f(-0.4, 0.02);
    glVertex2f(1.0, -0.1);
    glVertex2f(1.0, -0.5);
    glEnd();

    glColor3f(0.0, 1.0, 0.0); // ground
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -0.5);
    glVertex2f(-1.0,-0.2);
    glVertex2f(-0.4, 0.02);
    glVertex2f(1.0, -0.1);
    glVertex2f(1.0, -0.5);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    sea();
    ground();
    tree();
    house(0.5, 0.25, 0.5);
    fruitTree();
    flowerpot();
    horse();
    ManBoat();
    flowers();
    fish();
    sun();
    flowerpot2();
    drawCircle(-0.74,-0.25,0.02,20,1.0,0.75,0.8);
    drawCircle(-0.70,-0.28,0.02,20,0.5,0.0,0.5);
    drawCircle(-0.78,-0.30,0.02,20,1.0,0.0,0.0);


    glPushMatrix();
    glTranslatef(0.6,0.05,0.0);
    fruitTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,-0.05,0.0);
    house(0.5, 0.35, 0.75);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15,0.1,0.0);
    flowerpot();
    flowers();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.15,0.1,0.0);
    flowerpot2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.975,0.0,0.0);
    fish();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.3 ,-0.125, 0.0);
    fish2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.45,-1.45, 0.0);
    glRotatef(180.0,0.0,0.0,1.0);
    fish2();
    glPopMatrix();

glutSwapBuffers();
glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'b':
        boatMoving = true;
        break;
    case 'c':
        boatMoving = false;
        break;
    case 'h':
        horseMoving = true;
        break;
    case 's':
        horseMoving = false;
        break;
    case 'a':
        fishMoving = true;
        break;
    case 'f':
        fishMoving = false;
        break;
    case 'p':
        flowerpot2Scale *= 1.5;
        fish2Scale *= 1.5;
        glutPostRedisplay();
        break;
    case 'k':
        fruittreeScale *= 0.95;
        flowerpot2Scale *= 0.95;
        glutPostRedisplay();
        break;

    case ' ':
        sunX -= 0.2;
        flowerpot2Scale *= 0.95;
        glutPostRedisplay();
        break;
   }
}

void update(int value) {

    if (boatMoving) {
        boatPosition += 0.01; // boat moving
        if (boatPosition > 1.0) {
            boatPosition = -1.0;
        }
    }

   if (horseMoving) {
    horsePosition -= 0.01; // horse moving
    if (horsePosition < -1.0) {
        horsePosition = 1.0;
      }
   }

   if (fishMoving) {
        fishPosition += 0.01; // fish moving
        if (fishPosition > 1.0) {
            fishPosition = -1.0;
        }
    }

   tailR += tailDirection * 2.0f; //horse tail

    if (tailR > 20.0f || tailR < -20.0f) {
        tailDirection = -tailDirection;
    }

    fishFinAngle += fishFinDirection * 2.0f; // fish fins

    if (fishFinAngle > 20.0f || fishFinAngle < -20.0f) {
        fishFinDirection = -fishFinDirection;
    }


    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(1.0, 1.0, 0.4 ,0.0); // background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glLoadIdentity();
    LoadTexture("door.jpg");
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Scenery - Assignment");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);
    glutMainLoop();

    return 0;
}
