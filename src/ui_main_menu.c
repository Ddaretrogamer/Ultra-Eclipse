#include "global.h"
#include "ui_main_menu.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "main_menu.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "option_menu.h"
#include "overworld.h"
#include "outfit_menu.h"
#include "palette.h"
#include "pokedex.h"
#include "region_map.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "title_screen.h"
#include "constants/rgb.h"
#include "constants/flags.h"
#include "constants/songs.h"

#define TAG_CURSOR 30012
#define PORTRAIT_TILE 256
#define PORTRAIT_BG_TILE (PORTRAIT_TILE + 36)
#define PANEL_TILE_BYTES (128 * 80)
#define CRYSTAL_PALETTE_OFFSET 48
#define CRYSTAL_PALETTE_COLORS 74
#define CRYSTAL_ROW_X 6
#define CRYSTAL_ROW_Y 13

enum { OPTION_CONTINUE, OPTION_NEW_GAME, OPTION_OPTIONS };
enum { WIN_HEADER, WIN_INFO, WIN_NEW_GAME, WIN_OPTIONS, WIN_COUNT };
#include "mystery_event_menu.h"
#include "mystery_gift_menu.h"
#include "kukui_call.h"
#include "link.h"

struct MainMenuResources
{
    MainCallback savedCallback;
    u16 panelTilemap[32 * 32];
    u16 waterTilemap[32 * 32];
    u16 portraitTilemap[32 * 32];
    u8 *panelTiles;
    u8 cursorSpriteId;
};

static EWRAM_DATA struct MainMenuResources *sMainMenu = NULL;
static EWRAM_DATA u8 sSelectedOption = OPTION_CONTINUE;

static const struct BgTemplate sBgTemplates[] =
{
    {.bg = 0, .charBaseIndex = 0, .mapBaseIndex = 31, .priority = 0},
    {.bg = 1, .charBaseIndex = 1, .mapBaseIndex = 30, .paletteMode = 1, .priority = 2},
    {.bg = 2, .charBaseIndex = 2, .mapBaseIndex = 28, .priority = 3},
    {.bg = 3, .charBaseIndex = 0, .mapBaseIndex = 29, .priority = 1},
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_HEADER] = {.bg = 0, .tilemapLeft = 3, .tilemapTop = 1, .width = 14, .height = 2, .paletteNum = 15, .baseBlock = 1},
    [WIN_INFO] = {.bg = 0, .tilemapLeft = 12, .tilemapTop = 4, .width = 15, .height = 9, .paletteNum = 15, .baseBlock = 29},
    [WIN_NEW_GAME] = {.bg = 0, .tilemapLeft = 3, .tilemapTop = 17, .width = 10, .height = 2, .paletteNum = 15, .baseBlock = 164},
    [WIN_OPTIONS] = {.bg = 0, .tilemapLeft = 18, .tilemapTop = 17, .width = 10, .height = 2, .paletteNum = 15, .baseBlock = 184},
    DUMMY_WIN_TEMPLATE
};

