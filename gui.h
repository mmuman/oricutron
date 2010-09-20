/*
**  Oricutron
**  Copyright (C) 2009-2010 Peter Gordon
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation, version 2
**  of the License.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
**  GUI
*/

// Render modes available
enum
{
  RENDERMODE_NULL = 0,
  RENDERMODE_SW,
  RENDERMODE_GL
};

// Reserve your textzones here!
enum
{
  TZ_MONITOR = 0,
  TZ_DEBUG,
  TZ_MEMWATCH,
  TZ_REGS,
  TZ_VIA,
  TZ_VIA2,
  TZ_AY,
  TZ_DISK,
  TZ_MENU,
  TZ_MSGBOX,
  TZ_FILEREQ,
  NUM_TZ
};

struct textzone
{
  int x, y, w, h;           // Dimensions
  int px, py, cfc, cbc;     // Current position and text colours
  unsigned char *tx;        // Text buffer
  unsigned char *fc, *bc;   // Colour buffers
  SDL_bool modified;
};

// "on screen display" menus
#define OSDMENUBAR ((char *)-1)

struct osdmenuitem
{
  char *name;
  char *key;
  int  sdlkey;
  void (*func)(struct machine *,struct osdmenuitem *,int);
  int arg;
};

struct osdmenu
{
  char *title;
  int citem;
  struct osdmenuitem *items;
};

#define VSPTMPSIZE 1024

struct guiimg
{
  char *filename;
  Uint16 w, h;
  Uint8 *buf;
};

enum
{
  GIMG_STATUSBAR,
  GIMG_DISK_EJECTED,
  GIMG_DISK_IDLE,
  GIMG_DISK_ACTIVE,
  GIMG_DISK_IDLE_MOD,
  GIMG_DISK_ACTIVE_MOD,
  GIMG_TAPE_EJECTED,
  GIMG_TAPE_PAUSE,
  GIMG_TAPE_PLAY,
  GIMG_TAPE_STOP,
  GIMG_AVI_RECORD,
  NUM_GIMG
};

#define NUM_GUI_COLS 9

SDL_bool alloc_textzone( struct machine *oric, int i, int x, int y, int w, int h, char *title );
void free_textzone( struct machine *oric, int i );

void do_popup( struct machine *oric, char *str );
void makebox( struct textzone *ptz, int x, int y, int w, int h, int fg, int bg );
void tzsettitle( struct textzone *ptz, char *title );
void tzstr( struct textzone *ptz, char *text );
void tzstrpos( struct textzone *ptz, int x, int y, char *text );
void tzsetcol( struct textzone *ptz, int fc, int bc );
void tzprintf( struct textzone *ptz, char *fmt, ... );
void tzprintfpos( struct textzone *ptz, int x, int y, char *fmt, ... );
void draw_textzone( struct textzone *ptz );
void printstr( int x, int y, Uint32 fc, Uint32 bc, char *str );
void gotomenu( struct machine *oric, struct osdmenuitem *mitem, int menunum );
SDL_bool menu_event( SDL_Event *ev, struct machine *oric, SDL_bool *needrender );
void setmenutoggles( struct machine *oric );
void set_render_mode( struct machine *oric, int whichrendermode );

void render( struct machine *oric );
void preinit_gui( struct machine *oric );
SDL_bool init_gui( struct machine *oric, Sint32 rendermode );
void shut_gui( struct machine *oric );

void draw_statusbar( struct machine *oric );
void draw_disks( struct machine *oric );
void draw_avirec( struct machine *oric, SDL_bool recording );
void draw_tape( struct machine *oric );
void statusprintstr( int x, Uint32 fc, char *str );
void joinpath( char *path, char *file );

