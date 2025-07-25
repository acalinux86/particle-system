#include "./system.h"

void DrawTriangle(Renderer *renderer, Vector3 v1, Vector3 v2, Vector3 v3, Vector4 color)
{
    if (renderer->va.count + 3 > renderer->va.capacity ||
        renderer->current_mode != GL_TRIANGLES) {
        Flush(renderer);
        renderer->current_mode = GL_TRIANGLES;
    }
    uint32_t base = renderer->va.count;
    array_append(&renderer->va, ((Vertex){v1, color}));
    array_append(&renderer->va, ((Vertex){v2, color}));
    array_append(&renderer->va, ((Vertex){v3, color}));

    uint32_t tri_indices[3] = {base, base+1, base+2};
    for (uint32_t i = 0; i < 3; ++i)
    {
        array_append(&renderer->indices, tri_indices[i]);
    }
}

void DrawLines(Renderer *renderer, Vector3 v1, Vector3 v2, Vector4 color)
{
    if (renderer->va.count + 2 > renderer->va.capacity ||
        renderer->current_mode != GL_LINES) {
        Flush(renderer);
        renderer->current_mode = GL_LINES;
    }

    uint32_t base_index = renderer->va.count;
    array_append(&renderer->va, ((Vertex){v1, color}));
    array_append(&renderer->va, ((Vertex){v2, color}));
    
    uint32_t line_indices[2] = {base_index, base_index+1};
    for (uint32_t i = 0; i < 2; ++i)
    {
        array_append(&renderer->indices, line_indices[i]);
    }
}

void DrawRectangle(Renderer *renderer, Vector3 size, Vector3 position, Vector4 color)
{
    if (renderer->indices.count + 6 > renderer->indices.capacity ||
        renderer->va.count + 4 > renderer->va.capacity ||
        renderer->current_mode != GL_TRIANGLES) {
        Flush(renderer);
        renderer->current_mode = GL_TRIANGLES;
    }

    // Calculate corner positions
    Vector3 half_size = v3_scale(size, 0.5);
    Vector3 corners[4] = {
        v3_add(position, v3_init(-half_size.x, -half_size.y, 0.0f)), // botom-left
        v3_add(position, v3_init(-half_size.x,  half_size.y, 0.0f)), // top-left
        v3_add(position, v3_init(half_size.x,   half_size.y, 0.0f)), // top-right
        v3_add(position, v3_init(half_size.x,  -half_size.y, 0.0f)), // bottom-right
    };

    uint32_t base_index = renderer->indices.count;
    for (uint32_t i = 0; i < 4; ++i)
    {
        array_append(&renderer->va, ((Vertex){corners[i], color}));
    }

    uint32_t quad_indices[6] = {
        base_index, base_index+1, base_index+2,
        base_index, base_index+2, base_index+3
    };
    for (uint32_t i = 0; i < 6; ++i)
    {
        array_append(&renderer->indices, quad_indices[i]);
    }
}
