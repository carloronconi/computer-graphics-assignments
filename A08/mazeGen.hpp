void createCube(int i, int j, int& vCounter, std::vector<float>& vPos, std::vector<int>& vIdx);
void createSquare(int i, int j, int& vCounter, std::vector<float>& vPos, std::vector<int>& vIdx);
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

    static int vCounter = 0; // static counter to keep track of highest value of vIdx so far
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            if (maze[r][c] == '#') createCube(r, c, vCounter, vPos, vIdx);
            else if (maze[r][c] == ' ') createSquare(r, c, vCounter, vPos, vIdx);
        }
    }

}

void createCube(int i, int j, int& vCounter, std::vector<float>& vPos, std::vector<int>& vIdx) {
    // create 8 vertices of a cube
    createVertex(i, j, 0, vPos);
    createVertex(i, j, 1, vPos);
    createVertex(i + 1, j, 0, vPos);
    createVertex(i + 1, j, 1, vPos);
    createVertex(i, j + 1, 0, vPos);
    createVertex(i, j + 1, 1, vPos);
    createVertex(i + 1, j + 1, 0, vPos);
    createVertex(i + 1, j + 1, 1, vPos);

    // fill triangles following screenshot in project files
    createTriangle(vCounter + 0, vCounter + 1, vCounter + 2, vIdx);
    createTriangle(vCounter + 1, vCounter + 2, vCounter + 3, vIdx);
    createTriangle(vCounter + 4, vCounter + 5, vCounter + 6, vIdx);
    createTriangle(vCounter + 5, vCounter + 6, vCounter + 7, vIdx);

    createTriangle(vCounter + 0, vCounter + 4, vCounter + 6, vIdx);
    createTriangle(vCounter + 0, vCounter + 2, vCounter + 6, vIdx);

    createTriangle(vCounter + 0, vCounter + 1, vCounter + 4, vIdx);
    createTriangle(vCounter + 1, vCounter + 4, vCounter + 5, vIdx);

    createTriangle(vCounter + 2, vCounter + 6, vCounter + 7, vIdx);
    createTriangle(vCounter + 2, vCounter + 3, vCounter + 7, vIdx);

    createTriangle(vCounter + 1, vCounter + 5, vCounter + 7, vIdx);
    createTriangle(vCounter + 1, vCounter + 3, vCounter + 7, vIdx);

    vCounter += 8;
}

void createSquare(int i, int j, int& vCounter, std::vector<float>& vPos, std::vector<int>& vIdx) {
    // similar to cube but with fewer vertices
    createVertex(i, j, 0, vPos);
    createVertex(i + 1, j, 0, vPos);
    createVertex(i, j + 1, 0, vPos);
    createVertex(i + 1, j + 1, 0, vPos);

    createTriangle(vCounter + 0, vCounter + 1, vCounter + 2, vIdx);
    createTriangle(vCounter + 1, vCounter + 2, vCounter + 3, vIdx);

    vCounter += 4;
}

void createVertex(int i, int j, int k, std::vector<float>& vPos) {
    // indexes are switched to make the lay the maze horizontal
    // and shifted to spawn camera above and centered
    vPos.push_back((j - 5) * 1.0); vPos.push_back((k - 5) * 1.0); vPos.push_back((i - 10) * 1.0);
}

void createTriangle(int i, int j, int k, std::vector<int>& vIdx) {
    vIdx.push_back(i); vIdx.push_back(j); vIdx.push_back(k);
}




