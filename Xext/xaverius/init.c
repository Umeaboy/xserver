/* SPDX-License-Identifier: X11 OR MIT OR AGPL-3.0-or-later
 *
 * Copyright © 2026 Enrico Weigelt, metux IT consult <info@metux.net>
 */
#include <dix-config.h>

#include "dix/dix_priv.h"
#include "include/extnsionst.h"
#include "include/privates.h"
#include "miext/extinit_priv.h"

#include "xaverius_intern.h"
#include "xaverius_registry.h"
#include "xaverius_proto.h"

Bool noXaveriusExtension = TRUE;

int XaveriusEventBase = 0;
Atom xav_atom_device_uuid = 0;
Atom xav_atom_driver_uuid = 0;
Atom xav_atom_max_work_group_invocations = 0;
Atom xav_atom_max_work_group_size = 0;
Atom xav_atom_timeline_semaphore = 0;

static void
XaveriusExtensionFini(ExtensionEntry *extEntry)
{
    XaveriusRegistryFini();
}

void
XaveriusExtensionInit(void)
{
    ExtensionEntry *extEntry = AddExtension(XAVERIUS_EXTENSION_NAME, 0, 0,
                                            ProcXaveriusDispatch,
                                            ProcXaveriusDispatch,
                                            XaveriusExtensionFini,
                                            StandardMinorOpcode);
    if (!extEntry) {
        FatalError("failed adding Xaverius extension entry. OOM ?\n");
    }

    XaveriusEventBase = extEntry->eventBase;

    /* Register per-screen private key at extension init time */
    if (!dixRegisterPrivateKey(&XaveriusScreenPrivateKeyRec, PRIVATE_SCREEN, 0)) {
        FatalError("failed to register Xaverius screen private key\n");
    }

    /* Initialize property atoms */
    xav_atom_device_uuid = MakeAtom("XAverius.deviceUUID", strlen("XAverius.deviceUUID"), TRUE);
    xav_atom_driver_uuid = MakeAtom("XAverius.driverUUID", strlen("XAverius.driverUUID"), TRUE);
    xav_atom_max_work_group_invocations = MakeAtom("XAverius.compute.maxWorkGroupInvocations", strlen("XAverius.compute.maxWorkGroupInvocations"), TRUE);
    xav_atom_max_work_group_size = MakeAtom("XAverius.compute.maxWorkGroupSize", strlen("XAverius.compute.maxWorkGroupSize"), TRUE);
    xav_atom_timeline_semaphore = MakeAtom("XAverius.timelineSemaphore", strlen("XAverius.timelineSemaphore"), TRUE);

    /* Initialize process-wide PhysicalDevice registry */
    XaveriusRegistryInit();

    LogMessage(X_INFO, "Xaverius extension initialized\n");
}