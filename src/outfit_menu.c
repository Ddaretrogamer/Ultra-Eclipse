#include "global.h"
#include "main.h"
#include "bg.h"
#include "malloc.h"
#include "gpu_regs.h"
#include "sprite.h"
#include "string_util.h"
#include "text.h"
#include "window.h"
#include "data.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_weather.h"
#include "graphics.h"
#include "list_menu.h"
#include "menu.h"
#include "menu_helpers.h"
#include "outfit_menu.h"
#include "overworld.h"
#include "palette.h"
#include "palette_util.h"
#include "scanline_effect.h"
#include "sound.h"
#include "task.h"
#include "text_window.h"
#include "trainer_pokemon_sprites.h"
#include "grid_menu.h"
#include "event_data.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/trainers.h"

#define GRID_COLS   1
#define GRID_ROWS   4

enum BGs {
    BG_MSGBOX = 0,
    BG_TXT,
    BG_MAIN,
    BG_SCROLL
};

enum States {
    STATE_BEGIN = 0,
    STATE_RESET,
    STATE_LOADBG,
    STATE_LOADGFX,
    STATE_LOADWIN,
    STATE_LOADSTR,
    STATE_LOADGRID,
    STATE_LOADSPRITE,
    STATE_WAITFADE,
    STATE_TRANSITION,
    STATE_FADE,
    STATE_COUNT,
};

enum Windows {
    WIN_INFO = 0,
    WIN_MSGBOX,
};

enum Sprites {
    GFX_OW = 0,
    GFX_FTS, // front
    GFX_BTS, // back
    GFX_CURSOR,
    GFX_COUNT,
};

enum SpriteTags {
    TAG_SCROLL_ARROWS = 0x9000,
    TAG_INDICATOR,
    TAG_CURSOR,
};

enum ColorId {
    COLORID_NORMAL = 0,
    COLORID_MSGBOX,
};

enum IndicatorAnimIds {
    I_ANIM_NORMAL = 0,
    I_ANIM_CURSOR
};

static const u8 sFontColors[][3] = { // bgColor, textColor, shadowColor
    [COLORID_NORMAL] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE,      10},
    [COLORID_MSGBOX] = {TEXT_COLOR_WHITE,       TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
};

typedef struct {
    u8 tilemapBuffers[2][BG_SCREEN_SIZE];
    u8 spriteIds[GFX_COUNT];
    struct GridMenu *grid;
    u8 *list;
    u8 listCount;
    u8 currentOutfitSpriteIds[GRID_ROWS];
    u8 slotId:1; // flipped each time its used, for trainer sprites
    u8 unused:7;
    u16 idx;
    u8 gfxState;
    MainCallback retCB;
} OutfitMenuResources;

static void CB2_SetupOutfitMenu(void);
static void CB2_OutfitMenu(void);
static void VBlankCB_OutfitMenu(void);
static void SetupOutfitMenu_BGs(void);
static bool32 SetupOutfitMenu_Graphics(void);
static void SetupOutfitMenu_Windows(void);
static void SetupOutfitMenu_PrintStr(void);
static void SetupOutfitMenu_Sprites(void);
static void SetupOutfitMenu_Grids(void);
static void Task_WaitFadeInOutfitMenu(u8 taskId);
static void Task_OutfitMenuHandleInput(u8 taskId);
static void Task_CloseOutfitMenu(u8 taskId);
static u32 BuildOutfitLists(void);
static inline void UpdateOutfitInfo(void);
static void UpdateCursorPosition(void);

static const u8 sText_OutfitLocked[] = _("???");
static const u8 sText_OutfitLockedMsg[] =
_(
    "You don't have this OUTFIT yet.\n"
    "Unlock it to be able to use it."
);

static const u8 sText_OutfitError[] =
_(
    "You can't change your outfit {STR_VAR_1}"
);

static const u8 sText_OutfitError_Cycling[] =
_(
    "while\ncycling! You might get tripped over!"
);

static const u8 sText_OutfitError_Surfing[] =
_(
    "while\nsurfing! You might get wet!"
);

static const u8 sText_OutfitError_Diving[] =
_(
    "while\ndiving! Have common sense!" //! :masuda:
);

static const u8 sText_OutfitError_Default[] = _(
    "now!"
);

static const u16 sTiles[] = INCBIN_U16("graphics/outfit_menu/main.4bpp");
static const u16 sPalette[] = INCBIN_U16("graphics/outfit_menu/main.gbapal");
static const u32 sTilemap[] = INCBIN_U32("graphics/outfit_menu/main.bin.lz");
static const u32 sScrollingBG_Tilemap[] = INCBIN_U32("graphics/outfit_menu/scroll.bin.lz");

