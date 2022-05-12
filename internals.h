/******************************************************************************
* <internals.h>
* Bailey Jia-Tao Brown
* 2022
* 
*	Header file for lightweight utilities library
*	Contents:
*		- Header guard
*		- API Definition
*		- Includes
*		- Definitions
*		- Typedefs
*		- Struct definitions
*		- Module init and terminate functions
*		- Buffer functions
* 
******************************************************************************/

/* HEADER GUARD */
#ifndef __VINTERNALS_INCLUDE__
#define __VINTERNALS_INCLUDE__ 

/* API DEFINITION */
#ifdef  VINTERNAL_EXPORTS
#define VIAPI __declspec(dllexport)
#else
#define VIAPI __declspec(dllimport)
#endif

/* INCLUDES */
#include <stdint.h>

/* DEFINITIONS */
#define VI_BUFFERNAME_MAXLENGTH      0x100
#define VI_BUFFERINITAL_DEFAULT      0x800
#define VI_BUFFERSTEP_DEFAULT        0x800
#define VI_BUFFERCHANGETHRES_DEFAULT 0x20
#define VI_BUFFERMAXNODES_DEFAULT    0x40
#define VI_BUFFERS_MAX               0x200

/* TYPEDEFS */
typedef uint16_t viHandle;
typedef uint8_t  viField;

/* STRUCT DEFINITIONS */

typedef struct viBufferBehavior
{
	char bufferName[VI_BUFFERNAME_MAXLENGTH]; /* name */

	uint32_t sizeInitial;          /* initial buffer size */
	uint32_t sizeStep;             /* size step           */
	uint16_t sizeChangeThreshold;  /* when to change size */

	uint16_t nodesMax; /* maximum node count */
	
	size_t elementSize;    /* size of each element            */
	void*  elementDefault; /* ptr to default value of element */
} viBufferBehavior;

typedef struct viBufferNode
{
	struct viBuffer* root; /* root buffer object */

	struct viBufferNode* next; /* next buffer node     */
	struct viBufferNode* prev; /* previous buffer node */

	uint8_t  order;      /* buffer order */
	uint32_t indexStart; /* start index  */
	uint32_t indexEnd;   /* end index    */

	uint32_t bytesAllocated; /* bytes allocated */
	uint32_t bytesUsed;      /* bytes used */

	uint32_t fieldAllocated; /* field elements */
	uint32_t fieldUsed;      /* field used     */

	void*    block; /* memory block    */
	viField* field; /* block use field */

} viBufferNode;

typedef struct viBuffer
{
	viHandle behavior; /* buffer behavior */

	viBufferNode* head; /* head node */
	viBufferNode* tail; /* tail node */

	uint16_t numNodes;    /* amount of nodes           */
	uint64_t numElements; /* amount of elements        */
	uint64_t numByte;     /* amount of bytes allocated */
} viBuffer;

/* INIT AND TERMINATE FUNCTIONS */
VIAPI void viInit(void);
VIAPI void viTerminate(void);
VIAPI void __viBufferInit(void);
VIAPI void __viBufferTerminate(void);

/* BUFFER FUNCTIONS */
VIAPI viHandle viCreateBufferBehavior(char* name, uint32_t default,
	uint32_t step);
VIAPI viHandle viCreateBufferBehaviorC(viBufferBehavior reference);
VIAPI viHandle viCreateBuffer(viHandle behavior);
VIAPI void* viGetBufferIndex(viHandle buffer, uint64_t index);
VIAPI void viBufferAdd(viHandle buffer, void* data);
VIAPI void viBufferRemove(viHandle buffer, uint64_t index);

#endif /* header guard end */
