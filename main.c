#include "./utils/array.h"
#include "./utils/vector2.h"
#include "./utils/vector3.h"
#include "./utils/vector4.h"

typedef ARRAY(Vector2) Vector2_Array;
typedef ARRAY(Vector3) Vector3_Array;

void print_array(const Vector2_Array *va)
{
    array_analysis(va);
    for (uint32_t i = 0; i < va->count; ++i) {
        printf("index %u: ", i); v2_print(&va->items[i]);
    }
    printf("\n");
}

int main(void)
{
    Vector2_Array va = {NULL, 0, 0};

    uint32_t c = 15;
    for (uint32_t i = 0; i <= c; ++i) {
        Vector2 vec = v2_init(2.0*i, (float) i);
        array_append(&va, vec);
    }
    print_array(&va);

    printf("Attempting pop.\n");
    for (uint32_t i = va.count; i > 5; --i) {
        array_pop(&va);
    }
    print_array(&va);

    array_delete(&va);
    return 0;
}