static const u16 sIndicatorSprite_Gfx[] = INCBIN_U16("graphics/outfit_menu/indicator.4bpp");
static const u16 sIndicatorSprite_Pal[] = INCBIN_U16("graphics/outfit_menu/indicator.gbapal");
static const u16 sCursorSprite_Gfx[] = INCBIN_U16("graphics/outfit_menu/cursor.4bpp");
static const u16 sCursorSprite_Pal[] = INCBIN_U16("graphics/outfit_menu/cursor.gbapal");

static EWRAM_DATA OutfitMenuResources *sOutfitMenu = NULL;

static const struct BgTemplate sBGTemplates[] =
{
    [BG_MSGBOX] =
    { //! UI
        .baseTile = 0,
        .bg = BG_MSGBOX,
        .charBaseIndex = 1,
        .mapBaseIndex = 28,
        .paletteMode = 0,
        .priority = 0,
        .screenSize = 0,
    },
    [BG_TXT] =
    { //! UI
        .baseTile = 0,
        .bg = BG_TXT,
        .charBaseIndex = 1,
        .mapBaseIndex = 29,
        .paletteMode = 0,
        .priority = 1,
        .screenSize = 0,
    },
    [BG_MAIN] =
    { //! BG
        .baseTile = 0,
        .bg = BG_MAIN,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .paletteMode = 0,
        .priority = 2,
        .screenSize = 0,
    },
    [BG_SCROLL] =
    { //! SCROLLING BG
        .baseTile = 0,
        .bg = BG_SCROLL,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .paletteMode = 0,
        .priority = 3,
        .screenSize = 0,
    },
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_INFO] =
    {
        .bg = BG_TXT,
        .tilemapLeft = 1,
        .tilemapTop = 14,
        .width = 23,
        .height = 6,
        .paletteNum = 0,
        .baseBlock = 1,
    },
    [WIN_MSGBOX] =
    {
        .bg = BG_MSGBOX,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 1+(23*6),
    },
    DUMMY_WIN_TEMPLATE,
};

static const struct SpriteSheet sIndicator_SpriteSheet = {
    .data = sIndicatorSprite_Gfx,
    .size = 16*32/2,
    .tag = TAG_INDICATOR,
};

static const struct SpriteSheet sCursor_SpriteSheet = {
    .data = sCursorSprite_Gfx,
    .size = 32*32/2,
    .tag = TAG_CURSOR,
};

static const struct SpritePalette sIndicator_SpritePalette = {
    .data = sIndicatorSprite_Pal,
    .tag = TAG_INDICATOR,
};

static const struct SpritePalette sCursor_SpritePalette = {
    .data = sCursorSprite_Pal,
    .tag = TAG_CURSOR,
};

static const struct OamData sIndicator_SpriteOamData = {
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1,
};

static const struct OamData sCursor_SpriteOamData = {
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 2,
};

static const union AnimCmd sIndicator_NormalAnims[] = {
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END
};

static const union AnimCmd sIndicator_CursorAnims[] = {
    ANIMCMD_FRAME(4, 30),
    ANIMCMD_END
};

static const union AnimCmd *const sIndicator_Anims[] = {
    [I_ANIM_NORMAL] = sIndicator_NormalAnims,
    [I_ANIM_CURSOR] = sIndicator_CursorAnims,
};

static const struct SpriteTemplate sCursor_SpriteTemplate = {
    .tileTag = TAG_CURSOR,
    .paletteTag = TAG_CURSOR,
    .callback = SpriteCallbackDummy,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gDummySpriteAffineAnimTable,
    .images = NULL,
    .oam = &sCursor_SpriteOamData,
};

static const struct SpriteTemplate sIndicator_SpriteTemplate = {
    .tileTag = TAG_INDICATOR,
    .paletteTag = TAG_INDICATOR,
    .callback = SpriteCallbackDummy,
    .anims = sIndicator_Anims,
    .affineAnims = gDummySpriteAffineAnimTable,
    .images = NULL,
    .oam = &sIndicator_SpriteOamData,
};

/*
_________________
|_______________|
|             |#|
|             |#|
|_____________|#|
|_____________|#|
*/
static const u8 sGridPosX[] = { (208 + 16) };
static const u8 sGridPosY[] = { (20 + 16),   (52 + 16), (84 + 16), (116 + 16) };

void Task_OpenOutfitMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        CleanupOverworldWindowsAndTilemaps();
        OpenOutfitMenu(CB2_ReturnToField);
        DestroyTask(taskId);
    }
}

