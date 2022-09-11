//
// Created by loghin on 04/08/22.
//

#ifndef __AMSR_INSTANCE_H__
#define __AMSR_INSTANCE_H__

#include "amsr_public_types.h"

extern AMSR_Result AMSR_createInstance (
        AMSR_Instance                     * pInstance,
        AMSR_InstanceCreateInfo     const * pCreateInfo,
        AMSR_AllocationCallbacks    const * pAllocationCallbacks
);

#endif // __AMSR_INSTANCE_H__
