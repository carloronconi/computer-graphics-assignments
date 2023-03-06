

void SetupTriangles(Assignment01 *A) {
/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/

    // red upper body
    A->Triangle(-0.2, 0.1, 0.3, -0.4, 0.3, 0.6, 1, 0, 0);
    // blue lower body
    A->Triangle(-0.2, 0.1, -0.2, 0.9, 0.6, 0.9, 0.1, 0.1, 1);
    // yellow neck
    A->Triangle(0.3, -0.4, 0.3, 0.4, 0.7, 0, 0.9, 0.9, 0);
    // purple head (two triangles)
    A->Triangle(0.3, -0.4, 0.9, -0.4, 0.6, -0.1, 0.5, 0, 0.5);
    A->Triangle(0.3, -0.4, 0.9, -0.4, 0.6, -0.7, 0.5, 0, 0.5);
    // pink ear
    A->Triangle(0.3, -0.4, 0.3, -1, 0.6, -0.7, 0.9, 0.2, 0.9);
    // blue ear
    A->Triangle(0.9, -0.4, 0.9, -1, 0.6, -0.7, 0.1, 0.1, 1);
    // green tail
    A->Triangle(-0.2, 0.9, -0.5, 0.9, -0.7, 0.6, 0, 0.9, 0);
    A->Triangle(-0.2, 0.9, -0.4, 0.6, -0.7, 0.6, 0, 0.9, 0);
}
