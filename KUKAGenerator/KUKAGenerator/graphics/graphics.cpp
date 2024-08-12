#include <graphics.h>

float rot = 0.0f;
float resize_f = 1.0f;
std::vector<kuka_generator::DataRow> data_rows_for_graphics;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0, 0.0, -50.0,  /* eye is at (0,0,5) */
        0.0, 0.0, 0.0,      /* center is at (0,0,0) */
        0.0, 1.0, 0.0);      /* up is in positive Y direction */

    glRotatef(rot, 1.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);
    for (auto& data_row : data_rows_for_graphics)
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
    kuka_generator::Vector3d center;
    int count = 0;
    for (auto& data_row : data_rows_for_graphics)
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
    for (auto& data_row : data_rows_for_graphics)
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


