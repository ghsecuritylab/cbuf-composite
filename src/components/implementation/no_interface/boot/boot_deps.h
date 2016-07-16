#include <print.h>
#undef assert
#define assert(node) do { if (unlikely(!(node))) { debug_print("assert error in @ "); *((int *)0) = 0;} } while(0)

#include <mem_mgr.h>
#include <sched.h>
#include <cos_alloc.h>
#include <cobj_format.h>

/* 
 * Abstraction layer around 1) synchronization, 2) scheduling and
 * thread creation, and 3) memory operations.  
 */

/* synchronization... */
#define LOCK()   if (sched_component_take(cos_spd_id())) BUG();
#define UNLOCK() if (sched_component_release(cos_spd_id())) BUG();

/* scheduling/thread operations... */
#define __sched_create_thread_default sched_create_thread_default

/* memory operations... */
#define __local_mman_get_page   mman_get_page
#define __local_mman_alias_page mman_alias_page

#include <cinfo.h>
#include <cos_vect.h>

COS_VECT_CREATE_STATIC(spd_info_addresses);

int
cinfo_add_heap_pointer(spdid_t spdid, spdid_t target, void *heap_pointer)
{
	cos_vect_del(&spd_info_addresses, target);
	return cos_vect_add_id(&spd_info_addresses, heap_pointer, target);
}

void*
cinfo_get_heap_pointer(spdid_t spdid, spdid_t target)
{
	return cos_vect_lookup(&spd_info_addresses, target);
}

static void
boot_deps_init(void)
{
	cos_vect_init_static(&spd_info_addresses);
}

static void
boot_deps_save_hp(spdid_t spdid, void *hp)
{
	cinfo_add_heap_pointer(cos_spd_id(), spdid, hp);
}

static void
boot_deps_run(void) { return; }

