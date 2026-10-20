#include "constants/global.h"
#include "constants/event_objects.h"

#if MODERN == 0
static const u8 sText_OutfitName_UsualGreen[] = _("USUAL GREEN");
static const u8 sText_OutfitDesc_UsualGreen[] = _(
    "The usual, but basic OUTFIT.");

static const u8 sText_OutfitName_UnusualRed[] = _("UNUSUAL RED");
static const u8 sText_OutfitDesc_UnusualRed[] = _(
    "Rather unusual, but still basic\nOUTFIT.");
#endif

static const u16 sRegionMapPlayerIcon_BrendanGfx[] = INCBIN_U16("graphics/pokenav/region_map/brendan_icon.4bpp");

static const u16 sRegionMapPlayerIcon_RSBrendanGfx[] = INCBIN_U16("graphics/pokenav/region_map/rs_brendan_icon.4bpp");

static const u16 sRegionMapPlayerIcon_MayGfx[] = INCBIN_U16("graphics/pokenav/region_map/may_icon.4bpp");

static const u16 sRegionMapPlayerIcon_RSMayGfx[] = INCBIN_U16("graphics/pokenav/region_map/rs_may_icon.4bpp");

//! TODO: Should the gfx here be seperated?

static const u8 sFrontierPassPlayerIcons_BrendanMay_Gfx[] = INCBIN_U8("graphics/frontier_pass/map_heads.4bpp");

static const u8 sFrontierPassPlayerIcons_RSBrendanMay_Gfx[] = INCBIN_U8("graphics/frontier_pass/rs_map_heads.4bpp");

#define REGION_MAP_GFX(m, f) { sRegionMapPlayerIcon_ ## m ## Gfx, sRegionMapPlayerIcon_ ## f ## Gfx }

// bandaids to avoid adding unnecessary merge conflicts
// remove these if you have them added/renamed yourself.
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_NORMAL     OBJ_EVENT_GFX_LINK_RS_BRENDAN
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_ACRO_BIKE  OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_SURFING    OBJ_EVENT_GFX_BRENDAN_SURFING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_UNDERWATER OBJ_EVENT_GFX_BRENDAN_UNDERWATER
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FISHING    OBJ_EVENT_GFX_BRENDAN_FISHING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_WATERING   OBJ_EVENT_GFX_BRENDAN_WATERING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_DECORATING OBJ_EVENT_GFX_BRENDAN_DECORATING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE

#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_NORMAL     OBJ_EVENT_GFX_LINK_RS_MAY
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_ACRO_BIKE  OBJ_EVENT_GFX_MAY_ACRO_BIKE
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_SURFING    OBJ_EVENT_GFX_MAY_SURFING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_UNDERWATER OBJ_EVENT_GFX_MAY_UNDERWATER
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE OBJ_EVENT_GFX_MAY_FIELD_MOVE
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FISHING    OBJ_EVENT_GFX_MAY_FISHING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_WATERING   OBJ_EVENT_GFX_MAY_WATERING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_DECORATING OBJ_EVENT_GFX_MAY_DECORATING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE OBJ_EVENT_GFX_MAY_FIELD_MOVE

static const u16 sRegionMapPlayerIcon_ElioTealGfx[] = INCGFX_U16("graphics/pokenav/region_map/elio_teal_icon.png", ".4bpp");
static const u16 sRegionMapPlayerIcon_SeleneTealGfx[] = INCGFX_U16("graphics/pokenav/region_map/selene_teal_icon.png", ".4bpp");
static const u16 sRegionMapPlayerIcon_ElioVioletGfx[] = INCGFX_U16("graphics/pokenav/region_map/elio_violet_icon.png", ".4bpp");
static const u16 sRegionMapPlayerIcon_SeleneVioletGfx[] = INCGFX_U16("graphics/pokenav/region_map/selene_violet_icon.png", ".4bpp");
static const u16 sRegionMapPlayerIcon_ElioGreenGfx[] = INCGFX_U16("graphics/pokenav/region_map/elio_green_icon.png", ".4bpp");
static const u16 sRegionMapPlayerIcon_SeleneGreenGfx[] = INCGFX_U16("graphics/pokenav/region_map/selene_green_icon.png", ".4bpp");

