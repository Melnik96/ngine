/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <GL/glew.h>
#include <math.h>

#include <../obj/obj.h>
#include "iofile.h"
#include "shader_prog.h"
#include "texture.h"
#include "mesh.h"
#include "sc_obj.h"

#include "math/vector.h"

#include "render/render.h"
#include "render/technique.h"
#include "render/pass.h"
#include "render/framebuffer.h"

#include "gl30_tech.h"

struct ngine_tech* ngine_create_tech_gl30() {
  struct ngine_tech* new_tech = calloc(1, sizeof(struct ngine_tech));
  struct ngine_render_pass* pass_geom = calloc(1, sizeof(struct ngine_render_pass));// geometry
  struct ngine_render_pass* pass_ssao = calloc(1, sizeof(struct ngine_render_pass));// ssao
  struct ngine_render_pass* pass_light = calloc(1, sizeof(struct ngine_render_pass));// light final

  struct ngine_shdr_prog* shdr = NULL;
  
//   new_tech->gl_vendor = GL_VENDOR_NONE;
  new_tech->gl_ver = 30;
  new_tech->glsl_ver = 130;
  
  new_tech->deferred = 1;
  new_tech->ssao = 1;
  
  new_tech->num_render_passes = 3;
  
  new_tech->render_passes = calloc(3, sizeof(struct ngine_render_pass));
  
  pass_geom = &new_tech->render_passes[0];
  pass_ssao = &new_tech->render_passes[1];
  pass_light = &new_tech->render_passes[2];
  
  pass_geom->render_ents = 1;
  
  pass_geom->a_vert = 1;
  pass_geom->a_norm= 1;
  pass_geom->u_mvp = 1;
  pass_geom->u_model = 1;
  pass_geom->u_tex = 1;
  
  pass_geom->shdr_prog = shdr = ngine_shdr_prog_create("gl30_geom");
  
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl30/pass_geom.vert"), GL_VERTEX_SHADER);
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl30/pass_geom.frag"), GL_FRAGMENT_SHADER);
  
  ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_VERTEX, "a_vert");
//   ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_NORMAL, "a_norm");
  
  ngine_shdr_prog_link(shdr);
  
  shdr->uniform_locs[NGINE_UNIFORM_MVP] = ngine_shdr_prog_get_unf_loc(shdr, "u_mvp");
  shdr->uniform_locs[NGINE_UNIFORM_MODEL] = ngine_shdr_prog_get_unf_loc(shdr, "u_model");
  shdr->uniform_locs[NGINE_UNIFORM_TEX] = ngine_shdr_prog_get_unf_loc(shdr, "u_tex");
  
  pass_geom->fbuf_draw = ngine_framebuffer_create(1, 4, GL_RGB32F, GL_RGB, GL_FLOAT, 1024, 600);
  
  
  pass_ssao->render_screen_quad = 1;
  
  pass_ssao->a_vert = 1;
  pass_ssao->u_mvp = 0;
  
  pass_ssao->shdr_prog = ngine_shdr_prog_create("gl30_ssao");
  shdr = pass_ssao->shdr_prog;
  
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl30/pass_ssao.vert"), GL_VERTEX_SHADER);
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl30/pass_ssao.frag"), GL_FRAGMENT_SHADER);
  ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_VERTEX, "a_vert");
  ngine_shdr_prog_link(shdr);
  
  shdr->uniform_locs[NGINE_UNIFORM_PROJ] = ngine_shdr_prog_get_unf_loc(shdr, "u_proj");
  shdr->uniform_locs[NGINE_UNIFORM_VIEW] = ngine_shdr_prog_get_unf_loc(shdr, "u_view");
  shdr->uniform_locs[NGINE_UNIFORM_GTEX0] = ngine_shdr_prog_get_unf_loc(shdr, "rnm");
  shdr->uniform_locs[NGINE_UNIFORM_GTEX1] = ngine_shdr_prog_get_unf_loc(shdr, "g_norm_map");
  shdr->uniform_locs[NGINE_UNIFORM_GTEX2] = ngine_shdr_prog_get_unf_loc(shdr, "g_lindepth_map");
  
  struct ngine_texture* rnm_tex = ngine_texture_create(0);
  ngine_texture_image(rnm_tex, "media/textures/noise.tga");
  
  pass_ssao->fbuf_draw = ngine_framebuffer_create(0, 1, GL_RGB32F, GL_RGB, GL_FLOAT, 1024, 600);
  
  pass_ssao->num_texs_read = 3;
  pass_ssao->texs_read = malloc(pass_ssao->num_texs_read*sizeof(struct ngine_texture*));
  pass_ssao->texs_read[0] = rnm_tex;
  pass_ssao->texs_read[1] = &pass_geom->fbuf_draw->draw_texs[2];
  pass_ssao->texs_read[2] = &pass_geom->fbuf_draw->draw_texs[3];
  
  
//   pass_light->render_ents = 1;
  pass_light->render_lights = 1;
  
  pass_light->a_vert = 1;
  pass_light->u_mvp = 1;
  pass_light->u_light_dcolor = 1;
  pass_light->u_light_pos = 1;
  
  pass_light->shdr_prog = ngine_shdr_prog_create("gl30_light");
  shdr = pass_light->shdr_prog;
  
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl30/pass_light.vert"), GL_VERTEX_SHADER);
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl30/pass_light.frag"), GL_FRAGMENT_SHADER);
  ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_VERTEX, "a_vert");
  ngine_shdr_prog_link(shdr);
  
  shdr->uniform_locs[NGINE_UNIFORM_MVP] = ngine_shdr_prog_get_unf_loc(shdr, "u_mvp");
  shdr->uniform_locs[NGINE_UNIFORM_GTEX0] = ngine_shdr_prog_get_unf_loc(shdr, "g_difuse_map");
  shdr->uniform_locs[NGINE_UNIFORM_GTEX1] = ngine_shdr_prog_get_unf_loc(shdr, "g_wpos_map");
  shdr->uniform_locs[NGINE_UNIFORM_GTEX2] = ngine_shdr_prog_get_unf_loc(shdr, "g_norm_map");
  shdr->uniform_locs[NGINE_UNIFORM_GTEX3] = ngine_shdr_prog_get_unf_loc(shdr, "g_ssao_map");
  shdr->uniform_locs[NGINE_UNIFORM_LIGHT_DIFUSE] = ngine_shdr_prog_get_unf_loc(shdr, "u_light_dcolor");
  shdr->uniform_locs[NGINE_UNIFORM_LIGHT_POS] = ngine_shdr_prog_get_unf_loc(shdr, "u_light_pos");
  
  pass_light->num_texs_read = 4;
  pass_light->texs_read = malloc(pass_light->num_texs_read*sizeof(struct ngine_texture*));
  pass_light->texs_read[0] = &pass_geom->fbuf_draw->draw_texs[0];
  pass_light->texs_read[1] = &pass_geom->fbuf_draw->draw_texs[1];
  pass_light->texs_read[2] = &pass_geom->fbuf_draw->draw_texs[2];
  pass_light->texs_read[3] = &pass_ssao->fbuf_draw->draw_texs[0];
  
//   glClearColor(.4f, 0.2f, 0.0f, 1.0f);
//   glEnable(GL_CULL_FACE);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
  return new_tech;
}
