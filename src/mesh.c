#include "./system.h"

void Mesh_Create(Static_Mesh *mesh, Vertices *va, Indices *indices, GLenum draw_mode)
{
    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);

    glGenBuffers(1, &mesh->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, va->count*sizeof(va->items[0]), va->items, GL_STATIC_DRAW);

    glGenBuffers(1, &mesh->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->count*sizeof(indices->items[0]), indices->items, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(va->items[0]), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(va->items[0]), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    mesh->draw_mode = draw_mode;
    mesh->indices_count = indices->count;
}

void Mesh_Draw(const Static_Mesh *mesh)
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(mesh->draw_mode, mesh->indices_count, GL_UNSIGNED_INT, (void*)0);
}

void Mesh_Update(Static_Mesh *mesh, Mesh_Data *mesh_data)
{
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh_data->va.count*sizeof(mesh_data->va.items[0]), mesh_data->va.items, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_data->indices.count*sizeof(mesh_data->indices.items[0]), mesh_data->indices.items, GL_STATIC_DRAW);
    mesh->indices_count = mesh_data->indices.count;
}

void GenerateGrid(Mesh_Data *mesh_data, Grid *grid)
{
    mesh_data->va.count = 0;
    mesh_data->indices.count = 0;

    for (uint32_t row = 0; row < grid->rows; ++row)
    {
        for (uint32_t col = 0; col < grid->cols; ++col)
        {
            float x = col * grid->cell_size;
            float y = row * grid->cell_size;

            // Center of the cell in pixel coordinates
            float center_x = x + grid->cell_size / 2.0f;
            float center_y = y + grid->cell_size / 2.0f;

            // Normalize row and col to range [0, 1]
            float u = (float)col / (float)(grid->cols - 1);
            float v = (float)row / (float)(grid->rows - 1);

            // Simple HSV to RGB-like mapping (wraps across hue)
            float r = fabsf(sinf(u * 3.14159f));
            float g = fabsf(sinf((u + 0.33f) * 3.14159f));
            float b = fabsf(sinf((u + 0.66f) * 3.14159f));

            Color cell_color = (Color){
                (uint8_t)(r * 255),
                (uint8_t)(g * 255),
                (uint8_t)(b * 255),
                255
            };

            Vector3 position = v3_init(center_x, center_y, 0.0f);
            Vector3 size = v3_init(grid->cell_size, grid->cell_size, 0.0f);

            DrawRectangle(mesh_data, position, size, cell_color);
        }
    }
}

void Render_Draw_Mesh(Renderer *renderer, Static_Mesh *mesh)
{
    glUseProgram(renderer->ProgramID);
    GLint screen_size_loc = glGetUniformLocation(renderer->ProgramID, "screenSize");
    glUniform2f(screen_size_loc, renderer->window_width, renderer->window_height);
    Mesh_Draw(mesh);
}

void Mesh_Destroy(Static_Mesh *mesh)
{
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteVertexArrays(1, &mesh->VAO);
}
