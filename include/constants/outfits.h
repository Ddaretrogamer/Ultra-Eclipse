#ifndef GUARD_CONSTANTS_OUTFITS_H
#define GUARD_CONSTANTS_OUTFITS_H

//! macro modes

// ScrCmd_getoutfitstatus
#define OUTFIT_CHECK_FLAG 0
#define OUTFIT_CHECK_USED 1
// ScrCmd_toggleoutfit
#define OUTFIT_TOGGLE_UNLOCK 0
#define OUTFIT_TOGGLE_LOCK 1
// BufferOutfitStrings
#define OUTFIT_BUFFER_NAME  0
#define OUTFIT_BUFFER_DESC  1

//! outfits
#define OUTFIT_NONE 0
#define OUTFIT_USUAL_GREEN 1
#define OUTFIT_UNUSUAL_RED 2
#define OUTFIT_TEAL 3
#define OUTFIT_VIOLET 4
#define OUTFIT_GREEN 5
#define OUTFIT_COUNT 6

// inclusive
#define OUTFIT_BEGIN OUTFIT_USUAL_GREEN
#define OUTFIT_END   OUTFIT_GREEN

#define DEFAULT_OUTFIT OUTFIT_USUAL_GREEN

#endif //! GUARD_CONSTANTS_OUTFITS_H
