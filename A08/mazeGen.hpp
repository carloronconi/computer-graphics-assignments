using namespace glm;
using namespace std;

void createCube(int i, int j, std::vector<float>& vPos, std::vector<int>& vIdx);
void createSquare(int i, int j, std::vector<float>& vPos, std::vector<int>& vIdx);
int createVertex(int i, int j, int k, std::vector<float>& vPos);
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

    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            if (maze[r][c] == '#') createCube(r, c, vPos, vIdx);
            else if (maze[r][c] == ' ') createSquare(r, c, vPos, vIdx);
        }
    }

}

void createCube(int i, int j, std::vector<float>& vPos, std::vector<int>& vIdx) {
    // create 8 vertices of a cube
    int v0 = createVertex(i, j, 0, vPos);
    int v1 = createVertex(i, j, 1, vPos);
    int v2 = createVertex(i + 1, j, 0, vPos);
    int v3 = createVertex(i + 1, j, 1, vPos);
    int v4 = createVertex(i, j + 1, 0, vPos);
    int v5 = createVertex(i, j + 1, 1, vPos);
    int v6 = createVertex(i + 1, j + 1, 0, vPos);
    int v7 = createVertex(i + 1, j + 1, 1, vPos);

    // fill triangles following screenshot in project files
    createTriangle(v0, v1, v2, vIdx);
    createTriangle(v1, v2, v3, vIdx);
    createTriangle(v4, v5, v6, vIdx);
    createTriangle(v5, v6, v7, vIdx);

    createTriangle(v0, v4, v6, vIdx);
    createTriangle(v0, v2, v6, vIdx);

    createTriangle(v0, v1, v4, vIdx);
    createTriangle(v1, v4, v5, vIdx);

    createTriangle(v2, v6, v7, vIdx);
    createTriangle(v2, v3, v7, vIdx);

    createTriangle(v1, v5, v7, vIdx);
    createTriangle(v1, v3, v7, vIdx);
}

void createSquare(int i, int j, std::vector<float>& vPos, std::vector<int>& vIdx) {
    // similar to cube but with fewer vertices
    int v0 = createVertex(i, j, 0, vPos);
    int v1 = createVertex(i + 1, j, 0, vPos);
    int v2 = createVertex(i, j + 1, 0, vPos);
    int v3 = createVertex(i + 1, j + 1, 0, vPos);

    createTriangle(v0, v1, v2, vIdx);
    createTriangle(v1, v2, v3, vIdx);
}

int createVertex(int i, int j, int k, std::vector<float>& vPos) {
    static map<string , int> vertices; // stores existing vertices with position as key (string 1-0-0) and index as value
    // to optimise the amount of vertices created by avoiding any duplication in the same coordinates

    string key = to_string(i) + "-" + to_string(j) + "-" + to_string(k);
    if (vertices.find(key) == vertices.end()) { // if vertex in that position didn't already exist
        vertices[key] = vertices.size(); // add it to map
        // and create vertex
        // (indexes are switched to make the lay the maze horizontal
        // and shifted to spawn camera above and centered)
        vPos.push_back((j - 5) * 1.0); vPos.push_back((k - 5) * 1.0); vPos.push_back((i - 10) * 1.0);
    }
    return vertices[key];
}

void createTriangle(int i, int j, int k, std::vector<int>& vIdx) {
    vIdx.push_back(i); vIdx.push_back(j); vIdx.push_back(k);
}




