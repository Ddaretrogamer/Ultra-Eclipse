#include "global.h"
#include "bg.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "event_scripts.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "malloc.h"
#include "math_util.h"
#include "main_menu.h"
#include "menu.h"
#include "naming_screen.h"
#include "overworld.h"
#include "outfit_menu.h"
#include "palette.h"
#include "pokeball.h"
#include "random.h"
#include "rtc.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "international_string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "util.h"
#include "m4a.h"

static void Task_GettingACall(u8);
static void Task_LaunchCall(u8);
static void Task_HeyThere(u8);
static void Task_AlolaIsARegion(u8);
static void Task_CoolPokemon(u8);
static void Task_AllOver(u8);
static void Task_LoveOurPokemon(u8);
static void Task_AndYouAre(u8);
static void Task_WhichPhoto(u8);
static void Task_StartNamingScreen(u8);
static void CB2_NewGameKukuiCall_ReturnFromNamingScreen(void);
static void Task_SoItsPlayer(u8);
static void Task_YourePlayer(u8);
static void Task_AreYouReady(u8);
static void Task_EndCall(u8);
static void Task_Cleanup(u8);
// static void Task_TestLoop(u8);

static void Task_CreatePhotoYesNo(u8);
static void Task_ProcessPhotoYesNoMenu(u8);
static void Task_CreateNameYesNo(u8);
static void Task_ProcessNameYesNoMenu(u8);

// static void NewGameKukuiCall_PrintNameplate(void);
static void AddComputerBackgroundObjects(u8);
static void AddComputerBackgroundObjects_ReturnFromNamingScreen(u8);
static void LoadComputerPassportPhotos(u8);

extern void FastUnsafeCopy32(void *dst, const void *src, u32 size);

static void KukuiCreateYesNoMenuParameterized(u8 bg, u8 x, u8 y, u16 baseTileNum, u16 baseBlock, u8 yesNoPalNum, u8 winPalNum);

extern const struct OamData gOamData_AffineDouble_ObjNormal_64x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_64x64;
extern const struct OamData gOamData_AffineOff_ObjNormal_64x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x16;
extern const struct OamData gOamData_AffineOff_ObjNormal_16x16;
extern const struct OamData gOamData_AffineOff_ObjNormal_16x8;

#pragma region Asset Definitions

// The Player Character's PC Wallpaper - BG Layer 3 (Bottom, Priority 3) of the Kukui Call scene
static const u32 sComputer_Background_Tiles[] = INCGFX_U32("graphics/kukui_call/computer_bg_tiles.png", ".4bpp.smol");
static const u32 sComputer_Background_Tilemap[] = INCGFX_U32("graphics/kukui_call/computer_bg_tiles.bin", ".smolTM");
static const u32 sComputer_Background_Tilemap_Top[] = INCGFX_U32("graphics/kukui_call/computer_bg_top_tiles.bin", ".smolTM");
static const u16 sComputer_Background_Pals[] = INCGFX_U16("graphics/kukui_call/computer_bg_tiles.png", ".gbapal");

// Kukui's Background in the video call window - BG Layer 2 (Lower, Priority 2) of the Kukui Call scene
// Background1 is visually askew, Background2 is visually upright
static const u32 sCall_Background1_Tiles[] = INCGFX_U32("graphics/kukui_call/call_bg1_tiles.png", ".4bpp.smol");
static const u32 sCall_Background1_Tilemap[] = INCGFX_U32("graphics/kukui_call/call_bg1_tiles.bin", ".smolTM");
static const u32 sCall_Background2_Tiles[] = INCGFX_U32("graphics/kukui_call/call_bg2_tiles.png", ".4bpp.smol");
static const u32 sCall_Background2_Tilemap[] = INCGFX_U32("graphics/kukui_call/call_bg2_tiles.bin", ".smolTM");
static const u16 sCall_Background_Pals[] = INCGFX_U16("graphics/kukui_call/call_bg1_tiles.png", ".gbapal");

// Kukui himself - BG Layer 1 (Higher, Priority 1) of the Kukui Call scene
// Kukui1 - Leaned back, visually askew
// Kukui2 - Leaned forward, grabbing camera, still visually askew
// Kukui3 - Leaned forward, grabbing camera, now visually upright
// Kukui4 - Leaned back, waving to camera (4a is shifted right)
// Kukui5 - Default pose (5a is shifted left)
// Kukui6 - Leaned to his left, gesturing to content to his right
// Kukui7 - Holding out pokeball to camera
// Kukui8 - Head tilted back, hand up as if tossing pokeball up out of frame
static const u32 sKukui1_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui1_tiles.png", ".4bpp.smol");
static const u32 sKukui1_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui1_tiles.bin", ".smolTM");
static const u32 sKukui2_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui2_tiles.png", ".4bpp.smol");
static const u32 sKukui2_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui2_tiles.bin", ".smolTM");
static const u32 sKukui3_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui3_tiles.png", ".4bpp.smol");
static const u32 sKukui3_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui3_tiles.bin", ".smolTM");
static const u32 sKukui4_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui4_tiles.png", ".4bpp.smol");
static const u32 sKukui4_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui4_tiles.bin", ".smolTM");
static const u32 sKukui4a_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui4a_tiles.bin", ".smolTM");
static const u32 sKukui5_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui5_tiles.png", ".4bpp.smol");
static const u32 sKukui5_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui5_tiles.bin", ".smolTM");
static const u32 sKukui5a_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui5a_tiles.bin", ".smolTM");
static const u32 sKukui6_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui6_tiles.png", ".4bpp.smol");
static const u32 sKukui6_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui6_tiles.bin", ".smolTM");
static const u32 sKukui7_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui7_tiles.png", ".4bpp.smol");
static const u32 sKukui7_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui7_tiles.bin", ".smolTM");
static const u32 sKukui8_Tiles[] = INCGFX_U32("graphics/kukui_call/kukui/kukui8_tiles.png", ".4bpp.smol");
static const u32 sKukui8_Tilemap[] = INCGFX_U32("graphics/kukui_call/kukui/kukui8_tiles.bin", ".smolTM");
static const u16 sKukui_Pals[] = INCGFX_U16("graphics/kukui_call/kukui/kukui1_tiles.png", ".gbapal");

// Kukui's Rockruff - BG Layer 0 (Top, Priority 0) of the Kukui Call scene
// (Rockruff_a is hFlipped and shifted slightly left, b is hFlipped and shifted more left)
static const u32 sRockruff_Tiles[] = INCGFX_U32("graphics/kukui_call/rockruff/rockruff_tiles.png", ".4bpp.smol");
static const u32 sRockruff_Tilemap[] = INCGFX_U32("graphics/kukui_call/rockruff/rockruff_tiles.bin", ".smolTM");
static const u32 sRockruff_a_Tilemap[] = INCGFX_U32("graphics/kukui_call/rockruff/rockruff_tiles_a.bin", ".smolTM");
static const u32 sRockruff_b_Tilemap[] = INCGFX_U32("graphics/kukui_call/rockruff/rockruff_tiles_b.bin", ".smolTM");
static const u16 sRockruff_Pals[] = INCGFX_U16("graphics/kukui_call/rockruff/rockruff_tiles.png", ".gbapal");

// Sprites for the video call's app window
// call_window_scalable - 64x32 - a 46x28 rectangle that can be scaled up and down and hue-shifted to simulate a computer window opening and closing
// call_window_corner - 64x64 - a north-west corner that can be rotated +90* for NE, SE, and SW
// call_window_edge - 64x32 - a north edge that can be vertically flipped
// call_window_ui - 64x32 - the window's top bar with minimize, maximize, and close buttons
static const u32 sCall_Window_Scalable_Gfx[] = INCGFX_U32("graphics/kukui_call/call_window/call_window_scalable.png", ".4bpp.smol");
static const u32 sCall_Window_Corner_Gfx[] = INCGFX_U32("graphics/kukui_call/call_window/call_window_corner.png", ".4bpp.smol");
static const u32 sCall_Window_Edge_Gfx[] = INCGFX_U32("graphics/kukui_call/call_window/call_window_edge.png", ".4bpp.smol");
static const u32 sCall_Window_UI_Gfx[] = INCGFX_U32("graphics/kukui_call/call_window/call_window_ui.png", ".4bpp.smol");
static const u16 sCall_Window_Pals[] = INCGFX_U16("graphics/kukui_call/call_window/call_window_corner.png", ".gbapal");

// Sprites for the desktop's apps
// settings_icon - 32x32 - settings app icon
// camera_icon - 32x32 - seems to be a photos folder icon but might just be a camera app icon
// notification_icon - 16x16 - a red dot to place on the upper right corner of the video call app icon while the call is active
// video icon - 4x2 spritesheet of 32x32 frames - video call app icon
  // offset 0 - default visual
  // offset 16 - "Ringing Frame 1" - the icon raises slightly with a glowing border
  // offset 32 - "Ringing Frame 2" - the icon stays raised, the border expands out and away like a wave
  // offset 48 - "Ringing Frame 3" - the icon lowers slightly, the wave expands fully and thins as if disappating
  // offset 64 - "Selecting Frame 1" - the icon becomes fully white
  // offset 80 - "Selecting Frame 2" - the icon becomes larger, begins fading back to normal
  // offset 96 - "Selecting Frame 3" - the icon size remains, continues fading back to normal
  // offset 112 - "Selecting Frame 4" - the icon becomes slightly smaller, continues fading back to normal
static const u32 sSettings_Icon_Gfx[] = INCGFX_U32("graphics/kukui_call/icons/settings_icon.png", ".4bpp.smol");
static const u16 sSettings_Icon_Pals[] = INCGFX_U16("graphics/kukui_call/icons/settings_icon.png", ".gbapal");
static const u32 sCamera_Icon_Gfx[] = INCGFX_U32("graphics/kukui_call/icons/camera_icon.png", ".4bpp.smol");
static const u16 sCamera_Icon_Pals[] = INCGFX_U16("graphics/kukui_call/icons/camera_icon.png", ".gbapal");
static const u32 sNotification_Icon_Gfx[] = INCGFX_U32("graphics/kukui_call/icons/notification_icon.png", ".4bpp.smol");
static const u16 sNotification_Icon_Pals[] = INCGFX_U16("graphics/kukui_call/icons/notification_icon.png", ".gbapal");
static const u32 sVideo_Icon_Gfx[] = INCGFX_U32("graphics/kukui_call/icons/video_icon.png", ".4bpp.smol", "-mwidth 4 -mheight 4");
static const u16 sVideo_Icon_Pals[] = INCGFX_U16("graphics/kukui_call/icons/video_icon.png", ".gbapal");



static const u32 sArrowCursor_Gfx[]     = INCGFX_U32("graphics/interface/arrow_cursor.png", ".4bpp.smol");
static const u16 sArrowCursor_Pal[]    = INCGFX_U16("graphics/interface/red.pal", ".gbapal");

static const u16 sMainMenuTextPal[] = INCGFX_U16("graphics/interface/main_menu_text.pal", ".gbapal");

#pragma endregion

#define BIRCH_DLG_BASE_TILE_NUM 0x69

#define KUKUI_1_BASE_TILE_NUM   0x091 // 0xB5
#define KUKUI_2_BASE_TILE_NUM   0x146 // 0xB5
#define PC_BG_BASE_TILE_NUM     0x1FB // 0x141
#define CALL_BG_1_BASE_TILE_NUM 0x33C // 0x107
#define CALL_BG_2_BASE_TILE_NUM 0x443 // 0x107
#define BLANK_TILE_2            0x54A // 0x1
#define TEXT_BG_TILE            0x54B // 0x1

// QUESTION - Why these values? Does order actually matter?
#define KUKUI_1_SCREEN_INDEX 29
#define KUKUI_2_SCREEN_INDEX 28
#define CALL_BG_1_SCREEN_INDEX 30
#define CALL_BG_2_SCREEN_INDEX 27
#define ROCKRUFF_SCREEN_INDEX 26
#define PC_BG_SCREEN_INDEX 31
#define PC_BG_TOP_SCREEN_INDEX 24

#define PC_BG_HEIGHT 20
#define CALL_BG_HEIGHT 14
#define TEXTBOX_HEIGHT 6

#define USED_KUKUI_BTN(freeTileNum) ((freeTileNum == KUKUI_1_BASE_TILE_NUM) ? KUKUI_2_BASE_TILE_NUM : KUKUI_1_BASE_TILE_NUM)
#define USED_CALL_BG_BTN(freeTileNum) ((freeTileNum == CALL_BG_1_BASE_TILE_NUM) ? CALL_BG_2_BASE_TILE_NUM : CALL_BG_1_BASE_TILE_NUM)
#define USED_KUKUI_SI(freeScreenIndex) ((freeScreenIndex == KUKUI_1_SCREEN_INDEX) ? KUKUI_2_SCREEN_INDEX : KUKUI_1_SCREEN_INDEX)
#define USED_CALL_BG_SI(freeScreenIndex) ((freeScreenIndex == CALL_BG_1_SCREEN_INDEX) ? CALL_BG_2_SCREEN_INDEX : CALL_BG_1_SCREEN_INDEX)

// QUESTION - Why these charBaseIndex values? What does charBaseIndex actually mean?
static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = ROCKRUFF_SCREEN_INDEX,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = KUKUI_1_SCREEN_INDEX,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 1,
        .mapBaseIndex = CALL_BG_1_SCREEN_INDEX,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

// TODO - replace Nameplate TextWindow w/ Multichoice TextWindow
static const struct WindowTemplate sNewGameKukuiCallTextWindows[] =
{
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 1
    },
    {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 13,
        .width = DLW_WIN_PLATE_SIZE,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x81,
    },
    DUMMY_WIN_TEMPLATE
};

#pragma region Sprite Definitions

#define GFX_TAG_ICON_SETTINGS           0x1000
#define GFX_TAG_ICON_CAMERA             0x1001
#define GFX_TAG_ICON_NOTIFICATION       0x1002
#define GFX_TAG_ICON_VIDEO              0x1003
#define GFX_TAG_CALL_WINDOW_CORNER      0x1004
#define GFX_TAG_CALL_WINDOW_EDGE        0x1005
#define GFX_TAG_CALL_WINDOW_UI          0x1006
#define GFX_TAG_CALL_WINDOW_SCALABLE    0x1007
#define GFX_TAG_ARROW_CURSOR            0x1008
#define GFX_TAG_PHOTO_PLACEHOLDER_M1    0x1009
#define GFX_TAG_PHOTO_PLACEHOLDER_M2    0x100a
#define GFX_TAG_PHOTO_PLACEHOLDER_F1    0x100b
#define GFX_TAG_PHOTO_PLACEHOLDER_F2    0x100c

#define PAL_TAG_ICON_SETTINGS           0x1000
#define PAL_TAG_ICON_CAMERA             0x1001
#define PAL_TAG_ICON_NOTIFICATION       0x1002
#define PAL_TAG_ICON_VIDEO              0x1003
#define PAL_TAG_CALL_WINDOW             0x1004
#define PAL_TAG_ARROW_CURSOR            0x1008
#define PAL_TAG_PHOTO_PLACEHOLDER       0x1009