const struct Outfit gOutfits[OUTFIT_COUNT] =
{
    [OUTFIT_TEAL] = {
        .name = COMPOUND_STRING("TEAL OUTFIT"),
        .desc = COMPOUND_STRING("A teal OUTFIT."),
        .trainerPics = { TRAINER_PIC_ELIO_TEAL, TRAINER_PIC_SELENE_TEAL },
        .avatarGfxIds = {
            { OBJ_EVENT_GFX_ELIO_TEAL_NORMAL, OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE, OBJ_EVENT_GFX_ELIO_TEAL_SURFING, OBJ_EVENT_GFX_BRENDAN_UNDERWATER },
            { OBJ_EVENT_GFX_SELENE_TEAL_NORMAL, OBJ_EVENT_GFX_MAY_ACRO_BIKE, OBJ_EVENT_GFX_SELENE_TEAL_SURFING, OBJ_EVENT_GFX_MAY_UNDERWATER },
        },
        .animGfxIds = {
            { OBJ_EVENT_GFX_ELIO_TEAL_FIELD_MOVE, OBJ_EVENT_GFX_ELIO_TEAL_FISHING, OBJ_EVENT_GFX_BRENDAN_WATERING, OBJ_EVENT_GFX_BRENDAN_DECORATING, OBJ_EVENT_GFX_ELIO_TEAL_FIELD_MOVE },
            { OBJ_EVENT_GFX_SELENE_TEAL_FIELD_MOVE, OBJ_EVENT_GFX_SELENE_TEAL_FISHING, OBJ_EVENT_GFX_MAY_WATERING, OBJ_EVENT_GFX_MAY_DECORATING, OBJ_EVENT_GFX_SELENE_TEAL_FIELD_MOVE },
        },
        .riderGfxIds = { OBJ_EVENT_GFX_ELIO_TEAL_RIDING, OBJ_EVENT_GFX_SELENE_TEAL_RIDING },
        .iconsRM = { sRegionMapPlayerIcon_ElioTealGfx, sRegionMapPlayerIcon_SeleneTealGfx },
        .iconsFP = sFrontierPassPlayerIcons_BrendanMay_Gfx,
    },
    [OUTFIT_VIOLET] = {
        .name = COMPOUND_STRING("VIOLET OUTFIT"),
        .desc = COMPOUND_STRING("A violet OUTFIT."),
        .trainerPics = { TRAINER_PIC_ELIO_VIOLET, TRAINER_PIC_SELENE_VIOLET },
        .avatarGfxIds = {
            { OBJ_EVENT_GFX_ELIO_VIOLET_NORMAL, OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE, OBJ_EVENT_GFX_ELIO_VIOLET_SURFING, OBJ_EVENT_GFX_BRENDAN_UNDERWATER },
            { OBJ_EVENT_GFX_SELENE_VIOLET_NORMAL, OBJ_EVENT_GFX_MAY_ACRO_BIKE, OBJ_EVENT_GFX_SELENE_VIOLET_SURFING, OBJ_EVENT_GFX_MAY_UNDERWATER },
        },
        .animGfxIds = {
            { OBJ_EVENT_GFX_ELIO_VIOLET_FIELD_MOVE, OBJ_EVENT_GFX_ELIO_VIOLET_FISHING, OBJ_EVENT_GFX_BRENDAN_WATERING, OBJ_EVENT_GFX_BRENDAN_DECORATING, OBJ_EVENT_GFX_ELIO_VIOLET_FIELD_MOVE },
            { OBJ_EVENT_GFX_SELENE_VIOLET_FIELD_MOVE, OBJ_EVENT_GFX_SELENE_VIOLET_FISHING, OBJ_EVENT_GFX_MAY_WATERING, OBJ_EVENT_GFX_MAY_DECORATING, OBJ_EVENT_GFX_SELENE_VIOLET_FIELD_MOVE },
        },
        .riderGfxIds = { OBJ_EVENT_GFX_ELIO_VIOLET_RIDING, OBJ_EVENT_GFX_SELENE_VIOLET_RIDING },
        .iconsRM = { sRegionMapPlayerIcon_ElioVioletGfx, sRegionMapPlayerIcon_SeleneVioletGfx },
        .iconsFP = sFrontierPassPlayerIcons_BrendanMay_Gfx,
    },
    [OUTFIT_GREEN] = {
        .name = COMPOUND_STRING("GREEN OUTFIT"),
        .desc = COMPOUND_STRING("A green OUTFIT."),
        .trainerPics = { TRAINER_PIC_ELIO_GREEN, TRAINER_PIC_SELENE_GREEN },
        .avatarGfxIds = {
            { OBJ_EVENT_GFX_ELIO_GREEN_NORMAL, OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE, OBJ_EVENT_GFX_ELIO_GREEN_SURFING, OBJ_EVENT_GFX_BRENDAN_UNDERWATER },
            { OBJ_EVENT_GFX_SELENE_GREEN_NORMAL, OBJ_EVENT_GFX_MAY_ACRO_BIKE, OBJ_EVENT_GFX_SELENE_GREEN_SURFING, OBJ_EVENT_GFX_MAY_UNDERWATER },
        },
        .animGfxIds = {
            { OBJ_EVENT_GFX_ELIO_GREEN_FIELD_MOVE, OBJ_EVENT_GFX_ELIO_GREEN_FISHING, OBJ_EVENT_GFX_BRENDAN_WATERING, OBJ_EVENT_GFX_BRENDAN_DECORATING, OBJ_EVENT_GFX_ELIO_GREEN_FIELD_MOVE },
            { OBJ_EVENT_GFX_SELENE_GREEN_FIELD_MOVE, OBJ_EVENT_GFX_SELENE_GREEN_FISHING, OBJ_EVENT_GFX_MAY_WATERING, OBJ_EVENT_GFX_MAY_DECORATING, OBJ_EVENT_GFX_SELENE_GREEN_FIELD_MOVE },
        },
        .riderGfxIds = { OBJ_EVENT_GFX_ELIO_GREEN_RIDING, OBJ_EVENT_GFX_SELENE_GREEN_RIDING },
        .iconsRM = { sRegionMapPlayerIcon_ElioGreenGfx, sRegionMapPlayerIcon_SeleneGreenGfx },
        .iconsFP = sFrontierPassPlayerIcons_BrendanMay_Gfx,
    },
    [OUTFIT_NONE] = {
        .isHidden = TRUE
    },
    [OUTFIT_USUAL_GREEN] = {
        //! DESC: if sets to TRUE, it will not be shown in the OUTFIT menu if it's locked.
        .isHidden = FALSE,

        //! DESC: prices for purchasing them.
        .prices = { 0, 0 },

        //! agbcc doesnt like COMPOUND_STRING on my end
        //! DESC: outfit's name
        #if MODERN == 1
        .name = COMPOUND_STRING("USUAL OUTFIT"),
        #else
        .name = sText_OutfitName_UsualGreen,
        #endif

        //! DESC: outfit's description
        #if MODERN == 1
        .desc = COMPOUND_STRING("The usual, but basic OUTFIT."),
        #else
        .desc = sText_OutfitDesc_UsualGreen,
        #endif

        //! DESC: trainer front & back pic index
        //! (see include/constants/trainers.h)
        .trainerPics = {
            [MALE] =   TRAINER_PIC_BRENDAN,
            [FEMALE] = TRAINER_PIC_MAY,
        },

        //! DESC: overworld avatars, consisting of: walking, cycling,
        //! surfing, and underwater. (see include/constants/event_object.h)
        .avatarGfxIds = {
           [MALE] = {
               [OUTFIT_AVATAR_NORMAL] =     OBJ_EVENT_GFX_BRENDAN_NORMAL,
               [OUTFIT_AVATAR_BIKE] =       OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE,
               [OUTFIT_AVATAR_SURFING] =    OBJ_EVENT_GFX_BRENDAN_SURFING,
               [OUTFIT_AVATAR_UNDERWATER] = OBJ_EVENT_GFX_BRENDAN_UNDERWATER
           },
           [FEMALE] = {
               [OUTFIT_AVATAR_NORMAL] =     OBJ_EVENT_GFX_MAY_NORMAL,
               [OUTFIT_AVATAR_BIKE] =       OBJ_EVENT_GFX_MAY_ACRO_BIKE,
               [OUTFIT_AVATAR_SURFING] =    OBJ_EVENT_GFX_MAY_SURFING,
               [OUTFIT_AVATAR_UNDERWATER] = OBJ_EVENT_GFX_MAY_UNDERWATER
           },
        },

        //! DESC: overworld anims, consisting of: field move, fishing,
        //! water, and decorating. (see include/constants/event_object.h)
        .animGfxIds = {
            [MALE] = {
                [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE,
                [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_BRENDAN_FISHING,
                [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_BRENDAN_WATERING,
                [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_BRENDAN_DECORATING,
                [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
            },
            [FEMALE] = {
                [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_MAY_FIELD_MOVE,
                [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_MAY_FISHING,
                [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_MAY_WATERING,
                [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_MAY_DECORATING,
                [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_MAY_FIELD_MOVE
            },
        },

        //! DESC: rider sprites used when mounted on a transform Pokemon
        .riderGfxIds = { [MALE] = OBJ_EVENT_GFX_ELIO_RIDING, [FEMALE] = OBJ_EVENT_GFX_SELENE_RIDING },

        //! DESC: head icons gfx&pal for region map
        .iconsRM = { sRegionMapPlayerIcon_BrendanGfx, sRegionMapPlayerIcon_MayGfx },

        //! DESC: head icons gfx&pal for frontier pass
        //! note that frontier pass needs to be in one sprite instead of two,
        //! unlike region map. (probably should split them tbh)
        .iconsFP = sFrontierPassPlayerIcons_BrendanMay_Gfx,
    },
    [OUTFIT_UNUSUAL_RED] = {
        .isHidden = FALSE,
        .prices = { 200, 500 },
        #if MODERN == 1
        .name = COMPOUND_STRING("UNUSUAL RED"),
        .desc = COMPOUND_STRING("Rather unusual, but still basic\nOUTFIT."),
        #else
        .name = sText_OutfitName_UnusualRed,
        .desc = sText_OutfitDesc_UnusualRed,
        #endif
        .trainerPics = {
            [MALE]   = TRAINER_PIC_RS_BRENDAN,
            [FEMALE] = TRAINER_PIC_RS_MAY
        },
        .avatarGfxIds = {
           [MALE] = {
               [OUTFIT_AVATAR_NORMAL] =     OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_NORMAL,
               [OUTFIT_AVATAR_BIKE] =       OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_ACRO_BIKE,
               [OUTFIT_AVATAR_SURFING] =    OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_SURFING,
               [OUTFIT_AVATAR_UNDERWATER] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_UNDERWATER
           },
           [FEMALE] = {
               [OUTFIT_AVATAR_NORMAL] =     OBJ_EVENT_GFX_OUTFIT_RS_MAY_NORMAL,
               [OUTFIT_AVATAR_BIKE] =       OBJ_EVENT_GFX_OUTFIT_RS_MAY_ACRO_BIKE,
               [OUTFIT_AVATAR_SURFING] =    OBJ_EVENT_GFX_OUTFIT_RS_MAY_SURFING,
               [OUTFIT_AVATAR_UNDERWATER] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_UNDERWATER
           },
        },
        .animGfxIds = {
            [MALE] = {
                [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE,
                [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FISHING,
                [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_WATERING,
                [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_DECORATING,
                [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE
            },
            [FEMALE] = {
                [PLAYER_AVATAR_GFX_FIELD_MOVE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE,
                [PLAYER_AVATAR_GFX_FISHING] =    OBJ_EVENT_GFX_OUTFIT_RS_MAY_FISHING,
                [PLAYER_AVATAR_GFX_WATERING] =   OBJ_EVENT_GFX_OUTFIT_RS_MAY_WATERING,
                [PLAYER_AVATAR_GFX_DECORATING] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_DECORATING,
                [PLAYER_AVATAR_GFX_VSSEEKER] =   OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE
            },
        },
        .riderGfxIds = { [MALE] = OBJ_EVENT_GFX_ELIO_RIDING, [FEMALE] = OBJ_EVENT_GFX_SELENE_RIDING },
        .iconsRM = { sRegionMapPlayerIcon_RSBrendanGfx, sRegionMapPlayerIcon_RSMayGfx },
        .iconsFP = sFrontierPassPlayerIcons_RSBrendanMay_Gfx,
    },
};
