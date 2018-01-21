AM_CPPFLAGS="-I$(top_srcdir)/common"

LDADD = -L$(top_builddir)/src/common -lcommon

bin_PROGRAMS = \
	cbuf-test \
	list-test-0 \
	list-test-1 \
	list-test-2 \
	list-test-3 \
	list-test-4 \
	list-test-5 \
	list-test-6 \
	list-test-7 \
	list-test-queue \
	list-test-stack \
	log-test \
	xhash-test-0 \
	xmalloc-test \
	xstring-test \
	xtree-test-0 \
	xtree-test-1 

cbuf_test_SOURCES = cbuf_test.c		
cbuf_test_LDADD = $(top_builddir)/src/common/libcommon.la

list_test_0_SOURCES = list_test_0_basic_iterator.c
list_test_1_SOURCES = list_test_1_list_append_list.c
list_test_2_SOURCES = list_test_2_list_delete_all.c
list_test_3_SOURCES = list_test_3_list_transfer.c
list_test_4_SOURCES = list_test_4_append_prepend.c
list_test_5_SOURCES = list_test_5_list_find_first.c
list_test_6_SOURCES = list_test_6_list_for_each.c
list_test_7_SOURCES = list_test_7_list_sort_flush.c
list_test_queue_SOURCES = list_test_queue.c
list_test_stack_SOURCES = list_test_stack.c
log_test_SOURCES = log_test.c
xhash_test_0_SOURCES = xhash_test_0.c
xmalloc_test_SOURCES = xmalloc_test.c
xstring_test_SOURCES = xstring_test.c
xtree_test_0_SOURCES = xtree_test_0_init_free.c
xtree_test_1_SOURCES = xtree_test_1_addchild_find_parent_delete.c