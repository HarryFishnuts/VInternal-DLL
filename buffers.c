/* ==================== *
 * <buffers.c>
 * Bailey Jia-Tao Brown
 * 2022
 *
 * Source file for buffer data and functions
 * Contents:
 *	- Includes
 *	- Internal data
 *	- Internal allocation functions
 *	- Internal init and terminate functions
 *	- Buffer related functions
 * ==================== */

/* INCLUDES */
#include <stdio.h>   /* Basic I/O         */
#include <stdlib.h>  /* Memory Management */
#include <Windows.h> /* WIN32 Calls       */

#include "internals.h" /* Source Header */


/* INTERNAL DATA */
static HANDLE viHeap;

static viBufferBehavior* viBufferBehaviors; /* buffer behavior array */
static uint16_t viBufferBehaviorCount;      /* behavior counter      */

static viBuffer** viBuffers;     /* pointer to buffer objects */
static uint16_t   viBufferCount; /* buffer object counter     */
static uint8_t*   viBufferField; /* buffer use field          */

/* INTERNAL ALLOCATION FUNCTIONS */
static void* viAlloc(size_t numBytes)
{
	return HeapAlloc(viHeap, FALSE, numBytes);
}

static void* viAllocZ(size_t numBytes)
{
	return HeapAlloc(viHeap, HEAP_ZERO_MEMORY, numBytes);
}

static void viFree(void* block)
{
	HeapFree(viHeap, FALSE, block);
}

/* INTERNAL INIT AND TERMINATE FUNCTIONS */
VIAPI void __viBufferInit(void)
{
	/* get system info on page size */
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int pageSize = sysInfo.dwPageSize;

	/* get the amount of bytes for 2 pages */
	int pageSizeRequest = pageSize * VI_HEAP_PAGEALLOC;

	/* create heap */
	viHeap = HeapCreate(0, pageSizeRequest, 0);

	/* clear internal counters */
	viBufferCount = 0;
	viBufferBehaviorCount = 0;

	/* allocate internal data */
	viBufferBehaviors = viAlloc(sizeof(viBufferBehavior) *
		VI_BUFFERBEHAVIORS_MAX);
	viBuffers = viAlloc(sizeof(viBuffer*) * VI_BUFFERS_MAX);
	viBufferField = viAlloc(sizeof(uint8_t) * VI_BUFFERS_MAX);

}

VIAPI void __viBufferTerminate(void);

/* BUFFER FUNCTIONS */
VIAPI viHandle viCreateBufferBehavior(char* name, uint32_t default,
	uint32_t step);
VIAPI viHandle viCreateBufferBehaviorC(viBufferBehavior reference);
VIAPI viHandle viCreateBuffer(viHandle behavior);
VIAPI void* viGetBufferIndex(viHandle buffer, uint64_t index);
VIAPI void viBufferAdd(viHandle buffer, void* data);
VIAPI void viBufferRemove(viHandle buffer, uint64_t index);