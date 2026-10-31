#ifndef GUARD_OUTFIT_MENU_H
#define GUARD_OUTFIT_MENU_H

#include "main.h"

void OpenOutfitMenu(MainCallback retCB);
void Task_OpenOutfitMenu(u8 taskId);
const u16 *GetCurrentOutfitObjectPalette(u16 paletteTag, const u16 *palette);
// Runtime graphics IDs resolve the saved outfit and skin independently.
u32 GetOutfitSpriteId(u32 outfit, u32 skin);
u32 GetCurrentOutfitSpriteId(void);

//! misc funcs
void BufferOutfitStrings(u8 *dest, u8 outfitId, u8 dataType);
enum TrainerPicID GetPlayerTrainerPicIdByOutfitAndGender(u32 outfitId, enum Gender gender);
const void *GetPlayerHeadGfxOrPal(u8 which, bool32 isFP);
// GFX returns uncompressed 48x48 4bpp tiles; PAL returns the matching palette.
const void *GetCurrentOutfitMugshot(u8 which);
const void *GetOutfitMugshot(u32 outfitId, enum Gender gender, u32 paletteIndex, u8 which);
u16 *GetOutfitPointer(u16 id);
u16 UnlockOutfit(u16 id);
u16 ToggleOutfit(u16 id);
u16 LockOutfit(u16 id);
bool8 GetOutfitStatus(u16 id);
bool8 IsPlayerWearingOutfit(u16 id);
u32 GetOutfitPrice(u16 id);

#endif //! GUARD_OUTFIT_MENU_H
