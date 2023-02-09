#ifndef SSB_C_MACROS_H
#define SSB_C_MACROS_H

/// Floating Point Constants
#define FLOAT_MAX     3.4028235e38
#define FLOAT_NEG_MAX -FLOAT_MAX

/// Get the number of elements in a static array
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

/// Align value to size
#define ALIGN(x, align) (((x) + ((align)-1)) & ~((align)-1))

/// Math Functions
#define SQUARE(x) ((x) * (x))
#define CUBE(x)   ((x) * (x) * (x))

#define ABS(x)  ((x) < 0 ? -(x) : (x))
#define ABSF(x) ((x) < 0.0F ? -(x) : (x))

// Helpful to have some defines that are explicitly float-sized
#define M_PI_F      ((f32)M_PI)
#define M_DTOR_F(x) ((x) * (f32)M_DTOR)

/// Avoid compiler warnings for unused variables
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

/// Apply compiler printf format checking to function
#ifdef __GNUC__
#define PRINTF_CHECK(fmtpos, vargpos) __attribute__ ((__format__ (__printf__, (fmtpos), (vargpos))))
#else
#define PRINTF_CHECK(fmtpos, vargpos)
#endif

#define GLUE(a, b) a ## b
#define GLUE2(a, b) GLUE(a, b)

/// Static assertions
#ifdef __GNUC__
#define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else
#define STATIC_ASSERT(cond, msg) typedef char GLUE2(static_assertion_failed, __LINE__)[(cond) ? 1 : -1]
#endif

/// Convert from a physical addresss to a ROM (0xB0) address
#define PHYSICAL_TO_ROM(x) ((uintptr_t)(x) + 0xB0000000)

/// Turn off syntax check diagnostic
#ifdef __GNUC__
#define DO_PRAGMA(x) _Pragma (#x)
#define DIAGNOSTIC_SAVE() _Pragma("GCC diagnostic push")
#define DIAGNOSTIC_IGNORE(d) DO_PRAGMA(GCC diagnostic ignored d)
#define DIAGNOSTIC_RESTORE() _Pragma("GCC diagnostic pop")

#else
#define DIAGNOSTIC_SAVE()
#define DIAGNOSTIC_IGNORE(d)
#define DIAGNOSTIC_RESTORE()

#endif
#endif /* SSB_C_MACROS_H */