static const u32 sPanelTiles[] = INCGFX_U32("graphics/ui_main_menu/sm/bg_tiles.png", ".8bpp.lz");
// The supplied map is a packed 30 x 20 rectangle, including flip bits.
static const u16 sPanelTilemap[] = INCBIN_U16("graphics/ui_main_menu/sm/bg_tiles.bin");
static const u16 sPanelPalette[] = INCGFX_U16("graphics/ui_main_menu/sm/bg_tiles.png", ".gbapal", "-num_colors 32");
static const u8 sCrystalTiles[] = INCGFX_U8("graphics/ui_main_menu/sm/crystals.png", ".8bpp");
static const u16 sCrystalPalette[] = INCGFX_U16("graphics/ui_main_menu/sm/crystals.png", ".gbapal", "-num_colors 74");
// Matches the left-to-right tile order in crystals.png.
static const u16 sCrystalFlags[] =
{
    FLAG_COLLECTED_NORMALIUM_Z, FLAG_COLLECTED_FIRIUM_Z, FLAG_COLLECTED_WATERIUM_Z, FLAG_COLLECTED_ELECTRIUM_Z,
    FLAG_COLLECTED_GRASSIUM_Z, FLAG_COLLECTED_ICIUM_Z, FLAG_COLLECTED_FIGHTINIUM_Z, FLAG_COLLECTED_POISONIUM_Z,
    FLAG_COLLECTED_GROUNDIUM_Z, FLAG_COLLECTED_FLYINIUM_Z, FLAG_COLLECTED_PSYCHIUM_Z, FLAG_COLLECTED_BUGINIUM_Z,
    FLAG_COLLECTED_ROCKIUM_Z, FLAG_COLLECTED_GHOSTIUM_Z, FLAG_COLLECTED_DRAGONIUM_Z, FLAG_COLLECTED_DARKINIUM_Z,
    FLAG_COLLECTED_STEELIUM_Z, FLAG_COLLECTED_FAIRIUM_Z,
};
STATIC_ASSERT(sizeof(sCrystalTiles) == ARRAY_COUNT(sCrystalFlags) * 64, CrystalTileCount);
static const u32 sScrollBgTiles[] = INCGFX_U32("graphics/ui_main_menu/waterscroll.png", ".4bpp.lz");
static const u32 sScrollBgTilemap[] = INCGFX_U32("graphics/ui_main_menu/waterscroll.bin", ".lz");
static const u16 sScrollBgPalette[] = INCGFX_U16("graphics/ui_main_menu/waterscroll.png", ".gbapal");
static const u16 sPortraitBgTiles[] = INCGFX_U16("graphics/ui_main_menu/sm/mugshot_BG.png", ".4bpp");
static const u16 sPortraitBgPalette[] = INCGFX_U16("graphics/ui_main_menu/sm/mugshot_BG.png", ".gbapal");
static const u32 sCursorTiles[] = INCGFX_U32("graphics/ui_main_menu/sm/cursor.png", ".4bpp.lz");
static const u16 sCursorPalette[] = INCGFX_U16("graphics/ui_main_menu/sm/cursor.png", ".gbapal");
static const struct CompressedSpriteSheet sCursorSheet = {sCursorTiles, 16 * 16 / 2 * 3, TAG_CURSOR};
static const struct SpritePalette sCursorPal = {sCursorPalette, TAG_CURSOR};
static const struct OamData sCursorOam =
{
    .shape = SPRITE_SHAPE(16x16), .size = SPRITE_SIZE(16x16), .priority = 0,
};
static const union AnimCmd sCursorAnim[] =
{
    ANIMCMD_FRAME(0, 8), ANIMCMD_FRAME(4, 8), ANIMCMD_FRAME(8, 8), ANIMCMD_JUMP(0),
};
static const union AnimCmd *const sCursorAnims[] = {sCursorAnim};
static const struct SpriteTemplate sCursorTemplate =
{
    .tileTag = TAG_CURSOR, .paletteTag = TAG_CURSOR, .oam = &sCursorOam,
    .anims = sCursorAnims, .affineAnims = gDummySpriteAffineAnimTable, .callback = SpriteCallbackDummy,
};
static const u16 sTextPalette[16] = {[1] = RGB(9, 8, 7), [2] = RGB(27, 25, 21)};
static const u8 sTextContinue[] = _("Continue");
static const u8 sTextNewGame[] = _("New Game");
static const u8 sTextOptions[] = _("Options");
static const u8 sTextDex[] = _("Pokédex:                {STR_VAR_1}");
static const u8 sTextTime[] = _("Time:                  {STR_VAR_1}:{STR_VAR_2}");

static void MainMenu_RunSetup(void);
static void Task_MainMenuInput(u8 taskId);

static const struct ScanlineEffectParams sScanlineParams_Parallax =
{
    .dmaDest = &REG_BG2HOFS, // Destination is BG2HOFS (horizontal offset for BG2)
    .dmaControl = SCANLINE_EFFECT_DMACNT_16BIT, // Use 16-bit DMA
    .initState = 1 // Enable the scanline effect
};

static const u16 sParallaxScrollSpeeds[][8] =
{
    {Q_8_8(0.1), Q_8_8(0.2), Q_8_8(0.2), Q_8_8(0.3), Q_8_8(0.3), Q_8_8(0.4), Q_8_8(0.5), Q_8_8(0.1)},
};