static const struct CompressedSpriteSheet sSettings_Icon_SpriteSheet =
{
    .data = sSettings_Icon_Gfx,
    .size = 32 * 32 / 2,
    .tag = GFX_TAG_ICON_SETTINGS
};

static const struct CompressedSpriteSheet sCamera_Icon_SpriteSheet =
{
    .data = sCamera_Icon_Gfx,
    .size = 32 * 32 / 2,
    .tag = GFX_TAG_ICON_CAMERA
};

static const struct CompressedSpriteSheet sNotification_Icon_SpriteSheet =
{
    .data = sNotification_Icon_Gfx,
    .size = 16 * 16 / 2,
    .tag = GFX_TAG_ICON_NOTIFICATION
};

static const struct CompressedSpriteSheet sVideo_Icon_SpriteSheet =
{
    .data = sVideo_Icon_Gfx,
    .size = (32 * 32 / 2) * 8, // 8 frames of animation
    .tag = GFX_TAG_ICON_VIDEO
};

static const struct CompressedSpriteSheet sArrowCursor_SpriteSheet =
{
    .data = sArrowCursor_Gfx,
    .size = 16 * 16 / 2,
    .tag = GFX_TAG_ARROW_CURSOR
};

static const struct CompressedSpriteSheet sCall_Window_Corner_SpriteSheet =
{
    .data = sCall_Window_Corner_Gfx,
    .size = 64 * 64 / 2,
    .tag = GFX_TAG_CALL_WINDOW_CORNER
};

static const struct CompressedSpriteSheet sCall_Window_Edge_SpriteSheet =
{
    .data = sCall_Window_Edge_Gfx,
    .size = 64 * 64 / 2,
    .tag = GFX_TAG_CALL_WINDOW_EDGE
};

static const struct CompressedSpriteSheet sCall_Window_UI_SpriteSheet =
{
    .data = sCall_Window_UI_Gfx,
    .size = 64 * 32 / 2,
    .tag = GFX_TAG_CALL_WINDOW_UI
};

static const struct CompressedSpriteSheet sCall_Window_Scalable_SpriteSheet =
{
    .data = sCall_Window_Scalable_Gfx,
    .size = 64 * 32 / 2,
    .tag = GFX_TAG_CALL_WINDOW_SCALABLE
};

