

void SetupMatrices(Assignment03 *A) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S;


	/** To solve the puzzle: scale 2x proportionally, centered in (2,0,-3) **/
	S = glm::mat4(1);

    // Transform matrices:
    glm::mat4 T1 = glm::translate(S, glm::vec3(-2, 0, 3)); // translate matrix to origin
    glm::mat4 T2 = glm::scale(S, glm::vec3(2)); // scale matrix 2x
    glm::mat4 T3 = glm::translate(S, glm::vec3(2, 0, -3)); // translate matrix to original position

    glm::mat4 R = T3 * T2 * T1 * S; // resulting matrix using matrix-on-the-left notation

	A->Matrix(1, R); // sets the matrix corresponding to piece 1

    /** To solve the puzzle: scale 2x on an axis oriented 45 degrees between the x and z axis and passing through point (1,0,0) **/
	S = glm::mat4(1);

    // translate to origin and rotate 45 degrees along y axis (planar rotating on xz)
    T1 = glm::rotate(S, glm::radians(45.0f), glm::vec3(0, 1, 0)) * glm::translate(S, glm::vec3(-1, 0, 0));
    // scale 3x on z (as now the piece has been rotated to align scale axis with z)
    T2 = glm::scale(S, glm::vec3(1, 1, 3));
    // do inverse operation of T1
    T3 = glm::translate(S, glm::vec3(1, 0, 0)) * glm::rotate(S, glm::radians(-45.0f), glm::vec3(0, 1, 0));

	A->Matrix(2, T3 * T2 * T1 * S); // sets the matrix corresponding to piece 2

    /** To solve the puzzle: find it yourself! Hint: compose a rotation around an arbitrary point with a translation **/
    // - translate z-3 and x-2 to origin
    // - rotate along y by 45 degrees
    // - translate to new position x*1 and z*2
	S = glm::mat4(1);

    T1 = glm::rotate(S, glm::radians(45.0f), glm::vec3(0, 1, 0)) * glm::translate(S, glm::vec3(-2, 0, -3));
    T2 = glm::translate(S, glm::vec3(1, 0, 2));

	A->Matrix(3, T2 * T1 * S); // sets the matrix corresponding to piece 3

    /** To solve the puzzle: rotate 60 degree around the y axis, centered in (-1,0,-2) **/
	S = glm::mat4(1);

    T1 = glm::translate(S, glm::vec3(1, 0, 2));
    T2 = glm::rotate(S, glm::radians(60.0f), glm::vec3(0, 1, 0));

    A->Matrix(4, glm::inverse(T1) * T2 * T1* S); // sets the matrix corresponding to piece 4

    /** To solve the puzzle: rotate -90 degree around an arbitrary axis passing in (-1,0,0).
     * The x axis can be aligned to this arbitrary direction with a rotation of -45 around the y axis.**/
	S = glm::mat4(1);
	A->Matrix(5, S); // sets the matrix corresponding to piece 5

    /** To solve the puzzle: find it yourself! Hint: compose a non-proportional scaling that halves the object along one of the main axes,
     * centered in an arbitrary point, with a translation **/
	S = glm::mat4(1);
	A->Matrix(6, S); // sets the matrix corresponding to piece 6

}