static void Task_ParallaxScroll(u8 taskId)
{
    u32 i;
    s16 *data = gTasks[taskId].data;

    // Update the scroll data for each layer
    data[0] += sParallaxScrollSpeeds[0][0];
    data[1] += sParallaxScrollSpeeds[0][1];
    data[2] += sParallaxScrollSpeeds[0][2];
    data[3] += sParallaxScrollSpeeds[0][3];
    data[4] += sParallaxScrollSpeeds[0][4];
    data[5] += sParallaxScrollSpeeds[0][5];
    data[6] += sParallaxScrollSpeeds[0][6];
    data[7] -= sParallaxScrollSpeeds[0][7];

    // Update the scanline offsets for each line
    for (i = 0; i < DISPLAY_HEIGHT; i++)
    {
        if (i <= 88)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[7]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[7]);
        }
        else if (i <= 96)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[0]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[0]);
        }
        else if (i <= 104)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[1]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[1]);
        }
        else if (i <= 112)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[2]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[2]);
        }
        else if (i <= 120)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[3]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[3]);
        }
        else if (i <= 128)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[4]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[4]);
        }
        else if (i <= 138)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[5]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[5]);
        }
        else if (i <= DISPLAY_HEIGHT)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[6]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[6]);
        }
    }
}

static void InitParallaxEffect(void)
{
    // Stop and clear any previous scanline effects
    ScanlineEffect_Stop();
    ScanlineEffect_Clear();

    // Initialize the scanline buffers to 0
    CpuFastFill16(0, gScanlineEffectRegBuffers, sizeof(gScanlineEffectRegBuffers));

    // Set the scanline effect parameters
    ScanlineEffect_SetParams(sScanlineParams_Parallax);

    // Create the task to update the parallax scrolling
    CreateTask(Task_ParallaxScroll, 0);
}


static void MainMenu_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void MainMenu_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ScanlineEffect_InitHBlankDmaTransfer();
}

static void UpdateCursor(void)
{
    static const s16 positions[][2] = {{16, 72}, {8, 144}, {128, 144}};
    if (sMainMenu->cursorSpriteId != SPRITE_NONE)
    {
        gSprites[sMainMenu->cursorSpriteId].x = positions[sSelectedOption][0];
        gSprites[sMainMenu->cursorSpriteId].y = positions[sSelectedOption][1];
    }
}

static void PrintText(u8 window, u8 x, u8 y, const u8 *text)
{
    static const u8 colors[] = {0, 1, 2};
    AddTextPrinterParameterized4(window, FONT_NORMAL, x, y, 0, 0, colors, TEXT_SKIP_DRAW, text);
}

