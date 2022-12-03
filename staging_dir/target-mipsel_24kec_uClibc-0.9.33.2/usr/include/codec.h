#ifndef _CODEC_C_
#define _CODEC_C_
#include <json/json.h>
#include <stdio.h>
#include <stdbool.h>

enum vbs_type {
    vbs_type_boolean,
    vbs_type_double,
    vbs_type_int,
    vbs_type_object,
    vbs_type_array,
    vbs_type_string
};

struct vbs_map;
typedef struct  vbs_map  vbs_map_t;
struct vbs_array;
typedef struct  vbs_array vbs_array_t;

extern vbs_map_t *vbs_map_new();
extern void vbs_map_free(vbs_map_t *map);

extern int  vbs_map_size(const vbs_map_t *map);

extern bool vbs_map_get_bool(vbs_map_t *map, const char *key);
extern void vbs_map_set_bool(vbs_map_t *map, const char *key, bool b);
extern int vbs_map_get_int(vbs_map_t *map, const char *key);
extern void vbs_map_set_int(vbs_map_t *map, const char *key, int value);
extern int64_t vbs_map_get_int64(vbs_map_t *map, const char *key);
extern void vbs_map_set_int64(vbs_map_t *map, const char *key, int64_t value);
extern double vbs_map_get_double(vbs_map_t *map, const char *key);
extern void vbs_map_set_double(vbs_map_t *map, const char *key, double value);
extern const char *vbs_map_get_string(vbs_map_t *map, const char *key, size_t *value_len);
extern void vbs_map_set_string(vbs_map_t *map, const char *key, const char *value, int value_size);

extern vbs_map_t *vbs_map_get_map(vbs_map_t *map, const char *key);
extern vbs_map_t *vbs_map_set_map(vbs_map_t *map, const char *key);
extern vbs_array_t *vbs_map_get_array(vbs_map_t *map, const char *key);
extern vbs_array_t *vbs_map_set_array(vbs_map_t *map, const char *key);

extern const char* vbs_map_to_string(vbs_map_t *map);
extern void vbs_map_print(vbs_map_t *map, FILE* out);


extern vbs_array_t *vbs_array_new();
extern void vbs_array_free(vbs_array_t *array);

extern int vbs_array_size(vbs_array_t *array);

extern bool vbs_array_get_bool(vbs_array_t *array, int index);
extern void vbs_array_add_bool(vbs_array_t *array, bool value);
extern int vbs_array_get_int(vbs_array_t *array, int index);
extern void vbs_array_add_int(vbs_array_t *array, int value);
extern int64_t vbs_array_get_int64(vbs_array_t *array, int index);
extern void vbs_array_add_int64(vbs_array_t *array, int64_t value);
extern double vbs_array_get_double(vbs_array_t *array, int index);
extern void vbs_array_add_double(vbs_array_t *array, double value);
extern const char *vbs_array_get_string(vbs_array_t *array, int index, size_t *value_len);
extern void vbs_array_add_string(vbs_array_t *array, const char *value, int value_size);

extern vbs_map_t *vbs_array_get_map(vbs_array_t *array, int index);
extern vbs_map_t *vbs_array_add_map(vbs_array_t *array);
extern vbs_array_t *vbs_array_get_array(vbs_array_t *array, int index);
extern vbs_array_t *vbs_array_add_array(vbs_array_t *array);

extern const char* vbs_array_to_string(vbs_array_t *array);
extern void vbs_array_print(vbs_array_t *array, FILE* out);

#endif
