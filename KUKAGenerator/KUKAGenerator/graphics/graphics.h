#pragma once

#include <stdlib.h>
#include <glut.h>

#include <ProcessContext.h>
#include <Vector3f.h>
#include <DataRow.h>

extern float rot;
extern float resize_f;
extern std::vector<kuka_generator::DataRow> data_rows_for_graphics;

void display();
void reshape(int w, int h);
void idle();
void start_graphical_output();
