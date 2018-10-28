/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2014 Intel Corporation
 */

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
#if __GLIBC_PREREQ(2, 16)
#include <sys/auxv.h>
#define HAS_AUXV 1
#endif
#endif

#include <rte_common.h>
#include <rte_cpuflags.h>

/**
 * Checks if the machine is adequate for running the binary. If it is not, the
 * program exits with status 1.
 */
void
rte_cpu_check_supported(void)
{
	if (!rte_cpu_is_supported())
		exit(1);
}

int
rte_cpu_is_supported(void)
{
	/* This is generated at compile-time by the build system */
	static const enum rte_cpu_flag_t compile_time_flags[] = {
			RTE_COMPILE_TIME_CPUFLAGS
	};
	unsigned count = RTE_DIM(compile_time_flags), i;
	int ret;

	for (i = 0; i < count; i++) {
		ret = rte_cpu_get_flag_enabled(compile_time_flags[i]);

		if (ret < 0) {
			fprintf(stderr,
				"ERROR: CPU feature flag lookup failed with error %d\n",
				ret);
			return 0;
		}
		if (!ret) {
			fprintf(stderr,
			        "ERROR: This system does not support \"%s\".\n"
			        "Please check that RTE_MACHINE is set correctly.\n",
			        rte_cpu_get_flag_name(compile_time_flags[i]));
			return 0;
		}
	}

	return 1;
}

#ifndef HAS_AUXV
static unsigned long
getauxval(unsigned long type)
{
  errno = ENOTSUP;
  return 0;
}
#endif

#if RTE_ARCH_64
typedef Elf64_auxv_t Internal_Elfx_auxv_t;
#else
typedef Elf32_auxv_t Internal_Elfx_auxv_t;
#endif


/**
 * Provides a method for retrieving values from the auxiliary vector and
 * possibly running a string comparison.
 */
static unsigned long
_rte_cpu_getauxval(unsigned long type, int cmp_str, const char *str)
{
  unsigned long val;

  errno = 0;
  val = getauxval(type);

  if (!val && (errno == ENOTSUP || errno == ENOENT)) {
    Internal_Elfx_auxv_t auxv;
    int auxv_fd = open("/proc/self/auxv", O_RDONLY);

    errno = ENOENT;
    if (auxv_fd == -1)
      return 0;

    while (read(auxv_fd, &auxv, sizeof(auxv)) == sizeof(auxv)) {
      if (auxv.a_type == type) {
        errno = 0;
        val = auxv.a_un.a_val;
        if (cmp_str)
          val = strcmp((const char *)val, str);
        break;
      }
    }
    close(auxv_fd);
  }

  return val;
}

unsigned long
rte_cpu_getauxval(unsigned long type)
{
  return _rte_cpu_getauxval(type, 0, NULL);
}

int
rte_cpu_strcmp_auxval(unsigned long type, const char *str)
{
  return _rte_cpu_getauxval(type, 1, str);
}

