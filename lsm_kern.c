// SPDX-License-Identifier: GPL-2.0

/*
 * Copyright 2020 Google LLC.
 */

#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include  <errno.h>
struct {
	__uint(type,BPF_MAP_TYPE_ARRAY);
	__uint(max_entries,1);
	__type(key,__u32);
	__type(value,__u64);
} array SEC(".maps");

char _license[] SEC("license") = "GPL";
__u64 rm_count = 0;
SEC("lsm/inode_mkdir")
int BPF_PROG(my_inode_unlink, struct inode *dir,struct dentry *dentry)
{
	__u64 *value;
	__u32 key = 0;
	int ret = 0;
	int i = 0;
	rm_count++;
	value = bpf_map_lookup_elem(&array,&key);
	if(value){
		*value =rm_count;
		ret = bpf_map_update_elem(&array,&key,value,BPF_ANY);
	} else {
		ret = bpf_map_update_elem(&array,&key,&rm_count,BPF_ANY);
	}
	return 0;
}

