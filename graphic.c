#include <GL/glut.h>
#include <math.h>

// Initial positions for horse, boat, etc.
float horseX = 0.7f, boatX = -1.0f;
float sunX = 0.0f;
float horseTailAngle = 0.0f;
int horseMovingLeft = 1;

// Function to draw a house
void drawHouse(float x, float y) {
    // Base of the house
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the base
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y + 0.2f);
    glVertex2f(x - 0.1f, y + 0.2f);
    glEnd();
    
    // Roof of the house
    glColor3f(0.6f, 0.3f, 0.0f); // Brown color for the roof
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.12f, y + 0.2f);
    glVertex2f(x + 0.12f, y + 0.2f);
    glVertex2f(x, y + 0.3f);
    glEnd();
    
    // Door
    glColor3f(0.0f, 0.0f, 1.0f); // Blue door
    glBegin(GL_QUADS);
    glVertex2f(x - 0.03f, y);
    glVertex2f(x + 0.03f, y);
    glVertex2f(x + 0.03f, y + 0.1f);
    glVertex2f(x - 0.03f, y + 0.1f);
    glEnd();
}

// Function to draw a horse
void drawHorse(float x, float y) {
    glColor3f(0.6f, 0.4f, 0.2f); // Brown color for the horse
    glBegin(GL_QUADS);
    glVertex2f(x - 0.05f, y);
    glVertex2f(x + 0.05f, y);
    glVertex2f(x + 0.05f, y + 0.1f);
    glVertex2f(x - 0.05f, y + 0.1f);
    glEnd();

    // Tail of the horse
    glPushMatrix();
    glTranslatef(x + 0.05f, y + 0.05f, 0);
    glRotatef(horseTailAngle, 0, 0, 1); // Rotate tail based on key press
    glTranslatef(-(x + 0.05f), -(y + 0.05f), 0);
    glBegin(GL_LINES);
    glVertex2f(x + 0.05f, y + 0.05f);
    glVertex2f(x + 0.1f, y + 0.1f);
    glEnd();
    glPopMatrix();
}

// Function to draw the sun
void drawSun(float x, float y) {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow for the sun
    int numSegments = 100;
    float radius = 0.1f;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.14159f * i / numSegments;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the scene
    drawHouse(-0.5f, -0.2f); // Draw house 1
    drawHouse(0.5f, -0.2f);  // Draw house 2
    drawHorse(horseX, -0.4f); // Draw horse
    drawSun(sunX, 0.8f);      // Draw the sun

    // Swap buffers to display the scene
    glutSwapBuffers();
}

// Update function to animate horse and boat movement
void update(int value) {
    if (horseMovingLeft) {
        horseX -= 0.01f; // Move horse to the left
        if (horseX < -1.0f) horseMovingLeft = 0;
    } else {
        horseX += 0.01f; // Move horse to the right
        if (horseX > 1.0f) horseMovingLeft = 1;
    }
    boatX += 0.01f; // Move the boat
    if (boatX > 1.0f) boatX = -1.0f;
    
    // Redisplay the scene
    glutPostRedisplay();
    
    // Call update function again after 16 milliseconds (~60 FPS)
    glutTimerFunc(16, update, 0);
}

// Keyboard function to handle keypresses
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'F':
            // Move horse from right to left
            horseMovingLeft = 1;
            break;
        case 'R':
            // Rotate horse tail
            horseTailAngle += 10.0f;
            break;
        case 'Q':
            // Rotate horse 180 degrees
            // Add logic to rotate horse
            break;
        case 'B':
            // Move boat from left to right
            boatX += 0.05f;
            break;
        case 'W':
            // Move boat paddle backward
            // Implement paddle movement
            break;
        case 'U':
            // Scale up flowers and fish
            // Implement scaling logic
            break;
        case 'S':
            // Scale down plants
            // Implement scaling logic
            break;
        case ' ':
            // Move the sun and scale down flower pot
            sunX -= 0.05f;
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Village Scene");
    
    // Set the display function and timer
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(16, update, 0);

    // Set up the 2D world
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Enter the main loop
    glutMainLoop();
    return 0;
}
