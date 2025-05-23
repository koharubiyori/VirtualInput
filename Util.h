#pragma once

#include <ntddk.h>
#include <wdf.h>

EXTERN_C_START

NTSTATUS
CopyToRequestBuffer(
  _In_ WDFREQUEST       request,
  _In_ PVOID            sourceBuffer,
  _In_ size_t           numBytesToCopyFrom
);

EXTERN_C_END