void OpenOutfitMenu(MainCallback retCB)
{
    sOutfitMenu = AllocZeroed(sizeof(*sOutfitMenu));
    if (sOutfitMenu == NULL)
    {
        //! Alloc failed, exit
        SetMainCallback2(retCB);
    }
    // measures for existing saves
    if (gSaveBlock2Ptr->currOutfitId == OUTFIT_NONE)
    {
        UnlockOutfit(DEFAULT_OUTFIT);
        gSaveBlock2Ptr->currOutfitId = DEFAULT_OUTFIT;
    }
    sOutfitMenu->retCB = retCB;
    SetMainCallback2(CB2_SetupOutfitMenu);
}

static void CB2_SetupOutfitMenu(void)
{
    switch(gMain.state)
    {
    case STATE_BEGIN:
        CpuFill16(0, (void *) VRAM, VRAM_SIZE);
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
    case STATE_RESET:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case STATE_LOADBG:
        SetupOutfitMenu_BGs();
        sOutfitMenu->gfxState = 0;
        gMain.state++;
        break;
    case STATE_LOADGFX:
        if (SetupOutfitMenu_Graphics())
            gMain.state++;
        break;
    case STATE_LOADWIN:
        SetupOutfitMenu_Windows();
        gMain.state++;
        break;
    case STATE_LOADSTR:
        SetupOutfitMenu_PrintStr();
        gMain.state++;
        break;
    case STATE_LOADGRID:
        sOutfitMenu->listCount = BuildOutfitLists();
        SetupOutfitMenu_Grids();
        gMain.state++;
        break;
    case STATE_LOADSPRITE:
        SetupOutfitMenu_Sprites();
        gMain.state++;
        break;
    case STATE_WAITFADE:
        CreateTask(Task_WaitFadeInOutfitMenu, 0);
        gMain.state++;
        break;
    case STATE_TRANSITION:
        BlendPalettes(PALETTES_ALL, 16, 0);
        gMain.state++;
        break;
    case STATE_FADE:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_OutfitMenu);
        SetMainCallback2(CB2_OutfitMenu);
        break;
    }
}

static void CB2_OutfitMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_OutfitMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ChangeBgX(BG_SCROLL, 96, BG_COORD_SUB);
    ChangeBgY(BG_SCROLL, 96, BG_COORD_SUB);
}

