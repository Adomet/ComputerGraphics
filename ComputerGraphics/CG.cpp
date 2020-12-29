// Ahmed Talha Budak 161180015
// Libraries
#include <iostream>
#include <GL/glut.h>
#include <imgui.h>
#include <imgui_impl_glut.h>
#include <imgui_impl_opengl2.h>

//Colors

GLfloat cyan[3] = { 0,1,1 };
GLfloat green[3] = { 0,1,0 };
GLfloat blue[3] = { 0,0,1 };
GLfloat black[3] = { 0,0,0 };
GLfloat white[3] = { 1,1,1 };
GLfloat yellow[3] = { 0.8,0.8,0 };
GLfloat magenta[3] = { 1,0,1 };
GLfloat red[3] = { 1,0,0 };

//Field Of View
float fov =30;

//model transforms
float mxpos = 0;
float mypos = 0;
float mzpos = 0;
float mdeltapos = 0.1;
      
float mxrot = 0;
float myrot = 0;
float mzrot = 0;
float mdeltarot = 1;
      
float msca = 1;
float mdeltasca = 0.1;

// Eye Transforms
float vxpos = 0;
float vypos = 0;
float vzpos = -10;
float vdeltapos = 0.1;
      
float vxrot = 0;
float vyrot = 0;
float vzrot = 0;
float vdeltarot = 1;

//swicth var for windows
int swc = 0;

// Screen Size height,width
GLsizei h = 900, w = 900;

//Draw The Axis lines and Grid
void DrawCanvas()
{
    glLineWidth(1);

    glColor3fv(white);
    glutSolidCube(0.1);

    glBegin(GL_LINES);


    glColor4f(0.2,0.2,0.2,1);
    for (int i = -50; i < 51; i++)
    {
            glVertex3f( 50, 0, i);
            glVertex3f(-50, 0,i);
    }

    for (int i = -50; i < 51; i++)
    {
        glVertex3f(i , 0,  50);
        glVertex3f(i , 0, -50);
    }

    glColor3fv(red);
    glVertex3f(10000, 0, 0);
    glVertex3f(-10000, 0, 0);

    glColor3fv(green);
    glVertex3f(0, 10000, 0);
    glVertex3f(0, -10000, 0);

    glColor3fv(blue);
    glVertex3f(0, 0, 10000);
    glVertex3f(0, 0, -10000);



    glEnd();

}
//Cube Functions
void Cube(float * color)
{

    glLineWidth(1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_LINE_LOOP);
    glColor3fv(color);

    // top of cube            
    glVertex3f(1, 1, -1);	
    glVertex3f(-1, 1, -1);	
    glVertex3f(-1, 1, 1);	
    glVertex3f(1, 1, 1);	

    glEnd();				
    glBegin(GL_LINE_LOOP);


    // bottom of cube
    glVertex3f(1, -1, 1);	
    glVertex3f(-1, -1, 1);	
    glVertex3f(-1, -1, -1);	
    glVertex3f(1, -1, -1);	

    glEnd();				
    glBegin(GL_LINE_LOOP);
    // front of cube
    glVertex3f(1, 1, 1);	
    glVertex3f(-1, 1, 1);	
    glVertex3f(-1, -1, 1);	
    glVertex3f(1, -1, 1);	
   
    glEnd();				
    glBegin(GL_LINE_LOOP);


    // back of cube.
    glVertex3f(1, -1, -1);	
    glVertex3f(-1, -1, -1);	
    glVertex3f(-1, 1, -1);	
    glVertex3f(1, 1, -1);	

    glEnd();				
    glBegin(GL_LINE_LOOP);

    // left of cube
    glVertex3f(-1, 1, 1);	
    glVertex3f(-1, 1, -1);	
    glVertex3f(-1, -1, -1);	
    glVertex3f(-1, -1, 1);	

    glEnd();				
    glBegin(GL_LINE_LOOP);

    // Right of cube
    glVertex3f(1, 1, -1);	  
    glVertex3f(1, 1, 1);	
    glVertex3f(1, -1, 1);	
    glVertex3f(1, -1, -1);	


    glEnd();				

}


// 3D render operations
void render3D(float aspect) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, aspect, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Eye Transform Funtions

    glRotatef(vxrot, 1, 0, 0);
    glRotatef(vyrot, 0, 1, 0);
    glRotatef(vzrot, 0, 0, 1);
    glTranslatef(vxpos, vypos, vzpos);


    glColor3f(1, 0, 0);
    DrawCanvas();

    // Modal Transform Funtions
    //cube translate
    glTranslatef(mxpos, mypos, mzpos);

    //cube rotate
    glRotated(mxrot, 1, 0, 0);
    glRotated(myrot, 0, 1, 0);
    glRotated(mzrot, 0, 0, 1);
   
    //cube scale
    glScalef(msca, msca, msca);

    Cube(yellow);

    glFlush();
}
// Reset to default values
void reset()
{
    mxpos = 0;
    mypos = 0;
    mzpos = 0;

    mxrot = 0;
    myrot = 0;
    mzrot = 0;

    vxpos = 0;
    vypos = 0;
    vzpos = -10;

    vxrot = 0;
    vyrot = 0;
    vzrot = 0;

    fov = 30;
    msca = 1;
}