static void InitWindowsAndPortrait(void)
{
    u32 i, x, y;
    u32 dexCount = 0;
    u8 mapName[MAP_NAME_LENGTH + 1];

    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    LoadPalette(sTextPalette, 15 * 16, sizeof(sTextPalette));
    LoadPalette(GetCurrentOutfitMugshot(PAL), 13 * 16, 32);
    LoadPalette(sPortraitBgPalette, 14 * 16, 32);
    LoadBgTiles(0, GetCurrentOutfitMugshot(GFX), 48 * 48 / 2, PORTRAIT_TILE);
    LoadBgTiles(3, sPortraitBgTiles, sizeof(sPortraitBgTiles), PORTRAIT_BG_TILE);
    for (i = 0; i < WIN_COUNT; i++)
    {
        FillWindowPixelBuffer(i, PIXEL_FILL(0));
        PutWindowTilemap(i);
    }
    // Each portrait is six tiles wide; BG3 supplies the separate backdrop.
    for (y = 0; y < 6; y++)
    {
        for (x = 0; x < 6; x++)
        {
            FillBgTilemapBufferRect(0, PORTRAIT_TILE + y * 6 + x, 4 + x, 6 + y, 1, 1, 13);
            FillBgTilemapBufferRect(3, PORTRAIT_BG_TILE + y * 6 + x, 4 + x, 6 + y, 1, 1, 14);
        }
    }
    // Box centers are x = 72, 60, and 180; account for each window's origin.
    PrintText(WIN_HEADER, GetStringCenterAlignXOffset(FONT_NORMAL, sTextContinue, 96), 0, sTextContinue);
    PrintText(WIN_INFO, 0, 0, gSaveBlock2Ptr->playerName);
    GetMapName(mapName, GetCurrentRegionMapSectionId(), 0);
    PrintText(WIN_INFO, 0, 16, mapName);
    if (FlagGet(FLAG_SYS_POKEDEX_GET))
        dexCount = IsNationalPokedexEnabled() ? GetNationalPokedexCount(FLAG_GET_CAUGHT) : GetHoennPokedexCount(FLAG_GET_CAUGHT);
    ConvertIntToDecimalStringN(gStringVar1, dexCount, STR_CONV_MODE_LEFT_ALIGN, 4);
    StringExpandPlaceholders(gStringVar4, sTextDex);
    PrintText(WIN_INFO, 0, 32, gStringVar4);
    ConvertIntToDecimalStringN(gStringVar1, gSaveBlock2Ptr->playTimeHours, STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, gSaveBlock2Ptr->playTimeMinutes, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringExpandPlaceholders(gStringVar4, sTextTime);
    PrintText(WIN_INFO, 0, 48, gStringVar4);
    PrintText(WIN_NEW_GAME, GetStringCenterAlignXOffset(FONT_NORMAL, sTextNewGame, 72), 0, sTextNewGame);
    PrintText(WIN_OPTIONS, GetStringCenterAlignXOffset(FONT_NORMAL, sTextOptions, 72), 0, sTextOptions);
    for (i = 0; i < WIN_COUNT; i++)
        CopyWindowToVram(i, COPYWIN_FULL);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(3);
}

void MainMenu_Init(MainCallback callback)
{
    sMainMenu = AllocZeroed(sizeof(*sMainMenu));
    if (sMainMenu == NULL)
    {
        SetMainCallback2(callback);
        return;
    }
    sMainMenu->savedCallback = callback;
    sMainMenu->cursorSpriteId = SPRITE_NONE;
    if (sSelectedOption > OPTION_OPTIONS)
        sSelectedOption = OPTION_CONTINUE;
    gMain.state = 0;
    SetMainCallback2(MainMenu_RunSetup);
}

void Task_OpenMainMenu(u8 taskId)
{
    if (gPaletteFade.active)
        return;
    if (gTasks[taskId].data[0] == 0)
        SetMainCallback2(CB2_NewGameKukuiCall_FromNewMainMenu);
    else
    {
        CleanupOverworldWindowsAndTilemaps();
        MainMenu_Init(CB2_InitTitleScreen);
    }
    DestroyTask(taskId);
}

static void MainMenu_FreeResources(void)
{
    ScanlineEffect_Stop();
    SetVBlankCallback(NULL);
    ResetSpriteData();
    FreeAllSpritePalettes();
    FreeAllWindowBuffers();
    UnsetBgTilemapBuffer(1);
    UnsetBgTilemapBuffer(2);
    UnsetBgTilemapBuffer(3);
    if (sMainMenu->panelTiles != NULL)
        Free(sMainMenu->panelTiles);
    Free(sMainMenu);
    sMainMenu = NULL;
}

static void DrawCrystalProgress(void)
{
    u32 crystal, x, y;

    for (crystal = 0; crystal < ARRAY_COUNT(sCrystalFlags); crystal++)
    {
        u16 *entry = &sMainMenu->panelTilemap[CRYSTAL_ROW_Y * 32 + CRYSTAL_ROW_X + crystal];
        u16 originalTile = *entry;
        u8 *dest = sMainMenu->panelTiles + PANEL_TILE_BYTES + crystal * 64;

        if (!FlagGet(sCrystalFlags[crystal]))
            continue;

        // Composite onto the existing panel so transparent pixels keep its artwork.
        for (y = 0; y < 8; y++)
        {
            for (x = 0; x < 8; x++)
            {
                u32 sourceX = (originalTile & 0x400) ? 7 - x : x;
                u32 sourceY = (originalTile & 0x800) ? 7 - y : y;
                u8 pixel = sCrystalTiles[crystal * 64 + y * 8 + x];

                dest[y * 8 + x] = sMainMenu->panelTiles[(originalTile & 0x3FF) * 64 + sourceY * 8 + sourceX];
                if (pixel != 0)
                    dest[y * 8 + x] = CRYSTAL_PALETTE_OFFSET + pixel;
            }
        }
        *entry = PANEL_TILE_BYTES / 64 + crystal;
    }
}

static void MainMenu_RunSetup(void)
{
    u32 i;
    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetVramOamAndBgCntRegs();
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
        ClearScheduledBgCopiesToVram();
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        ResetAllBgsCoordinates();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        SetBgTilemapBuffer(1, sMainMenu->panelTilemap);
        SetBgTilemapBuffer(2, sMainMenu->waterTilemap);
        SetBgTilemapBuffer(3, sMainMenu->portraitTilemap);
        sMainMenu->panelTiles = Alloc(PANEL_TILE_BYTES + sizeof(sCrystalTiles));
        if (sMainMenu->panelTiles == NULL)
        {
            MainCallback callback = sMainMenu->savedCallback;
            MainMenu_FreeResources();
            SetMainCallback2(callback);
            return;
        }
        DecompressDataWithHeaderWram(sPanelTiles, sMainMenu->panelTiles);
        // Index 30 is the supplied magenta backdrop. Index 1 duplicates white 0.
        for (i = 0; i < PANEL_TILE_BYTES; i++)
        {
            if (sMainMenu->panelTiles[i] == 0)
                sMainMenu->panelTiles[i] = 1;
            else if (sMainMenu->panelTiles[i] == 30)
                sMainMenu->panelTiles[i] = 0;
        }
        CopyToBgTilemapBufferRect(1, sPanelTilemap, 0, 0, 30, 20);
        DrawCrystalProgress();
        LoadBgTiles(1, sMainMenu->panelTiles, PANEL_TILE_BYTES + sizeof(sCrystalTiles), 0);
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sScrollBgTiles, 0, 0, 0);
        gMain.state++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() || IsDma3ManagerBusyWithBgCopy())
            return;
        Free(sMainMenu->panelTiles);
        sMainMenu->panelTiles = NULL;
        DecompressDataWithHeaderWram(sScrollBgTilemap, sMainMenu->waterTilemap);
        // Relocate the water's original palette bank 1 beyond the panel's 32 colors.
        for (i = 0; i < ARRAY_COUNT(sMainMenu->waterTilemap); i++)
            sMainMenu->waterTilemap[i] = (sMainMenu->waterTilemap[i] & 0x0FFF) | (2 << 12);
        LoadPalette(sPanelPalette, 0, 32 * sizeof(u16));
        LoadPalette(sScrollBgPalette, 2 * 16, 32);
        LoadPalette(sCrystalPalette, CRYSTAL_PALETTE_OFFSET, CRYSTAL_PALETTE_COLORS * sizeof(u16));
        LoadCompressedSpriteSheet(&sCursorSheet);
        LoadSpritePalette(&sCursorPal);
        InitWindowsAndPortrait();
        ScheduleBgCopyTilemapToVram(1);
        ScheduleBgCopyTilemapToVram(2);
        gMain.state++;
        break;
    case 2:
        if (IsDma3ManagerBusyWithBgCopy())
            return;
        sMainMenu->cursorSpriteId = CreateSprite(&sCursorTemplate, 0, 0, 0);
        UpdateCursor();
        InitParallaxEffect();
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        for (i = 0; i < 4; i++)
            ShowBg(i);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        CreateTask(Task_MainMenuInput, 0);
        SetVBlankCallback(MainMenu_VBlankCB);
        SetMainCallback2(MainMenu_MainCB);
        break;
    }
}

