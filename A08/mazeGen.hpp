void createCube(int i, int j, std::vector<float>& vPos, std::vector<int>& vIdx);
void createVertex(int i, int j, int k, std::vector<float>& vPos);
void createTriangle(int i, int j, int k, std::vector<int>& vIdx);

void Assignment08::createMazeMesh(int row, int col, char **maze) {
    // The procedure gets in input the number of rows <row> of the maze, and the number of columns <col>
    // Element <maze[r][c]>, with 0 <= r <= row-1 and 0 <= c <= col-1 contains:
    //		Symbol ' ' if there is an empty space
    //		Symbol '#' if there is a wall
    //
    // Example: The following piece of code executes the instruction in the ... section
    //          if there is a wall in position r=5, c=7
    //
    // int r, c;
    // r = 5; c = 7;
    // if(maze[r][c] == '#') {
    //		...
    // }
    //
    // The example below creates a square, with four vertices and two triangles.
    // It must be deleted and replaced with your code creating the mesh of the maze.
    /*
    // Fill array vPos with the positions of the vertices of the mesh
    vPos.push_back(0.0); vPos.push_back(0.0); vPos.push_back(0.0);	// vertex 0
    vPos.push_back(1.0); vPos.push_back(0.0); vPos.push_back(0.0);	// vertex 1
    vPos.push_back(0.0); vPos.push_back(1.0); vPos.push_back(0.0);	// vertex 2
    vPos.push_back(1.0); vPos.push_back(1.0); vPos.push_back(0.0);	// vertex 3

    // Fill the array vIdx with the indices of the vertices of the triangles
    vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	// First triangle
    vIdx.push_back(1); vIdx.push_back(2); vIdx.push_back(3);	// Second triangle
    */
    createCube(0, 0, vPos, vIdx);
}

void createCube(int i, int j, std::vector<float>& vPos, std::vector<int>& vIdx) {
    // create 8 vertices of a cube
    createVertex(i, j, 0, vPos);
    createVertex(i, j, 1, vPos);
    createVertex(i + 1, j, 0, vPos);
    createVertex(i + 1, j, 1, vPos);
    createVertex(i, j + 1, 0, vPos);
    createVertex(i, j + 1, 1, vPos);
    createVertex(i + 1, j + 1, 0, vPos);
    createVertex(i + 1, j + 1, 1, vPos);
    // fill triangles
    createTriangle(0, 1, 2, vIdx);
    createTriangle(1, 2, 3, vIdx);
    createTriangle(4, 5, 6, vIdx);
    createTriangle(5, 6, 7, vIdx);

    createTriangle(0, 4, 6, vIdx);
    createTriangle(0, 2, 6, vIdx);

    createTriangle(0, 1, 4, vIdx);
    createTriangle(1, 4, 5, vIdx);

    createTriangle(2, 6, 7, vIdx);
    createTriangle(2, 3, 7, vIdx);

    createTriangle(1, 5, 7, vIdx);
    createTriangle(1, 3, 7, vIdx);
}

void createVertex(int i, int j, int k, std::vector<float>& vPos) {
    vPos.push_back(i * 1.0); vPos.push_back(j * 1.0); vPos.push_back(k * 1.0);
}

void createTriangle(int i, int j, int k, std::vector<int>& vIdx) {
    vIdx.push_back(i); vIdx.push_back(j); vIdx.push_back(k);
}