//Generate UI Windows
void generateWindows()
{
    ImGui::Begin("Main Menu");
    ImGuiCond cond = 0;
    ImGui::SetWindowPos(ImVec2(5, 5), cond);
    ImGui::SetWindowSize(ImVec2(350, 250), cond);

    ImGui::Text("Choose a Window to Show");             
    ImGui::RadioButton("Trans Model Menu", &swc, 0);
    ImGui::RadioButton("Rot Model Menu", &swc, 1);
    ImGui::RadioButton("Scale Model Menu", &swc, 2);

    ImGui::RadioButton("Trans Eye Menu", &swc, 3);
    ImGui::RadioButton("Rot Eye Menu", &swc, 4);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat("Fov", &fov, 5.0f, 160.0f);
    if (ImGui::Button("Reset"))
        reset();
    ImGui::SameLine();
    if (ImGui::Button("Exit"))
        exit(0);
    ImGui::End();


    if (swc ==0)
    {
        ImGui::Begin("Trans Model Menu");

        ImGuiCond cond = 0;
        ImGui::SetWindowPos(ImVec2(700, 10), cond);
        ImGui::SetWindowSize(ImVec2(200, 175), cond);

        ImGui::PushButtonRepeat(true);

        if (ImGui::Button("Trans +X"))
            mxpos += mdeltapos;
        ImGui::SameLine();
        if (ImGui::Button("Trans -X"))
            mxpos -= mdeltapos;

        if (ImGui::Button("Trans +Y"))
            mypos += mdeltapos;
        ImGui::SameLine();
        if (ImGui::Button("Trans -Y"))
            mypos -= mdeltapos;

        if (ImGui::Button("Trans +Z"))
            mzpos += mdeltapos;
        ImGui::SameLine();
        if (ImGui::Button("Trans -Z"))
            mzpos -= mdeltapos;


        ImGui::End();
    }
    if (swc == 1)
    {
      ImGui::Begin("Rot Model Menu");
        ImGuiCond cond = 0;
        ImGui::SetWindowPos(ImVec2(650, 10), cond);
        ImGui::SetWindowSize(ImVec2(250, 175), cond);

        ImGui::SliderFloat("Rot X", &mxrot, -360.0f, 360.0f);
        ImGui::SliderFloat("Rot Y", &myrot, -360.0f, 360.0f);
        ImGui::SliderFloat("Rot Z", &mzrot, -360.0f, 360.0f);
        ImGui::End();
    }

    if (swc == 2)
    {
        ImGui::Begin("Scale Model Menu");

        ImGuiCond cond = 0;
        ImGui::SetWindowPos(ImVec2(650, 10), cond);
        ImGui::SetWindowSize(ImVec2(250, 175), cond);


        ImGui::SliderFloat("Scale Model", &msca, 0, 5);

        ImGui::End();
    }
    if (swc == 3)
    {
        ImGui::Begin("Trans Eye Menu");

        ImGuiCond cond = 0;
        ImGui::SetWindowPos(ImVec2(700, 10), cond);
        ImGui::SetWindowSize(ImVec2(200, 175), cond);


        ImGui::PushButtonRepeat(true);

        if (ImGui::Button("Trans +X"))
            vxpos += vdeltapos;
        ImGui::SameLine();
        if (ImGui::Button("Trans -X"))
            vxpos -= vdeltapos;

        if (ImGui::Button("Trans +Y"))
            vypos += vdeltapos;
        ImGui::SameLine();
        if (ImGui::Button("Trans -Y"))
            vypos -= vdeltapos;

        if (ImGui::Button("Trans +Z"))
            vzpos += vdeltapos;
        ImGui::SameLine();
        if (ImGui::Button("Trans -Z"))
            vzpos -= vdeltapos;

        ImGui::End();
    }

    if (swc == 4)
    {
        ImGui::Begin("Rot Eye Menu");

        ImGuiCond cond = 0;
        ImGui::SetWindowPos(ImVec2(650, 10), cond);
        ImGui::SetWindowSize(ImVec2(250, 175), cond);

        ImGui::PushButtonRepeat(true);

        ImGui::SliderFloat("Rot X", &vxrot, -180.0f, 180.0f);
        ImGui::SliderFloat("Rot Y", &vyrot, -180.0f, 180.0f);
        ImGui::SliderFloat("Rot Z", &vzrot, -180.0f, 180.0f);
        ImGui::End();
    }
   
    ImGui::Begin("Object Info");

    ImGui::SetWindowPos(ImVec2(10, 790), cond);
    ImGui::SetWindowSize(ImVec2(300, 100), cond);

    ImGui::Text("Model Pos Info:   X:%.1f, Y:%.1f, Z:%.1f", mxpos, mypos, mzpos);
    ImGui::Text("Model Rot Info:   X:%.1f, Y:%.1f, Z:%.1f", mxrot, myrot, mzrot);
    ImGui::Text("Eye   Pos Info:   X:%.1f, Y:%.1f, Z:%.1f", vxpos, vypos, vzpos);
    ImGui::Text("Eye   Rot Info:   X:%.1f, Y:%.1f, Z:%.1f", vxrot, vyrot, vzrot);

    ImGui::End();
    
}

//UI render operations
void renderUI()
{

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();


    generateWindows();


    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

// Display function
void display()
{
    float aspect = w / h;
    glClearColor(0.1,0.1,0.12,1);
    glClear(GL_COLOR_BUFFER_BIT);
    renderUI();
    render3D(aspect);
    glutSwapBuffers();
    glutPostRedisplay();
}

//Keyboard function
void Keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {

    case 'a' | 'A':
        reset();
        break;
    case 'q' | 'Q':
        exit(0);
        break;
    case 'o':
        swc = 4;
        break;
    case 'e':
        swc = 3;
        break;
    case 'r':
        swc = 1;
        break;
    case 't':
        swc = 0;
        break;
    case 's':
        swc = 2;
    default:
        break;
    }

    glutPostRedisplay();
}


// Main
void main(int argc, char** argv)
{
    //Window setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    glutInitWindowPosition((screenWidth / 2) - (w / 2), (screenHeight / 2) - (h / 2));
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("HW3");

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.Fonts->AddFontDefault();

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();
   
  
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(display);

    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();


}

