/* ==================== *
 * <buffers.c>
 * Bailey Jia-Tao Brown
 * 2022
 *
 * Source file for buffer data and functions
 * Contents:
 *	- Includes
 *	- Internal data
 *	- Internal error handling functions
 *	- Internal allocation functions
 *	- Internal init and terminate functions
 *	- Internal buffer related functions
 *	- Buffer related functions
 * ==================== */






/* ========== INCLUDES ========== */




#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>   /* Basic I/O         */
#include <stdlib.h>  /* Memory Management */
#include <Windows.h> /* WIN32 Calls       */

#include "internals.h" /* Source Header */







/* ========== INTERNAL DATA ========== */





static HANDLE vHeap;

static viBufferBehavior* vBufferBehaviors; /* buffer behavior array */
static uint16_t vBufferBehaviorCount;      /* behavior counter      */

static viBuffer** vBuffers;     /* pointer to buffer objects */
static uint16_t   vBufferCount; /* buffer object counter     */
static uint8_t*   vBufferField; /* buffer use field          */






/* ========== INTERNAL ERROR FUNCTIONS ========== */





static void vShowError(const char* action, const char* reason)
{
	char strBuff[0xFF] = { 0 };
	sprintf(strBuff, "ERROR AT: %s\nREASON: %s",
		action, reason);
	MessageBoxA(NULL, strBuff, "VINTERNAL ERROR",
		MB_OK);
	ExitProcess(0);
}





/* ========== INTERNAL ALLOCATION FUNCTIONS ========== */




static void* vAlloc(size_t numBytes)
{
	return HeapAlloc(vHeap, FALSE, numBytes);
}

static void* vAllocZ(size_t numBytes)
{
	return HeapAlloc(vHeap, HEAP_ZERO_MEMORY, numBytes);
}

static void vFree(void* block)
{
	HeapFree(vHeap, FALSE, block);
}

static viBuffer* vGetNextBuffer(viHandle* handle)
{
	/* get start index */
	int startIndex = max(0, vBufferCount >> 1);

	/* search free buffer spot */
	for (int i = 0; i < VI_BUFFERS_MAX; i++)
	{
		/* check index and continue if used */
		int indexActual = (startIndex + i) % VI_BUFFERS_MAX;
		if (vBufferField[indexActual] == VI_TAKEN) continue;

		/* on empty, return buffer object */
		*handle = indexActual;
		return vBuffers + indexActual;
	}

	*handle = ~(0);
	return NULL;
}




/* ========== INTERNAL BUFFER FUNCTIONS ========== */
static void vBufferAddNode(viBuffer* target)
{
	/* get behavior */
	viBufferBehavior* bhv = vBufferBehaviors + target->behavior;


}





/* ========== INTERNAL INIT AND TERMINATE FUNCTIONS ========== */




VIAPI void __viBufferInit(void)
{
	/* get system info on page size */
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int pageSize = sysInfo.dwPageSize;

	/* get the amount of bytes for 2 pages */
	int pageSizeRequest = pageSize * VI_HEAP_PAGEALLOC;

	/* create heap */
	vHeap = HeapCreate(0, pageSizeRequest, 0);

	/* clear internal counters */
	vBufferCount = 0;
	vBufferBehaviorCount = 0;

	/* allocate internal data */
	vBufferBehaviors = vAllocZ(sizeof(viBufferBehavior) *
		VI_BUFFERBEHAVIORS_MAX);
	vBuffers     = vAllocZ(sizeof(viBuffer*) * VI_BUFFERS_MAX);
	vBufferField = vAllocZ(sizeof(uint8_t) * VI_BUFFERS_MAX);
}

VIAPI void __viBufferTerminate(void)
{
	HeapDestroy(vHeap);
}





/* ========== BUFFER FUNCTIONS ========== */




VIAPI viHandle viCreateBufferBehavior(char* name, size_t elementSize,
	uint32_t inital, uint32_t step)
{
	/* get handle and object */
	int index = vBufferCount;
	viBufferBehavior* toEdit = vBufferBehaviors + index;
	
	/* copy name */
	strcpy(toEdit->bufferName, name);

	/* set params */
	toEdit->elementSize = elementSize;
	toEdit->sizeInitial = inital;
	toEdit->sizeStep    = step;

	return index;
}

VIAPI viHandle viCreateBufferBehaviorC(viBufferBehavior* reference)
{
	/* get handle and object */
	int index = vBufferCount;
	viBufferBehavior* toEdit = vBufferBehaviors + index;

	/* copy and return handle */
	memcpy(toEdit, reference, sizeof(viBufferBehavior));
	return index;
}

VIAPI viHandle viCreateBuffer(viHandle behavior)
{
	/* get free buffer spot */
	viHandle  bufferHandle;
	viBuffer* buffer = vGetNextBuffer(&bufferHandle);

	/* error handling */
	if (buffer == NULL || bufferHandle == ~(0))
		vShowError("Buffer Creation", "No Buffers Left");

	/* alloc and set parameters */
	buffer = vAllocZ(sizeof(viBuffer));
	buffer->behavior = behavior;
}

VIAPI void* viGetBufferIndex(viHandle buffer, uint64_t index);
VIAPI void viBufferAdd(viHandle buffer, void* data);
VIAPI void viBufferRemove(viHandle buffer, uint64_t index);