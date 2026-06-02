## Day 2 (grid generation)

The debug grid was generated using GL_LINES before terrain rendering was added.

```
std::vector<float> makeGridVertices(int halfSize) {
    // Generate line segments on the XZ plane. Each grid line contributes two vertices.
    //
    std::vector<float> vertices;

    for (int i = -halfSize; i <= halfSize; ++i) {
        // Line parallel to Z axis
        vertices.push_back(static_cast<float>(i));
        vertices.push_back(0.0f);
        vertices.push_back(static_cast<float>(-halfSize));

        vertices.push_back(static_cast<float>(i));
        vertices.push_back(0.0f);
        vertices.push_back(static_cast<float>(halfSize));

        // Line parallel to X axis
        vertices.push_back(static_cast<float>(-halfSize));
        vertices.push_back(0.0f);
        vertices.push_back(static_cast<float>(i));

        vertices.push_back(static_cast<float>(halfSize));
        vertices.push_back(0.0f);
        vertices.push_back(static_cast<float>(i));
    }

    return vertices;
}
```
