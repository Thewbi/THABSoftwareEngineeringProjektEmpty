#include <ctime>
#include <iostream>
#include <valarray>

//#include "BmpHandler.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>

#include "DataRow.h"
#include "DP.h"
#include "userinterface.h"
#include <CopyFilterProcessStep.h>
#include <ExampleProcessStep.h>
#include <IProcessStep.h>
#include <LoadInputFileProcessStep.h>
#include <ProcessContext.h>

#include <glut.h>

using namespace std;

// here, the process context variable is declared.
// This is the variable that is used throughout the entire process.
// It is passed from step to step. Each step is allowed to add or remove information from the context.
kuka_generator::ProcessContext process_context;

float rot = 0.0f;
float resize_f = 1.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0, 0.0, -50.0,  /* eye is at (0,0,5) */
        0.0, 0.0, 0.0,      /* center is at (0,0,0) */
        0.0, 1.0, 0.0);      /* up is in positive Y direction */

    glRotatef(rot, 1.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);
    for (auto& data_row : process_context.data_rows)
    {
        // ignore points that DouglasPeucker has removed
        if (!data_row.alive)
        {
            continue;
        }

        // render the point
        glVertex3f(data_row.position_filtered.x, data_row.position_filtered.y, data_row.position_filtered.z);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(40.0, // field of view in degree
        resize_f * w / h, // aspect ratio
        resize_f, // Z near
        100 * resize_f // Z far
    );
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    rot += 0.03f;
    glutPostRedisplay();
}

void start_graphical_output()
{


    // compute center of gravity of all points (3d average point)
    kuka_generator::Vector3f center;
    int count = 0;
    for (auto& data_row : process_context.data_rows)
    {
        // ignore points that DouglasPeucker has removed
        if (!data_row.alive)
        {
            continue;
        }

        center += data_row.position_filtered;
        count++;
    }
    center.x /= count;
    center.y /= count;
    center.z /= count;

    // align all points around the origin
    // make the point cloud fit onto the screen
    for (auto& data_row : process_context.data_rows)
    {
        // ignore points that DouglasPeucker has removed
        if (!data_row.alive)
        {
            continue;
        }

        // move the center of gravity of all points to the origin (0|0|0)
        data_row.position_filtered.x -= center.x;
        data_row.position_filtered.y -= center.y;
        data_row.position_filtered.z -= center.z;

        // shrink the point cloud so that it fits onto the screen
        data_row.position_filtered.x /= 50.0;
        data_row.position_filtered.y /= 50.0;
        data_row.position_filtered.z /= 50.0;
    }

    // copy glut32.dll to C:\Windows\SysWOW64
    // this will only compile using the x86 configuration since glut is 32 bit!
    int argc = 1;
    char* argv[1] = { (char*)"Something" };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("GLUT");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
}

int main()
{
    //
    // Create all steps
    //

    // Step 0 - example step
    //
    // this step does nothing really
    kuka_generator::ExampleProcessStep example_process_step(process_context);

    // Step 1 - read user input
    //
    kuka_generator::Userinterface userinterface_process_step(process_context);

    // this input file will be processed (TODO: step 1 has to produce this information!)
    //process_context.input_file = "resources\\path_01.csv";
    //process_context.input_file = "resources\\path_02.csv";
    process_context.input_file = "resources\\path_03.csv";

    // Step 2 - load input file
    // 
    // create the LoadInputFileStep and insert it into the vector
    // pass the process context into the constructor
    kuka_generator::LoadInputFileProcessStep load_input_file_process_step(process_context);

    // Step 3 - Apply Filter (Position)
    //

    // Step 4 - Apply Filter (Orientation)
    //

    // TODO: replace this implementation by a real implementation
    kuka_generator::CopyFilterProcessStep copy_filter_process_step(process_context);

    // Step 5 - Douglas Peucker (3D)
    //

    // The Varible DP is given the adress of process_context, the first element, the last element
    // and the tolerance (width of the DP Line) in
    // which the points are allowed to be without creating a new corner point

    kuka_generator::CDP DP;

    // Step 6 - Umrechnung Orientierungsmatrix in Euler Winkel
    //

    // Step 7 - Berechnung der Geschwindigkeit
    //

    // Step 8 - Ausgabe in KUKA KRL (.src)
    //

    //
    // Execute all steps
    //

    // step 0
    //

    example_process_step.process();

    // step 1
    //

    userinterface_process_step.process();

    // step 2
    //

    int result_load_input_file = load_input_file_process_step.process();
    if (result_load_input_file != kuka_generator::NO_ERROR)
    {
        std::cout << "[ERROR] Anwendung wird abgebrochen!" << std::endl;
        std::cout << "[ERROR] Ursache ist, dass das Einlesen der Datendatei " << process_context.input_file << " nicht moeglich war!" << std::endl;

        // return 2 to show that step 2 failed
        return 2;
    }

    // step 3
    //

    // TODO

    // step 4
    //

    // TODO

    // TODO: replace this implementation by a real implementation
    // 
    // this is needed to have any usable data in the filtered position data.
    // Otherwise the filtered data is just 0 and the doublas peucker will not work correctly
    copy_filter_process_step.process();

    // step 5
    //

    std::cout << std::endl << "Step 5 - Douglas Peucker algorithm started" << std::endl;

    double max_distance = process_context.douglas_peucker_max_distance;

    std::vector<kuka_generator::DataRow>::iterator lastItr = std::prev(process_context.data_rows.end());
    DP.DPRecursive(process_context.data_rows, process_context.data_rows.begin(), lastItr, max_distance);

    size_t total_count = process_context.data_rows.size();

    size_t not_deleted_count = std::count_if(std::begin(process_context.data_rows), std::end(process_context.data_rows),
        [](const kuka_generator::DataRow& obj) { return obj.alive; });

    std::cout << "Total: " << total_count << " after Douglas-Peucker: " << not_deleted_count << std::endl;

    // step 6
    //

    // TODO

    // step 7
    //

    // TODO

    // step 8
    //

    // TODO

    //
    // DEBUG - graphical output
    //

    start_graphical_output();

    return 0;
}
