/* SPDX-License-Identifier: X11 OR MIT OR AGPL-3.0-or-later
 *
 * Copyright © 2026 Enrico Weigelt, metux IT consult <info@metux.net>
 *
 * Xaverius internal definitions shared between source files within the extension.
 */

#ifndef _XLIBRE_XAVERIUS_INTERN_H
#define _XLIBRE_XAVERIUS_INTERN_H

#include <stdbool.h>
#include <stdint.h>

#include <X11/Xdefs.h>

#include "include/list.h"
#include "include/privates.h"
#include "include/xlibre_ptrtypes.h"

#include "xaverius_priv.h"
#include "xaverius_proto.h"

/* Forward declarations for internal types */
struct _XaveriusDevice;
typedef struct _XaveriusDevice XaveriusDeviceRec, *XaveriusDevicePtr;

/* Global property atoms (initialized in init.c) */
extern Atom xav_atom_device_uuid;
extern Atom xav_atom_driver_uuid;
extern Atom xav_atom_max_work_group_invocations;
extern Atom xav_atom_max_work_group_size;
extern Atom xav_atom_timeline_semaphore;

/* Extension event base */
extern int XaveriusEventBase;
extern int XaveriusExtensionMajorOpcode;

/*
 * Global device registry (defined in xaverius_registry.c).
 * Only one registry exists per server process.
 */
extern struct xorg_list xaverius_devices;
extern uint32_t xaverius_device_count;

/* Dispatch */
int ProcXaveriusDispatch(ClientPtr client);

int ProcXaveriusEnumeratePhysicalDevices(ClientPtr client);
int ProcXaveriusGetPhysicalDeviceProperty(ClientPtr client);
int ProcXaveriusGetPhysicalDeviceQueueFamilyProperties(ClientPtr client);

/* Registry functions */
void XaveriusRegistryInit(void);
void XaveriusRegistryFini(void);

bool XaveriusRegisterDeviceDirect(const XaveriusDeviceIdentity *identity,
                                  const XaveriusProviderCapabilities *caps,
                                  int native_handle,
                                  void *context);
XaveriusDevicePtr XaveriusFindDeviceByXid(XID xid);
XaveriusDevicePtr XaveriusFindDeviceByIdentity(XaveriusDeviceIdentity identity);
void XaveriusSetDeviceStatus(XaveriusDevicePtr device, XaveriusDeviceStatus status);
XaveriusDevicePtr XaveriusFirstDevice(void);
XaveriusDevicePtr XaveriusNextDevice(XaveriusDevicePtr device);
uint32_t XaveriusDeviceCount(void);

/* Internal device record (defined here, opaque to the DDX) */
struct _XaveriusDevice {
    XID xid;
    XaveriusDeviceIdentity identity;
    XaveriusDeviceStatus status;
    uint64_t generation;
    XaveriusProviderCapabilities callbacks;
    int native_handle;
    void *context;
    struct xorg_list list;
};

#endif /* _XLIBRE_XAVERIUS_INTERN_H */