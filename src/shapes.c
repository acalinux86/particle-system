#include "./system.h"

void DrawTriangle(Mesh_Data *mesh_data, Vector3 v1, Vector3 v2, Vector3 v3, Color color)
{
    uint32_t base = mesh_data->va.count;
    array_append(&mesh_data->va, ((Vertex){v1, color_to_gl(color)}));
    array_append(&mesh_data->va, ((Vertex){v2, color_to_gl(color)}));
    array_append(&mesh_data->va, ((Vertex){v3, color_to_gl(color)}));

    uint32_t tri_indices[3] = {base, base+1, base+2};
    for (uint32_t i = 0; i < 3; ++i)
    {
        array_append(&mesh_data->indices, tri_indices[i]);
    }
}

void DrawLines(Mesh_Data *mesh_data, Vector3 v1, Vector3 v2, Color color)
{
    uint32_t base_index = mesh_data->va.count;
    array_append(&mesh_data->va, ((Vertex){v1, color_to_gl(color)}));
    array_append(&mesh_data->va, ((Vertex){v2, color_to_gl(color)}));

    uint32_t line_indices[2] = {base_index, base_index+1};
    for (uint32_t i = 0; i < 2; ++i)
    {
        array_append(&mesh_data->indices, line_indices[i]);
    }
}

void DrawRectangle(Mesh_Data *mesh_data, Vector3 position, Vector3 size, Color color)
{
    // Calculate corner positions
    Vector3 half_size = v3_scale(size, 0.5);
    float x = half_size.x;
    float y = half_size.y;
    Vector3 corners[4] = {
        v3_add(position, v3_init(-x,  -y, 0.0f)), // botom-left
        v3_add(position, v3_init(-x,   y, 0.0f)), // top-left
        v3_add(position, v3_init( x,   y, 0.0f)), // top-right
        v3_add(position, v3_init( x,  -y, 0.0f)), // bottom-right
    };

    uint32_t base_index = mesh_data->va.count;
    for (uint32_t i = 0; i < 4; ++i)
    {
        array_append(&mesh_data->va, ((Vertex){corners[i], color_to_gl(color)}));
    }

    uint32_t quad_indices[6] = {
        base_index, base_index+1, base_index+2,
        base_index, base_index+2, base_index+3
    };
    for (uint32_t i = 0; i < 6; ++i)
    {
        array_append(&mesh_data->indices, quad_indices[i]);
    }
}