static const struct SpriteTemplate sSettings_Icon_SpriteTemplate =
{
    .tileTag = GFX_TAG_ICON_SETTINGS,
    .paletteTag = PAL_TAG_ICON_SETTINGS,
    .oam = &gOamData_AffineOff_ObjNormal_32x32,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpritePalette sSettings_Icon_SpritePalette =
{
    .data = sSettings_Icon_Pals,
    .tag = PAL_TAG_ICON_SETTINGS
};

static const struct SpriteTemplate sCamera_Icon_SpriteTemplate =
{
    .tileTag = GFX_TAG_ICON_CAMERA,
    .paletteTag = PAL_TAG_ICON_CAMERA,
    .oam = &gOamData_AffineOff_ObjNormal_32x32,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpritePalette sCamera_Icon_SpritePalette =
{
    .data = sCamera_Icon_Pals,
    .tag = PAL_TAG_ICON_CAMERA
};

static const struct SpriteTemplate sNotification_Icon_SpriteTemplate =
{
    .tileTag = GFX_TAG_ICON_NOTIFICATION,
    .paletteTag = PAL_TAG_ICON_NOTIFICATION,
    .oam = &gOamData_AffineOff_ObjNormal_16x16,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpritePalette sNotification_Icon_SpritePalette =
{
    .data = sNotification_Icon_Pals,
    .tag = PAL_TAG_ICON_NOTIFICATION
};

static const union AnimCmd sVideo_Icon_No_Anim[] =
{
    ANIMCMD_FRAME( 0, 0),
    ANIMCMD_END
};

static const union AnimCmd sVideo_Icon_Ringing_Anim[] =
{
    ANIMCMD_FRAME( 0, 0),
    ANIMCMD_FRAME(16, 6),
    ANIMCMD_FRAME(32, 3),
    ANIMCMD_FRAME(48, 6),
    ANIMCMD_FRAME( 0, 0),
    ANIMCMD_END
};

static const union AnimCmd sVideo_Icon_Selecting_Anim[] =
{
    ANIMCMD_FRAME( 0, 0),
    ANIMCMD_FRAME( 64,3),
    ANIMCMD_FRAME( 80,6),
    ANIMCMD_FRAME( 96,6),
    ANIMCMD_FRAME( 112,6),
    ANIMCMD_FRAME( 0,0),
    ANIMCMD_END
};

static const union AnimCmd *const sVideo_Icon_Anims[] =
{
    sVideo_Icon_No_Anim,
    sVideo_Icon_Ringing_Anim,
    sVideo_Icon_Selecting_Anim
};

static const struct SpriteFrameImage sVideo_Icon_PicTable[] =
{
    obj_frame_tiles(sVideo_Icon_Gfx) // Only works correctly because of "-mwidth 4 -mheight 4" in definition of sVideo_Icon_Gfx
};

static const struct SpriteTemplate sVideo_Icon_SpriteTemplate =
{
    .tileTag = GFX_TAG_ICON_VIDEO,
    .paletteTag = PAL_TAG_ICON_VIDEO,
    .oam = &gOamData_AffineOff_ObjNormal_32x32,
    .anims = sVideo_Icon_Anims,
    .images = sVideo_Icon_PicTable,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct SpritePalette sVideo_Icon_SpritePalette =
{
    .data = sVideo_Icon_Pals,
    .tag = PAL_TAG_ICON_VIDEO
};

static const struct SpriteTemplate sPhoto_Placeholder_M1_SpriteTemplate =
{
    .tileTag = GFX_TAG_PHOTO_PLACEHOLDER_M1,
    .paletteTag = PAL_TAG_PHOTO_PLACEHOLDER,
    .oam = &gOamData_AffineOff_ObjNormal_64x64,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sPhoto_Placeholder_M2_SpriteTemplate =
{
    .tileTag = GFX_TAG_PHOTO_PLACEHOLDER_M2,
    .paletteTag = PAL_TAG_PHOTO_PLACEHOLDER,
    .oam = &gOamData_AffineOff_ObjNormal_64x64,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sPhoto_Placeholder_F1_SpriteTemplate =
{
    .tileTag = GFX_TAG_PHOTO_PLACEHOLDER_F1,
    .paletteTag = PAL_TAG_PHOTO_PLACEHOLDER,
    .oam = &gOamData_AffineOff_ObjNormal_64x64,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sPhoto_Placeholder_F2_SpriteTemplate =
{
    .tileTag = GFX_TAG_PHOTO_PLACEHOLDER_F2,
    .paletteTag = PAL_TAG_PHOTO_PLACEHOLDER,
    .oam = &gOamData_AffineOff_ObjNormal_64x64,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sArrowCursor_SpriteTemplate =
{
    .tileTag = GFX_TAG_ARROW_CURSOR,
    .paletteTag = PAL_TAG_ARROW_CURSOR,
    .oam = &gOamData_AffineOff_ObjNormal_16x16,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpritePalette sArrowCursor_SpritePalette =
{
    .data = sArrowCursor_Pal,
    .tag = PAL_TAG_ARROW_CURSOR
};

static const struct SpriteTemplate sCall_Window_Corner_SpriteTemplate =
{
    .tileTag = GFX_TAG_CALL_WINDOW_CORNER,
    .paletteTag = PAL_TAG_CALL_WINDOW,
    .oam = &gOamData_AffineOff_ObjNormal_64x64,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sCall_Window_Edge_SpriteTemplate =
{
    .tileTag = GFX_TAG_CALL_WINDOW_EDGE,
    .paletteTag = PAL_TAG_CALL_WINDOW,
    .oam = &gOamData_AffineOff_ObjNormal_64x32,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sCall_Window_UI_SpriteTemplate =
{
    .tileTag = GFX_TAG_CALL_WINDOW_UI,
    .paletteTag = PAL_TAG_CALL_WINDOW,
    .oam = &gOamData_AffineOff_ObjNormal_64x32,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sCall_Window_Scalable_SpriteTemplate =
{
    .tileTag = GFX_TAG_CALL_WINDOW_SCALABLE,
    .paletteTag = PAL_TAG_CALL_WINDOW,
    .oam = &gOamData_AffineDouble_ObjNormal_64x32,
    .images = NULL,
    .callback = SpriteCallbackDummy
};

static const struct SpritePalette sCall_Window_SpritePalette =
{
    .data = sCall_Window_Pals,
    .tag = PAL_TAG_CALL_WINDOW
};

#pragma endregion

#pragma region Rendering Boilerplate

static void CB2_KukuiCall(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static EWRAM_DATA s16 sLastVCount;
static EWRAM_DATA bool8 sShouldLayerFade;
static EWRAM_DATA bool8 sLayerFadeActive;
static EWRAM_DATA u16 sLayerFadeTargetY, sLayerFadeY;
static EWRAM_DATA u8 sLayerFadeDelay, sLayerFadeDeltaY, sLayerFadeDelayCounter;
static EWRAM_DATA bool8 sLayerFadeDec;
static EWRAM_DATA bool8 sShouldUpdateLayerFade;
static EWRAM_DATA u16 sLayerFadeBldCnt;
static EWRAM_DATA bool8 sShouldChopRockruff;

static bool8 IsLayerFadeActive()
{
    return sShouldLayerFade || sLayerFadeActive;
}

static void PrepareForLayerFade(u16 targets, u8 startY)
{
    sLayerFadeY = startY;
    sLayerFadeBldCnt = targets | BLDCNT_EFFECT_BLEND;
}

static void BeginLayerFade(u16 targets, s8 delay, u8 startY, u8 targetY)
{
    sLayerFadeDeltaY = 2;

    if (delay < 0)
    {
        sLayerFadeDeltaY += (delay * -1);
        delay = 0;
    }

    sLayerFadeDelay = delay;
    sLayerFadeDelayCounter = delay;
    sLayerFadeY = startY;
    sLayerFadeTargetY = targetY;

    if (startY < targetY)
        sLayerFadeDec = FALSE;
    else
        sLayerFadeDec = TRUE;

    sLayerFadeBldCnt = targets | BLDCNT_EFFECT_BLEND;
    sLayerFadeActive = FALSE;
    sShouldLayerFade = TRUE;
}

static void UpdateLayerFade(void)
{
    if (sShouldLayerFade)
    {
        sLayerFadeActive = TRUE;
        sShouldLayerFade = FALSE;
    }

    if (!sLayerFadeActive)
        return;

    if (sLayerFadeDelayCounter < sLayerFadeDelay)
    {
        sLayerFadeDelayCounter++;
        return;
    }
    sLayerFadeDelayCounter = 0;

    if (sLayerFadeY == sLayerFadeTargetY)
    {
        sLayerFadeActive = FALSE;
    }
    else
    {
        s8 val;

        if (!sLayerFadeDec)
        {
            val = sLayerFadeY;
            val += sLayerFadeDeltaY;
            if (val > sLayerFadeTargetY)
                val = sLayerFadeTargetY;
            sLayerFadeY = val;
        }
        else
        {
            val = sLayerFadeY;
            val -= sLayerFadeDeltaY;
            if (val < sLayerFadeTargetY)
                val = sLayerFadeTargetY;
            sLayerFadeY = val;
        }
    }
}

static void UpdateLayerFadeRegs(void)
{
    REG_BLDCNT = sLayerFadeBldCnt;
    REG_BLDALPHA = BLDALPHA_BLEND(16 - sLayerFadeY, sLayerFadeY);
}

#define PP_X 30
#define PP_DELTA_X 44
#define PP_Y 38
#define PP_DELTA_Y 50

#define PS_X 214
#define PS_Y 90

// Keep frame pixels out of the Kukui tiles: BG1 still references those while
// faded white. The free range after TEXT_BG_TILE ends at screen block 24.
#define PASSPORT_BG_CHARBASE 2
#define PASSPORT_BG_BASE_TILE (TEXT_BG_TILE + 1)
#define PASSPORT_BG_BLANK_TILE 0x5FF
#define PASSPORT_BG_TILE_OFFSET (PASSPORT_BG_CHARBASE * 0x200)
#define PASSPORT_BG_BLANK_INDEX (PASSPORT_BG_BLANK_TILE - PASSPORT_BG_TILE_OFFSET)
#define PASSPORT_BG_PALETTE 14
#define PASSPORT_PHOTO_WIDTH 40
#define PASSPORT_PHOTO_HEIGHT 44
#define PASSPORT_FRAME_WIDTH (PASSPORT_PHOTO_WIDTH + 2)
#define PASSPORT_FRAME_HEIGHT (PASSPORT_PHOTO_HEIGHT + 2)
#define PASSPORT_CORNER_PHOTO_HEIGHT 40
#define PASSPORT_CORNER_FRAME_HEIGHT (PASSPORT_CORNER_PHOTO_HEIGHT + 2)
// These prebuilt assets use PP_X=30, PP_Y=38, and spacing 44x50.
// Keep the prebuilt frame assets aligned with the layout coordinates.
#define PASSPORT_BG_BOTTOM_ROW ((PP_Y - PASSPORT_FRAME_HEIGHT / 2 + PP_DELTA_Y) / 8)

EWRAM_DATA static const u16 *sPassportTilemap = NULL;
EWRAM_DATA static bool8 sPassportMapPending = FALSE;
EWRAM_DATA static bool8 sPassportShowSkins = FALSE;
EWRAM_DATA static bool8 sPassportCornerPending = FALSE;

static void CopyPassportCornerToVram(void);

static void VBlankCB_KukuiCall(void)
{
    sLastVCount = -1;

    if (sPassportMapPending && sPassportTilemap != NULL)
    {
        DmaCopy16(3, sPassportTilemap, BG_SCREEN_ADDR(ROCKRUFF_SCREEN_INDEX), 32 * 32 * sizeof(u16));
        if (!sPassportShowSkins)
            DmaFill16(3, PASSPORT_BG_BLANK_INDEX | (PASSPORT_BG_PALETTE << 12),
                      BG_SCREEN_ADDR(ROCKRUFF_SCREEN_INDEX) + PASSPORT_BG_BOTTOM_ROW * 32 * sizeof(u16),
                      (32 - PASSPORT_BG_BOTTOM_ROW) * 32 * sizeof(u16));
        sPassportMapPending = FALSE;
        ShowBg(0);
    }
    if (sPassportCornerPending)
    {
        CopyPassportCornerToVram();
        sPassportCornerPending = FALSE;
    }
    UpdateLayerFade();

    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

#define TEXT_BG_TRANS 10
#define TEXT_BG_START (112 - 1)
STATIC_ASSERT(PS_Y + PASSPORT_CORNER_FRAME_HEIGHT / 2 <= TEXT_BG_START, CornerFrameAboveDialogueBlend);

static void HBlankCB_KukuiCall(void)
{
    u16 vCount = REG_VCOUNT;

    if (vCount >= TEXT_BG_START && vCount < 160)
    {
        sShouldUpdateLayerFade = TRUE;

        s16 blend = (((TEXT_BG_START + TEXT_BG_TRANS) - vCount) * TEXT_BG_TRANS) / ((TEXT_BG_START + TEXT_BG_TRANS) - TEXT_BG_START);
        if (blend < 0) blend = 0;
        blend += (16 - TEXT_BG_TRANS);
        REG_BLDCNT = BLDCNT_TGT1_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND;
        REG_BLDALPHA = BLDALPHA_BLEND(16 - blend, blend);
    }
    else if (sShouldUpdateLayerFade)
    {
        sShouldUpdateLayerFade = FALSE;
        if (sShouldChopRockruff)
        {
            REG_BLDCNT = BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND;
            REG_BLDALPHA = BLDALPHA_BLEND(0, 16);
        }
        else
            UpdateLayerFadeRegs();
    }
}

// For loading a new mapping for a pre-loaded tileset (such as shifting the image)
static void LoadTilemapAtOffset(u8 bgId, u16 tilesOffset, u8 charBaseIndex, const u32 *tilemap, u8 tilemapHeight, u16 screenIndex, u16 palOffset)
{
    DecompressDataWithHeaderVram(tilemap, (u8 *)(BG_SCREEN_ADDR(screenIndex)));

    for(u16 i = 0; i < (32 * tilemapHeight); i++)
    {
        u16 * tilemapPtr = (u16 *)(BG_SCREEN_ADDR(screenIndex));
        u16 tileIndex = tilemapPtr[i] & 0x03FF;
        tileIndex += tilesOffset - (charBaseIndex * 0x200);
        tilemapPtr[i] = (tilemapPtr[i] & 0x0C00) | tileIndex | (palOffset << 12);
    }
    
    SetBgAttribute(bgId, BG_ATTR_CHARBASEINDEX, charBaseIndex);
    SetBgAttribute(bgId, BG_ATTR_MAPBASEINDEX, screenIndex);
}

// For loading a new image with a pre-loaded palette (such as swapping between frames of the same animated subject)
static void LoadTilesAndMapAtOffset(u8 bgId, const u32 *tiles, u16 tilesOffset, u8 charBaseIndex, const u32 *tilemap, u8 tilemapHeight, u16 screenIndex, u16 palOffset)
{
    DecompressDataWithHeaderVram(tiles, (u8 *)VRAM + (TILE_SIZE_4BPP * tilesOffset));
    LoadTilemapAtOffset(bgId, tilesOffset, charBaseIndex, tilemap, tilemapHeight, screenIndex, palOffset);
}

// For loading a new image wholesale - new tiles near start of VRAM, new tilemap near end of VRAM, and a new palette
static void LoadTilesMapAndPalAtOffset(u8 bgId, const u32 *tiles, u16 tilesOffset, u8 charBaseIndex, const u32 *tilemap, u8 tilemapHeight, u16 screenIndex, const void* pal, u16 palOffset, bool8 unfade)
{
    LoadTilesAndMapAtOffset(bgId, tiles, tilesOffset, charBaseIndex, tilemap, tilemapHeight, screenIndex, palOffset);

    FastUnsafeCopy32(&gPlttBufferUnfaded[BG_PLTT_ID(palOffset)], pal, PLTT_SIZE_4BPP);

    if (unfade)
        FastUnsafeCopy32(&gPlttBufferFaded[BG_PLTT_ID(palOffset)], pal, PLTT_SIZE_4BPP);
}

static void CopyPartialTilemap(u32 dstScreen, u32 srcScreen, u8 startHeight, u8 rows)
{
    FastUnsafeCopy32((u8 *)(BG_SCREEN_ADDR(dstScreen) + (32 * startHeight * 2)), (u8 *)(BG_SCREEN_ADDR(srcScreen) + (32 * startHeight * 2)), rows * 32 * 2);
}

static void ShowTextBoxBackground(void)
{
    DmaFill16(3, (TEXT_BG_TILE - 0x200) | (0xF << 12), BG_SCREEN_ADDR(CALL_BG_1_SCREEN_INDEX) + (32 * 14 * 2), 6 * 32 * 2);
    DmaFill16(3, (TEXT_BG_TILE - 0x200) | (0xF << 12), BG_SCREEN_ADDR(CALL_BG_2_SCREEN_INDEX) + (32 * 14 * 2), 6 * 32 * 2);
}

static void HideTextBoxBackground(void)
{
    DmaFill16(3, (BLANK_TILE_2 - 0x200) | (0xF << 12), BG_SCREEN_ADDR(CALL_BG_1_SCREEN_INDEX) + (32 * 14 * 2), 6 * 32 * 2);
    DmaFill16(3, (BLANK_TILE_2 - 0x200) | (0xF << 12), BG_SCREEN_ADDR(CALL_BG_2_SCREEN_INDEX) + (32 * 14 * 2), 6 * 32 * 2);
}

static void AddTextPrinterForMessageKukui(bool8 allowSkippingDelayWithButtonPress)
{
    gTextFlags.canABSpeedUpPrint = allowSkippingDelayWithButtonPress;
    AddTextPrinterParameterized2(0, FONT_NORMAL, gStringVar4, GetPlayerTextSpeedDelay(), NULL, TEXT_COLOR_LIGHT_GRAY, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY);
}

#pragma endregion

// One of six sprites that make up the Call Window Border
EWRAM_DATA static u8 sCallWindowCornerNWSpriteId, sCallWindowEdgeNSpriteId, sCallWindowCornerNESpriteId, sCallWindowCornerSESpriteId, sCallWindowEdgeSSpriteId, sCallWindowCornerSWSpriteId;
// The sprite for the Call Window UI (top bar + buttons)
EWRAM_DATA static u8 sCallWindowUISpriteId;
// The sprite for the Cursor when selecting a Passport Photo
EWRAM_DATA static u8 sArrowCursorSpriteId;
// One of four sprites representing the four possible character models
EWRAM_DATA static u8 sPassportSkinModel = 0;
EWRAM_DATA static bool8 sPassportBackdropActive = FALSE;
EWRAM_DATA static u8 sPhotoPlaceholderM1SpriteId, sPhotoPlaceholderM2SpriteId, sPhotoPlaceholderF1SpriteId, sPhotoPlaceholderF2SpriteId;
// One of four sprites representing the four possible palettes for a given character model
EWRAM_DATA static u8 sPhotoPlaceholderASpriteId, sPhotoPlaceholderBSpriteId, sPhotoPlaceholderCSpriteId, sPhotoPlaceholderDSpriteId;

#define tTimer                       data[0] // used for tracking the number of frames passed
#define tState                       data[1] // used for tracking the current state of the given task
#define tFreeKukuiBaseTileNum        data[2] // the currently unused base tile num for Kukui Tiles
#define tFreeCallBgBaseTileNum       data[3] // the currently unused base tile num for Call Background Tiles
#define tFreeKukuiScreenIndex        data[4] // the currently unused screen index for Kukui Tilemap
#define tFreeCallBgScreenIndex       data[5] // the currently unused screen index for Call Background Tilemap
#define tSettingsIconSpriteId        data[6]
#define tCameraIconSpriteId          data[7]
#define tNotificationIconSpriteId    data[8]
#define tVideoIconSpriteId           data[9]
#define tCallWindowScalable0SpriteId data[10] // the Top-Left of four identical sprites that move and scale in tandem to appear as one
#define tCallWindowScalable1SpriteId data[11] // the Top-Right of four identical sprites that move and scale in tandem to appear as one
#define tCallWindowScalable2SpriteId data[12] // the Bottom-Right of four identical sprites that move and scale in tandem to appear as one
#define tCallWindowScalable3SpriteId data[13] // the Bottom-Left of four identical sprites that move and scale in tandem to appear as one
#define tModelSelect                 data[14] // the currently selected index of the four character models
#define tPaletteSelect               data[15] // the currently selected index of the four character palettes

#define SETTINGS_ICON gSprites[gTasks[taskId].tSettingsIconSpriteId]
#define CAMERA_ICON gSprites[gTasks[taskId].tCameraIconSpriteId]
#define NOTIFICATION_ICON gSprites[gTasks[taskId].tNotificationIconSpriteId]
#define VIDEO_ICON gSprites[gTasks[taskId].tVideoIconSpriteId]
#define SW0 gSprites[gTasks[taskId].tCallWindowScalable0SpriteId]
#define SW1 gSprites[gTasks[taskId].tCallWindowScalable1SpriteId]
#define SW2 gSprites[gTasks[taskId].tCallWindowScalable2SpriteId]
#define SW3 gSprites[gTasks[taskId].tCallWindowScalable3SpriteId]
#define CW_NW gSprites[sCallWindowCornerNWSpriteId]
#define CW_N gSprites[sCallWindowEdgeNSpriteId]
#define CW_NE gSprites[sCallWindowCornerNESpriteId]
#define CW_SE gSprites[sCallWindowCornerSESpriteId]
#define CW_S gSprites[sCallWindowEdgeSSpriteId]
#define CW_SW gSprites[sCallWindowCornerSWSpriteId]
#define CW_UI gSprites[sCallWindowUISpriteId]
#define CURSOR gSprites[sArrowCursorSpriteId]
#define PP_M1 gSprites[sPhotoPlaceholderM1SpriteId]
#define PP_M2 gSprites[sPhotoPlaceholderM2SpriteId]
#define PP_F1 gSprites[sPhotoPlaceholderF1SpriteId]
#define PP_F2 gSprites[sPhotoPlaceholderF2SpriteId]
#define PP_A gSprites[sPhotoPlaceholderASpriteId]
#define PP_B gSprites[sPhotoPlaceholderBSpriteId]
#define PP_C gSprites[sPhotoPlaceholderCSpriteId]
#define PP_D gSprites[sPhotoPlaceholderDSpriteId]

#define SETTINGS_X 213
#define SETTINGS_Y 57
#define CAMERA_X SETTINGS_X
#define CAMERA_Y 36
#define NOTIFICATION_X (VIDEO_X + 9)
#define NOTIFICATION_Y (VIDEO_Y - 6)
#define VIDEO_X SETTINGS_X
#define VIDEO_Y 15

#define SW_WIDTH 23
#define SW_START_X 213
#define SW_END_X 96
#define SW_DELTA_X (SW_END_X - SW_START_X)

#define SW_HEIGHT 14
#define SW_START_Y 15
#define SW_END_Y 52
#define SW_DELTA_Y (SW_END_Y - SW_START_Y)

#define CW_X 32
#define CW_DELTA_X 64
#define CW_Y 32
#define CW_DELTA_Y 56
#define CW_EDGE_Y (CW_Y / 2)
#define CW_EDGE_DELTA_Y (CW_Y + CW_DELTA_Y)

#define CW_UI_X (CW_X + 2*CW_DELTA_X - 8)
#define CW_UI_Y CW_EDGE_Y

#define CURSOR_X 8
#define CURSOR_DELTA_X 44
#define CURSOR_Y 30
#define CURSOR_DELTA_Y 50

#define GAC_DELAY 60 // Task_GettingACall # frames delay before first ring

void CB2_NewGameKukuiCall_FromNewMainMenu(void)
{
    sPassportCornerPending = FALSE;
    sPassportBackdropActive = FALSE;
    sPassportSkinModel = 0xFF;
    sPassportMapPending = FALSE;
    sPassportTilemap = NULL;
    ResetBgsAndClearDma3BusyFlags(0);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    DmaFill16(3, 0, VRAM, VRAM_SIZE);
    DmaFill32(3, 0, OAM, OAM_SIZE);
    DmaFill16(3, 0, PLTT, PLTT_SIZE);
    DmaFill16(3, BLANK_TILE_2 - 0x200, BG_SCREEN_ADDR(CALL_BG_1_SCREEN_INDEX), 0x800);
    DmaFill16(3, BLANK_TILE_2 - 0x200, BG_SCREEN_ADDR(CALL_BG_2_SCREEN_INDEX), 0x800);
    ResetPaletteFade();

    LoadTilesMapAndPalAtOffset(3, sComputer_Background_Tiles, PC_BG_BASE_TILE_NUM, 0, sComputer_Background_Tilemap, PC_BG_HEIGHT, PC_BG_SCREEN_INDEX, sComputer_Background_Pals, 0, TRUE);
    LoadTilemapAtOffset(0, PC_BG_BASE_TILE_NUM, 0, sComputer_Background_Tilemap_Top, PC_BG_HEIGHT, PC_BG_TOP_SCREEN_INDEX, 0);

    ResetTasks();
    u8 taskId = CreateTask(Task_GettingACall, 0);
    gTasks[taskId].tFreeKukuiBaseTileNum  = KUKUI_2_BASE_TILE_NUM;
    gTasks[taskId].tFreeCallBgBaseTileNum = CALL_BG_2_BASE_TILE_NUM;
    gTasks[taskId].tFreeKukuiScreenIndex  = KUKUI_2_SCREEN_INDEX;
    gTasks[taskId].tFreeCallBgScreenIndex = CALL_BG_2_SCREEN_INDEX;
    gTasks[taskId].tTimer = -GAC_DELAY;
    gTasks[taskId].tState = 0;

    ScanlineEffect_Stop();
    ResetSpriteData();
    FreeAllSpritePalettes();
    AddComputerBackgroundObjects(taskId);

    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
    SetGpuReg(REG_OFFSET_BLDY, 0);

    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
    sLastVCount = -1;
    sLayerFadeActive = FALSE;
    sShouldLayerFade = FALSE; 
    sShouldChopRockruff = FALSE;
    sShouldUpdateLayerFade = TRUE;
    sLayerFadeY = 0;
    SetHBlankCallback(HBlankCB_KukuiCall);
    SetVBlankCallback(VBlankCB_KukuiCall);
    EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_HBLANK);
    SetMainCallback2(CB2_KukuiCall);
    InitWindows(sNewGameKukuiCallTextWindows);
    DmaFill32(3, 0xFFFFFFFF, BG_VRAM + (8 * 8 / 2) * TEXT_BG_TILE, 8 * 8 / 2);
    // LoadMessageBoxGfx(0, BIRCH_DLG_BASE_TILE_NUM, BG_PLTT_ID(15));
    LoadPalette(sMainMenuTextPal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void AddComputerBackgroundObjects(u8 taskId)
{
    LoadCompressedSpriteSheet(&sSettings_Icon_SpriteSheet);
    LoadCompressedSpriteSheet(&sCamera_Icon_SpriteSheet);
    LoadCompressedSpriteSheet(&sNotification_Icon_SpriteSheet);
    LoadCompressedSpriteSheetByTemplate(&sVideo_Icon_SpriteTemplate, 0);

    LoadCompressedSpriteSheet(&sCall_Window_Corner_SpriteSheet);
    LoadCompressedSpriteSheet(&sCall_Window_Edge_SpriteSheet);
    LoadCompressedSpriteSheet(&sCall_Window_UI_SpriteSheet);
    LoadCompressedSpriteSheet(&sCall_Window_Scalable_SpriteSheet);

    LoadSpritePalette(&sSettings_Icon_SpritePalette);
    gTasks[taskId].tSettingsIconSpriteId = CreateSprite(&sSettings_Icon_SpriteTemplate, SETTINGS_X, SETTINGS_Y, 1);
    SETTINGS_ICON.oam.priority = 2;
    SETTINGS_ICON.invisible = FALSE;
    
    LoadSpritePalette(&sCamera_Icon_SpritePalette);
    gTasks[taskId].tCameraIconSpriteId = CreateSprite(&sCamera_Icon_SpriteTemplate, CAMERA_X, CAMERA_Y, 1);
    CAMERA_ICON.oam.priority = 2;
    CAMERA_ICON.invisible = FALSE;

    LoadSpritePalette(&sNotification_Icon_SpritePalette);
    gTasks[taskId].tNotificationIconSpriteId = CreateSprite(&sNotification_Icon_SpriteTemplate, NOTIFICATION_X, NOTIFICATION_Y, 1);
    NOTIFICATION_ICON.oam.priority = 0;
    NOTIFICATION_ICON.invisible = TRUE;

    LoadSpritePalette(&sVideo_Icon_SpritePalette);
    gTasks[taskId].tVideoIconSpriteId = CreateSprite(&sVideo_Icon_SpriteTemplate, VIDEO_X, VIDEO_Y, 1);
    VIDEO_ICON.oam.priority = 1;
    VIDEO_ICON.invisible = FALSE;

    LoadSpritePalette(&sCall_Window_SpritePalette);

    sCallWindowCornerNWSpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X,                CW_Y,                        1);
    sCallWindowEdgeNSpriteId    = CreateSprite(&sCall_Window_Edge_SpriteTemplate,   CW_X + CW_DELTA_X,   CW_EDGE_Y,                   1);
    sCallWindowCornerNESpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X + 2*CW_DELTA_X, CW_Y,                        1);
    sCallWindowCornerSESpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X + 2*CW_DELTA_X, CW_Y + CW_DELTA_Y,           1);
    sCallWindowEdgeSSpriteId    = CreateSprite(&sCall_Window_Edge_SpriteTemplate,   CW_X + CW_DELTA_X,   CW_EDGE_Y + CW_EDGE_DELTA_Y, 1);
    sCallWindowCornerSWSpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X,                CW_Y + CW_DELTA_Y,           1);

    SetSpriteOamFlipBits(&CW_NE, TRUE,  FALSE);
    SetSpriteOamFlipBits(&CW_SE, TRUE,  TRUE);
    SetSpriteOamFlipBits(&CW_S,  FALSE, TRUE);
    SetSpriteOamFlipBits(&CW_SW, FALSE, TRUE);

    CW_NW.oam.priority = CW_N.oam.priority = CW_NE.oam.priority = CW_SE.oam.priority = CW_S.oam.priority = CW_SW.oam.priority = 1;
    CW_NW.invisible = CW_N.invisible = CW_NE.invisible = CW_SE.invisible = CW_S.invisible = CW_SW.invisible = TRUE;

    sCallWindowUISpriteId = CreateSprite(&sCall_Window_UI_SpriteTemplate, CW_UI_X, CW_UI_Y, 1);
    CW_UI.oam.priority = 0;
    CW_UI.invisible = TRUE;

    gTasks[taskId].tCallWindowScalable0SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_START_X, SW_START_Y, 1);
    gTasks[taskId].tCallWindowScalable1SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_START_X, SW_START_Y, 1);
    gTasks[taskId].tCallWindowScalable2SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_START_X, SW_START_Y, 1);
    gTasks[taskId].tCallWindowScalable3SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_START_X, SW_START_Y, 1);
    SW0.oam.priority = SW1.oam.priority = SW2.oam.priority = SW3.oam.priority = 0;
    SW0.oam.matrixNum = SW1.oam.matrixNum = SW2.oam.matrixNum = SW3.oam.matrixNum = AllocOamMatrix();
    SW0.invisible = SW1.invisible = SW2.invisible = SW3.invisible = TRUE;

    SetOamMatrixRotationScaling(SW0.oam.matrixNum, 10, 10, 0);
}

static const u16 sPassportFrameTiles[] = INCBIN_U16("graphics/kukui_call/icons/passport_frames.4bpp");
static const u16 sPassportFrameTilemap[] = INCBIN_U16("graphics/kukui_call/icons/passport_frames.bin");
static const u16 sPassportCornerTilemap[] = INCBIN_U16("graphics/kukui_call/icons/passport_corner.bin");
STATIC_ASSERT(PASSPORT_BG_BASE_TILE * TILE_SIZE_4BPP + sizeof(sPassportFrameTiles) <= PASSPORT_BG_BLANK_TILE * TILE_SIZE_4BPP, PassportFramesFitReservedVram);
static const u16 sPassportBackdropPalette[] = INCGFX_U16("graphics/ui_main_menu/sm/mugshot_BG.png", ".gbapal");

static void DrawPassportBackgrounds(bool32 showSkins)
{
    sPassportShowSkins = showSkins;
    sPassportMapPending = TRUE;
}

static void LoadPassportFrameGraphics(void)
{
    u16 palette[16];

    DmaCopy16(3, sPassportFrameTiles, BG_VRAM + PASSPORT_BG_BASE_TILE * TILE_SIZE_4BPP, sizeof(sPassportFrameTiles));
    DmaFill16(3, 0, BG_VRAM + PASSPORT_BG_BLANK_TILE * TILE_SIZE_4BPP, TILE_SIZE_4BPP);
    CpuCopy16(sPassportBackdropPalette, palette, sizeof(palette));
    palette[4] = RGB(3, 5, 9);
    LoadPalette(palette, BG_PLTT_ID(PASSPORT_BG_PALETTE), sizeof(palette));
}

static void CopyPassportCornerToVram(void)
{
    u32 row;
    const u32 left = (PS_X - PASSPORT_FRAME_WIDTH / 2) / 8;
    const u32 top = (PS_Y - PASSPORT_CORNER_FRAME_HEIGHT / 2) / 8;
    const u32 right = (PS_X + PASSPORT_FRAME_WIDTH / 2 + 7) / 8;
    const u32 bottom = (PS_Y + PASSPORT_CORNER_FRAME_HEIGHT / 2 + 7) / 8;

    // BG2 remains the call backdrop when BG0 is reused for Rockruff.
    // Patch both alternating maps without touching the call or dialogue area.
    for (row = top; row < bottom; row++)
    {
        u32 offset = (row * 32 + left) * sizeof(u16);
        DmaCopy16(3, sPassportCornerTilemap + row * 32 + left,
                  BG_SCREEN_ADDR(CALL_BG_1_SCREEN_INDEX) + offset, (right - left) * sizeof(u16));
        DmaCopy16(3, sPassportCornerTilemap + row * 32 + left,
                  BG_SCREEN_ADDR(CALL_BG_2_SCREEN_INDEX) + offset, (right - left) * sizeof(u16));
    }
}

static void InitPassportBackgrounds(void)
{
    sPassportTilemap = sPassportFrameTilemap;
    LoadPassportFrameGraphics();
    SetBgAttribute(0, BG_ATTR_CHARBASEINDEX, PASSPORT_BG_CHARBASE);
    SetBgAttribute(0, BG_ATTR_MAPBASEINDEX, ROCKRUFF_SCREEN_INDEX);
    SetBgAttribute(0, BG_ATTR_SCREENSIZE, 0);
    SetBgAttribute(0, BG_ATTR_PALETTEMODE, 0);
    SetBgAttribute(0, BG_ATTR_PRIORITY, 2);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    sPassportBackdropActive = TRUE;
    DrawPassportBackgrounds(FALSE);
}

// M2/F2 use teal until their replacement character art is ready.
static const u8 sPhotoOutfits[] = { DEFAULT_OUTFIT, OUTFIT_TEAL, DEFAULT_OUTFIT, OUTFIT_GREEN };

static void LoadPassportMugshot(u8 model, u8 skin, u16 tag, u8 paletteNum, u32 height)
{
    u16 tiles[64 * 64 / 4] = {0};
    const u8 *src = GetOutfitMugshot(sPhotoOutfits[model], model < 2 ? MALE : FEMALE, skin, GFX);
    struct SpriteSheet sheet = { tiles, sizeof(tiles), tag };
    u32 x, y;
    u8 *dest = (u8 *)tiles;

    // Keep the original pixels and crop to the selected frame height.
    for (y = 0; y < height; y++)
    {
        u32 sourceY = y + (48 - height) / 2;
        u32 sy = y + (64 - height) / 2;
        for (x = 0; x < PASSPORT_PHOTO_WIDTH; x += 2)
        {
            u32 sourceX = x + (48 - PASSPORT_PHOTO_WIDTH) / 2;
            u32 sx = x + (64 - PASSPORT_PHOTO_WIDTH) / 2;
            u32 srcOffset = ((sourceY / 8) * 6 + sourceX / 8) * TILE_SIZE_4BPP
                          + (sourceY % 8) * 4 + (sourceX % 8) / 2;
            u32 offset = ((sy / 8) * 8 + sx / 8) * TILE_SIZE_4BPP + (sy % 8) * 4 + (sx % 8) / 2;
            u8 pixels = src[srcOffset];

            if (x == 0 || x == PASSPORT_PHOTO_WIDTH - 2)
            {
                if (y == 0 || y == height - 1)
                    pixels = 0;
                else if (y == 1 || y == height - 2)
                    pixels &= x == 0 ? 0xF0 : 0x0F;
            }
            dest[offset] = pixels;
        }
    }
    FreeSpriteTilesByTag(tag);
    LoadSpriteSheet(&sheet);
    LoadPalette(GetOutfitMugshot(sPhotoOutfits[model], model < 2 ? MALE : FEMALE, skin, PAL), OBJ_PLTT_ID(paletteNum), PLTT_SIZE_4BPP);
}

static void LoadPassportSkinChoices(u8 model)
{
    u8 i;
    u8 ids[] = { sPhotoPlaceholderASpriteId, sPhotoPlaceholderBSpriteId, sPhotoPlaceholderCSpriteId, sPhotoPlaceholderDSpriteId };

    if (sPassportSkinModel == model)
        return;
    sPassportSkinModel = model;

    for (i = 0; i < OUTFIT_SKIN_COUNT; i++)
    {
        LoadPassportMugshot(model, i, 0x1010 + i, 12 + i, PASSPORT_PHOTO_HEIGHT);
        gSprites[ids[i]].oam.tileNum = GetSpriteTileStartByTag(0x1010 + i);
    }
}

static void AddComputerBackgroundObjects_ReturnFromNamingScreen(u8 taskId)
{
    LoadCompressedSpriteSheet(&sSettings_Icon_SpriteSheet);
    LoadCompressedSpriteSheet(&sCamera_Icon_SpriteSheet);
    LoadCompressedSpriteSheet(&sNotification_Icon_SpriteSheet);
    LoadCompressedSpriteSheetByTemplate(&sVideo_Icon_SpriteTemplate, 0);

    LoadCompressedSpriteSheet(&sCall_Window_Corner_SpriteSheet);
    LoadCompressedSpriteSheet(&sCall_Window_Edge_SpriteSheet);
    LoadCompressedSpriteSheet(&sCall_Window_UI_SpriteSheet);
    LoadCompressedSpriteSheet(&sCall_Window_Scalable_SpriteSheet);

    u8 model = gSaveBlock2Ptr->playerGender == FEMALE ? 2 : 0;
    if (gSaveBlock2Ptr->currOutfitId == sPhotoOutfits[model + 1])
        model++;
    LoadPassportMugshot(model, gSaveBlock2Ptr->currOutfitPalette, GFX_TAG_PHOTO_PLACEHOLDER_M1, 12, PASSPORT_CORNER_PHOTO_HEIGHT);

    LoadSpritePalette(&sSettings_Icon_SpritePalette);
    gTasks[taskId].tSettingsIconSpriteId = CreateSprite(&sSettings_Icon_SpriteTemplate, SETTINGS_X, SETTINGS_Y, 1);
    SETTINGS_ICON.oam.priority = 1;
    SETTINGS_ICON.invisible = FALSE;
    
    LoadSpritePalette(&sCamera_Icon_SpritePalette);
    gTasks[taskId].tCameraIconSpriteId = CreateSprite(&sCamera_Icon_SpriteTemplate, CAMERA_X, CAMERA_Y, 1);
    CAMERA_ICON.oam.priority = 1;
    CAMERA_ICON.invisible = FALSE;

    LoadSpritePalette(&sNotification_Icon_SpritePalette);
    gTasks[taskId].tNotificationIconSpriteId = CreateSprite(&sNotification_Icon_SpriteTemplate, NOTIFICATION_X, NOTIFICATION_Y, 1);
    NOTIFICATION_ICON.oam.priority = 0;
    NOTIFICATION_ICON.invisible = FALSE;

    LoadSpritePalette(&sVideo_Icon_SpritePalette);
    gTasks[taskId].tVideoIconSpriteId = CreateSprite(&sVideo_Icon_SpriteTemplate, VIDEO_X, VIDEO_Y, 1);
    VIDEO_ICON.oam.priority = 1;
    VIDEO_ICON.invisible = FALSE;

    sPhotoPlaceholderM1SpriteId = CreateSprite(&sPhoto_Placeholder_M1_SpriteTemplate, PS_X, PS_Y, 1);

    PP_M1.oam.paletteNum = 12;
    PP_M1.oam.priority = 1;
    PP_M1.invisible = TRUE;

    LoadSpritePalette(&sCall_Window_SpritePalette);

    sCallWindowCornerNWSpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X,                CW_Y,                        1);
    sCallWindowEdgeNSpriteId    = CreateSprite(&sCall_Window_Edge_SpriteTemplate,   CW_X + CW_DELTA_X,   CW_EDGE_Y,                   1);
    sCallWindowCornerNESpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X + 2*CW_DELTA_X, CW_Y,                        1);
    sCallWindowCornerSESpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X + 2*CW_DELTA_X, CW_Y + CW_DELTA_Y,           1);
    sCallWindowEdgeSSpriteId    = CreateSprite(&sCall_Window_Edge_SpriteTemplate,   CW_X + CW_DELTA_X,   CW_EDGE_Y + CW_EDGE_DELTA_Y, 1);
    sCallWindowCornerSWSpriteId = CreateSprite(&sCall_Window_Corner_SpriteTemplate, CW_X,                CW_Y + CW_DELTA_Y,           1);

    SetSpriteOamFlipBits(&CW_NE, TRUE,  FALSE);
    SetSpriteOamFlipBits(&CW_SE, TRUE,  TRUE);
    SetSpriteOamFlipBits(&CW_S,  FALSE, TRUE);
    SetSpriteOamFlipBits(&CW_SW, FALSE, TRUE);

    CW_NW.oam.priority = CW_N.oam.priority = CW_NE.oam.priority = CW_SE.oam.priority = CW_S.oam.priority = CW_SW.oam.priority = 1;
    CW_NW.invisible = CW_N.invisible = CW_NE.invisible = CW_SE.invisible = CW_S.invisible = CW_SW.invisible = FALSE;

    sCallWindowUISpriteId = CreateSprite(&sCall_Window_UI_SpriteTemplate, CW_UI_X, CW_UI_Y, 1);
    CW_UI.oam.priority = 0;
    CW_UI.invisible = FALSE;

    gTasks[taskId].tCallWindowScalable0SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_END_X, SW_END_Y, 1);
    gTasks[taskId].tCallWindowScalable1SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_END_X, SW_END_Y, 1);
    gTasks[taskId].tCallWindowScalable2SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_END_X, SW_END_Y, 1);
    gTasks[taskId].tCallWindowScalable3SpriteId = CreateSpriteAtEnd(&sCall_Window_Scalable_SpriteTemplate, SW_END_X, SW_END_Y, 1);
    SW0.oam.priority = SW1.oam.priority = SW2.oam.priority = SW3.oam.priority = 0;
    SW0.oam.matrixNum = SW1.oam.matrixNum = SW2.oam.matrixNum = SW3.oam.matrixNum = AllocOamMatrix();
    SW0.invisible = SW1.invisible = SW2.invisible = SW3.invisible = TRUE;

    SW0.x2 = SW1.x2 = SW2.x2 = SW3.x2 = SW_END_X - 5;
    SW0.y2 = SW1.y2 = SW2.y2 = SW3.y2 = SW_END_Y - 2;

    SW0.x = SW3.x = -SW_WIDTH;
    SW1.x = SW2.x = 3*SW_WIDTH;

    SW0.y = SW1.y = -SW_HEIGHT;
    SW2.y = SW3.y = 3*SW_HEIGHT;

    SetOamMatrixRotationScaling(SW0.oam.matrixNum, 0x200, 0x200, 0);
}

static void LoadComputerPassportPhotos(u8 taskId)
{
    FreeSpriteOamMatrix(&SW0);

    FreeSpriteTiles(&SW0);
    DestroySprite(&SW0);
    FreeSpriteTiles(&SW1);
    DestroySprite(&SW1);
    FreeSpriteTiles(&SW2);
    DestroySprite(&SW2);
    FreeSpriteTiles(&SW3);
    DestroySprite(&SW3);

    u8 i;
    for (i = 0; i < ARRAY_COUNT(sPhotoOutfits); i++)
        LoadPassportMugshot(i, i, GFX_TAG_PHOTO_PLACEHOLDER_M1 + i, 8 + i, PASSPORT_PHOTO_HEIGHT);
    LoadCompressedSpriteSheet(&sArrowCursor_SpriteSheet);

    LoadSpritePalette(&sArrowCursor_SpritePalette);

    sArrowCursorSpriteId = CreateSprite(&sArrowCursor_SpriteTemplate, CURSOR_X, CURSOR_Y, 1);
    CURSOR.oam.priority = 1;
    CURSOR.invisible = TRUE;


    sPhotoPlaceholderM1SpriteId = CreateSprite(&sPhoto_Placeholder_M1_SpriteTemplate, PP_X,                PP_Y, 1);
    sPhotoPlaceholderM2SpriteId = CreateSprite(&sPhoto_Placeholder_M2_SpriteTemplate, PP_X + PP_DELTA_X,   PP_Y, 1);
    sPhotoPlaceholderF1SpriteId = CreateSprite(&sPhoto_Placeholder_F1_SpriteTemplate, PP_X + 2*PP_DELTA_X, PP_Y, 1);
    sPhotoPlaceholderF2SpriteId = CreateSprite(&sPhoto_Placeholder_F2_SpriteTemplate, PP_X + 3*PP_DELTA_X, PP_Y, 1);
    sPhotoPlaceholderASpriteId  = CreateSprite(&sPhoto_Placeholder_M1_SpriteTemplate, PP_X,                PP_Y + PP_DELTA_Y, 1);
    sPhotoPlaceholderBSpriteId  = CreateSprite(&sPhoto_Placeholder_M1_SpriteTemplate, PP_X + PP_DELTA_X,   PP_Y + PP_DELTA_Y, 1);
    sPhotoPlaceholderCSpriteId  = CreateSprite(&sPhoto_Placeholder_M1_SpriteTemplate, PP_X + 2*PP_DELTA_X, PP_Y + PP_DELTA_Y, 1);
    sPhotoPlaceholderDSpriteId  = CreateSprite(&sPhoto_Placeholder_M1_SpriteTemplate, PP_X + 3*PP_DELTA_X, PP_Y + PP_DELTA_Y, 1);

    LoadPassportSkinChoices(0);
    PP_M1.oam.paletteNum = 8;
    PP_M2.oam.paletteNum = 9;
    PP_F1.oam.paletteNum = 10;
    PP_F2.oam.paletteNum = 11;
    PP_A.oam.paletteNum = 12;
    PP_B.oam.paletteNum = 13;
    PP_C.oam.paletteNum = 14;
    PP_D.oam.paletteNum = 15;
    PP_M1.oam.priority = PP_M2.oam.priority = PP_F1.oam.priority = PP_F2.oam.priority = PP_A.oam.priority = PP_B.oam.priority = PP_C.oam.priority = PP_D.oam.priority = 1;
    PP_M1.invisible = PP_M2.invisible = PP_F1.invisible = PP_F2.invisible = PP_A.invisible = PP_B.invisible = PP_C.invisible = PP_D.invisible = TRUE;
}

#define GAC_RING_LENGTH 20 // Task_GettingACall # frames between each ring
#define GAC_SE_CUTOFF 15 // Task_GettingACall # frames ring SE gets cut off after
#define GAC_NUM_RINGS 3 // Task_GettingACall # rings per ringtone loop
#define GAC_LOOP_LENGTH (GAC_NUM_RINGS * GAC_RING_LENGTH + GAC_DELAY) // Task_GettingACall total # frames per ringtone loop
#define GAC_NUM_LOOPS 2 // Task_GettingACall # ringtone loops to complete before printing text

#define LC_DELAY 30 // Task_LaunchCall # frames delay before launch sequence

static void Task_GettingACall(u8 taskId)
{
    if (gTasks[taskId].tTimer != GAC_LOOP_LENGTH)
    {
        if (   gTasks[taskId].tTimer == 0 * GAC_RING_LENGTH  // first ring
            || gTasks[taskId].tTimer == 1 * GAC_RING_LENGTH  // second ring
            || gTasks[taskId].tTimer == 2 * GAC_RING_LENGTH) // third ring
        {
            StartSpriteAnim(&gSprites[gTasks[taskId].tVideoIconSpriteId], 1);
            PlaySE(SE_POKENAV_CALL);
        }
        if (   gTasks[taskId].tTimer == 0 * GAC_RING_LENGTH + GAC_SE_CUTOFF
            || gTasks[taskId].tTimer == 1 * GAC_RING_LENGTH + GAC_SE_CUTOFF
            || gTasks[taskId].tTimer == 2 * GAC_RING_LENGTH + GAC_SE_CUTOFF)
        {
            m4aSongNumStop(SE_POKENAV_CALL);
        }

        gTasks[taskId].tTimer++;
    }
    else
    {
        if (gTasks[taskId].tState <= GAC_NUM_LOOPS)
            gTasks[taskId].tState++;

        if (gTasks[taskId].tState == GAC_NUM_LOOPS)
        {
            // Print text and enable user input at start of third ringtone loop
            ShowTextBoxBackground();
            StringExpandPlaceholders(gStringVar4, gText_Kukui_YouHaveACall);
            AddTextPrinterForMessageKukui(TRUE);
        }
        
        gTasks[taskId].tTimer = 0; // replay the ringtone until user input
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState > GAC_NUM_LOOPS)
    {
        HideTextBoxBackground();
        gTasks[taskId].tTimer = -LC_DELAY;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_LaunchCall;
    }
}

static bool8 sShouldMosaic;

#define LC_ANIM_LENGTH 15 // Task_LaunchCall # frames duration of Video App Icon animation
#define LC_SCALE_LENGTH 20 // Task_LaunchCall # frames duration of Scalable animation 
#define LC_LAUNCH_LENGTH (LC_ANIM_LENGTH + LC_SCALE_LENGTH + 1) // Task_LaunchCall # frames duration launch sequence

#define LC_MOSAIC_FADE0 16
#define LC_MOSAIC_FADE1 14
#define LC_MOSAIC_DELAY1 8
#define LC_MOSAIC_HANG1 30
#define LC_MOSAIC_FADE2 6
#define LC_MOSAIC_DELAY2 5
#define LC_MOSAIC_HANG2 5
#define LC_MOSAIC_FADE3 10
#define LC_MOSAIC_DELAY3 3
#define LC_MOSAIC_HANG3 30
#define LC_MOSAIC_FADE4 0
#define LC_MOSAIC_DELAY4 5
#define LC_MOSAIC_HANG4 60

#define HT_DELAY 30

static void Task_LaunchCall(u8 taskId)
{
    if (gTasks[taskId].tState == 0)
    {
        // RunTextPrinters();

        if (gTasks[taskId].tTimer == 0)
        {
            // TODO - add an SE to this?
            PlaySE(SE_POKENAV_ON);
            StartSpriteAnim(&gSprites[gTasks[taskId].tVideoIconSpriteId], 2);
        }
        else if (gTasks[taskId].tTimer == LC_ANIM_LENGTH)
        {
            ShowBg(0);
            SW0.invisible = SW1.invisible = SW2.invisible = SW3.invisible = FALSE;
        }
        else if (gTasks[taskId].tTimer > LC_ANIM_LENGTH && (gTasks[taskId].tTimer - LC_ANIM_LENGTH) <= LC_SCALE_LENGTH)
        {
            u8 frame = gTasks[taskId].tTimer - LC_ANIM_LENGTH;

            BlendPalette(OBJ_PLTT_ID(IndexOfSpritePaletteTag(PAL_TAG_CALL_WINDOW)) + 8, 1, 16 * frame / LC_SCALE_LENGTH, RGB_WHITE);

            // Actual Size = 2x = 92x56 (2x2 of 46x28 sprites)
            // Final Size = 4x = 184x112 (2x2 of 92x56 sprites)
            // linear size increase - scale is effectively finalScale * frame/LC_SCALE_LENGTH
            s16 scale = 0x200 * frame / LC_SCALE_LENGTH; // 0x200 is 2x in Fixed-point division
            SetOamMatrixRotationScaling(SW0.oam.matrixNum, scale, scale, 0);

            // Initial Position = 213x15 (not sure why cX cY needed finagling)
            // Final Position = 96x52
            // currently linear translation - TODO - try exponential/parabolic decay?
            s16 cX = (SW_START_X - 5) + (SW_DELTA_X * frame / LC_SCALE_LENGTH); // x-coordinate of the collective sprite center
            s16 cY = (SW_START_Y - 2) + (SW_DELTA_Y * frame / LC_SCALE_LENGTH); // y-coordinate of the collective sprite center
            s16 sX = SW_WIDTH * frame / LC_SCALE_LENGTH; // x-spacing of the individual sprite centers from the collective center
            s16 sY = SW_HEIGHT * frame / LC_SCALE_LENGTH; // y-spacing of the individual sprite centers from the collective center
            
            SW0.x2 = SW1.x2 = SW2.x2 = SW3.x2 = cX;
            SW0.y2 = SW1.y2 = SW2.y2 = SW3.y2 = cY;

            // truly not sure why the centers only need to shift a half-dimension left or up, but 3 half-dimensions right or down
            SW0.x = SW3.x = -sX;
            SW1.x = SW2.x = 3*sX;

            SW0.y = SW1.y = -sY;
            SW2.y = SW3.y = 3*sY;
        }
        else if (gTasks[taskId].tTimer == LC_LAUNCH_LENGTH)
        {
            SW0.invisible = SW1.invisible = SW2.invisible = SW3.invisible = TRUE;
            CW_NW.invisible = CW_N.invisible = CW_NE.invisible = CW_SE.invisible = CW_S.invisible = CW_SW.invisible = CW_UI.invisible = NOTIFICATION_ICON.invisible = FALSE;
 
            FillPalette(0xFFFF, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
            FillPalette(0xFFFF, BG_PLTT_ID(2), PLTT_SIZE_4BPP);

            LoadTilesMapAndPalAtOffset(1, sKukui1_Tiles,           gTasks[taskId].tFreeKukuiBaseTileNum,  0, sKukui1_Tilemap,           CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex,  sKukui_Pals,           1, FALSE);
            LoadTilesMapAndPalAtOffset(2, sCall_Background1_Tiles, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sCall_Background1_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeCallBgScreenIndex, sCall_Background_Pals, 2, FALSE);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);

            SetBgAttribute(1, BG_ATTR_MOSAIC, 1);
            SetBgAttribute(2, BG_ATTR_MOSAIC, 1);
            SetGpuReg(REG_OFFSET_MOSAIC, (8 << 0) | (8 << 4));

            sShouldMosaic = TRUE;

            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeCallBgBaseTileNum = USED_CALL_BG_BTN(gTasks[taskId].tFreeCallBgBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);
            gTasks[taskId].tFreeCallBgScreenIndex = USED_CALL_BG_SI(gTasks[taskId].tFreeCallBgScreenIndex);

            gTasks[taskId].tState = 1;
            gTasks[taskId].tTimer = -1;
        }

        gTasks[taskId].tTimer++;
    }
    else if (gTasks[taskId].tState == 1)
    {
        UpdatePaletteFade();

        if (sShouldMosaic)
            SetGpuReg(REG_OFFSET_MOSAIC, ((gPaletteFade.y / 2) << 0) | ((gPaletteFade.y / 2) << 4));

        if (!gPaletteFade.active && !IsLayerFadeActive())
        {
            if (gTasks[taskId].tTimer == 0)
            {
                ShowBg(1);
                ShowBg(2);
            }
            else if (gTasks[taskId].tTimer == 1)
            {
                // PlaySE(SE_POKENAV_ON);
                BeginNormalPaletteFade(1 << 1 | 1 << 2, LC_MOSAIC_DELAY1, LC_MOSAIC_FADE0, LC_MOSAIC_FADE1, RGB_WHITE);
            }
            else if (gTasks[taskId].tTimer == 1 + LC_MOSAIC_HANG1)
            {
                BeginNormalPaletteFade(1 << 1 | 1 << 2, LC_MOSAIC_DELAY2, LC_MOSAIC_FADE1, LC_MOSAIC_FADE2, RGB_WHITE);
            }
            else if (gTasks[taskId].tTimer == 1 + LC_MOSAIC_HANG1 + LC_MOSAIC_HANG2)
            {
                BeginNormalPaletteFade(1 << 1 | 1 << 2, LC_MOSAIC_DELAY3, LC_MOSAIC_FADE2, LC_MOSAIC_FADE3, RGB_WHITE);
            }
            else if (gTasks[taskId].tTimer == 1 + LC_MOSAIC_HANG1 + LC_MOSAIC_HANG2 + LC_MOSAIC_HANG3)
            {
                BeginNormalPaletteFade(1 << 1 | 1 << 2, LC_MOSAIC_DELAY4, LC_MOSAIC_FADE3, LC_MOSAIC_FADE4, RGB_WHITE);
            }
            else if (gTasks[taskId].tTimer == 1 + LC_MOSAIC_HANG1 + LC_MOSAIC_HANG2 + LC_MOSAIC_HANG3 + LC_MOSAIC_HANG4)
            {
                sShouldMosaic = FALSE;
                SetGpuReg(REG_OFFSET_MOSAIC, 0);
                SetBgAttribute(1, BG_ATTR_MOSAIC, 0);
                SetBgAttribute(2, BG_ATTR_MOSAIC, 0);
                ShowTextBoxBackground();
                BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);

                gTasks[taskId].tTimer = -1;
                gTasks[taskId].tState = 2;
            }

            gTasks[taskId].tTimer++;
        }
    }
    else if (gTasks[taskId].tState == 2)
    {
        UpdatePaletteFade();

        if (!gPaletteFade.active && !IsLayerFadeActive())
        {
            if (gTasks[taskId].tTimer == 0)
            {
                LoadTilesAndMapAtOffset(1, sKukui2_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui2_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
                CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
                
                gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
                gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

                ShowBg(1);
                ShowBg(2);
            }
            else if (gTasks[taskId].tTimer == 1)
            {
                BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
                PlayBGM(MUS_USUM_REGION_THEME);

                StringExpandPlaceholders(gStringVar4, gText_Kukui_JustASec);
                AddTextPrinterForMessageKukui(TRUE);
            }
            else if (gTasks[taskId].tTimer == 61)
            {
                BeginNormalPaletteFade(1 << 1 | 1 << 2, 0, 0, 16, RGB_WHITE);
            }
            else if (gTasks[taskId].tTimer == 62)
            {
                LoadTilesAndMapAtOffset(1, sKukui3_Tiles,           gTasks[taskId].tFreeKukuiBaseTileNum,  0, sKukui3_Tilemap,           CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
                LoadTilesAndMapAtOffset(2, sCall_Background2_Tiles, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sCall_Background2_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeCallBgScreenIndex, 2);
                CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);

                gTasks[taskId].tFreeKukuiBaseTileNum  = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
                gTasks[taskId].tFreeCallBgBaseTileNum = USED_CALL_BG_BTN(gTasks[taskId].tFreeCallBgBaseTileNum);
                gTasks[taskId].tFreeKukuiScreenIndex  = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);
                gTasks[taskId].tFreeCallBgScreenIndex = USED_CALL_BG_SI(gTasks[taskId].tFreeCallBgScreenIndex);
                
                HideBg(0);
                ShowBg(1);
                ShowBg(2);
            }
            else if (gTasks[taskId].tTimer == 63)
            {
                gTasks[taskId].tState = 3;
                BeginNormalPaletteFade(1 << 1 | 1 << 2, 0, 16, 0, RGB_WHITE);
            }

            gTasks[taskId].tTimer++;
        }
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState == 3)
    {
        gTasks[taskId].tTimer = -HT_DELAY;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_HeyThere;
    }
}

