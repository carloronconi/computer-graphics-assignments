/**
 * Adapted from the sol of the previous assignment.
 * Because the box is centered in the origin, we know that the coordinate of each point will either be
 * + or - a value (eg horizontal = 1.16 -> all points either have z = +1.16 or z = -1.16)
 */
void createRectangleFace(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx, glm::vec3 norm,
                         glm::vec3 boxDimensions/*, glm::vec2 lowUV*/, glm::vec2 pixels, float scale) {

    int fixedIndex;
    float fixedValue;
    for (int i : {0, 1, 2}) {
        if (norm[i] != 0){
            fixedIndex = i;
            fixedValue = norm[i] * boxDimensions[i] / scale;
        }
    }

    std::vector<int> variableIndices = {0, 1, 2};
    variableIndices.erase(variableIndices.begin() + fixedIndex);

    int firstVIdx = -1;
    for (float i : {1.0f, -1.0f}) {
        for (float j : {1.0f, -1.0f}) {
            glm::vec3 pos = {};
            pos[fixedIndex] = fixedValue;
            pos[variableIndices[0]] = i * boxDimensions[variableIndices[0]] / scale;
            pos[variableIndices[1]] = j * boxDimensions[variableIndices[1]] / scale;

            if (firstVIdx == -1) firstVIdx = (int)vDef.size();

            /**
             * attempt to automatically compute UV
             */
            //uv coords of the lowest corner of the rectangle are passed, others are deducted from the dimensions of the box
            //float u = (i > 0) ? (lowUV.x + boxDimensions[variableIndices[1]]) / pixels.x : lowUV.x / pixels.x;
            //float v = (j > 0) ? (lowUV.y + boxDimensions[variableIndices[0]]) / pixels.y : lowUV.y / pixels.y;
            vDef.push_back({pos, norm, /*{u, v}*/{}});
        }
    }

    vIdx.push_back(firstVIdx); vIdx.push_back(firstVIdx + 1); vIdx.push_back(firstVIdx + 2);
    vIdx.push_back(firstVIdx + 1); vIdx.push_back(firstVIdx + 2); vIdx.push_back(firstVIdx + 3);
}

void Assignment15::createBoxMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a box centered in the origin, with proportions respecting the texture.

	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	//vDef.push_back({{0,0,0}, {0,0,1}, {95.0 / 1024.0, 95.0 / 512.0}});	// vertex 0 - Position, Normal and uv

    /* calculations for box coordinates and uv (computed from the box texture pixels measurements):
     * horizontal = 349 -> 349/300 = 1.16 (z)
     * vertical = 324 -> 324/300 = 1.08 (y)
     * short = 95 -> 95/300 = 0.32 (x)
     *
     * other coordinates written on the image TBs_20140623_1_02-annotated.png
     */
    float scale = 300.0;
    glm::vec3 boxDim = {95.0, 324.0, 349.0};
    glm::vec2 pixels = {1024.0, 512.0};

    createRectangleFace(vDef, vIdx, {1.0, 0.0, 0.0}, boxDim, pixels, scale);
    vDef[0].UV = {95.0 / 1024.0, 95.0 / 512.0};
    vDef[1].UV = {444.0 / 1024.0, 95.0 / 512.0};
    vDef[2].UV = {95.0 / 1024.0, 419.0 / 512.0};
    vDef[3].UV = {444.0 / 1024.0, 419.0 / 512.0};
    createRectangleFace(vDef, vIdx, {-1.0, 0.0, 0.0}, boxDim, pixels, scale);
    vDef[4].UV = {893.0 / 1024.0, 95.0 / 512.0};
    vDef[5].UV = {541.0 / 1024.0, 95.0 / 512.0};
    vDef[6].UV = {893.0 / 1024.0, 419.0 / 512.0};
    vDef[7].UV = {541.0 / 1024.0, 419.0 / 512.0};
    createRectangleFace(vDef, vIdx, {0.0, 1.0, 0.0}, boxDim, pixels, scale);
    vDef[8].UV = {95.0 / 1024.0, 95.0 / 512.0};
    vDef[9].UV = {444.0 / 1024.0, 95.0 / 512.0};
    vDef[10].UV = {95.0 / 1024.0, 0.0 / 512.0};
    vDef[11].UV = {444.0 / 1024.0, 0.0 / 512.0};
    createRectangleFace(vDef, vIdx, {0.0, -1.0, 0.0}, boxDim, pixels, scale);
    vDef[12].UV = {444.0 / 1024.0, 419.0 / 512.0};
    vDef[13].UV = {95.0 / 1024.0, 419.0 / 512.0};
    vDef[14].UV = {444.0 / 1024.0, 512.0 / 512.0};
    vDef[15].UV = {95.0 / 1024.0, 512.0 / 512.0};
    createRectangleFace(vDef, vIdx, {0.0, 0.0, 1.0}, boxDim, pixels, scale);
    vDef[16].UV = {95.0 / 1024.0, 95.0 / 512.0};
    vDef[17].UV = {95.0 / 1024.0, 419.0 / 512.0};
    vDef[18].UV = {0.0 / 1024.0, 95.0 / 512.0};
    vDef[19].UV = {0.0 / 1024.0, 419.0 / 512.0};
    createRectangleFace(vDef, vIdx, {0.0, 0.0, -1.0}, boxDim, pixels, scale);
    vDef[20].UV = {444.0 / 1024.0, 95.0 / 512.0};
    vDef[21].UV = {444.0 / 1024.0, 419.0 / 512.0};
    vDef[22].UV = {541.0 / 1024.0, 95.0 / 512.0};
    vDef[23].UV = {541.0 / 1024.0, 419.0 / 512.0};

}

