#include <cmath>

glm::mat4 isometricProjection(float a, float w, float n, float f);

glm::mat4 dimetricProjection(float a, float w, float n, float f, float alpha);

glm::mat4 trimetricProjection(float a, float w, float n, float f, float alpha, float beta);

glm::mat4 parallelProjection(float a, float w, float n, float f);

void SetupProjectionMatrices(Assignment04 *A, float Ar) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S;

    float a = Ar; // aspect ratio
	float w = 10.0f; // half-width
    float n = -50.0f; // near plane
    float f = 50.0f; // far plane

	// Isometric projection
	S = isometricProjection(a, w, n, f);
	A->Matrix(1, S); // sets the matrix corresponding to piece 1

	// Dimetric
	S = dimetricProjection(a, w, n, f, 15.0f);
	A->Matrix(2, S); // sets the matrix corresponding to piece 2

	// Trimetric
	S = trimetricProjection(a, w, n, f, 15.0f, 15.0f);
	A->Matrix(3, S); // sets the matrix corresponding to piece 3

	// Cabinet
	S = glm::mat4(1);
	A->Matrix(4, S); // sets the matrix corresponding to piece 4

}

glm::mat4 isometricProjection(float a, float w, float n, float f) {
    /*
    float deg35 = 35.26 * M_PI / 180;
    float deg45 = -45.0f * M_PI / 180;

    return glm::mat4(1/w, 0, 0, 0, 0, -a/w, 0, 0, 0, 0, 1/(n-f), 0, 0, 0, n/(n-f), 1) *
    glm::mat4(1, 0, 0, 0, 0, cos(deg35), -sin(deg35), 0, 0, sin(deg35), cos(deg35), 0, 0, 0, 0, 1) *
    glm::mat4(cos(deg45), 0, -sin(deg45), 0, 0, 1, 0, 0, sin(deg45), 0, cos(deg45), 0, 0, 0, 0, 1);
    */

    return dimetricProjection(a, w, n, f, 35.26f);
}


glm::mat4 dimetricProjection(float a, float w, float n, float f, float alpha) {

    return trimetricProjection(a, w, n, f, alpha, -45.0f);
}

glm::mat4 trimetricProjection(float a, float w, float n, float f, float alpha, float beta) {

    return parallelProjection(a, w, n, f) *
           glm::rotate(glm::mat4(1), glm::radians(alpha), glm::vec3(1, 0, 0)) *
           glm::rotate(glm::mat4(1), glm::radians(beta), glm::vec3(0, 1, 0));
}


glm::mat4 parallelProjection(float a, float w, float n, float f) {
    return glm::mat4(1/w, 0, 0, 0, 0, -a/w, 0, 0, 0, 0, 1/(n-f), 0, 0, 0, n/(n-f), 1);
}