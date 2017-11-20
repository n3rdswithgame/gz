/**
 * zu.h
 * zelda64 utilities header
 * -glank
**/

#ifndef ZU_H
#define ZU_H
#include <stddef.h>
#include <stdint.h>
#include <vector/vector.h>
#include <n64.h>
#include "gu.h"
#include "z64.h"

#define ZU_MAKE_SEG(seg,off)  (((((uint32_t)(seg))&0x0000000F)<<24)|          \
                               ((((uint32_t)(off))&0x00FFFFFF)<<0))
#define ZU_MESH_OPA           0
#define ZU_MESH_XLU           1
#define ZU_MESH_NEAR          2
#define ZU_MESH_FAR           3
#define ZU_MESH_TYPES         4

struct zu_file
{
  uint32_t vrom_start;
  uint32_t vrom_end;
};

struct zu_mesh_entry
{
  int       size;
  uint32_t *dlists;
};

struct zu_mesh
{
  union
  {
    struct zu_mesh_entry    all[ZU_MESH_TYPES];
    struct
    {
      struct zu_mesh_entry  opa;
      struct zu_mesh_entry  xlu;
      struct zu_mesh_entry  near;
      struct zu_mesh_entry  far;
    };
  };
};

struct zu_vlist
{
  struct vector v;
};

struct zu_bbox
{
  float x1, x2,
        y1, y2,
        z1, z2;
};

struct zu_scene_info
{
  const char   *scene_name;
  int           no_entrances;
  const char  **entrance_names;
};

struct zu_gfx
{
  Gfx *work;
  Gfx *work_p;
  Gfx *work_d;
  Gfx *work_w;
  Gfx *z_work_p;
  Gfx *z_work_d;
  Gfx *poly_opa;
  Gfx *poly_opa_p;
  Gfx *poly_opa_d;
  Gfx *poly_opa_w;
  Gfx *z_poly_opa_p;
  Gfx *z_poly_opa_d;
  Gfx *poly_xlu;
  Gfx *poly_xlu_p;
  Gfx *poly_xlu_d;
  Gfx *poly_xlu_w;
  Gfx *z_poly_xlu_p;
  Gfx *z_poly_xlu_d;
  Gfx *overlay;
  Gfx *overlay_p;
  Gfx *overlay_d;
  Gfx *overlay_w;
  Gfx *z_overlay_p;
  Gfx *z_overlay_d;
};

void *zu_seg_locate(const z64_stab_t *stab, uint32_t seg_addr);
void *zu_zseg_locate(uint32_t seg_addr);
void zu_getfile(uint32_t vrom_addr, void *dram_addr, size_t size);

void *zu_sr_header(void *sr, int header_index, const z64_stab_t *stab);
void zu_scene_rooms(const void *scene, struct zu_file *ftab, int ftab_size,
                    int *no_rooms, const z64_stab_t *stab);
void zu_room_mesh(const void *room, struct zu_mesh *mesh,
                  const z64_stab_t *stab);
void zu_mesh_destroy(struct zu_mesh *mesh);

void zu_vlist_init(struct zu_vlist *vlist);
void zu_vlist_add_dl(struct zu_vlist *vlist,
                     const z64_stab_t *stab, const Gfx *dl);
void zu_vlist_bbox(const struct zu_vlist *vlist, struct zu_bbox *bbox);
void zu_vlist_transform(const struct zu_vlist *vlist, const MtxF *mf);
void zu_vlist_destroy(struct zu_vlist *vlist);

void zu_sram_read(void *dram_addr, uint32_t sram_addr, size_t size);
void zu_sram_write(void *dram_addr, uint32_t sram_addr, size_t size);

void zu_reset(void);

void zu_void(void);

void zu_execute_game(int16_t entrance_index, uint16_t cutscene_index);
void zu_execute_filemenu(void);

void zu_setmusic(uint32_t command);

void zu_set_event_flag(int flag_index);
void zu_clear_event_flag(int flag_index);

void zu_gfx_init(struct zu_gfx *gfx);
void zu_gfx_destroy(struct zu_gfx *gfx);
void zu_gfx_inject(struct zu_gfx *gfx);
void zu_gfx_restore(struct zu_gfx *gfx);
Gfx *zu_gfx_flush(struct zu_gfx *gfx);

extern struct zu_scene_info zu_scene_info[];

#endif