static void SetupOutfitMenu_BGs(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    ResetBgsAndClearDma3BusyFlags(0);
    ResetAllBgsCoordinates();
    InitBgsFromTemplates(0, sBGTemplates, ARRAY_COUNT(sBGTemplates));
    SetBgTilemapBuffer(BG_MAIN, sOutfitMenu->tilemapBuffers[0]);
    SetBgTilemapBuffer(BG_SCROLL, sOutfitMenu->tilemapBuffers[1]);
    ScheduleBgCopyTilemapToVram(BG_MAIN);
    ScheduleBgCopyTilemapToVram(BG_SCROLL);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(BG_MSGBOX);
    ShowBg(BG_TXT);
    ShowBg(BG_MAIN);
    ShowBg(BG_SCROLL);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

static bool32 SetupOutfitMenu_Graphics(void)
{
    switch(sOutfitMenu->gfxState)
    {
    case 0:
        ResetTempTileDataBuffers();
        LoadBgTiles(BG_MAIN, &sTiles, 96*72/2, 0x0);
        LoadMessageBoxGfx(BG_MSGBOX, 0x100, BG_PLTT_ID(13));
        LoadUserWindowBorderGfx(BG_MSGBOX, 0x10D, BG_PLTT_ID(14));
        sOutfitMenu->gfxState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sTilemap, sOutfitMenu->tilemapBuffers[0]);
            LZDecompressWram(sScrollingBG_Tilemap, sOutfitMenu->tilemapBuffers[1]);
            sOutfitMenu->gfxState++;
        }
        break;
    case 2:
        LoadPalette(&sPalette, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        LoadPalette(GetTextWindowPalette(2), BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        sOutfitMenu->gfxState++;
        break;
    default:
        return TRUE;
    }
    return FALSE;
}

static inline void PrintTexts(u8 winId, u8 font, u8 x, u8 y, u8 color, const u8 *str)
{
    AddTextPrinterParameterized4(winId, font, x, y, 0, 0, sFontColors[color], 0, str);
}

static void SetupOutfitMenu_Windows(void)
{
    u32 i;
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    for (i = 0; i < ARRAY_COUNT(sWindowTemplates); i++)
    {
        FillWindowPixelBuffer(i, PIXEL_FILL(0));
        PutWindowTilemap(i);
    }

    ScheduleBgCopyTilemapToVram(BG_MSGBOX);
    ScheduleBgCopyTilemapToVram(BG_TXT);
}

static void SetupOutfitMenu_PrintStr(void)
{
    PrintTexts(WIN_INFO, FONT_NORMAL, 2, 0, COLORID_NORMAL, gOutfits[gSaveBlock2Ptr->currOutfitId].name);
    PrintTexts(WIN_INFO, FONT_NORMAL, 2, 16, COLORID_NORMAL, gOutfits[gSaveBlock2Ptr->currOutfitId].desc);
    CopyWindowToVram(WIN_INFO, COPYWIN_FULL);
}

static inline void SetupOutfitMenu_Sprites_DrawTrainerSprite(bool32 update, bool32 unlocked)
{
    enum TrainerPicID picId = GetPlayerTrainerPicIdByOutfitAndGender(sOutfitMenu->idx, gSaveBlock2Ptr->playerGender);
    u32 frontSpriteId = picId;
    u32 backSpriteId = picId;
    u32 frontPalSlot = sOutfitMenu->slotId ? 9 : 10;
    u32 backPalSlot = sOutfitMenu->slotId ? 12 : 13;
    if (update)
    {
        FreeAndDestroyTrainerPicSprite(sOutfitMenu->spriteIds[GFX_FTS]);
        FreeAndDestroyTrainerPicSprite(sOutfitMenu->spriteIds[GFX_BTS]);
    }

    sOutfitMenu->spriteIds[GFX_FTS] = CreateTrainerPicSprite(frontSpriteId, TRUE, 32+27, 32+32, frontPalSlot, TAG_NONE);
    sOutfitMenu->spriteIds[GFX_BTS] = CreateTrainerPicSprite(backSpriteId, FALSE, 32+117, 32+32, backPalSlot, TAG_NONE);
    LoadPalette(GetTrainerBackPicPalette(backSpriteId), OBJ_PLTT_ID(backPalSlot), PLTT_SIZE_4BPP);
    gSprites[sOutfitMenu->spriteIds[GFX_BTS]].anims = GetTrainerBackPicAnims(backSpriteId);
    StartSpriteAnim(&gSprites[sOutfitMenu->spriteIds[GFX_BTS]], 0);
    if (!unlocked)
    {
        // bc we're directly tint to idx 1-15, skipping idx 0
        // there's no point of tinting idx 0

        // front
        TintPalette_GrayScale(&gPlttBufferUnfaded[OBJ_PLTT_ID(frontPalSlot)+1], PLTT_SIZE_4BPP-1);
        CpuCopy16(&gPlttBufferUnfaded[OBJ_PLTT_ID(frontPalSlot)+1], &gPlttBufferFaded[OBJ_PLTT_ID(frontPalSlot)+1], PLTT_SIZE_4BPP-1);

        // back
        TintPalette_GrayScale(&gPlttBufferUnfaded[OBJ_PLTT_ID(backPalSlot)+1], PLTT_SIZE_4BPP-1);
        CpuCopy16(&gPlttBufferUnfaded[OBJ_PLTT_ID(backPalSlot)+1], &gPlttBufferFaded[OBJ_PLTT_ID(backPalSlot)+1], PLTT_SIZE_4BPP-1);
    }
    sOutfitMenu->slotId ^= 1;
}

static inline void SetupOutfitMenu_Sprites_DrawCursorSprite(void)
{
    u32 row = sOutfitMenu->grid->selectedItem / sOutfitMenu->grid->maxCols;
    u32 col = sOutfitMenu->grid->selectedItem % sOutfitMenu->grid->maxCols;
    u32 x = ((col % GRID_COLS) < ARRAY_COUNT(sGridPosX)) ? sGridPosX[col] : sGridPosX[0];
    u32 y = ((row % GRID_ROWS) < ARRAY_COUNT(sGridPosY)) ? sGridPosY[row] : sGridPosY[0];

    LoadSpriteSheet(&sCursor_SpriteSheet);
    LoadSpritePalette(&sCursor_SpritePalette);
    sOutfitMenu->spriteIds[GFX_CURSOR] = CreateSprite(&sCursor_SpriteTemplate, x, y, 2);
}

static void SetupOutfitMenu_Sprites(void)
{
    SetupOutfitMenu_Sprites_DrawTrainerSprite(FALSE, GetOutfitStatus(sOutfitMenu->idx));
    SetupOutfitMenu_Sprites_DrawCursorSprite();
}

static u32 CountAndFilterTotalOutfit(void)
{
    u32 i = 0, j = OUTFIT_BEGIN;
    while (j < OUTFIT_COUNT)
    {
        if ((gOutfits[j].isHidden && !GetOutfitStatus(j)))
        {
            j++;
            continue; // skip
        }

        DebugPrintf("i: %d, j: %d, list: %S", i, j, gOutfits[j].name);
        i++;
        j++;
    }
    return i;
}

static void SpriteCB_Indicator(struct Sprite *s)
{
    u32 idx = s->data[0];
    u32 i = sOutfitMenu->list[sOutfitMenu->grid->topLeftItemIndex + idx];
    if (i == gSaveBlock2Ptr->currOutfitId)
    {
        s->invisible = FALSE;
    }
    else
    {
        s->invisible = TRUE;
    }

    // use different anim when there's a cursor for cool immersion
    if (idx == sOutfitMenu->grid->selectedItem && GetOutfitStatus(i))
    {
        StartSpriteAnimIfDifferent(s, I_ANIM_CURSOR);
    }
    else
    {
        StartSpriteAnimIfDifferent(s, I_ANIM_NORMAL);
    }
}

static inline void ForEachCB_DrawIndicatorSprites(u32 idx, u32 col, u32 row)
{
    u32 x, y, i;
    if (idx >= sOutfitMenu->listCount)
        return;

    i = sOutfitMenu->grid->topLeftItemIndex + idx;
    x = ((col % GRID_COLS) < ARRAY_COUNT(sGridPosX)) ? sGridPosX[col] : sGridPosX[0];
    y = ((row % GRID_ROWS) < ARRAY_COUNT(sGridPosY)) ? sGridPosY[row] : sGridPosY[0];
    x -= 8, y -= 8;
    sOutfitMenu->currentOutfitSpriteIds[idx] = CreateSprite(&sIndicator_SpriteTemplate, x, y, 0);
    gSprites[sOutfitMenu->currentOutfitSpriteIds[idx]].data[0] = idx;
    gSprites[sOutfitMenu->currentOutfitSpriteIds[idx]].callback = SpriteCB_Indicator;
}

static void ForAllCb_DestroyIndicatorSprites(u32 idx, u32 col, u32 row)
{
    if (sOutfitMenu->currentOutfitSpriteIds[idx] == SPRITE_NONE)
        return;

    if (gSprites[sOutfitMenu->currentOutfitSpriteIds[idx]].inUse)
    {
        DestroySprite(&gSprites[sOutfitMenu->currentOutfitSpriteIds[idx]]);
    }

    sOutfitMenu->currentOutfitSpriteIds[idx] = SPRITE_NONE;
}

static void SpriteCB_Overworld(struct Sprite *s)
{
    u32 idx = s->data[0];
    u32 i = sOutfitMenu->list[sOutfitMenu->grid->topLeftItemIndex + idx];
    // play anim only if it's currecntly picked AND that it's unlocked
    if (idx == sOutfitMenu->grid->selectedItem && GetOutfitStatus(i))
    {
        StartSpriteAnimIfDifferent(s, ANIM_STD_GO_SOUTH);
    }
    else
    {
        StartSpriteAnimIfDifferent(s, ANIM_STD_FACE_SOUTH);
    }
}

static void ForEachCB_PopulateOutfitOverworlds(u32 idx, u32 col, u32 row)
{
    u32 i = sOutfitMenu->list[sOutfitMenu->grid->topLeftItemIndex + idx];
    u32 gfx, x, y;
    if (i >= OUTFIT_COUNT || idx >= sOutfitMenu->listCount)
        return;

    gfx = GetPlayerAvatarGraphicsIdByOutfitStateIdAndGender(i, PLAYER_AVATAR_STATE_NORMAL, gSaveBlock2Ptr->playerGender);
    x = ((col % GRID_COLS) < ARRAY_COUNT(sGridPosX)) ? sGridPosX[col] : sGridPosX[0];
    y = ((row % GRID_ROWS) < ARRAY_COUNT(sGridPosY)) ? sGridPosY[row] : sGridPosY[0];

    sOutfitMenu->grid->iconSpriteIds[idx] = CreateObjectGraphicsSprite(gfx, SpriteCB_Overworld, x, y, 0);
    gSprites[sOutfitMenu->grid->iconSpriteIds[idx]].data[0] = idx;
    if (!GetOutfitStatus(i))
    {
        // bc we're directly tint to idx 1-15, skipping idx 0
        // there's no point of tinting idx 0
        u32 j = OBJ_PLTT_ID(gSprites[sOutfitMenu->grid->iconSpriteIds[idx]].oam.paletteNum)+1;
        TintPalette_GrayScale(&gPlttBufferUnfaded[j], PLTT_SIZE_4BPP-1);
        CpuCopy16(&gPlttBufferUnfaded[j], &gPlttBufferFaded[j], PLTT_SIZE_4BPP-1);
    }
}

static void ForAllCB_FreeOutfitOverworlds(u32 idx, u32 col, u32 row)
{
    if (sOutfitMenu->grid->iconSpriteIds[idx] == SPRITE_NONE)
        return;

    if (gSprites[sOutfitMenu->grid->iconSpriteIds[idx]].inUse)
    {
        DestroySprite(&gSprites[sOutfitMenu->grid->iconSpriteIds[idx]]);
    }

    sOutfitMenu->grid->iconSpriteIds[idx] = SPRITE_NONE;
}

static void InputCB_UpDownScroll(void)
{
    sOutfitMenu->idx = sOutfitMenu->list[GridMenu_SelectedIndex(sOutfitMenu->grid)];
    GridMenu_ForAll(sOutfitMenu->grid, ForAllCB_FreeOutfitOverworlds);
    GridMenu_ForAll(sOutfitMenu->grid, ForAllCb_DestroyIndicatorSprites);
    GridMenu_ForEach(sOutfitMenu->grid, ForEachCB_PopulateOutfitOverworlds);
    GridMenu_ForEach(sOutfitMenu->grid, ForEachCB_DrawIndicatorSprites);
    UpdateOutfitInfo();
    if (!IsSEPlaying())
        PlaySE(SE_RG_BAG_CURSOR);
}

static void InputCB_Move(void)
{
    sOutfitMenu->idx = sOutfitMenu->list[GridMenu_SelectedIndex(sOutfitMenu->grid)];
    UpdateOutfitInfo();
    if (!IsSEPlaying())
        PlaySE(SE_RG_BAG_CURSOR);
}

static void InputCB_Fail(void)
{
    if (!IsSEPlaying())
        PlaySE(SE_BOO);
}

// the return value here is the count
static u32 BuildOutfitLists(void)
{
    u32 i = 0, j = 1;
    sOutfitMenu->list = AllocZeroed(CountAndFilterTotalOutfit() * sizeof(u8));
    while (j < OUTFIT_COUNT)
    {
        if ((gOutfits[j].isHidden && !GetOutfitStatus(j)))
        {
            j++;
            continue; // skip
        }

        sOutfitMenu->list[i] = j;
        DebugPrintf("i: %d, j: %d, list: %S", i, j, gOutfits[sOutfitMenu->list[i]].name);
        i++;
        j++;
    }

    return i;
}

static void SetupOutfitMenu_Grids(void)
{
    sOutfitMenu->grid = GridMenu_Init(GRID_COLS, GRID_ROWS, CountAndFilterTotalOutfit());

    LoadSpriteSheet(&sIndicator_SpriteSheet);
    LoadSpritePalette(&sIndicator_SpritePalette);

    GridMenu_EnableVerticalWrapAround(sOutfitMenu->grid);
    GridMenu_SetIndex(sOutfitMenu->grid, gSaveBlock2Ptr->currOutfitId - 1);
    sOutfitMenu->idx = sOutfitMenu->list[GridMenu_SelectedIndex(sOutfitMenu->grid)];

    GridMenu_SetInputCallback(sOutfitMenu->grid, InputCB_Move, DIRECTION_UP, TYPE_MOVE);
    GridMenu_SetInputCallback(sOutfitMenu->grid, InputCB_Move, DIRECTION_DOWN, TYPE_MOVE);
    GridMenu_SetInputCallback(sOutfitMenu->grid, InputCB_Fail, DIRECTION_UP, TYPE_FAIL);
    GridMenu_SetInputCallback(sOutfitMenu->grid, InputCB_Fail, DIRECTION_DOWN, TYPE_FAIL);
    GridMenu_SetInputCallback(sOutfitMenu->grid, InputCB_UpDownScroll, DIRECTION_UP, TYPE_SCROLL);
    GridMenu_SetInputCallback(sOutfitMenu->grid, InputCB_UpDownScroll, DIRECTION_DOWN, TYPE_SCROLL);
    GridMenu_ForEach(sOutfitMenu->grid, ForEachCB_PopulateOutfitOverworlds);
    GridMenu_ForEach(sOutfitMenu->grid, ForEachCB_DrawIndicatorSprites);
}

//! Similar to above, but without redrawing the frame
//! and also clean up the frame.
static inline void UpdateOutfitInfo(void)
{
    FillWindowPixelBuffer(WIN_INFO, PIXEL_FILL(0));

    if (GetOutfitStatus(sOutfitMenu->idx) == FALSE)
    {
        PrintTexts(WIN_INFO, FONT_NORMAL, 2, 0, COLORID_NORMAL, sText_OutfitLocked);
        PrintTexts(WIN_INFO, FONT_NORMAL, 2, 16, COLORID_NORMAL, sText_OutfitLocked);
    }
    else
    {
        PrintTexts(WIN_INFO, FONT_NORMAL, 2, 0, COLORID_NORMAL, gOutfits[sOutfitMenu->idx].name);
        PrintTexts(WIN_INFO, FONT_NORMAL, 2, 16, COLORID_NORMAL, gOutfits[sOutfitMenu->idx].desc);
    }
    CopyWindowToVram(WIN_INFO, COPYWIN_FULL);

    SetupOutfitMenu_Sprites_DrawTrainerSprite(TRUE, GetOutfitStatus(sOutfitMenu->idx));
}

static void Task_WaitFadeInOutfitMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        PlaySE(SE_RG_HELP_OPEN);
        gTasks[taskId].func = Task_OutfitMenuHandleInput;
    }
}