static void Task_HeyThere(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 0)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 1)
        {
            LoadTilesAndMapAtOffset(1, sKukui4_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui4_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 2)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);

            StringExpandPlaceholders(gStringVar4, gText_Kukui_HeyThere);
            AddTextPrinterForMessageKukui(TRUE);
        }
        else if (gTasks[taskId].tTimer == 62)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 63)
        {
            LoadTilesAndMapAtOffset(1, sKukui5_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui5_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 64)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
            gTasks[taskId].tState = 1;
        }

        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState)
    {
        gTasks[taskId].tTimer = -30;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_AlolaIsARegion;
    }
}

static void Task_AlolaIsARegion(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 0)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 1)
        {
            LoadTilesAndMapAtOffset(1, sKukui6_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui6_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 2)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);

            gTasks[taskId].tState = 1;
            StringExpandPlaceholders(gStringVar4, gText_Kukui_AlolaIsARegion);
            AddTextPrinterForMessageKukui(TRUE);
        }

        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState)
    {
        gTasks[taskId].tTimer = -30;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_CoolPokemon;
    }
}

static void Task_CoolPokemon(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 0)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 1)
        {
            LoadTilesAndMapAtOffset(1, sKukui5_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui5_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 2)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);

            StringExpandPlaceholders(gStringVar4, gText_Kukui_CoolPokemon);
            AddTextPrinterForMessageKukui(TRUE);
        }
        else if (gTasks[taskId].tTimer == 62)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 63)
        {
            LoadTilesAndMapAtOffset(1, sKukui7_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui7_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 64)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
            gTasks[taskId].tState = 1;
        }

        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState)
    {
        gTasks[taskId].tTimer = -30;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_AllOver;
    }
}

