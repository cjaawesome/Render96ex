#include <stdio.h>
#include "types.h"

struct unifont_glyph{
    int height, width;
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