static void Task_WaitMessage(u8 taskId)
{
    if (!IsTextPrinterActive(WIN_MSGBOX) && (JOY_NEW(A_BUTTON | B_BUTTON) || --gTasks[taskId].data[0] == 0))
    {
        ClearDialogWindowAndFrame(WIN_MSGBOX, TRUE);
        UpdateOutfitInfo();
        gTasks[taskId].func = Task_OutfitMenuHandleInput;
    }
}

static inline void PrintDialogueBoxWithDescWin(const u8 *str, bool32 expandPlaceholders, u8 taskId)
{
    const u8 *txt = expandPlaceholders ? gStringVar4 : str;
    DrawDialogFrameWithCustomTileAndPalette(WIN_MSGBOX, TRUE, 0x100, 13);

    if (expandPlaceholders)
    {
        StringExpandPlaceholders(gStringVar4, str);
    }

    PrintTexts(WIN_MSGBOX, FONT_NORMAL, 0, 0, COLORID_MSGBOX, txt);
    CopyWindowToVram(WIN_MSGBOX, COPYWIN_FULL);
    gTasks[taskId].data[0] = 120;
    gTasks[taskId].func = Task_WaitMessage;
}

static void Task_PrintCantChangeOutfit(u8 taskId)
{
    if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_BIKE)
        StringCopy(gStringVar1, sText_OutfitError_Cycling);
    else if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_SURFING)
        StringCopy(gStringVar1, sText_OutfitError_Surfing);
    else if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_UNDERWATER)
        StringCopy(gStringVar1, sText_OutfitError_Diving);
    else
        StringCopy(gStringVar1, sText_OutfitError_Default);

    PrintDialogueBoxWithDescWin(sText_OutfitError, TRUE, taskId);
}