static void Task_AllOver(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 0)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 1)
        {
            LoadTilesAndMapAtOffset(1, sKukui8_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui8_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 2)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
            PlaySE(SE_BALL_THROW);
        }
        else if (gTasks[taskId].tTimer == 32)
        {
            PlaySE(SE_BALL_OPEN);
            BeginNormalPaletteFade(1 << 1 | 1 << 2, 0, 0, 16, RGB_CYAN);
        }
        else if (gTasks[taskId].tTimer == 37)
        {
            BeginNormalPaletteFade(1 << 1 | 1 << 2, 0, 16, 0, RGB_CYAN);
        }
        else if (gTasks[taskId].tTimer == 62 - 20)
        {
            PlayCry_Normal(SPECIES_ROCKRUFF, 0);
            PrepareForLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 16);
        }
        else if (gTasks[taskId].tTimer == 63 - 20)
        {
            assertf(gTasks[taskId].tFreeCallBgScreenIndex == ROCKRUFF_SCREEN_INDEX + 1);
            SetBgAttribute(0, BG_ATTR_SCREENSIZE, 1);

            LoadTilesAndMapAtOffset(   1, sKukui5_Tiles,   gTasks[taskId].tFreeKukuiBaseTileNum,  0, sKukui5a_Tilemap,  CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            LoadTilesMapAndPalAtOffset(0, sRockruff_Tiles, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sRockruff_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, sRockruff_Pals, 3, TRUE);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            DmaFill16(3, (BLANK_TILE_2 - 0x200) | (0xF << 12), BG_SCREEN_ADDR(ROCKRUFF_SCREEN_INDEX) + (32 * 14 * 2), 18 * 32 * 2);
            DmaFill16(3, (BLANK_TILE_2 - 0x200) | (0xF << 12), BG_SCREEN_ADDR(ROCKRUFF_SCREEN_INDEX + 1), 32 * 32 * 2);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(0);
        }
        else if (gTasks[taskId].tTimer == 64 - 20)
        {
            BeginNormalPaletteFade(1 << 3, 0, 16, 0, RGB_RED);
            BeginLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
        }
        else if (gTasks[taskId].tTimer == 65 - 20)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 66 - 20)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
            StringExpandPlaceholders(gStringVar4, gText_Kukui_AllOver);
            AddTextPrinterForMessageKukui(TRUE);
            gTasks[taskId].tState = 1;
            ShowBg(1);
        }

        gTasks[taskId].tTimer++;
    }

    // if (gTasks[taskId].tState && !IsLayerFadeActive())
    // {
    //     static u16 rockruffOffset = 0;

    //     sShouldChopRockruff = TRUE;
    //     SetGpuReg(REG_OFFSET_BG0HOFS, (rockruffOffset += 4) % 512);
    // }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState)
    {
        gTasks[taskId].tTimer = -30;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_LoveOurPokemon;
    }
}