static void Task_MainMenuExit(u8 taskId)
{
    MainCallback callback;
    if (gPaletteFade.active)
        return;
    callback = sMainMenu->savedCallback;
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    MainMenu_FreeResources();
    DestroyTask(taskId);
    SetMainCallback2(callback);
}

static void Task_MainMenuInput(u8 taskId)
{
    u8 previous = sSelectedOption;
    if (gPaletteFade.active)
        return;
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_PC_OFF);
            sMainMenu->savedCallback = CB2_InitTitleScreen;
            sSelectedOption = OPTION_CONTINUE;
        }
        else
        {
            PlaySE(SE_SELECT);
            switch (sSelectedOption)
            {
            case OPTION_CONTINUE:
                sMainMenu->savedCallback = CB2_ContinueSavedGame;
                break;
            case OPTION_NEW_GAME:
                sMainMenu->savedCallback = CB2_NewGameKukuiCall_FromNewMainMenu;
                sSelectedOption = OPTION_CONTINUE;
                break;
            case OPTION_OPTIONS:
                gMain.savedCallback = CB2_ReinitMainMenu;
                sMainMenu->savedCallback = CB2_InitOptionMenu;
                break;
            }
        }
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_MainMenuExit;
        return;
    }
    if (JOY_NEW(DPAD_UP | DPAD_DOWN))
        sSelectedOption = sSelectedOption == OPTION_CONTINUE ? OPTION_NEW_GAME : OPTION_CONTINUE;
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT) && sSelectedOption != OPTION_CONTINUE)
        sSelectedOption = sSelectedOption == OPTION_NEW_GAME ? OPTION_OPTIONS : OPTION_NEW_GAME;
    if (previous != sSelectedOption)
    {
        PlaySE(SE_SELECT);
        UpdateCursor();
    }
}