static void Task_PrintOutfitLocked(u8 taskId)
{
    PrintDialogueBoxWithDescWin(sText_OutfitLockedMsg, FALSE, taskId);
}

static inline void CloseOutfitMenu(u8 taskId)
{
    PlaySE(SE_RG_HELP_CLOSE);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_CloseOutfitMenu;
}

static void UpdateCursorPosition(void)
{
    u32 row = sOutfitMenu->grid->selectedItem / sOutfitMenu->grid->maxCols;
    u32 col = sOutfitMenu->grid->selectedItem % sOutfitMenu->grid->maxCols;
    u32 x = ((col % GRID_COLS) < ARRAY_COUNT(sGridPosX)) ? sGridPosX[col] : sGridPosX[0];
    u32 y = ((row % GRID_ROWS) < ARRAY_COUNT(sGridPosY)) ? sGridPosY[row] : sGridPosY[0];
    gSprites[sOutfitMenu->spriteIds[GFX_CURSOR]].x = x;
    gSprites[sOutfitMenu->spriteIds[GFX_CURSOR]].y = y;
}

#define PICK_BUTTONS  (DPAD_DOWN | DPAD_UP)
#define CLOSE_BUTTONS (B_BUTTON | START_BUTTON)

static void Task_OutfitMenuHandleInput(u8 taskId)
{
    GridMenu_HandleInput(sOutfitMenu->grid);
    if (JOY_NEW(CLOSE_BUTTONS))
        CloseOutfitMenu(taskId);

    if (JOY_NEW(A_BUTTON))
    {
        if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_ON_FOOT)
        {
            if (GetOutfitStatus(sOutfitMenu->idx))
            {
                PlaySE(SE_SUCCESS);
                gSaveBlock2Ptr->currOutfitId = sOutfitMenu->idx;
            }
            else
            {
                PlaySE(SE_BOO);
                gTasks[taskId].func = Task_PrintOutfitLocked;
            }
        }
        else
        {
            PlaySE(SE_BOO);
            if (GetOutfitStatus(sOutfitMenu->idx))
                gTasks[taskId].func = Task_PrintCantChangeOutfit;
            else
                gTasks[taskId].func = Task_PrintOutfitLocked; //! might be confusing?
        }
    }

    UpdateCursorPosition();
}