// original sliding code in case we still want it.
// #define LOP_V 4
// #define LOP_FORTH_L_POS 128
// #define LOP_FORTH_R_POS -152
// #define LOP_BACK_R_POS -104
// #define LOP_BACK_L_POS 176
// #define LOP_1_R_POS 0
// #define LOP_1_L_POS LOP_BACK_L_POS
// #define LOP_1_LENGTH ((LOP_1_L_POS - LOP_1_R_POS) / LOP_V)
// #define LOP_TURN_LENGTH 15
// #define LOP_2_START (LOP_1_LENGTH + LOP_TURN_LENGTH + 1)
// #define LOP_2_L_POS LOP_FORTH_L_POS
// #define LOP_2_R_POS 0
// #define LOP_2_LENGTH ((LOP_2_L_POS - LOP_2_R_POS) / LOP_V)
// #define LOP_2_END (LOP_2_START + LOP_2_LENGTH)
// #define LOP_3_START (LOP_1_LENGTH + LOP_TURN_LENGTH + 1)
// #define LOP_3_L_POS 112
// #define LOP_3_R_POS 0
// #define LOP_3_LENGTH ((LOP_3_L_POS - LOP_3_R_POS) / LOP_V)
// #define LOP_3_END (LOP_3_START + LOP_3_LENGTH)
// #define LOP_STILL_LENGTH 90
// #define LOP_BNF_LENGTH ((LOP_FORTH_L_POS - LOP_FORTH_R_POS) / LOP_V)
// #define LOP_FORTH_START (0 + LOP_TURN_LENGTH + 1)
// #define LOP_FORTH_END (LOP_FORTH_START + LOP_BNF_LENGTH)
// #define LOP_BACK_START (LOP_FORTH_END + LOP_TURN_LENGTH + 1)
// #define LOP_BACK_END (LOP_BACK_START + LOP_BNF_LENGTH)
//
// static void Task_LoveOurPokemon(u8 taskId)
// {
//     UpdatePaletteFade();
//
//     if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
//     {
//         if (gTasks[taskId].tTimer == 0)
//         {
//             sShouldChopRockruff = TRUE;
//         }
//         else if (gTasks[taskId].tTimer >= 1 && gTasks[taskId].tTimer <= LOP_1_LENGTH)
//         {
//             s32 endFrame = LOP_1_LENGTH;
//             s32 start = LOP_1_R_POS;
//             s32 end = LOP_1_L_POS;
//
//             s32 midFrame = endFrame/2;
//             s32 frame = (gTasks[taskId].tTimer - 0) - midFrame;
//             s32 m = (end + start)/2;
//             s32 d = end - start;
//             s32 a = (frame > 0) ? -d/2 : d/2;
//             s32 p = m + (d * frame / midFrame) + (a * frame * frame / (midFrame * midFrame));
//
//             SetGpuReg(REG_OFFSET_BG0HOFS, p % 512);
//         }
//         else if (gTasks[taskId].tTimer == LOP_1_LENGTH + LOP_TURN_LENGTH)
//         {
//             LoadTilemapAtOffset(0, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sRockruff_a_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, 3);
//             ShowBg(0);
//         }
//         else if (gTasks[taskId].tTimer >= LOP_2_START && gTasks[taskId].tTimer <= LOP_2_END)
//         {
//             s32 endFrame = LOP_2_LENGTH;
//             s32 start = LOP_2_L_POS;
//             s32 end = LOP_2_R_POS;
//
//             s32 midFrame = endFrame/2;
//             s32 frame = (gTasks[taskId].tTimer - (LOP_2_START - 1)) - midFrame;
//             s32 m = (end + start)/2;
//             s32 d = end - start;
//             s32 a = (frame > 0) ? -d/2 : d/2;
//             s32 p = m + (d * frame / midFrame) + (a * frame * frame / (midFrame * midFrame));
//
//             SetGpuReg(REG_OFFSET_BG0HOFS, p % 512);
//         }
//         else if (gTasks[taskId].tTimer == LOP_2_END + 1)
//         {
//             SetGpuReg(REG_OFFSET_BG0HOFS, 0);
//             sShouldChopRockruff = FALSE;
//             BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
//         }
//         else if (gTasks[taskId].tTimer == LOP_2_END + 2)
//         {
//             LoadTilesAndMapAtOffset(1, sKukui6_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum,  0, sKukui6_Tilemap,     CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
//             CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
//             gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
//             gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);
//
//             ShowBg(2);
//             ShowBg(1);
//         }
//         else if (gTasks[taskId].tTimer == LOP_2_END + 3)
//         {
//             StringExpandPlaceholders(gStringVar4, gText_Kukui_LoveOurPokemon);
//             AddTextPrinterForMessageKukui(TRUE);
//             BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
//             gTasks[taskId].tTimer = -LOP_STILL_LENGTH;
//             gTasks[taskId].tState = 1;
//         }
//
//         gTasks[taskId].tTimer++;
//     }
//     else if (gTasks[taskId].tState == 1 && !gPaletteFade.active && !IsLayerFadeActive())
//     {
//         if (gTasks[taskId].tTimer == 0)
//         {
//             sShouldChopRockruff = TRUE;
//         }
//         else if (gTasks[taskId].tTimer >= 1 && gTasks[taskId].tTimer <= (LOP_BNF_LENGTH - LOP_2_LENGTH))
//         {
//             s32 endFrame = (LOP_BNF_LENGTH - LOP_2_LENGTH);
//             s32 start = LOP_2_R_POS;
//             s32 end = LOP_FORTH_R_POS;
//
//             s32 midFrame = endFrame/2;
//             s32 frame = (gTasks[taskId].tTimer - 0) - midFrame;
//             s32 m = (end + start)/2;
//             s32 d = end - start;
//             s32 a = (frame > 0) ? -d/2 : d/2;
//             s32 p = m + (d * frame / midFrame) + (a * frame * frame / (midFrame * midFrame));
//
//             SetGpuReg(REG_OFFSET_BG0HOFS, p % 512);
//         }
//         else if (gTasks[taskId].tTimer == (LOP_BNF_LENGTH - LOP_2_LENGTH) + LOP_TURN_LENGTH)
//         {
//             LoadTilemapAtOffset(0, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sRockruff_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, 3);
//             ShowBg(0);
//             gTasks[taskId].tTimer = LOP_BACK_START - 1;
//             gTasks[taskId].tState = 2;
//         }
//
//         gTasks[taskId].tTimer++;
//     }
//     else if ((gTasks[taskId].tState == 2 || gTasks[taskId].tState == 3) && !gPaletteFade.active && !IsLayerFadeActive())
//     {
//         if (gTasks[taskId].tTimer == LOP_TURN_LENGTH)
//         {
//             LoadTilemapAtOffset(0, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sRockruff_a_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, 3);
//             ShowBg(0);
//         }
//         else if (gTasks[taskId].tTimer >= LOP_FORTH_START && gTasks[taskId].tTimer <= LOP_FORTH_END)
//         {
//             s32 endFrame = LOP_BNF_LENGTH;
//             s32 start = LOP_FORTH_L_POS;
//             s32 end = LOP_FORTH_R_POS;
//
//             s32 midFrame = endFrame/2;
//             s32 frame = (gTasks[taskId].tTimer - (LOP_FORTH_START - 1)) - midFrame;
//             s32 m = (end + start)/2;
//             s32 d = end - start;
//             s32 a = (frame > 0) ? -d/2 : d/2;
//             s32 p = m + (d * frame / midFrame) + (a * frame * frame / (midFrame * midFrame));
//
//             if (gTasks[taskId].tState == 3 && frame == -1)
//                 gTasks[taskId].tState = 4;
//
//             SetGpuReg(REG_OFFSET_BG0HOFS, p % 512);
//         }
//         if (gTasks[taskId].tTimer == LOP_FORTH_END + LOP_TURN_LENGTH)
//         {
//             LoadTilemapAtOffset(0, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sRockruff_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, 3);
//             ShowBg(0);
//         }
//         else if (gTasks[taskId].tTimer >= LOP_BACK_START && gTasks[taskId].tTimer <= LOP_BACK_END)
//         {
//             s32 endFrame = LOP_BNF_LENGTH;
//             s32 start = LOP_BACK_R_POS;
//             s32 end = LOP_BACK_L_POS;
//
//             s32 midFrame = endFrame/2;
//             s32 frame = (gTasks[taskId].tTimer - (LOP_BACK_START - 1)) - midFrame;
//             s32 m = (end + start)/2;
//             s32 d = end - start;
//             s32 a = (frame > 0) ? -d/2 : d/2;
//             s32 p = m + (d * frame / midFrame) + (a * frame * frame / (midFrame * midFrame));
//
//             if (gTasks[taskId].tState == 3 && frame == midFrame/8)
//                 gTasks[taskId].tState = 4;
//
//             SetGpuReg(REG_OFFSET_BG0HOFS, p % 512);
//         }
//         else if (gTasks[taskId].tTimer == LOP_BACK_END + 1)
//         {
//             gTasks[taskId].tTimer = 0;
//         }
//
//         gTasks[taskId].tTimer++;
//     }
//
//     if (!RunTextPrintersAndIsPrinter0Active() && (gTasks[taskId].tState == 1 || gTasks[taskId].tState == 2))
//     {
//         gTasks[taskId].tState = 3;
//     }
//
//     if (gTasks[taskId].tState == 4)
//     {
//         gTasks[taskId].tTimer = 0;
//         gTasks[taskId].tState = 0;
//         gTasks[taskId].func = Task_AndYouAre;
//     }
// }


