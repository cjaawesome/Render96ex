#include <stdio.h>
#include "types.h"

struct unifont_glyph{
    int height, width, visible_width, loaded_from_png;
    u32 codepoint;
    char *bitmap;
    struct unifont_glyph *next;
};

int add_glyph(FILE *font_file,u32 codepoint);
int add_glyph_using_loaded_font(u32 codepoint);
char *read_hex_from_file(FILE *font_file, u32 codepoint, int start_from_begining_of_file);
struct unifont_glyph *hex_string_to_unifont_glyph(char *hex_input);
int add_glyph_to_list_from_hex(struct unifont_glyph **unifont_glyph_head_ptr, u32 codepoint, char *buffer);
struct unifont_glyph *delete_glyph_from_list(struct unifont_glyph *glyph_to_delete);
int batch_add_glyphs(FILE *font_file, u32 codepoint_array[], u32 size);
char *get_bitmap(u32 codepoint);
struct unifont_glyph *get_unifont_glyph(u32 codepoint);
void preload_codepoints();
int get_visible_width_from_bitmap(char *bitmap,  int size_of_bitmap,  int width);
int get_visible_width_from_main_png(u8 *RGBAbuffer);
u8 *RGBA_from_unifont(u8 *bitmap, int size);
void rotate_texture(u8 **texture, int height, int width);

#define max(a,b) (((a) > (b)) ? (a) : (b))




