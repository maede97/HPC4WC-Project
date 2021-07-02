#pragma once

/**
 * @brief General note on the configuration
 * 
 * @todo Write this note.
 * 
 */

#define USE_OPENMP_ON_K

#define BLOCK_SIZE_I 15
#define BLOCK_SIZE_J 10

#define BLOCK_I
#define BLOCK_J

// No follow helpers for the diffusion.cpp
#if !defined(BLOCK_I) && !defined(BLOCK_J)
#define BLOCK_NONE
#endif
#if defined(BLOCK_I) && defined(BLOCK_J)
#define BLOCK_I_AND_J
// undefine block_i and block_j to make cpp file easier (no if/else required)
#undef BLOCK_I
#undef BLOCK_J
#endif
// End helpers for diffusion.cpp