// Barking version:
#define ROCKRUFF_BARK_DELAY 30
#define ROCKRUFF_BARK_INTERVAL 150

static void Task_LoveOurPokemon(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 0)
        {
            BeginLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 1)
        {
            SetGpuReg(REG_OFFSET_BG0HOFS, 0);
            sShouldChopRockruff = FALSE;
            LoadTilemapAtOffset(0, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sRockruff_a_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, 3);
            ShowBg(0);
        }
        else if (gTasks[taskId].tTimer == 2)
        {
            BeginLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
        }
        else if (gTasks[taskId].tTimer == 14)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 15)
        {
            LoadTilesAndMapAtOffset(1, sKukui6_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum,  0, sKukui6_Tilemap,     CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 16)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
        }
        else if (gTasks[taskId].tTimer == 17)
        {
            StringExpandPlaceholders(gStringVar4, gText_Kukui_LoveOurPokemon);
            AddTextPrinterForMessageKukui(TRUE);
            gTasks[taskId].tState = 1;
            gTasks[taskId].tTimer = -ROCKRUFF_BARK_DELAY - 1;
        }

        gTasks[taskId].tTimer++;
    }
    else if (gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        // quick shake animation for Rockruff's bark
        static const s8 shakeX[] = {0, -2, -3, -2, 0, 2, 3, 2, 0, -1, -2, -1, 0, 1, 1, 0};
        s16 frame = gTasks[taskId].tTimer;

        if (frame == 0 && gTasks[taskId].tState == 1)
            PlayCry_Normal(SPECIES_ROCKRUFF, 0);

        if (frame >= 0 && frame < ARRAY_COUNT(shakeX))
        {
            SetGpuReg(REG_OFFSET_BG0HOFS, shakeX[frame] & 0x1FF);
            SetGpuReg(REG_OFFSET_BG0VOFS, frame < 8 ? 0x1FF : 0);
        }
        else
        {
            SetGpuReg(REG_OFFSET_BG0HOFS, 0);
            SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        }

        if (++gTasks[taskId].tTimer >= ROCKRUFF_BARK_INTERVAL)
            gTasks[taskId].tTimer = 0;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState == 1)
        gTasks[taskId].tState = 2;

    // Finish any current shake before recalling Rockruff, as with the old slide.
    if (gTasks[taskId].tState == 2
     && (gTasks[taskId].tTimer <= 0 || gTasks[taskId].tTimer > 16))
    {
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        gTasks[taskId].tTimer = 0;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_AndYouAre;
    }
}

static void Task_AndYouAre(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 25)
        {
            PlayCry_Normal(SPECIES_ROCKRUFF, 0);
        }
        else if (gTasks[taskId].tTimer == 30)
        {
            BeginNormalPaletteFade(1 << 3, 0, 0, 8, RGB_RED);
        }
        else if (gTasks[taskId].tTimer == 31)
        {
            BeginNormalPaletteFade(1 << 3, 0, 9, 16, RGB_RED);
            BeginLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 32)
        {
            HideBg(0);
            sShouldChopRockruff = FALSE;
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 33)
        {
            LoadTilesAndMapAtOffset(1, sKukui5_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui5_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            LoadComputerPassportPhotos(taskId);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 34)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
            StringExpandPlaceholders(gStringVar4, gText_Kukui_AndYouAre);
            AddTextPrinterForMessageKukui(TRUE);
            gTasks[taskId].tState = 1;
        }

        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState)
    {
        BeginNormalPaletteFade(1 << 1 | 1 << 2, 0, 0, 16, RGB_WHITE);
        BeginLayerFade(BLDCNT_TGT2_ALL, 1, 16, 0);
        PP_M1.invisible = PP_M2.invisible = PP_F1.invisible = PP_F2.invisible = CURSOR.invisible = FALSE;
        PP_M1.oam.objMode = PP_M2.oam.objMode = PP_F1.oam.objMode = PP_F2.oam.objMode = CURSOR.oam.objMode = ST_OAM_OBJ_BLEND;

        StringExpandPlaceholders(gStringVar4, gText_Kukui_WhichPhoto);
        AddTextPrinterForMessageKukui(TRUE);

        gTasks[taskId].tModelSelect = 0;
        gTasks[taskId].tPaletteSelect = -1;

        gTasks[taskId].tTimer = 0;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_WhichPhoto;
    }
}

static void Task_WhichPhoto(u8 taskId)
{
    UpdatePaletteFade();
    if (!gPaletteFade.active && !sPassportBackdropActive)
        InitPassportBackgrounds();

    if (!IsTextPrinterActiveOnWindow(0))
    {
        if (gTasks[taskId].tPaletteSelect < 0)
        {
            if (JOY_NEW(A_BUTTON | DPAD_DOWN))
            {
                DrawPassportBackgrounds(TRUE);
                LoadPassportSkinChoices(gTasks[taskId].tModelSelect);
                PP_A.invisible = PP_B.invisible = PP_C.invisible = PP_D.invisible = FALSE;
                
                if (JOY_NEW(A_BUTTON))
                    gTasks[taskId].tPaletteSelect = 0;
                else
                    gTasks[taskId].tPaletteSelect = gTasks[taskId].tModelSelect;
            }
            else if (JOY_NEW(DPAD_LEFT))
            {
                gTasks[taskId].tModelSelect = (gTasks[taskId].tModelSelect == 0) ? 3 : gTasks[taskId].tModelSelect - 1;
            }
            else if (JOY_NEW(DPAD_RIGHT))
            {
                gTasks[taskId].tModelSelect = (gTasks[taskId].tModelSelect == 3) ? 0 : gTasks[taskId].tModelSelect + 1;
            }
        }
        else
        {
            if (JOY_NEW(B_BUTTON | DPAD_UP))
            {
                DrawPassportBackgrounds(FALSE);
                PP_A.invisible = PP_B.invisible = PP_C.invisible = PP_D.invisible = TRUE;
                
                if (JOY_NEW(DPAD_UP))
                    gTasks[taskId].tModelSelect = gTasks[taskId].tPaletteSelect;
                gTasks[taskId].tPaletteSelect = -1;
            }
            else if (JOY_NEW(A_BUTTON))
            {
                FillWindowPixelBuffer(0, PIXEL_FILL(0));
                CopyWindowToVram(0, COPYWIN_GFX);
                StringExpandPlaceholders(gStringVar4, gText_Kukui_ChoiceOK);
                AddTextPrinterForMessageKukui(TRUE);
                gTasks[taskId].func = Task_CreatePhotoYesNo;
                // gTasks[taskId].tState = 1;
            }
            else if (JOY_NEW(DPAD_LEFT))
            {
                gTasks[taskId].tPaletteSelect = (gTasks[taskId].tPaletteSelect == 0) ? 3 : gTasks[taskId].tPaletteSelect - 1;
            }
            else if (JOY_NEW(DPAD_RIGHT))
            {
                gTasks[taskId].tPaletteSelect = (gTasks[taskId].tPaletteSelect == 3) ? 0 : gTasks[taskId].tPaletteSelect + 1;
            }
        }

        if (gTasks[taskId].tState < 2 && JOY_NEW(DPAD_ANY | A_BUTTON | B_BUTTON))
        {
            s16 x = CURSOR.x;
            s16 y = CURSOR.y;

            if (gTasks[taskId].tPaletteSelect < 0)
            {
                CURSOR.x = CURSOR_X + (gTasks[taskId].tModelSelect * CURSOR_DELTA_X);
                CURSOR.y = CURSOR_Y;
            }
            else
            {
                CURSOR.x = CURSOR_X + (gTasks[taskId].tPaletteSelect * CURSOR_DELTA_X);
                CURSOR.y = CURSOR_Y + CURSOR_DELTA_Y;


            }

            if (!JOY_NEW(DPAD_ANY) || x != CURSOR.x || y != CURSOR.y)
                PlaySE(SE_SELECT);
        }
    }

    if (!RunTextPrintersAndIsPrinter0Active())
    {
        if (gTasks[taskId].tState == 1)
        {
            StringExpandPlaceholders(gStringVar4, gText_Kukui_WhatsYourName);
            AddTextPrinterForMessageKukui(TRUE);
            gTasks[taskId].tState++;
        }
        else if (gTasks[taskId].tState > 1)
        {
            // Preserve the solid picker fill in both BG palettes before fading to black.
            // This means we need to reload them, but we do that when returning from the naming screen anyways
            FastUnsafeCopy32(&gPlttBufferUnfaded[BG_PLTT_ID(1)], &gPlttBufferFaded[BG_PLTT_ID(1)], PLTT_SIZE_4BPP);
            FastUnsafeCopy32(&gPlttBufferUnfaded[BG_PLTT_ID(2)], &gPlttBufferFaded[BG_PLTT_ID(2)], PLTT_SIZE_4BPP);

            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);

            gSaveBlock2Ptr->playerGender = (gTasks[taskId].tModelSelect == 0 || gTasks[taskId].tModelSelect == 1) ? MALE : FEMALE;
            gSaveBlock2Ptr->currOutfitId = sPhotoOutfits[gTasks[taskId].tModelSelect];
            gSaveBlock2Ptr->currOutfitPalette = gTasks[taskId].tPaletteSelect;
            gTasks[taskId].tTimer = 0;
            gTasks[taskId].tState = 0;
            gTasks[taskId].func = Task_StartNamingScreen;
        }
    }
}

static void Task_StartNamingScreen(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        sPassportMapPending = FALSE;
        sPassportTilemap = NULL;
        SetHBlankCallback(NULL);
        FreeAllWindowBuffers();
        NewGameBirchSpeech_SetRandomDefaultPlayerName();
        DestroyTask(taskId);
        DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerName, gSaveBlock2Ptr->playerGender, 0, GetCurrentOutfitSpriteId(), CB2_NewGameKukuiCall_ReturnFromNamingScreen);
    }
}

static void CB2_NewGameKukuiCall_ReturnFromNamingScreen(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    DmaFill16(3, 0, VRAM, VRAM_SIZE);
    DmaFill32(3, 0, OAM, OAM_SIZE);
    DmaFill16(3, 0, PLTT, PLTT_SIZE);
    DmaFill16(3, BLANK_TILE_2 - 0x200, BG_SCREEN_ADDR(CALL_BG_1_SCREEN_INDEX), 0x800);
    DmaFill16(3, BLANK_TILE_2 - 0x200, BG_SCREEN_ADDR(CALL_BG_2_SCREEN_INDEX), 0x800);
    ResetPaletteFade();

    ResetTasks();
    u8 taskId = CreateTask(Task_SoItsPlayer, 0);
    gTasks[taskId].tFreeKukuiBaseTileNum  = KUKUI_2_BASE_TILE_NUM;
    gTasks[taskId].tFreeCallBgBaseTileNum = CALL_BG_2_BASE_TILE_NUM;
    gTasks[taskId].tFreeKukuiScreenIndex  = KUKUI_2_SCREEN_INDEX;
    gTasks[taskId].tFreeCallBgScreenIndex = CALL_BG_2_SCREEN_INDEX;
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].tState = 0;

    ScanlineEffect_Stop();
    ResetSpriteData();
    FreeAllSpritePalettes();
    AddComputerBackgroundObjects_ReturnFromNamingScreen(taskId);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
    SetGpuReg(REG_OFFSET_BLDY, 0);

    sLastVCount = -1;
    sLayerFadeActive = FALSE;
    sShouldLayerFade = FALSE; 
    sShouldChopRockruff = FALSE;
    sShouldUpdateLayerFade = TRUE;
    sLayerFadeY = 0;
    SetHBlankCallback(HBlankCB_KukuiCall);
    SetVBlankCallback(VBlankCB_KukuiCall);
    EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_HBLANK);
    SetMainCallback2(CB2_KukuiCall);
    InitWindows(sNewGameKukuiCallTextWindows);
    DmaFill32(3, 0xFFFFFFFF, BG_VRAM + (8 * 8 / 2) * TEXT_BG_TILE, 8 * 8 / 2);
    LoadPalette(sMainMenuTextPal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);

    LoadTilesMapAndPalAtOffset(3, sComputer_Background_Tiles, PC_BG_BASE_TILE_NUM,                                     0, sComputer_Background_Tilemap, PC_BG_HEIGHT,   PC_BG_SCREEN_INDEX,                                     sComputer_Background_Pals, 0, FALSE);
    LoadTilesMapAndPalAtOffset(2, sCall_Background2_Tiles,    USED_CALL_BG_BTN(gTasks[taskId].tFreeCallBgBaseTileNum), 1, sCall_Background2_Tilemap,    CALL_BG_HEIGHT, USED_CALL_BG_SI(gTasks[taskId].tFreeCallBgScreenIndex), sCall_Background_Pals, 2, FALSE);
    LoadTilesMapAndPalAtOffset(1, sKukui5_Tiles,              USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum),    0, sKukui5_Tilemap,              CALL_BG_HEIGHT, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex),    sKukui_Pals, 1, FALSE);
    ShowTextBoxBackground();
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
}

