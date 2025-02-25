/** @file
  This file is part of OpenCanopy, OpenCore GUI.

  Copyright (c) 2018-2019, Download-Fritz. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-3-Clause
**/

#ifndef GUI_APP_H
#define GUI_APP_H

#include "OpenCanopy.h"
#include "BmfLib.h"

#include <Library/OcBootManagementLib.h>

#define MAX_CURSOR_DIMENSION  144U

#define BOOT_CURSOR_OFFSET  4U

#define BOOT_ENTRY_DIMENSION       144U
#define BOOT_ENTRY_ICON_DIMENSION  APPLE_DISK_ICON_DIMENSION
#define BOOT_ENTRY_ICON_SPACE      ((BOOT_ENTRY_DIMENSION - BOOT_ENTRY_ICON_DIMENSION) / 2)
#define BOOT_ENTRY_LABEL_SPACE     4U
#define BOOT_ENTRY_LABEL_HEIGHT    12U

#define BOOT_ENTRY_SPACE  8U

#define BOOT_SELECTOR_WIDTH                 144U
#define BOOT_SELECTOR_BACKGROUND_DIMENSION  BOOT_SELECTOR_WIDTH
#define BOOT_SELECTOR_BUTTON_WIDTH          BOOT_SELECTOR_WIDTH
#define BOOT_SELECTOR_BUTTON_HEIGHT         40U
#define BOOT_SELECTOR_BUTTON_SPACE          (BOOT_ENTRY_LABEL_SPACE + BOOT_ENTRY_LABEL_HEIGHT + 3)
#define BOOT_SELECTOR_HEIGHT                (BOOT_SELECTOR_BACKGROUND_DIMENSION + BOOT_SELECTOR_BUTTON_SPACE + BOOT_SELECTOR_BUTTON_HEIGHT)

#define BOOT_ENTRY_WIDTH   (BOOT_ENTRY_DIMENSION)
#define BOOT_ENTRY_HEIGHT  (BOOT_ENTRY_DIMENSION + BOOT_ENTRY_LABEL_SPACE + BOOT_ENTRY_LABEL_HEIGHT)

#define BOOT_SCROLL_BUTTON_DIMENSION  40U
#define BOOT_SCROLL_BUTTON_SPACE      40U

#define BOOT_ACTION_BUTTON_DIMENSION  144U
#define BOOT_ACTION_BUTTON_SPACE      36U

typedef enum {
  LABEL_GENERIC_HDD,
  LABEL_APPLE,
  LABEL_APPLE_RECOVERY,
  LABEL_APPLE_TIME_MACHINE,
  LABEL_WINDOWS,
  LABEL_OTHER,
  LABEL_TOOL,
  LABEL_RESET_NVRAM,
  LABEL_SHELL,
  LABEL_NUM_TOTAL
} LABEL_TARGET;

typedef enum {
  ICON_CURSOR,
  ICON_SELECTED,
  ICON_SELECTOR,
  ICON_LEFT,
  ICON_RIGHT,
  ICON_SHUT_DOWN,
  ICON_RESTART,
  ICON_NUM_SYS,
  ICON_GENERIC_HDD       = ICON_NUM_SYS,
  ICON_NUM_MANDATORY,
  ICON_APPLE             = ICON_NUM_MANDATORY,
  ICON_APPLE_RECOVERY,
  ICON_APPLE_TIME_MACHINE,
  ICON_WINDOWS,
  ICON_OTHER,
  ICON_TOOL,
  ICON_RESET_NVRAM,
  ICON_SHELL,
  ICON_NUM_TOTAL
} ICON_TARGET;

typedef enum {
  ICON_TYPE_BASE     = 0,
  ICON_TYPE_EXTERNAL = 1,
  ICON_TYPE_HELD     = 1,
  ICON_TYPE_COUNT    = 2,
} ICON_TYPE;

typedef struct _BOOT_PICKER_GUI_CONTEXT {
  GUI_IMAGE                            Background;
  GUI_IMAGE                            Icons[ICON_NUM_TOTAL][ICON_TYPE_COUNT];
  GUI_IMAGE                            Labels[LABEL_NUM_TOTAL];
  // GUI_IMAGE                         Poof[5];
  GUI_FONT_CONTEXT                     FontContext;
  VOID                                 *BootEntry;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION  BackgroundColor;
  BOOLEAN                              HideAuxiliary;
  BOOLEAN                              Refresh;
  BOOLEAN                              LightBackground;
  BOOLEAN                              DoneIntroAnimation;
  BOOLEAN                              ReadyToBoot;
  UINT8                                Scale;
  UINT32                               CursorDefaultX;
  UINT32                               CursorDefaultY;
  INT32                                AudioPlaybackTimeout;
  OC_PICKER_CONTEXT                    *PickerContext;
} BOOT_PICKER_GUI_CONTEXT;

EFI_STATUS
BootPickerViewInitialize (
  OUT GUI_DRAWING_CONTEXT      *DrawContext,
  IN  BOOT_PICKER_GUI_CONTEXT  *GuiContext,
  IN  GUI_CURSOR_GET_IMAGE     GetCursorImage,
  IN  UINT8                    NumBootEntries
  );

VOID
BootPickerViewLateInitialize (
  IN BOOT_PICKER_GUI_CONTEXT  *GuiContext,
  IN UINT8                    DefaultIndex
  );

EFI_STATUS
BootPickerEntriesSet (
  IN OC_PICKER_CONTEXT              *Context,
  IN BOOT_PICKER_GUI_CONTEXT        *GuiContext,
  IN OC_BOOT_ENTRY                  *Entry,
  IN UINT8                          EntryIndex
  );

VOID
BootPickerViewDeinitialize (
  IN OUT GUI_DRAWING_CONTEXT      *DrawContext,
  IN OUT BOOT_PICKER_GUI_CONTEXT  *GuiContext
  );

CONST GUI_IMAGE *
InternalGetCursorImage (
  IN BOOT_PICKER_GUI_CONTEXT  *Context
  );

#endif // GUI_APP_H
