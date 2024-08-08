#include "OBJParser.h"

void OBJParser::OBJRead(const char* path, int id) {
    
    std::ifstream stream(path);
    if (!stream.good())
        std::cout << "file couldnt open";

    std::string line;
    char init[128];

    std::vector<glm::vec3> coords;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    std::vector<Vertex> verts;
    std::vector<unsigned int> faces;

    int vertIDUV = 0;

    std::getline(stream, line);
    while (!stream.eof())
    {
        std::vector<std::string> words;
        Words(line, words, ' ');
        if (words.size() > 0) {
            if (words[0] == "v") {
                glm::vec3 pos;
                pos.x = std::stof(words[1]);
                pos.y = std::stof(words[2]);
                pos.z = std::stof(words[3]);
                coords.push_back(pos);

            }
            if (words[0] == "vn") {
                glm::vec3 n;
                n.x = std::stof(words[1]);
                n.y = std::stof(words[2]);
                n.z = std::stof(words[3]);
                normals.push_back(n);
            }
            if (words[0] == "vt") {
                glm::vec2 uv;
                uv.x = std::stof(words[1]);
                uv.y = std::stof(words[2]);
                uvs.push_back(uv);
            }


            if (words[0] == "f") {
                // for TRIS
                if (words.size() == 4)
                {
                    std::vector<int> vertIDs;
                    for (int i = 1; i < 4; i++)
                    {
                        std::vector<std::string> values;
                        Words(words[i], values, '/');
                        unsigned int posID = std::stoi(values[0]) - 1;
                        unsigned int uvID = std::stoi(values[1]) - 1;
                        unsigned int normalID = std::stoi(values[2]) - 1;

                        glm::vec3 pos = coords[posID];
                        glm::vec2 uv = uvs[uvID];
                        glm::vec3 n = normals[normalID];

                        vertIDs.push_back(posID);
                        verts.push_back(Vertex(pos.x, pos.y, pos.z, uv.x, uv.y, n.x, n.y, n.z));
                    }
                    faces.push_back(verts.size() - 1);
                    faces.push_back(verts.size() - 2);
                    faces.push_back(verts.size() - 3);
                }
                //for QUADS
                if (words.size() == 5)
                {
                    std::vector<int> vertIDs;
                    for (int i = 1; i < 5; i++)
                    {
                        std::vector<std::string> values;
                        Words(words[i], values, '/');
                        unsigned int posID = std::stoi(values[0]) - 1;
                        unsigned int uvID = std::stoi(values[1]) - 1;
                        unsigned int normalID = std::stoi(values[2]) - 1;

                        glm::vec3 pos = coords[posID];
                        glm::vec2 uv = uvs[uvID];
                        glm::vec3 n = normals[normalID];

                        vertIDs.push_back(posID);
                        verts.push_back(Vertex(pos.x, pos.y, pos.z, uv.x, uv.y, n.x, n.y, n.z));
                    }
                    faces.push_back(verts.size() - 4);
                    faces.push_back(verts.size() - 3);
                    faces.push_back(verts.size() - 2);
                    faces.push_back(verts.size() - 4);
                    faces.push_back(verts.size() - 2);
                    faces.push_back(verts.size() - 1);
                }
            }
        }
        std::getline(stream, line);
    }

    std::shared_ptr<VertexData> mesh = VertexData::CreateVertexData(id);
    mesh->LoadVerts(&verts[0], verts.size());
    mesh->LoadFaces(&faces[0], faces.size());
    mesh->Setup();
}

void OBJParser::Words(std::string line, std::vector<std::string> &res, char separator, bool ignoreEmpty) {

    res.clear();
    int wordStart = 0;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == separator)
        {
            if (wordStart != i || !ignoreEmpty)
            {
                std::string word = line.substr(wordStart, i - wordStart);
                res.push_back(word);
                wordStart = i+1;
            }
        }
    }
    if (wordStart < line.size())
    {
        std::string word = line.substr(wordStart, line.size() - wordStart);
        res.push_back(word);
    }

}