static void FreeOutfitMenuResources(void)
{
    u32 i;
    DestroySprite(&gSprites[sOutfitMenu->spriteIds[GFX_OW]]);
    FreeAndDestroyTrainerPicSprite(sOutfitMenu->spriteIds[GFX_FTS]);
    FreeAndDestroyTrainerPicSprite(sOutfitMenu->spriteIds[GFX_BTS]);
    for (i = 0; i < sOutfitMenu->grid->maxSize; i++)
    {
        DestroySprite(&gSprites[sOutfitMenu->currentOutfitSpriteIds[i]]);
    }
    GridMenu_Destroy(sOutfitMenu->grid);
    TRY_FREE_AND_SET_NULL(sOutfitMenu->list);
    TRY_FREE_AND_SET_NULL(sOutfitMenu);
    ResetSpriteData();
    FreeAllSpritePalettes();
    FreeAllWindowBuffers();
}

static void Task_CloseOutfitMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sOutfitMenu->retCB);
        FreeOutfitMenuResources();
        DestroyTask(taskId);
    }
}

//! misc funcs

void BufferOutfitStrings(u8 *dest, u8 outfitId, u8 dataType)
{
    const u8 *src = NULL;

    if (outfitId == OUTFIT_NONE || outfitId >= OUTFIT_COUNT)
    {
        outfitId = DEFAULT_OUTFIT;
    }

    switch(dataType)
    {
    default:
    case OUTFIT_BUFFER_NAME:
        src = gOutfits[outfitId].name;
        break;
    case OUTFIT_BUFFER_DESC:
        src = gOutfits[outfitId].desc;
        break;
    }
    StringCopy(dest, src);
}

