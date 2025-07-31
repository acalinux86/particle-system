#include "./system.h"

/*
Current Range => 0...1 => A...B
Target Range  => 0...255 => C...D
*/
static float convert_range(float value, float A, float B, float C, float D)
{
    float target = ((value - A) * (D - C) / (B - A)) + C;
    return floorf(target);
}

Color gl_to_color(Color color)
{
    return (Color) {
        .r = (unsigned char) convert_range(color.r, 0, 1, 0, 255),
        .g = (unsigned char) convert_range(color.g, 0, 1, 0, 255),
        .b = (unsigned char) convert_range(color.b, 0, 1, 0, 255),
        .a = (unsigned char) convert_range(color.a, 0, 1, 0, 255),
    };
}

Color color_to_gl(Color color)
{
    return (Color) {
        .r = convert_range(color.r, 0, 255, 0, 1),
        .g = convert_range(color.g, 0, 255, 0, 1),
        .b = convert_range(color.b, 0, 255, 0, 1),
        .a = convert_range(color.a, 0, 255, 0, 1),
    };
}

void color_print(Color color, const char *name)
{
    Log(INFO, "%s: [%d, %d, %d, %d]\n",
    name, color.r, color.g, color.b, color.a
    );
}