static void Task_SoItsPlayer(u8 taskId)
{
    UpdatePaletteFade();

    if (!gPaletteFade.active && !IsLayerFadeActive() && !gTasks[taskId].tState)
    {
        if (!gTasks[taskId].tTimer)
        {
            StringExpandPlaceholders(gStringVar4, gText_Kukui_SoItsPlayer);
            AddTextPrinterForMessageKukui(TRUE);
            gTasks[taskId].tState = 1;
        }

        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState)
    {
        gTasks[taskId].tTimer = 0;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_CreateNameYesNo; // Task_YourePlayer;
    }
}

static void Task_YourePlayer(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 0)
        {
            LoadPassportFrameGraphics();
            sPassportCornerPending = TRUE;
            PP_M1.invisible = FALSE;
            StringExpandPlaceholders(gStringVar4, gText_Kukui_YourePlayer);
            AddTextPrinterForMessageKukui(TRUE);
            gTasks[taskId].tState = 1;
        }

        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active())
    {
        if (gTasks[taskId].tState)
        {
            gTasks[taskId].tTimer = 0;
            gTasks[taskId].tState = 0;
            gTasks[taskId].func = Task_AreYouReady;
        }
    }
}

static void Task_AreYouReady(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 30)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 31)
        {
            assertf(gTasks[taskId].tFreeCallBgScreenIndex == ROCKRUFF_SCREEN_INDEX + 1);
            SetBgAttribute(0, BG_ATTR_SCREENSIZE, 1);

            LoadTilemapAtOffset(       1,                  USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum), 0, sKukui5a_Tilemap,  CALL_BG_HEIGHT, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), 1);
            LoadTilesMapAndPalAtOffset(0, sRockruff_Tiles, gTasks[taskId].tFreeCallBgBaseTileNum,                1, sRockruff_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, sRockruff_Pals, 3, TRUE);
            // CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), 14, 6);
            DmaFill16(3, (BLANK_TILE_2 - 0x200) | (0xF << 12), BG_SCREEN_ADDR(ROCKRUFF_SCREEN_INDEX) + (32 * 14 * 2), 18 * 32 * 2);
            DmaFill16(3, (BLANK_TILE_2 - 0x200) | (0xF << 12), BG_SCREEN_ADDR(ROCKRUFF_SCREEN_INDEX + 1), 32 * 32 * 2);
            // gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            // gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 32)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
        }
        else if (gTasks[taskId].tTimer == 33)
        {
            PlayCry_Normal(SPECIES_ROCKRUFF, 0);
            PrepareForLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 16);
        }
        else if (gTasks[taskId].tTimer == 34)
        {
            BeginNormalPaletteFade(1 << 3, 0, 16, 0, RGB_RED);
            BeginLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
            StringExpandPlaceholders(gStringVar4, gText_Kukui_AreYouReady);
            AddTextPrinterForMessageKukui(TRUE);
            gTasks[taskId].tState = 1;
            ShowBg(0);
        }

        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState)
    {
        gTasks[taskId].tTimer = -30;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_EndCall;
    }
}

static void Task_EndCall(u8 taskId)
{
    UpdatePaletteFade();

    if (!gTasks[taskId].tState && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer == 0)
        {
            BeginLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 1)
        {
            SetGpuReg(REG_OFFSET_BG0HOFS, 0);
            sShouldChopRockruff = FALSE;
            LoadTilemapAtOffset(0, gTasks[taskId].tFreeCallBgBaseTileNum, 1, sRockruff_b_Tilemap, CALL_BG_HEIGHT, ROCKRUFF_SCREEN_INDEX, 3);
            ShowBg(0);
        }
        else if (gTasks[taskId].tTimer == 2)
        {
            BeginLayerFade(BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
        }
        else if (gTasks[taskId].tTimer == 14)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 15)
        {
            LoadTilesAndMapAtOffset(1, sKukui4_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum,  0, sKukui4a_Tilemap,     CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 16)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
        }
        else if (gTasks[taskId].tTimer == 76)
        {
            HideBg(0);
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
        }
        else if (gTasks[taskId].tTimer == 77)
        {
            LoadTilesAndMapAtOffset(1, sKukui3_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui3_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
            CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
            gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

            ShowBg(2);
            ShowBg(1);
        }
        else if (gTasks[taskId].tTimer == 78)
        {
            BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
        }
        else if (gTasks[taskId].tTimer == 108)
        {
            SW0.invisible = SW1.invisible = SW2.invisible = SW3.invisible = FALSE;
            BlendPalette(OBJ_PLTT_ID(IndexOfSpritePaletteTag(PAL_TAG_CALL_WINDOW)) + 8, 1, 16, RGB_WHITE);
            PlaySE(SE_POKENAV_OFF);
            FadeOutBGM(10);
            gTasks[taskId].tTimer = 0;
            gTasks[taskId].tState = 1;
        }

        gTasks[taskId].tTimer++;
    }
    else if (gTasks[taskId].tState == 1 && !gPaletteFade.active && !IsLayerFadeActive())
    {
        if (gTasks[taskId].tTimer > 0 && gTasks[taskId].tTimer <= LC_SCALE_LENGTH)
        {
            if (gTasks[taskId].tTimer == 1)
            {
                CW_NW.invisible = CW_N.invisible = CW_NE.invisible = CW_SE.invisible = CW_S.invisible = CW_SW.invisible = CW_UI.invisible = NOTIFICATION_ICON.invisible = TRUE;
                PP_M1.invisible = TRUE;

                HideBg(0);
                HideBg(1);
                HideBg(2);
            }

            u8 frame = LC_SCALE_LENGTH - gTasks[taskId].tTimer + 1;

            BlendPalette(OBJ_PLTT_ID(IndexOfSpritePaletteTag(PAL_TAG_CALL_WINDOW)) + 8, 1, 16 * frame / LC_SCALE_LENGTH, RGB_WHITE);

            // Actual Size = 2x = 92x56 (2x2 of 46x28 sprites)
            // Final Size = 4x = 184x112 (2x2 of 92x56 sprites)
            // linear size increase - scale is effectively finalScale * frame/LC_SCALE_LENGTH
            s16 scale = 0x200 * frame / LC_SCALE_LENGTH; // 0x200 is 2x in Fixed-point division
            SetOamMatrixRotationScaling(SW0.oam.matrixNum, scale, scale, 0);

            // Initial Position = 213x15 (not sure why cX cY needed finagling)
            // Final Position = 96x52
            // currently linear translation - TODO - try exponential/parabolic decay?
            s16 cX = (SW_START_X - 5) + (SW_DELTA_X * frame / LC_SCALE_LENGTH); // x-coordinate of the collective sprite center
            s16 cY = (SW_START_Y - 2) + (SW_DELTA_Y * frame / LC_SCALE_LENGTH); // y-coordinate of the collective sprite center
            s16 sX = SW_WIDTH * frame / LC_SCALE_LENGTH; // x-spacing of the individual sprite centers from the collective center
            s16 sY = SW_HEIGHT * frame / LC_SCALE_LENGTH; // y-spacing of the individual sprite centers from the collective center
            
            SW0.x2 = SW1.x2 = SW2.x2 = SW3.x2 = cX;
            SW0.y2 = SW1.y2 = SW2.y2 = SW3.y2 = cY;

            // truly not sure why the centers only need to shift a half-dimension left or up, but 3 half-dimensions right or down
            SW0.x = SW3.x = -sX;
            SW1.x = SW2.x = 3*sX;

            SW0.y = SW1.y = -sY;
            SW2.y = SW3.y = 3*sY;
        }
        else if (gTasks[taskId].tTimer == LC_SCALE_LENGTH + 1)
        {
            SW0.invisible = SW1.invisible = SW2.invisible = SW3.invisible = TRUE;
        }
        else if (gTasks[taskId].tTimer == 2*LC_SCALE_LENGTH + 1)
        {
            gTasks[taskId].tState = 2;
        }
        
        gTasks[taskId].tTimer++;
    }

    if (!RunTextPrintersAndIsPrinter0Active() && gTasks[taskId].tState == 2)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 10, 0, 16, RGB_BLACK);
        gTasks[taskId].tTimer = 0;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_Cleanup;
    }
}

static void Task_Cleanup(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        FreeAllWindowBuffers();
        SetMainCallback2(CB2_NewGame); // comment this out and uncomment the two lines below for a clock at newgame
        //SetMainCallback2(CB2_StartWallClock);
        //gMain.savedCallback = CB2_NewGame;
        DestroyTask(taskId);
    }
}

static void Task_CreatePhotoYesNo(u8 taskId)
{
    if (!RunTextPrintersAndIsPrinter0Active())
    {
        KukuiCreateYesNoMenuParameterized(1, 24, 9, 0x88, 0x69, 13, 15);
        gTasks[taskId].func = Task_ProcessPhotoYesNoMenu;
    }
}

static void Task_ProcessPhotoYesNoMenu(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        PlaySE(SE_SELECT);
        FillWindowPixelBuffer(0, PIXEL_FILL(0));
        CopyWindowToVram(0, COPYWIN_GFX);
        gTasks[taskId].tState = 1;
        gTasks[taskId].func = Task_WhichPhoto;
        break;
    case MENU_B_PRESSED:
    case 1:
        PlaySE(SE_SELECT);
        FillWindowPixelBuffer(0, PIXEL_FILL(0));
        CopyWindowToVram(0, COPYWIN_GFX);
        StringExpandPlaceholders(gStringVar4, gText_Kukui_WhichPhoto);
        AddTextPrinterForMessageKukui(TRUE);
        gTasks[taskId].func = Task_WhichPhoto;
    }
}

static void Task_CreateNameYesNo(u8 taskId)
{
    if (!RunTextPrintersAndIsPrinter0Active())
    {
        ShowBg(0);
        KukuiCreateYesNoMenuParameterized(0, 24, 9, 0x88, 0x69, 13, 15);
        gTasks[taskId].func = Task_ProcessNameYesNoMenu;
    }
}

static void Task_ProcessNameYesNoMenu(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        PlaySE(SE_SELECT);
        HideBg(0);
        FillWindowPixelBuffer(0, PIXEL_FILL(0));
        CopyWindowToVram(0, COPYWIN_GFX);
        gTasks[taskId].func = Task_YourePlayer;
        break;
    case MENU_B_PRESSED:
    case 1:
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_StartNamingScreen;
    }
}

static void KukuiCreateYesNoMenuParameterized(u8 bg, u8 x, u8 y, u16 baseTileNum, u16 baseBlock, u8 yesNoPalNum, u8 winPalNum)
{
    struct WindowTemplate template = CreateWindowTemplate(bg, x + 1, y + 1, 4, 4, winPalNum, baseBlock);
    LoadUserWindowBorderGfxOnBg(bg, baseTileNum, BG_PLTT_ID(yesNoPalNum));
    CreateYesNoMenu(&template, baseTileNum, yesNoPalNum, 0);
}

// static void Task_TestLoop(u8 taskId)
// {
//     UpdatePaletteFade();

//     if (!gPaletteFade.active && !IsLayerFadeActive())
//     {
//         if (!gTasks[taskId].tState)
//         {
//             BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
//         }
//         else if (gTasks[taskId].tState == 1)
//         {
//             if (!gTasks[taskId].tTimer)
//             {
//                 LoadTilesAndMapAtOffset(1, sKukui5_Tiles, gTasks[taskId].tFreeKukuiBaseTileNum, 0, sKukui5_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
//                 gTasks[taskId].tFreeKukuiBaseTileNum = USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum);
//                 gTasks[taskId].tTimer = 1;
//             }
//             else
//                 LoadTilemapAtOffset(1, USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum), 0, sKukui5_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
//             CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);
            
//             gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

//             ShowBg(2);
//             ShowBg(1);
//         }
//         else if (gTasks[taskId].tState == 2)
//         {
//             BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
//         }
//         else if (gTasks[taskId].tState == 62)
//         {
//             BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 0, 16);
//         }
//         else if (gTasks[taskId].tState == 63)
//         {
//             LoadTilemapAtOffset(1, USED_KUKUI_BTN(gTasks[taskId].tFreeKukuiBaseTileNum), 0, sKukui5a_Tilemap, CALL_BG_HEIGHT, gTasks[taskId].tFreeKukuiScreenIndex, 1);
//             CopyPartialTilemap(gTasks[taskId].tFreeKukuiScreenIndex, USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex), CALL_BG_HEIGHT, TEXTBOX_HEIGHT);

//             gTasks[taskId].tFreeKukuiScreenIndex = USED_KUKUI_SI(gTasks[taskId].tFreeKukuiScreenIndex);

//             ShowBg(2);
//             ShowBg(1);
//         }
//         else if (gTasks[taskId].tState == 64)
//         {
//             BeginLayerFade(BLDCNT_TGT1_BG1 | BLDCNT_TGT2_BG_ALL, 0, 16, 0);
//         }
//         else if (gTasks[taskId].tState == 124)
//         {
//             gTasks[taskId].tState = -1;
//         }

//         gTasks[taskId].tState++;
//     }

//     if (!RunTextPrintersAndIsPrinter0Active())
//     {
//         StringExpandPlaceholders(gStringVar4, gText_Kukui_JustASec);
//         AddTextPrinterForMessageKukui(TRUE);
//     }
// }

// static void NewGameKukuiCall_PrintNameplate(void)
// {
//     int strLen;
//     const u8 colors[3] = {0, 1, 14};

//     StringExpandPlaceholders(gStringVar1, gText_Kukui_Nameplate);
//     strLen = GetStringWidth(FONT_SMALL, gStringVar1, -1);

//     if (strLen > 0)
//     {
//         strLen = GetDialogFramePlateWidth() / 2 - strLen / 2;
//         gNamePlateBuffer[0] = EXT_CTRL_CODE_BEGIN;
//         gNamePlateBuffer[1] = EXT_CTRL_CODE_CLEAR_TO;
//         gNamePlateBuffer[2] = strLen;
//         StringExpandPlaceholders(&gNamePlateBuffer[3], gStringVar1);
//     }
//     else
//     {
//         StringExpandPlaceholders(&gNamePlateBuffer[0], gStringVar1);
//     }

//     FillDialogFramePlate(1);
//     AddTextPrinterParameterized3(1, FONT_SMALL, 0, 0, colors, 0, gNamePlateBuffer);

//     DrawNamePlateWithCustomTile(1, TRUE, BIRCH_DLG_BASE_TILE_NUM);
// }
