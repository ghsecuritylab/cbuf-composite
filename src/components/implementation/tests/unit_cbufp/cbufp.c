#include <cos_component.h>
#include <print.h>
#include <cbuf.h>
#include <cbuf_mgr.h>
#include <unit_cbufp.h>

void unit_cbufp2buf(cbuf_t cbuf, int sz)
{
	char *c = cbuf2buf(cbuf, sz);
	assert(!c);
}

cbuf_t unit_cbufp_alloc(int sz)
{
	cbuf_t cbuf;
	char *addr;
	addr = cbuf_alloc(sz, &cbuf);
	assert(addr);
	assert(cbuf);
	addr[0] = '_';
	cbuf_send(cbuf);
	return cbuf;
}

void unit_cbufp_deref(cbuf_t cbuf, int sz)
{
	cbuf_free(cbuf);
}

int unit_cbufp_map_at(cbuf_t cbuf, int sz, spdid_t spdid, vaddr_t buf)
{
	vaddr_t d = cbuf_map_at(cos_spd_id(), cbuf, spdid, buf | MAPPING_RW);
	if ( d != buf ) return -EINVAL;
	return 0;
}

int unit_cbufp_unmap_at(cbuf_t cbuf, int sz, spdid_t spdid, vaddr_t buf)
{
	cbuf_unmap_at(cos_spd_id(), cbuf, spdid, buf);
	return 0;
}

void cos_init(void)
{
	return;
}

int unit_cbuf_debug_info()
{
	cbuf_debug_cbuf_info(cos_spd_id(), 0, 1);
	cbuf_mempool_resize(cos_spd_id(), 0);
	cbuf_debug_cbuf_info(cos_spd_id(), 0, 1);
	printc("on freelist %d\n", cbuf_debug_freelist_num(PAGE_SIZE));
}