enum TrainerPicID GetPlayerTrainerPicIdByOutfitAndGender(u32 outfitId, enum Gender gender)
{
    if (outfitId > OUTFIT_NONE && outfitId < OUTFIT_COUNT)
        return gOutfits[outfitId].trainerPics[gender];
    else
        return gOutfits[DEFAULT_OUTFIT].trainerPics[gender];
}

const void *GetPlayerHeadGfxOrPal(u8 which, bool32 isFP)
{
    if (which == PAL)
    {
        u32 tag = GetObjectEventGraphicsInfo(
            GetPlayerAvatarGraphicsIdByOutfitStateIdAndGender(gSaveBlock2Ptr->currOutfitId, PLAYER_AVATAR_STATE_NORMAL, gSaveBlock2Ptr->playerGender))->paletteTag;

        return GetObjectEventPaletteFromTag(tag)->data;
    }
    else
    {
        if (gSaveBlock2Ptr->currOutfitId == OUTFIT_NONE || gSaveBlock2Ptr->currOutfitId >= OUTFIT_COUNT)
        {
            gSaveBlock2Ptr->currOutfitId = DEFAULT_OUTFIT;
        }

        if (isFP)
        {
            return gSaveBlock2Ptr->playerGender ?
                        gOutfits[gSaveBlock2Ptr->currOutfitId].iconsFP + 0x80 :
                        gOutfits[gSaveBlock2Ptr->currOutfitId].iconsFP;
        }
        else
            return gOutfits[gSaveBlock2Ptr->currOutfitId].iconsRM[gSaveBlock2Ptr->playerGender];
    }
}

u16 *GetOutfitPointer(u16 id)
{
    if (id > OUTFIT_COUNT)
        return NULL;
    else
        return &gSaveBlock2Ptr->outfits[id / 8];
}

u16 UnlockOutfit(u16 id)
{
    u16 *ptr = GetOutfitPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u16 ToggleOutfit(u16 id)
{
    u16 *ptr = GetOutfitPointer(id);
    if (ptr)
        *ptr ^= 1 << (id & 7);
    return 0;
}

u16 LockOutfit(u16 id)
{
    u16 *ptr = GetOutfitPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 GetOutfitStatus(u16 id)
{
    u16 *ptr = GetOutfitPointer(id);

    // return false if GetOutfitPointer returns NULL
    if (!ptr)
        return FALSE;

    // return false if flag is not set
    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    // rest
    return TRUE;
}

bool8 IsPlayerWearingOutfit(u16 id)
{
    if (gSaveBlock2Ptr->currOutfitId == id)
        return TRUE;

    return FALSE;
}

u32 GetOutfitPrice(u16 id)
{
    return gOutfits[id].prices[gSaveBlock2Ptr->playerGender];
}

void SetCurrentOutfitGfxIntoVar(struct ScriptContext *ctx)
{
    u32 varId = ScriptReadHalfword(ctx);
    u32 state = ScriptReadHalfword(ctx);
    u32 gfxId = GetPlayerAvatarGraphicsIdByOutfitStateIdAndGender(
        gSaveBlock2Ptr->currOutfitId, state, gSaveBlock2Ptr->playerGender);

    VarSet(varId, gfxId);
}
