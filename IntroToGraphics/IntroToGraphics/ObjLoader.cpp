#include "ObjLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

Mesh* ObjLoader::Load(const char* filename)
{
    Mesh* mesh = new Mesh();

    std::ifstream inFile(filename);
    std::string line;

    while (std::getline(inFile, line))
    {
        if (line.substr(0, 2) == "f ")
        {
			mesh->numVertices += 3; // each face has 3 vertices		
        }
    }

    inFile.close();
    mesh->vertices = new Vertex[mesh->numVertices];

    std::vector<Vector3> positions;
    std::vector<Vector2> texCoordinates;
    std::vector<Vector3> normals;
	int vertexIndex = 0;

    // Pass 2 - read the data
	inFile.open(filename);

    while (std::getline(inFile, line))
    {
		// if the line starts with v, it's a vertex position

        if (line.substr(0, 2) == "v ")
        {
            Vector3 pos;
            sscanf_s(line.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
            positions.push_back(pos);
        }

		// if the line starts with vn, it's a vertex normal
        else if (line.substr(0, 3) == "vt ")
        {
            Vector2 texCoords;
            sscanf_s(line.c_str(), "vt %f %f", &texCoords.x, &texCoords.y);
            texCoordinates.push_back(texCoords);
        }

		// if the line starts with vt, it's a vertex texture coordinate
        else if (line.substr(0, 3) == "vn ")
        {
            Vector3 norms;
            sscanf_s(line.c_str(), "vn %f %f %f", &norms.x, &norms.y, &norms.z);
            normals.push_back(norms);
        }

		// if the line starts with f, it's a face
        else if (line.substr(0, 2) == "f ")
        {
            int positionIndex[3], texCoordIndex[3], normalIndex[3];

            if (line.find('/') == std::string::npos)
            {
                sscanf_s(line.c_str(), "f %d %d %d", &positionIndex[0], &positionIndex[1], &positionIndex[2]);
                for (int i = 0; i < 3; i++)
                {
                    mesh->vertices[vertexIndex].x = positions[positionIndex[i] - 1].x;
                    mesh->vertices[vertexIndex].y = positions[positionIndex[i] - 1].y;
                    mesh->vertices[vertexIndex].z = positions[positionIndex[i] - 1].z;
                    vertexIndex++;
                }
                continue;
			}
            sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &positionIndex[0], &texCoordIndex[0], &normalIndex[0],
                &positionIndex[1], &texCoordIndex[1], &normalIndex[1],
                &positionIndex[2], &texCoordIndex[2], &normalIndex[2]);

            for (int i = 0; i < 3; i++)
            {
                mesh->vertices[vertexIndex].x = positions[positionIndex[i] - 1].x;
                mesh->vertices[vertexIndex].y = positions[positionIndex[i] - 1].y;
                mesh->vertices[vertexIndex].z = positions[positionIndex[i] - 1].z;

                if (texCoordinates.size() > 0)
                {
                    mesh->vertices[vertexIndex].u = texCoordinates[texCoordIndex[i] - 1].x;
                    mesh->vertices[vertexIndex].v = texCoordinates[texCoordIndex[i] - 1].y;
                }

                if (normals.size() > 0)
                {
                    mesh->vertices[vertexIndex].nx = normals[normalIndex[i] - 1].x;
                    mesh->vertices[vertexIndex].ny = normals[normalIndex[i] - 1].y;
                    mesh->vertices[vertexIndex].nz = normals[normalIndex[i] - 1].z;
                }

                vertexIndex++;
            }
        }
    }

    return mesh;
}