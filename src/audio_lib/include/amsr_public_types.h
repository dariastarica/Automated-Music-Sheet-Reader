//
// Created by loghin on 04/08/22.
//

#ifndef __AMSR_PUBLIC_TYPES_H__
#define __AMSR_PUBLIC_TYPES_H__

#define __DEFINE_AMSR_OBJECT(_handle) typedef struct AMSR_ ## _handle ## _PT * AMSR_ ## _handle


#define AMSR_TRUE           (1U)
#define AMSR_FALSE          (0U)

#define AMSR_NULL           ((void *) 0U)
#define AMSR_NULL_FLAGS     ((AMSR_Flags) 0U)


__DEFINE_AMSR_OBJECT(Instance);


typedef unsigned char               AMSR_uint8;
typedef unsigned short int          AMSR_uint16;
typedef unsigned int                AMSR_uint32;
typedef unsigned long long int      AMSR_uint64;

typedef signed char                 AMSR_sint8;
typedef signed short int            AMSR_sint16;
typedef signed int                  AMSR_sint32;
typedef signed long long int        AMSR_sint64;


typedef AMSR_uint8      AMSR_bool;
typedef AMSR_uint64     AMSR_size;
typedef char const *    AMSR_StringLiteral;


typedef enum {
    AMSR_SUCCESS                    = 0,
    AMSR_NOT_READY                  = 1,
    AMSR_TOO_SMALL                  = 2,

    AMSR_ERROR_UNKNOWN              = -1,
    AMSR_ERROR_ILLEGAL_ARGUMENT     = -2,
    AMSR_ERROR_OUT_OF_MEMORY        = -3
} AMSR_Result;


typedef enum {
    AMSR_SYSTEM_ALLOCATION_SCOPE_NOT_DEFINED,
    AMSR_SYSTEM_ALLOCATION_SCOPE_INSTANCE
} AMSR_SystemAllocationScope;


typedef enum {
    AMSR_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    AMSR_STRUCTURE_TYPE_DEBUG_MESSENGER_CREATE_INFO
} AMSR_StructureType;


typedef void * ( * AMSR_AllocationFunction ) (
        void                      * pUserData,
        AMSR_size                   size,
        AMSR_size                   alignment,
        AMSR_SystemAllocationScope  allocationScope
);


typedef void * ( * AMSR_ReallocationFunction ) (
        void                      * pUserData,
        void                      * pOriginal,
        AMSR_size                   size,
        AMSR_size                   alignment,
        AMSR_SystemAllocationScope  allocationScope
);


typedef void * ( * AMSR_FreeFunction ) (
        void                      * pUserData,
        void                      * pMemory
);


typedef enum {
    AMSR_ALLOCATION_NOTIFICATION_TYPE_ALLOCATION,
    AMSR_ALLOCATION_NOTIFICATION_TYPE_REALLOCATION,
    AMSR_ALLOCATION_NOTIFICATION_TYPE_FREE
} AMSR_AllocationNotificationType;


typedef struct {
    void                          * pMemory;
    AMSR_size                       size;
    AMSR_size                       alignment;
    AMSR_SystemAllocationScope      allocationScope;
    AMSR_StringLiteral              explicitPurpose;
} AMSR_AllocationNotificationAllocationData;


typedef struct {
    void                          * pNewMemory;
    void                          * pOldMemory;
    AMSR_size                       size;
    AMSR_size                       alignment;
    AMSR_SystemAllocationScope      allocationScope;
    AMSR_StringLiteral              explicitPurpose;
} AMSR_AllocationNotificationReallocationData;


typedef struct {
    void                          * pMemory;
    AMSR_SystemAllocationScope      allocationScope;
} AMSR_AllocationNotificationFreeData;


typedef union {
    AMSR_AllocationNotificationAllocationData   allocation;
    AMSR_AllocationNotificationReallocationData reallocation;
    AMSR_AllocationNotificationFreeData         free;
} AMSR_AllocationNotificationData;


typedef struct {
    AMSR_StructureType                      structureType;
    void                            const * pNext;
    AMSR_AllocationNotificationType         type;
    AMSR_AllocationNotificationData const * pData;
} AMSR_AllocationNotification;


typedef void ( * AMSR_InternalAllocationNotificationFunction ) (
        void                              * pUserData,
        AMSR_AllocationNotification const * pNotification
);


typedef struct {
    void                                          * pUserData;
    AMSR_AllocationFunction                         allocationFunction;
    AMSR_ReallocationFunction                       reallocationFunction;
    AMSR_FreeFunction                               freeFunction;
    AMSR_InternalAllocationNotificationFunction     internalNotificationFunction;
} AMSR_AllocationCallbacks;


typedef enum {
    AMSR_DEBUG_MESSENGER_MESSAGE_SEVERITY_VERBOSE_FLAG_BIT  = 0x00000001U,
    AMSR_DEBUG_MESSENGER_MESSAGE_SEVERITY_INFO_FLAG_BIT     = 0x00000002U,
    AMSR_DEBUG_MESSENGER_MESSAGE_SEVERITY_WARNING_FLAG_BIT  = 0x00000004U,
    AMSR_DEBUG_MESSENGER_MESSAGE_SEVERITY_ERROR_FLAG_BIT    = 0x00000008U
} AMSR_DebugMessengerMessageSeverityFlagBits;


typedef enum {
    AMSR_DEBUG_MESSENGER_MESSAGE_TYPE_GENERAL_FLAG_BIT      = 0x00000001U,
    AMSR_DEBUG_MESSENGER_MESSAGE_TYPE_VALIDATION_FLAG_BIT   = 0x00000002U,
    AMSR_DEBUG_MESSENGER_MESSAGE_TYPE_PERFORMANCE_FLAG_BIT  = 0x00000004U
} AMSR_DebugMessengerMessageTypeFlagBits;


typedef struct {
    AMSR_StructureType          structureType;
    void                const * pNext;
} AMSR_GenericInputStructure;


typedef struct {
    AMSR_StructureType          structureType;
    void                      * pNext;
} AMSR_GenericOutputStructure;


typedef struct {
    AMSR_StructureType      structureType;
    void            const * pNext;
} AMSR_InstanceCreateInfo;


typedef struct {
    AMSR_StructureType      structureType;
    void            const * pNext;
} AMSR_DebugMessengerCreateInfo;

#endif // __AMSR_PUBLIC_TYPES_H__