#define M_PI 3.141595f
/**
 * creates a disc of the unitary-radius sphere of n vertices at the specified height for which the radius is computed based on the height
 * @param vDef vertices vector
 * @param h height
 * @param n number of points in the disc, must be odd so that using n - 1 (even) the [n/2] point has u = 1
 */
void createVertexDisc(std::vector<Vertex> &vDef, float h, int nDisc) {
    float r = sqrt(1.0 - pow(h, 2.0)); // compute the radius of the disc using Pythagoras' theorem
    int n = nDisc - 1;

    for (int i = 0; i < n; ++i) {
        auto x = (float) r * cos(2 * M_PI * ((float)i) / n);
        auto z = (float) r * sin(2 * M_PI * ((float)i) / n);
        glm::vec3 pos = {x, h, z};
        glm::vec3 norm = glm::normalize(pos); // the norm is the same as the pos for an origin-centered sphere!
        auto u = (float) 1.0f - (0.5 + ( (atan2(z, x)) / (2 * M_PI) ));
        auto v = (float) 1.0f - (0.5 + ( (asin(h)) / M_PI ));

        if (i == n / 2) { // overlap the point with another one with same pos but 0 coord instead of 0.999 to fix wrapping
            vDef.push_back({pos, norm, {0.0, v}});
            std::cout << 0.0 << " " << v << "\n";
        }

        vDef.push_back({pos, norm, {u, v}});
        std::cout << u << " " << v << "\n";
    }
}

void Assignment15::createSphereMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a sphere of radius 1, centered in the origin, on which the Mars texture is applied seamless.
    int nDisc = 101;
    int nHeight = 300;

    for (int i = 0; i < nHeight; ++i) { // for each complete horizontal slice (including North and South Pole)
        // createVertexDisc with nHeight different heights from +1 to -1: 1 - (2i)/nH
        createVertexDisc(vDef, 1.0f - (2.0f * (float) i)/((float) nHeight), nDisc);
    }

    //connect all discs
    for (int i = 0; i < nHeight; ++i) {
        int upperLeft = i * nDisc;
        int lowerLeft = (i + 1) * nDisc;
        for (int j = 0; j < nDisc - 1; ++j) {
            vIdx.push_back(upperLeft + j); vIdx.push_back(upperLeft + j + 1); vIdx.push_back(lowerLeft + j);
            vIdx.push_back(upperLeft + j + 1); vIdx.push_back(lowerLeft + j); vIdx.push_back(lowerLeft + j + 1);
        }
        vIdx.push_back(upperLeft); vIdx.push_back(upperLeft + nDisc - 1); vIdx.push_back(lowerLeft + nDisc - 1);
        vIdx.push_back(upperLeft); vIdx.push_back(lowerLeft); vIdx.push_back(lowerLeft + nDisc - 1);
    }
}

