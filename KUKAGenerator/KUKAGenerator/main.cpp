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
        if (!data_row.alive)
        {
            continue;
        }
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

    gluPerspective(/* field of view in degree */ 40.0,
        /* aspect ratio */ resize_f * w / h,
        /* Z near */ resize_f,
        /* Z far */ 100 * resize_f);
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    rot += 0.03f;
    glutPostRedisplay();
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

    // following lines are just for TESTING PURPOSE
    /*
    kuka_generator::DataRow test1;
    test1.position_filtered.x = 1;
    test1.position_filtered.y = 2;
    test1.position_filtered.z = 3;
    process_context.data_rows.push_back(test1);

    kuka_generator::DataRow test2;
    test2.position_filtered.x = 2;
    test2.position_filtered.y = 2;
    test2.position_filtered.z = 3;
    process_context.data_rows.push_back(test2);

    kuka_generator::DataRow test3;
    test3.position_filtered.x = 3;
    test3.position_filtered.y = 2;
    test3.position_filtered.z = 3;
    process_context.data_rows.push_back(test3);

    kuka_generator::DataRow test4;
    test4.position_filtered.x = 3;
    test4.position_filtered.y = 15;
    test4.position_filtered.z = 3;
    process_context.data_rows.push_back(test4);

    kuka_generator::DataRow test5;
    test5.position_filtered.x = 13;
    test5.position_filtered.y = 20;
    test5.position_filtered.z = 3;
    process_context.data_rows.push_back(test5);

    kuka_generator::DataRow test6;
    test6.position_filtered.x = 16;
    test6.position_filtered.y = 20;
    test6.position_filtered.z = 3;
    process_context.data_rows.push_back(test6);

    kuka_generator::DataRow test7;
    test7.position_filtered.x = 20;
    test7.position_filtered.y = 20;
    test7.position_filtered.z = 3;
    process_context.data_rows.push_back(test7);

    std::vector<kuka_generator::DataRow>::iterator it = process_context.data_rows.begin() +6;
    */

    // Step 5 - Douglas Peucker (3D)
    //

    kuka_generator::CopyFilterProcessStep copy_filter_process_step(process_context);

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
    // Execute the process
    //

    example_process_step.process();

    // step 2
    load_input_file_process_step.process();

    // step 5

    // this is needed to have any usable data in the filtered position data.
    // Otherwise the filtered data is just 0 and the doublas peucker will not work correctly
    copy_filter_process_step.process();

    //constexpr double max_distance = 99999.0;
    constexpr double max_distance = 25.0;
    //constexpr double max_distance = 5.0;
    //constexpr double max_distance = 0.5;
    //constexpr double max_distance = 0.001;

    std::vector<kuka_generator::DataRow>::iterator lastItr = std::prev(process_context.data_rows.end());
    DP.DPRecursive(&process_context, process_context.data_rows.begin(), lastItr, max_distance);
    //DP.DPRecursive(&process_context, process_context.data_rows.begin(), process_context.data_rows.end(), max_distance);

    // this following line is just for TESTING PURPOSE | if the line is used (testing) the line above must be commended out
    //DP.DPRecursive(&process_context, process_context.data_rows.begin(), it, 5.0);

    size_t total_count = process_context.data_rows.size();

    size_t not_deleted_count = std::count_if(std::begin(process_context.data_rows), std::end(process_context.data_rows),
        [](const kuka_generator::DataRow& obj) { return obj.alive; });

    std::cout << "Total: " << total_count << " after Douglas-Peucker: " << not_deleted_count << std::endl;

    kuka_generator::Vector3f center;
    int count = 0;
    for (auto& data_row : process_context.data_rows)
    {
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

    for (auto& data_row : process_context.data_rows)
    {
        if (!data_row.alive)
        {
            continue;
        }

        data_row.position_filtered.x -= center.x;
        data_row.position_filtered.y -= center.y;
        data_row.position_filtered.z -= center.z;

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

    return 0;
}
