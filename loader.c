#include <stdio.h>
#include <linux/bpf.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <assert.h>
#include <unistd.h>
//#include "bpf_load.h"
#include "lsm_kern.h"

struct m_path {
	char name[16];
};

int main(int argc,char *argv)
{
	struct lsm_kern *skel = NULL;
	int err = 0;
	__u64 val = 0;
	__u32 key = 0;
	int array_fd = 0;

	skel = lsm_kern__open_and_load();
	if(!skel){
		printf("load error!\n");
	}
	err = lsm_kern__attach(skel);
	if(err)
		printf("attach error!\n");
#if 1
	array_fd = bpf_object__find_map_fd_by_name(skel->obj,"array");
	if(array_fd < 0){
		printf("%s:%d find map error!\n",__func__,__LINE__);
		return 1;
	}
	while(1){
		sleep(2);
		bpf_map_lookup_elem(array_fd,&key,&val);
	
		printf("rm count:%d\n",val);

//		val +=1;
//		bpf_map_update_elem(array_fd,&key,&val,0);
//		val = 0;
	}
#endif
	return 0;
}

