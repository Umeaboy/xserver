/* SPDX-License-Identifier: X11 OR MIT OR AGPL-3.0-or-later
 *
 * Copyright © 2026 Enrico Weigelt, metux IT consult <info@metux.net>
 *
 * Xaverius Physical Device Registry — public API for DDX drivers.
 */

#ifndef XAVERIUS_REGISTRY_H
#define XAVERIUS_REGISTRY_H

#include <stdbool.h>
#include <stdint.h>

#include "xaverius_intern.h"

/*
 * DDX-wide provider registration entry point (Phase A).
 *
 * Callable by the DDX without a ScreenPtr, ScrnInfoPtr, or an existing
 * XAverius Screen-private record. Submits an exact device binding to
 * the one process-wide XAverius registry.
 *
 * Identity resolution and duplicate-claim policy remain governed by the
 * normative registry spec; Phase A must not invent a local alternative.
 *
 * @param caps      Immutable metadata snapshot (metadata only, not executable dispatch)
 * @param ops       DDX callbacks for device discovery
 *
 * @return true on success (device newly registered or already present
 *         with identical identity), false on allocation/internal failure.
 */
bool XaveriusRegisterProvider(const XaveriusProviderCapabilities *caps,
                              const XaveriusProviderOpsRec *ops);

#endif /* XAVERIUS_REGISTRY_H */